/* 
 * File:   main.cpp
 * Author: furkan
 *
 * Created on 22 Ekim 2016 Cumartesi, 13:14
 */

#include <cstdlib>
#include <iostream>
#include "CPU.h"
#include "CPUProgram.h"

using namespace std;

int main(int argc, char** argv) {
    
    CPUProgram myProg(argv[1]);
    
    int size = myProg.size();
    
    CPU myCPU( argv[2][0], size);
    
    while(!myCPU.halted()){
        string instruction = myProg.getLine(myCPU.getPC());
        myCPU.execute(instruction);
        myCPU.setPC();
    }
    myCPU.print();
    return 0;
}


