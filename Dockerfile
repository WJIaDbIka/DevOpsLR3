FROM alpine AS build
RUN apk add --no-cache git build-base cmake automake autoconf coreutils
WORKDIR home/optima
COPY . /home/optima
RUN ./configure && make

FROM alpine
RUN apk add --no-cache libstdc++
COPY --from=build /home/optima/funcA /usr/local/bin/funcA
ENTRYPOINT ["/usr/local/bin/funcA"]

