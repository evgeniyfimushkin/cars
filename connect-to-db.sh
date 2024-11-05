CONTAINER_NAME=$(docker compose ps -q db)
docker exec -it "$CONTAINER_NAME" psql -U admin -d cars