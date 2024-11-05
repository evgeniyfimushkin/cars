// SparePart.h
#pragma once
#include <string>

class SparePart {
   public:
    int id;
    std::string name;
    std::string make;
    std::string model;
    double price;
    int stockQuantity;

    SparePart();
    SparePart(int id, const std::string& name, const std::string& make, const std::string& model,
              double price, int stockQuantity);

    // Методы для отображения информации
    void print() const;
};