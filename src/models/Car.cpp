// Car.cpp
#include "Car.h"

#include <iomanip>  // Для std::fixed и std::setprecision
#include <iostream>
Car::Car() : id(0), mileage(0), manufacturePrice(0.0), salePrice(0.0), purchasePrice(0.0), expertId(0) {}

Car::Car(int id, const std::string& make, const std::string& model, const std::string& color,
         const std::string& engineNumber, const std::string& registrationNumber,
         const std::string& bodyNumber, const std::string& chassisNumber, const std::string& manufactureDate,
         int mileage, double manufacturePrice, double salePrice, double purchasePrice,
         const std::string& technicalCertificateNumber, const std::string& technicalCertificateDate,
         int expertId)
    : id(id),
      make(make),
      model(model),
      color(color),
      engineNumber(engineNumber),
      registrationNumber(registrationNumber),
      bodyNumber(bodyNumber),
      chassisNumber(chassisNumber),
      manufactureDate(manufactureDate),
      mileage(mileage),
      manufacturePrice(manufacturePrice),
      salePrice(salePrice),
      purchasePrice(purchasePrice),
      technicalCertificateNumber(technicalCertificateNumber),
      technicalCertificateDate(technicalCertificateDate),
      expertId(expertId) {}

void Car::print() const {
    std::cout << "ID: " << id << ", Марка: " << make << ", Модель: " << model << ", Цвет: " << color
              << ", Цена продажи: " << std::fixed << std::setprecision(2) << salePrice << std::endl;
}