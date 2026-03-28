#include "RedBlack.h"
#include "BTree.h"
#include "Car.h"
#include "CSVLoader.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <chrono>

double runRedBlackResults(const std::vector<Car>& cars, int numRandomSearches) {
    RedBlackTree tree;
    std::cout << "\n--- Red-Black Tree Results ---\n";


    auto start = std::chrono::high_resolution_clock::now();
    for (const Car& car : cars) {
        tree.insert(car.id, const_cast<Car*>(&car));
    }
    auto end = std::chrono::high_resolution_clock::now();
    double insertTime = std::chrono::duration<double, std::micro>(end - start).count();
    std::cout << "Insertion completed in " << insertTime << " microseconds\n";


    std::cout << "Sequential search for all cars...\n";
    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= cars.size(); i++) tree.search(i);
    end = std::chrono::high_resolution_clock::now();
    double seqTime = std::chrono::duration<double, std::micro>(end - start).count();
    double avg = seqTime / cars.size();
    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Total sequential search time: " << seqTime << " microseconds\n";
    std::cout << "Average search time per car: " << avg << " microseconds\n";


    std::cout << "Performing " << numRandomSearches << " random searches...\n";
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numRandomSearches; i++) {
        int id = rand() % cars.size() + 1;
        tree.search(id);
    }
    end = std::chrono::high_resolution_clock::now();
    double randTime = std::chrono::duration<double, std::micro>(end - start).count();
    std::cout << "Random searches completed in " << randTime << " microseconds\n";

    return insertTime + seqTime + randTime;
}

double runBTreeResults(const std::vector<Car>& cars, int numRndSearch) {
    BTree tree;
    std::cout << "\n--- B-Tree Results ---\n";


    auto start = std::chrono::high_resolution_clock::now();
    for (const Car& car : cars) {
        tree.insert(car.id, const_cast<Car*>(&car));
    }
    auto end = std::chrono::high_resolution_clock::now();
    double insertTime = std::chrono::duration<double, std::micro>(end - start).count();
    std::cout << "Insertion completed in " << insertTime << " microseconds\n";


    std::cout << "Sequential search for all cars...\n";
    start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= cars.size(); i++) tree.search(i);
    end = std::chrono::high_resolution_clock::now();
    double seqTime = std::chrono::duration<double, std::micro>(end - start).count();
    double avg = seqTime / cars.size();
    std::cout << std::fixed << std::setprecision(8);
    std::cout << "Total sequential search time: " << seqTime << " microseconds\n";
    std::cout << "Average search time per car: " << avg << " microseconds\n";


    std::cout << "Performing " << numRndSearch << " random searches...\n";
    start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < numRndSearch; i++) {
        int id = rand() % cars.size() + 1;
        tree.search(id);
    }
    end = std::chrono::high_resolution_clock::now();
    double randTime = std::chrono::duration<double, std::micro>(end - start).count();
    std::cout << "Random searches completed in " << randTime << " microseconds\n";

    return insertTime + seqTime + randTime;
}

int main() {
    srand(time(nullptr));


    std::vector<Car> cars = loadCSV("Car_DataRead.txt");
    if (cars.empty()) {
        std::cerr << "Failed to load CSV file or file empty\n";
        return 1;
    }
    std::cout << "Loaded " << cars.size() << " cars from CSV\n";

    int choice = 0;
    while (choice != 7) {
        std::cout << "\n--- Data Structure Menu ---\n";
        std::cout << "1. Run Red-Black Tree Benchmark\n";
        std::cout << "2. Run B-Tree Benchmark\n";
        std::cout << "3. Run Both Benchmarks\n";
        std::cout << "4. Search by Car ID\n";
        std::cout << "5. Show Random Car\n";
        std::cout << "6. Print Tree Info\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int numSearches;
                std::cout << "Number of random searches? ";
                std::cin >> numSearches;
                if (numSearches <= 0) {
                    numSearches = 10000000;
                }
                runRedBlackResults(cars, numSearches);
                break;
            }
            case 2: {
                int numSearches;
                std::cout << "Number of random searches? ";
                std::cin >> numSearches;
                if (numSearches <= 0) {
                    numSearches = 10000000;
                }
                runBTreeResults(cars, numSearches);
                break;
            }
            case 3: {
                int numSearches;
                std::cout << "Number of random searches? ";
                std::cin >> numSearches;
                if (numSearches <= 0) {
                    numSearches = 10000000;
                }
                double rbTime = runRedBlackResults(cars, numSearches);
                double bTime = runBTreeResults(cars, numSearches);
                std::cout << "\n--- Summary ---\n";
                std::cout << std::setw(15) << "Structure"
                          << std::setw(26) << "Total Time(microseconds)\n";
                std::cout << std::setw(15) << "Red-Black" << std::setw(15) << rbTime << "\n";
                std::cout << std::setw(15) << "B-Tree" << std::setw(15) << bTime << "\n";
                std::cout << '\n';
                if (rbTime > bTime) {
                    std::cout << std::setw(15) << "B-Tree was " << std::setw(15) << ((rbTime - bTime) / rbTime) * 100 << "% faster" << "\n";
                }
                if (rbTime < bTime) {
                    std::cout << std::setw(15) << "Red-Black Tree was " << std::setw(15) << ((bTime - rbTime) / bTime) * 100 << "% faster" << "\n";
                }
                break;
            }
            case 4: {
                int searchID;
                std::cout << "Enter Car ID to search: ";
                std::cin >> searchID;
                if (searchID <= 0){break;}

                RedBlackTree rbTree;
                BTree bTree;
                for (Car& car : cars) {
                    rbTree.insert(car.id, &car);
                    bTree.insert(car.id, &car);
                }


                auto start = std::chrono::high_resolution_clock::now();
                Car* rbFound = rbTree.search(searchID);
                auto end = std::chrono::high_resolution_clock::now();
                double rbTime = std::chrono::duration<double, std::micro>(end - start).count();


                start = std::chrono::high_resolution_clock::now();
                Car* bFound = bTree.search(searchID);
                end = std::chrono::high_resolution_clock::now();
                double bTime = std::chrono::duration<double, std::micro>(end - start).count();

                std::cout << std::fixed << std::setprecision(8);
                std::cout << "\n--- Search Results ---\n";

                if (rbFound != nullptr) {
                    std::cout << "[RB] Found in " << rbTime << " microseconds\n";
                    std::cout << "ID: " << rbFound->id << " Brand: " << rbFound->brand<< " Model: " << rbFound->model<< " Year: " << rbFound->year << " Color: " << rbFound->color;
                    std::cout << " Mileage: " << rbFound->mileage << " Price: $" << rbFound->price << " Condition: " << rbFound->condition << "\n";
                } else {
                    std::cout << "[RB] Car not found\n";
                }

                if (bFound != nullptr) {
                    std::cout << "[B-Tree] Found in " << bTime << " microseconds\n";
                    std::cout << "ID: " << bFound->id << " Brand: " << bFound->brand << " Model: " << bFound->model << " Year: " << bFound->year << " Color: " << bFound->color;
                    std::cout << " Mileage: " << bFound->mileage << " Price: $" << bFound->price << " Condition: " << bFound->condition << "\n";
                } else {
                    std::cout << "[B-Tree] Car not found\n";
                }

                break;
            }
            case 5: {
                int idx = rand() % cars.size();
                Car& randomsec = cars[idx];
                std::cout << "Random car: \n ID: " << randomsec.id << "\n" << " Brand: " << randomsec.brand << "\n" << " Model: " << randomsec.model << "\n" << " Year: " << randomsec.year << "\n" << " Color: " << randomsec.color << "\n";
                std::cout << " Mileage: " << randomsec.mileage << "\n" << " Price: $" << randomsec.price << "\n" << " Condition: " << randomsec.condition << "\n";
                break;
            }

            case 6: {
                std::cout << "\n--- Print Tree Info ---\n";
                std::cout << "1. Summary (tree height)\n";
                std::cout << "2. Detailed printing (all nodes)\n";
                std::cout << "Enter your choice: ";
                int printChoice;
                std::cin >> printChoice;

                RedBlackTree rbTree;
                BTree bTree;
                for (const Car& car : cars) {
                    rbTree.insert(car.id, const_cast<Car*>(&car));
                    bTree.insert(car.id, const_cast<Car*>(&car));
                }

                switch (printChoice) {
                    case 1:
                        std::cout << "[RB] Tree height: " << rbTree.getHeight() << "\n";
                        std::cout << "[B-Tree] Tree height: " << bTree.getHeight() << "\n";
                        break;
                    case 2:
                        std::cout << "\n[RB] Detailed Red-Black Tree:\n";
                        rbTree.print();
                        std::cout << "\n[B-Tree] Detailed B-Tree:\n";
                        bTree.print();
                        break;
                    default:
                        std::cout << "Invalid choice\n";
                        break;
                }
                break;
            }
            case 7:
                std::cout << "Exiting program\n";
                break;

            default:
                std::cout << "Invalid choice, try again\n";
                break;
        }
    }

    return 0;
}
