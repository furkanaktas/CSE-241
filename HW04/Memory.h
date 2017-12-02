/* 
 * File:   Memory.h
 * Author: furkan
 *
 * Created on 27 Ekim 2016 Perşembe, 19:47
 */

#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>

using namespace std;

class Memory {
public:
    Memory(int option);
    Memory();
    int getMem(int number)const;
    void setMem(int i, int number);
    void printAll();
private:
    unsigned int adress[50];
    void setMemos();
};

#endif /* MEMORY_H */


