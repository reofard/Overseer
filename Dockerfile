# 배포용 이미지

# 기본 Ubuntu 24.04 LTS 이미지
FROM ubuntu:24.04

# 필수 패키지들 설치
RUN apt-get update && apt-get install -y \
    build-essential \
    ninja-build \
    cmake \
    curl \
    git \
    && apt-get clean

# 작업 디렉토리 설정
WORKDIR /overseer

# 로컬 소스 코드와 CMakeLists.txt를 Docker 컨테이너로 복사
COPY . /overseer

# CMake를 사용하여 빌드 폴더 생성 및 빌드 설정
RUN cmake -B /build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release

# Make를 사용하여 실행 파일을 빌드
RUN make -C /build overseer

# 실행파일에 실행 권한 부여
RUN chmod +x /build/overseer

# 컨테이너 시작 시 실행될 명령어 설정
CMD ["/build/overseer"]




