#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "Car.h"

std::vector<Car> loadCSV(const std::string& file) {
    std::vector<Car> cars;
    std::ifstream fobject(file);

    if (!fobject.is_open()) {
        std::cout << "Couldn't open file" << "\n";
        return cars;
    }

    std::string aline;

    std::getline(fobject, aline);

    while (std::getline(fobject, aline)) {
        std::stringstream flow(aline);
        std::string data;

        Car currcar;

        std::getline(flow, data, ',');
        currcar.id = std::stoi(data);

        std::getline(flow, data, ',');
        currcar.brand = data;

        std::getline(flow, data, ',');
        currcar.model = data;

        std::getline(flow, data, ',');
        currcar.year = std::stoi(data);

        std::getline(flow, data, ',');
        currcar.color = data;

        std::getline(flow, data, ',');
        currcar.mileage = std::stoi(data);

        std::getline(flow, data, ',');
        currcar.price = std::stoi(data);

        std::getline(flow, data, ',');
        currcar.condition = data;

        cars.push_back(currcar);
    }
    fobject.close();
    return cars;
}

// Created by danpe on 3/22/2026.
//
