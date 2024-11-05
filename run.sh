#!/bin/bash

# Определение цветов
GREEN="\e[32m"
RED="\e[31m"
NC="\e[0m" # Нет цвета

# Функция для вывода успешного сообщения
function success {
    echo -e "${GREEN}$1${NC}"
}

# Функция для вывода сообщения об ошибке
function error {
    echo -e "${RED}$1${NC}"
    exit 1
}

# Сборка проекта
echo "Сборка проекта..."
make || error "Ошибка при сборке проекта."

success "Проект успешно собран."

# Подъем Docker
echo "Поднимаем Docker контейнеры..."
docker compose up -d || error "Ошибка при поднятии Docker контейнеров."

success "Docker контейнеры успешно подняты."
success "Ждём..."
sleep 4
# Запуск программы
echo "Запускаем программу..."
./bin/autodealership || error "Ошибка при запуске программы."

success "Программа успешно запущена."
