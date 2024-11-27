# Ubuntu 24.04 LTS 기반
FROM ubuntu:24.04

# 필수 패키지들 설치
RUN apt-get update && apt-get install -y \
    build-essential \
    ninja-build \
    cmake \
    bash \
    git \
    gdb \
    curl \
    && apt-get clean

# CMake 버전 설치 (옵션)
ARG REINSTALL_CMAKE_VERSION_FROM_SOURCE="none"
COPY ./reinstall-cmake.sh /tmp/
RUN if [ "${REINSTALL_CMAKE_VERSION_FROM_SOURCE}" != "none" ]; then \
        chmod +x /tmp/reinstall-cmake.sh && /tmp/reinstall-cmake.sh ${REINSTALL_CMAKE_VERSION_FROM_SOURCE}; \
    fi \
    && rm -f /tmp/reinstall-cmake.sh
