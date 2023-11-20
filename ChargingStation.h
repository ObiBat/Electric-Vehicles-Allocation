//
//  ChargingStation.h
//  Practical 7.2 + 7.3
//
//  Created by Otgonbileg on 10/10/2023.
//

#include "Constant.h"

#ifndef ChargingStation_h
#define ChargingStation_h

class ChargingStation {
    
private:
    
    int cityId;
    string cityName;
    int distanceToLastCity;
    int numberOfChargers;
    int queueLength;
    double averageWaitingTime;

    
    
    
public:




    // Constructor to initialize data members
    ChargingStation(int id, const string& name, int distance, int chargers)
        : cityId(id), cityName(name), distanceToLastCity(distance), numberOfChargers(chargers) {
            
            
            
        }
    

    

    // Function to display information of a city/charging station
    void displayInfo() {
        cout << setw(5) << cityId;
        cout << setw(20) << cityName;
        cout << setw(20) << distanceToSydney() << " km";
        cout << setw(20) << numberOfChargers;
    }
    
    // Function to calculate distance from Sydney to this city
    int distanceToSydney() {
        int distance = 0;
        for (int i = 0; i <= cityId; i++) {
            distance += distanceMap[i];
        }
        return distance;
    }
    
    int getCityId() {
        return cityId;
    }
    
    void setQueueLength(int newQueueLength) {
        queueLength = newQueueLength;
    }
    
    
    int getQueueLength() {
        return queueLength;
    }

    int getNumberOfChargers() {
        return numberOfChargers;
    }
    
    void setAverageWaitingTime(double averageWaitingTimes) {

        averageWaitingTime = averageWaitingTimes;
    }
    
    double getAverageWaitingTime() {
        return averageWaitingTime;
    }
    
};

#endif /* ChargingStation_h */
