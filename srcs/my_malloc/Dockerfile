FROM debian:latest

RUN apt-get update;
RUN apt-get update && apt-get install gcc -y \
    valgrind -y \
    gdb -y \
    gcc -y \
    curl -y \
    git -y \
    make -y \
    zsh -y;
RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" -y;

WORKDIR /malloc

# COPY MemoryManager.c .
# COPY MemoryManager.h .

ENTRYPOINT ["tail", "-f", "/dev/null"]
