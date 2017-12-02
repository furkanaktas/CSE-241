/* 
 * File:   main.cpp
 * Author: furkan
 *
 * Created on 22 Ekim 2016 Cumartesi, 13:14
 */

#include <cstdlib>
#include <iostream>

#include "requiredIncs.h"

using namespace std;

int main(int argc, char** argv) {
    
    const char* filename = argv[1];
    
    int option = atoi(argv[2]);
    
    Memory myMemory(option);
    
    myMemory.setMem(0, 100);
    cout << myMemory.getMem(0) << endl;
    myMemory.printAll();
    
    
    CPU myCPU(option);
    myCPU.execute("MOV #0, R1", myMemory);
    myCPU.execute("MOVR1, #1", myMemory);
    myCPU.print();
    myMemory.printAll();
    
   
    CPUProgram myCPUProgram(option);
    myCPUProgram.ReadFile(filename);
    cout << myCPUProgram.getLine(1) << endl;
    cout << myCPUProgram.getLine(myCPUProgram.size() - 1) << endl;
    
    Computer myComputer(myCPU, myCPUProgram, myMemory, option);
    
    Computer myComputer1(option);
    
    myComputer1.setCPU(myComputer.getCPU());
    myComputer1.setCPUProgram(myComputer.getCPUProgram());
    myComputer1.setMemory(myComputer.getMemory());
    myComputer1.execute();
    
    return 0;
}


