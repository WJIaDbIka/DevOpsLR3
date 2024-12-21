#!/bin/bash

# Функція для отримання поточного завантаження CPU контейнера
check_container_cpu() {
    docker stats --no-stream --format "{{.CPUPerc}}" "$1" | cut -d'%' -f1
}

# Функція для запуску контейнера із заданими параметрами
start_container() {
    local container_name=$1
    local cpu_core=$2

    if docker ps --filter "name=$container_name" --format '{{.Names}}' | grep -q "^$container_name$"; then
        echo "Контейнер $container_name вже запущений. Використовуємо існуючий контейнер."
    else
        echo "Запуск контейнера $container_name на ядрі CPU $cpu_core..."
        docker run -d --name "$container_name" --cpuset-cpus="$cpu_core" --network camry-network dmytro392/optimaserver
    fi
}

# Функція для моніторингу стану контейнерів
monitor_system() {
    local srv2_last_used=$(date +%s)
    local srv3_last_used=$(date +%s)
    local srv2_start_time=0
    local srv3_start_time=0

    while true; do
        local current_time=$(date +%s)

        for container in srv1 srv2 srv3; do
            if docker ps --filter "name=$container" --format '{{.Names}}' | grep -q "^$container$"; then
                local cpu_load=$(check_container_cpu "$container")

                # Умова запуску додаткових контейнерів
                if (( $(echo "$cpu_load > 80" | bc -l) )); then
                    echo "Контейнер $container перевантажений..."
                    if [ "$container" == "srv1" ] && ! docker ps --filter "name=srv2" --format '{{.Names}}' | grep -q "^srv2$"; then
                        echo "Запуск srv2 через перевантаження srv1..."
                        start_container srv2 1
                        srv2_start_time=$current_time
                    elif [ "$container" == "srv2" ] && ! docker ps --filter "name=srv3" --format '{{.Names}}' | grep -q "^srv3$"; then
                        echo "Запуск srv3 через перевантаження srv2..."
                        start_container srv3 2
                        srv3_start_time=$current_time
                    fi
                fi

                # Оновлення часу активності
                if (( $(echo "$cpu_load > 20" | bc -l) )); then
                    if [ "$container" == "srv2" ]; then
                        srv2_last_used=$current_time
                    elif [ "$container" == "srv3" ]; then
                        srv3_last_used=$current_time
                    fi
                fi

                # Умова зупинки контейнерів
                if [ "$container" != "srv1" ]; then
                    local last_used_time_var="${container}_last_used"
                    local last_used_time=${!last_used_time_var}
                    local start_time_var="${container}_start_time"
                    local start_time=${!start_time_var}

                    if (( current_time - start_time > 20 )) && (( current_time - last_used_time > 20 )) && (( $(echo "$cpu_load < 20" | bc -l) )); then
                        echo "Контейнер $container неактивний або має низьке навантаження. Зупинка..."
                        docker stop --time 10 "$container"
                        docker rm "$container"
                    fi
                fi
            fi
        done

        sleep 5
    done
}

# Запуск основного контейнера та моніторинг
start_container srv1 0
monitor_system

