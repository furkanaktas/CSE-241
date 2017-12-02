/* 
 * File:   Computer.cpp
 * Author: furkan
 * 
 * Created on 04 Kasım 2016 Cuma, 19:51
 */

#include "Computer.h"

Computer::Computer(int option){

}

Computer::Computer(CPU& myCPU, CPUProgram& myProg, Memory& adrss, int option){
    
    myCPU.sizeOfLines = myProg.size();
    setCPU(myCPU);
    setMemory(adrss);
    setCPUProgram(myProg);    
}
void Computer::setMemory(Memory obj){
    mem = obj;
    return;
}
void Computer::setCPU(CPU obj){
    cpu = obj;
    return;
}
void Computer::setCPUProgram(CPUProgram obj){
    prog=obj;
    return;
}
void Computer::execute(){
    
    while(!cpu.halted()){
        string instruction = prog.getLine(cpu.getPC()-1);
        cpu.execute(instruction, mem);
        cpu.setPC();
    }
    return;
}


