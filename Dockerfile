FROM --platform=linux/amd64 alpine:3.20.1

WORKDIR /app

RUN apk add --no-cache gcc libc-dev bash python3 py3-pip curl

RUN curl -sSL https://install.python-poetry.org | python3 -

COPY build.sh /app/build.sh

COPY . .

ENV PATH="/root/.local/bin/poetry"

RUN poetry config virtualenvs.create false \
 && poetry install --no-interaction --no-ansi

RUN poetry config virtualenvs.create false \
 && poetry install --no-interaction --no-ansi

#RUN apk add --no-cache gcc libc-dev bash

#RUN ls -l /app && chmod +x /app/build.sh && /app/build.sh

ENV LD_LIBRARY_PATH=/app

CMD ["/app/test_libcsv"]
