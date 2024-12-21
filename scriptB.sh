#!/bin/bash

send_request() {
    while true; do
        curl -s "http://10.0.2.15/compute" > /dev/null
        echo "Запит надіслано"
         
    done
}

for i in {1..5}; do
    send_request &  
done

wait

