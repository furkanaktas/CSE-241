/* 
 * File:   main.cpp
 * Author: furkan
 *
 * Created on 11 Kasım 2016 Cuma, 16:23
 */

#include <cstdlib>
#include <iostream>
/*#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"*/
#include "Computer.h"
using namespace std;

int main(int argc, char** argv) {
    
    const char* filename = argv[1];
    
    int option = atoi(argv[2]);
    
    
    //Testing class CPUProgram
    //op []
    CPUProgram myCPUProgram(option);
    myCPUProgram.ReadFile(filename);
    cout << myCPUProgram[0] << endl;
    cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
    
    //op +
    cout <<((myCPUProgram + "MOV R1, #45" )[myCPUProgram.size()-1]) << endl;
    
    //op +=
    myCPUProgram += "MOV R2, #50";
    cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
   
    //op + <<
    CPUProgram myOtherCPUProgram(option);
    myOtherCPUProgram.ReadFile(filename);
    cout << (myCPUProgram + myOtherCPUProgram) << endl;
    
    //op COMP --
    cout<< (myCPUProgram == myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout<< (myCPUProgram <= myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout<< (myCPUProgram > myOtherCPUProgram ? "FAIL" : "DONE") << endl;    
    
    --myOtherCPUProgram;
    
    cout << (myCPUProgram != myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout << (myCPUProgram >= myOtherCPUProgram ? "DONE" : "FAIL") << endl;
    cout << (myCPUProgram < myOtherCPUProgram ? "FAIL" : "DONE") << endl;
   
    //op ()
    cout << myCPUProgram(5,10) << endl;
    
    //error check////////////////
    
    //cout << myCPUProgram[myCPUProgram.size()] << endl;
    myCPUProgram += "";
    cout << myCPUProgram[myCPUProgram.size() - 1] << endl;
//////////////////////////////////////////////////////////////////////////
    return 0;
}



