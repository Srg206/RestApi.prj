.PHONY: up
up:
    docker compose -f docker-compose-dev.yaml up -d

.PHONY: down
down:
    docker compose -f docker-compose-dev.yaml down