//
//  ChargingAllocation.h
//  Practical 7.2 + 7.3
//
//  Created by Otgonbileg on 13/10/2023.
//

#ifndef ChargingAllocation_h
#define ChargingAllocation_h

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Constant.h"
#include "Vehicle.h"
#include "ChargingStation.h"

using namespace std;

class ChargingAllocation {
public:
    // Constructor to initialize the ChargingAllocation object
    ChargingAllocation(const string& demandFilename) {
        createChargingStations();
        readDemandList(demandFilename);
        printing_ChargingStations();
        allocateChargingStations();
        calculateQueueLengths();
        calculateAverageWaitingTimes();
        
        cout << "Initial charging allocation ...\n";
        displayInformation(vehicles, chargingStations);
        
        cout << "\n Overall average waiting time per vehicle = " << calculateOverallWaitingTime() << endl;
        
        cout << "\n Number of simulations = 5000" << endl;
        cout << "\nOptimising..." << endl;
        cout << "Optimising..." << endl;
        cout << "Optimising..." << endl;
        
        double new_waiting_time = monteCarloBalanceChargingQueues(SIMULATION_TIMES);
        
        cout << "\nCharging allocation after balacing --->" << endl;
        displayInformation(best, bestStations);
        
        cout << "\nOverall average waiting time per vehicle = " << new_waiting_time << endl;
        
    }

private:
    
    vector<Vehicle> vehicles; // Vector to store vehicle objects
    vector<ChargingStation> chargingStations; // Vector to store charging station objects
    
    
    vector<Vehicle> best;
    vector<ChargingStation> bestStations;
    
    
    
    // Read the demand list from the text file and store it in the 'vehicles' vector
    void readDemandList(const string& filename) {
        ifstream inputFile(filename);
        if (!inputFile) {
            cerr << "Failed to open the demand file." << endl;
            return;
        }

            string line;
            while (getline(inputFile, line)) {
        //         Parse the line to extract the values
                        line = line.substr(1, line.size() - 2);
                        stringstream ss(line);
                        vector<int> values;
                        int value;
                        while (ss >> value) {
                            values.push_back(value);
                            if (ss.peek() == ',') {
                                ss.ignore();
                            }
                        }
        
                        // Extract values from the vector
                        int vehicleId = values[0];
                        int destinationId = values[1];
                        int capacityRange = values[2];
                        int remainRange = values[3];
        
                    // Create a Vehicle object and set its attributes
        
                    Vehicle vehicle(vehicleId, destinationId, capacityRange, remainRange);
        
                    vehicles.push_back(vehicle);
        
                    // Check if the vehicle needs to charge
//                    if (chargingStations[destinationId].distanceToSydney() > remainRange) {
//                        vehicles.push_back(vehicle);
//                    }
    
                }
        
        
        

            //  Display the stored vehicle information
        
        
            cout << setw(5) << "Vehicle Id" << setw(20) << "Origin" << setw(20) << "Destination" << setw(20)
             << "Capacity Range" << setw(20) << "Remaining Range" << endl;

            for (const Vehicle& vehicle : vehicles) {
                cout << setw(5) << vehicle.vehicleId;
                cout << setw(20) << nameMap[0];
                cout << setw(20) << nameMap[vehicle.destinationId];
                cout << setw(20) << vehicle.capacityRange;
                cout << setw(20) << vehicle.remainRange << endl;

            }
        

        inputFile.close();
    }
    
    void createChargingStations() {
        
        
        for (int i = 0; i < NUM_CITIES; i++) {
            ChargingStation station(i, nameMap[i], distanceMap[i], chargersMap[i]);
            
            chargingStations.push_back(station);
            
        }
        
    }
    
    void printing_ChargingStations() {
        
        cout << endl;
        
        cout << "Charging station information: " << endl;
        
        cout << setw(5) << "Location Id" << setw(20) << "Location name" << setw(20)
         << "Distance to Sydney" << setw(20) << "no of Chargers" << endl;
        
        for (ChargingStation& station : chargingStations) {
            station.displayInfo();
            cout << endl;
            
        }
        
        cout << endl;
        cout << endl;
        
    
    }
    


    // Allocate charging stations based on vehicle demands
    void allocateChargingStations() {
        // Logic to allocate charging stations (calculate the farthest city)
        for (Vehicle& vehicle : vehicles) {
            
            int distanceToDestination = chargingStations[vehicle.destinationId].distanceToSydney();
            
            if (vehicle.remainRange < distanceToDestination) {
                
                int charged_station1 = vehicle.calculateFarthestCity(0);
                
                vehicle.update_farthestCity1(charged_station1);
                
                int distanceToDestination_fromCharginPoint = chargingStations[vehicle.destinationId].distanceToSydney() - chargingStations[vehicle.farthestCity1].distanceToSydney();
                
                
                if (vehicle.capacityRange < distanceToDestination_fromCharginPoint) {
                    // Vehicle needs to recharge at the farthest city
                    
                    int charged_station2 =  vehicle.calculateFarthestCity2(charged_station1);
                    
                    vehicle.update_farthestCity2(charged_station2);
                    
                    
                }
            }
            
   
        }
        
    }
    
    
    // Function to perform the Monte Carlo simulation to reduce overall waiting time.
    double monteCarloBalanceChargingQueues(int numSimulations) {
        double bestOverallWaitingTime = 99999999999999;

        for (int simulation = 0; simulation < numSimulations; simulation++) {
           

            for (Vehicle& vehicle : vehicles) {

                int originalDestination = vehicle.destinationId;
                int distanceToDestination = chargingStations[vehicle.destinationId].distanceToSydney();
                // Check if the vehicle needs to charge on the way to its destination
                if (vehicle.remainRange < distanceToDestination) {
                    // Vehicle needs to recharge at the farthest city
                    int charged_station1 = rand() % originalDestination + 1;
                    vehicle.update_farthestCity1(charged_station1);
                    
                    
                    int distanceToDestination_fromCharginPoint = chargingStations[vehicle.destinationId].distanceToSydney() - chargingStations[vehicle.farthestCity1].distanceToSydney();
                    if (vehicle.capacityRange < distanceToDestination_fromCharginPoint) {
                        
                        int charged_station2 =  rand() % (originalDestination - charged_station1 - 1) + charged_station1 + 1; // Generate the second random farthest city
                        vehicle.update_farthestCity2(charged_station2);
                    }
                }
                
                }
            
            calculateQueueLengths();
            calculateAverageWaitingTimes();
            double currentOverallWaitingTime = calculateOverallWaitingTime();
            if (currentOverallWaitingTime < bestOverallWaitingTime) {
                bestOverallWaitingTime = currentOverallWaitingTime;
                best = vehicles;
                bestStations = chargingStations;
            }
        }

        return bestOverallWaitingTime;
    }





        

    // Calculate queue lengths at each charging station
    void calculateQueueLengths() {
        // Logic to calculate queue lengths
        for (ChargingStation& station : chargingStations) {
            int queueLength = 0;
            for (const Vehicle& vehicle : vehicles) {
                if (vehicle.farthestCity1 == station.getCityId()) {
                    queueLength++;
                }
                if (vehicle.farthestCity2 == station.getCityId()) {
                    queueLength++; // Increment the queue length if the vehicle is queuing at the 2nd charging station
                }


                
            }
            station.setQueueLength(queueLength);
        }
    }
    
    

    // Calculate average waiting times for each vehicle
    void calculateAverageWaitingTimes() {
        // Logic to calculate average waiting times
    
            for (ChargingStation& station : chargingStations) {
               
                    int queueLength = station.getQueueLength();
                    int numChargers = station.getNumberOfChargers();
                    double averageWaitingTime = 0.5 * queueLength / numChargers;
                    station.setAverageWaitingTime(averageWaitingTime);
            }
        
    }
    
    
    double calculateOverallWaitingTime() {
        double overallWaitingTime = 0.0;  // Initialize the overall waiting time.

        int totalVehiclesQueued = 0;  // Initialize the total number of vehicles queued for charging (n).

        for (ChargingStation& station : chargingStations) {
            int queueLength = station.getQueueLength();
            int numChargers = station.getNumberOfChargers();
            double averageWaitingTime = 0.5 * queueLength / numChargers;

            // Sum the product of queue length and average waiting time for each charging station.
            overallWaitingTime += queueLength * averageWaitingTime;

            // Update the total number of vehicles queued.
            totalVehiclesQueued += queueLength;
        }

        // Calculate the overall waiting time by dividing the sum by the total number of vehicles queued.
        if (totalVehiclesQueued > 0) {
            overallWaitingTime /= totalVehiclesQueued;
        }

        return overallWaitingTime;
    }
    
    
    

    

    // Display the information of each vehicle in the demand list
    // Display information for each vehicle, including both charging stations
    void displayInformation(vector<Vehicle> vehiclesss,  vector<ChargingStation> chargingStationsss) {

        
        cout << setw(5) << "Vehicle Id" << setw(20) << "Destination" << setw(20)
        << "Capacity Range" << setw(20) << "Remaining Range"  <<  setw(20) << "First recharge" << setw(20) << "Second recharge" << endl;
        
        for (const Vehicle& vehicle : vehiclesss) {
            
            
            cout << setw(5) << vehicle.vehicleId;
            cout << setw(20) << nameMap[vehicle.destinationId];
            cout << setw(20) << vehicle.capacityRange;
            cout << setw(20) << vehicle.remainRange;
            
            if (vehicle.farthestCity1 == -1) {
                cout << setw(20) << "------";
            } else {
                cout << setw(20) << nameMap[vehicle.farthestCity1];
            }
            
            if (vehicle.farthestCity2 == -1) {
                cout << setw(20) << "------" << endl;
            } else {
                cout << setw(20) << nameMap[vehicle.farthestCity2]  << endl;
            }
            
        }
        
        
        cout << setw(5) << "Location Id" << setw(20) << "Location name" << setw(20)
         << "Distance to Sydney" << setw(20) << "no of Chargers" << setw(20)
        << "Queue length" << setw(20) << "Waiting hours" << endl;
        
        for (ChargingStation& station : chargingStationsss) {
            
            station.displayInfo();
            cout << setw(20) << station.getQueueLength();
            cout << setw(20) << station.getAverageWaitingTime() << endl;

        }
    }
    


};




#endif /* ChargingAllocation_h */
