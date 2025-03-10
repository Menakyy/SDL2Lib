FROM ubuntu:22.04

ENV TZ=Europe/Warsaw
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

RUN apt update && apt install -y \
    git cmake g++ valgrind clang clang-tidy clang-format \
    libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-mixer-dev \
    lcov xvfb

RUN mkdir /root/sdl
COPY . /root/sdl

WORKDIR /root/sdl

ENV DISPLAY=:99 \
    XDG_RUNTIME_DIR=/tmp/runtime-dir

RUN mkdir -p ${XDG_RUNTIME_DIR} && chown root:root ${XDG_RUNTIME_DIR}

CMD Xvfb :99 -screen 0 1024x768x16 & \
    sleep 2 && \
    bash
