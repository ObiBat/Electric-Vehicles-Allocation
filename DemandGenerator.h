//
//  DemandGenerator.h
//  Practical 7.2 + 7.3
//
//  Created by Otgonbileg on 12/10/2023.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "Constant.h" // Include the Constant.h header file



using namespace std;

// Define the VehicleDemand structure to represent a charging demand
struct VehicleDemand {
    int vehicleId;
    int destinationId;
    int capacityRange;
    int remainRange;
};

class DemandGenerator {
public:
    
    
    // Generate a random number between min and max
    int randomInt(int min, int max) {
        return min + rand() % (max - min + 1);
    }

    // Generate a list of EV charging demands and write them to a text file
    void generateDemands(int minDemands, int maxDemands, const string& filename) {
        ofstream outputFile(filename);
        if (!outputFile) {
            cerr << "Failed to open the output file." << endl;
            return;
        }

        // Seed the random number generator with the current time
        srand(static_cast<unsigned>(time(nullptr)));

        int numDemands = randomInt(minDemands, maxDemands);
        for (int i = 0; i < numDemands; ++i) {
            VehicleDemand demand;
            demand.vehicleId = i; // Generate vehicle IDs starting from 200
            demand.destinationId = randomInt(1, NUM_CITIES - 1); // Random destination
            demand.capacityRange = randomInt(MIN_CAPACITY, MAX_CAPACITY); // Random capacity range
            demand.remainRange = randomInt(MIN_REMAIN_RANGE, demand.capacityRange); // Random remaining range

            // Write the demand to the output file
            outputFile << "[" << demand.vehicleId << "," << demand.destinationId << ","
                << demand.capacityRange << "," << demand.remainRange << "]" << endl;
        }

        outputFile.close();
        cout << "Generated " << numDemands << " charging demands and saved to " << filename << endl;
    }
};


