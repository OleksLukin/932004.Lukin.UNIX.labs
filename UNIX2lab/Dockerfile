FROM ubuntu:latest

RUN apt-get update && apt-get -y upgrade && apt-get install -y coreutils

WORKDIR /app

COPY script.sh /app/script.sh
RUN chmod +x /app/script.sh

CMD ["./script.sh"]
