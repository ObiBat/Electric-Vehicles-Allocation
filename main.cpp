//Created by Obi



//I hold a copy of this assignment that I can produce if the original is lost or damaged.
//I hereby certify that no part of this assignment has been copied from any other student’s work or
//from any other source except where due acknowledgement is made in the assignment. No part
//of this assignment has been written/produced for me by another person except where such
//collaboration has been authorised by the subject lecturer concerned.


#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include "Constant.h"  // Include the Constant.h header file
#include "Vehicle.h"    // Include the Vehicle.h header file
#include "ChargingStation.h"    // Include the ChargingStation.h header file
#include "DemandGenerator.h"
#include "ChargingAllocation.h"


using namespace std;


int main() {
    
    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    
    DemandGenerator demandGenerator;
    
    demandGenerator.generateDemands(MIN_DEMANDS, MAX_DEMANDS, "GenchargingDemands.txt");
    
    ChargingAllocation chargingAllocation("GenchargingDemands.txt");
    
    return 0;

    

}

//       ONE THING MISSING IS AFTER ALLOCATION WITH MONTE CARLO, IT DOESNT CHECK IF SECOND CHARGING STATION CLOSE ENOUGH TO REACH DESTINATION WITH THE CAPACITY CHARGE ( IT IS BEING RANDOMLY GENERATED BETWEEN FIRST CHARGED STATION AND DESTINATION CITY)

