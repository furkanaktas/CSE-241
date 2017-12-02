/* 
 * File:   Computer.h
 * Author: furkan
 *
 * Created on 04 Kasım 2016 Cuma, 19:51
 */

#ifndef COMPUTER_H
#define COMPUTER_H

#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"

class Computer {
public:
    Computer(int option);
    Computer(CPU& myCPU, CPUProgram& myProg, Memory& adrss, int option);
    
    void setCPU(CPU obj);
    CPU getCPU()const{return cpu;};
    void setCPUProgram(CPUProgram obj);
    CPUProgram getCPUProgram()const{return prog;}
    void setMemory(Memory obj);
    Memory getMemory()const{return mem;}
    void execute();
private:
    CPU cpu;
    CPUProgram prog;
    Memory mem;
};    

#endif /* COMPUTER_H */


