// Car.h
#pragma once
#include <string>

class Car {
   public:
    int id;
    std::string make;
    std::string model;
    std::string color;
    std::string engineNumber;
    std::string registrationNumber;
    std::string bodyNumber;
    std::string chassisNumber;
    std::string manufactureDate;  // Формат: "YYYY-MM-DD"
    int mileage;
    double manufacturePrice;
    double salePrice;
    double purchasePrice;
    std::string technicalCertificateNumber;
    std::string technicalCertificateDate;  // Формат: "YYYY-MM-DD"
    int expertId;

    Car();
    Car(int id, const std::string& make, const std::string& model, const std::string& color,
        const std::string& engineNumber, const std::string& registrationNumber, const std::string& bodyNumber,
        const std::string& chassisNumber, const std::string& manufactureDate, int mileage,
        double manufacturePrice, double salePrice, double purchasePrice,
        const std::string& technicalCertificateNumber, const std::string& technicalCertificateDate,
        int expertId);

    // Методы для отображения информации
    void print() const;
};