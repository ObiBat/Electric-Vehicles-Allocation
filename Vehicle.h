//
//  Vehicle.h
//  Practical 7.2 + 7.3
//
//  Created by Otgonbileg on 10/10/2023.
//

#ifndef Vehicle_h
#define Vehicle_h

#include "ChargingStation.h"

class Vehicle {
public:
    int vehicleId;
    int currentCityId = 0; // Initialized as 0
    int destinationId;
    int capacityRange;
    int remainRange;
    
    int distanceToDestination;
    int farthestCity1 = -1;
    int farthestCity2 = -1;
    
    double averageWaitingTimes[12];
    
    
    
    
    // Constructor to initialize data members
    Vehicle(int id, int destinationId, int capacityRange, int remainRange)
    : vehicleId(id), destinationId(destinationId), capacityRange(capacityRange), remainRange(remainRange) {
        
        
        
    }
    // Function to calculate the farthest city the vehicle can travel to
    
    
    int calculateFarthestCity(int currentcity) {
        
        
        // Calculate the farthest city based on the remaining battery
        int remainingBattery = remainRange;
        while (remainingBattery >= distanceMap[currentcity+1]) {
            remainingBattery -= distanceMap[currentcity+1];
            currentcity++;
        }

            return currentcity; // Return the farthest city
        
        
    }
    
    int calculateFarthestCity2(int currentcity) {
        
        
        // Calculate the farthest city based on the remaining battery
        int remainingBattery = capacityRange;
        while (remainingBattery >= distanceMap[currentcity+1]) {
            remainingBattery -= distanceMap[currentcity+1];
            currentcity++;
        }

            return currentcity; // Return the farthest city
        
        
    }
    
    void update_farthestCity1(int farthestCity) {
        farthestCity1 = farthestCity;
    }
    
    void update_farthestCity2(int farthestCity) {
        farthestCity2 = farthestCity;
    }
    

    
    
};
    




#endif /* Vehicle_h */
