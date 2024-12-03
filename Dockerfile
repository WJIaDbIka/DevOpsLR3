FROM alpine AS build
RUN apk add --no-cache git build-base cmake automake autoconf coreutils
WORKDIR home/optima
RUN git clone https://github.com/WJIaDbIka/DevOpsLR3.git .
RUN [ -f configure ] || autoreconf -i && chmod +x configure && ./configure && make

FROM alpine
RUN apk add --no-cache libstdc++
COPY --from=build /home/optima/funcA /usr/local/bin/funcA
ENTRYPOINT ["/usr/local/bin/funcA"]

