// SparePart.cpp
#include "SparePart.h"

#include <iostream>

SparePart::SparePart() : id(0), price(0.0), stockQuantity(0) {}

SparePart::SparePart(int id, const std::string& name, const std::string& make, const std::string& model,
                     double price, int stockQuantity)
    : id(id), name(name), make(make), model(model), price(price), stockQuantity(stockQuantity) {}

void SparePart::print() const {
    std::cout << "ID: " << id << ", Наименование: " << name << ", Марка: " << make << ", Модель: " << model
              << ", Цена: " << price << ", Количество на складе: " << stockQuantity << std::endl;
}