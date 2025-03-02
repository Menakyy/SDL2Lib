FROM ubuntu:22.04

ENV TZ=Europe/Warsaw
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt update && apt install -y git cmake g++ valgrind clang clang-tidy clang-format libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-mixer-dev lcov

RUN mkdir /root/sdl
COPY . /root/sdl