FROM gcc:11.3.0

RUN apt-get update && apt-get install -y \
    build-essential 

COPY src/write_shared.c /app/src/write_shared.c
COPY src/read_shared.c /app/src/read_shared.c
COPY scripts/run.sh /app/scripts/run.sh

WORKDIR /app

CMD ["scripts/run.sh"]
