# Overseer

모바일 로봇, 주변 설비(엘리베이터, 스피드 게이트 등) 연동 및 제어 서버

### 세부 기능 

- **로봇 상태 모니터링:** 로봇의 현재 위치, 배터리 상태, 속도, 작업 진행 상황 모니터링
- **작업 스케줄 관리 및 할당:** 복수의 로봇에게 적합한 작업을 할당하고 일정을 조정하여 전체 작업 최적화 및 제어
- **경로 계획 및 네비게이션:** 복수의 로봇이 교착, 병목없이 최적의 경로로 이동하도록 계획 및 제어
- **장비 연동 및 제어:** 모바일 로봇과 상호작용 가능한 장비(엘리베이터, 충전스테이션 등)의 작업을 지시하고 제어하는 기능
- **통신 및 데이터 전송:** 로봇과 관제 시스템 간에 명령어와 데이터를 주고받기 위한 통신 기능을 제공
- **안전 관리:** 비상 상황이 발생하면 원격 제어 기능을 통해 로봇을 멈추거나 수동조작
- **데이터 분석 및 성능 최적화:** 로봇의 동작 및 작업 수행 데이터를 분석하여 효율성, 과거 작업에 대한 리포트 제공

<br>
<br>

# Project Structure

![Project Structure](/asset/readme/program_structure.png)

<br>

# Prerequisites

- [VSCode](https://code.visualstudio.com/)
    - [DevContainers Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)
- [Docker](https://www.docker.com/)
- [Windows Terminal](https://apps.microsoft.com/detail/9n0dx20hk701?rtc=1&hl=ko-kr&gl=KR)
- [Linux Terminator](https://gnome-terminator.org/)

<br>

# Build Overseer to Dev Environment

1. Clone the repository:

```bash
git clone git@github.com:LKRBT/Overseer.git
```

2. install Dev Containers Extension:

```bash
cd Overseer
code .
```

3. press ```ctrl``` + ```shift``` + ```P``` and choose ```Dev Containers: Rebuild and Reopen in Container```:

![start dev container](/asset/readme/setting_first.png)

4. press ```f5``` to build and debug

<br>

# Build Overseer to Deployment docker image

1. enter repository

```bash
cd Overseer
```

2. build deployment image

```bash
docker build -t overseer .
```
