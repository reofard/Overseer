FROM ubuntu:latest
RUN apt-get update \
&& apt-get install -y g++ cmake \
&& apt-get clean

EXPOSE 8000
ENTRYPOINT ["/bin/bash"]