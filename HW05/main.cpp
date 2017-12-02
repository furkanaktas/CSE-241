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
    CPU myCPU(option);
    CPUProgram myCPUProgram(option);
    myCPUProgram.ReadFile(filename);
    
    Computer myComputer(myCPU, myCPUProgram, myMemory, option);
    Computer myComputer1(option);
    
    myComputer1.setCPU(myComputer.getCPU());
    myComputer1.setCPUProgram(myComputer.getCPUProgram());
    myComputer1.setMemory(myComputer.getMemory());
    myComputer1.execute();
    ////////////////////////// yeni ödev ///////////////////////////////////
    
    //op+
    CPUProgram prog = myCPUProgram + "MOV R1, 61";
    cout <<endl << endl<< prog[prog.size()-1] << endl;
    
    //op+=
    prog += "MOV R1, R2";
    cout << prog[prog.size()-1] << endl<<endl;
    
    //op+  , op <<
    CPUProgram temp = prog + myCPUProgram;
    cout << temp << endl<<endl;
    
    //op() , > ,  op<<
    if( temp > prog)
    	cout << prog(3,8) << endl<<endl;
    	
    temp += "";
    cout<< (prog+"")[prog.size()-1] << endl<< endl;
    
    cout <<  temp(8,3) << prog << prog(0,prog.size()) << endl;	   
    return 0;
}


