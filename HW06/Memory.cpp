/* 
 * File:   Memory.cpp
 * Author: furkan
 * 
 * Created on 27 Ekim 2016 Perşembe, 19:47
 */

#include "Memory.h"

Memory::Memory(){
    setMemos();
}
Memory::Memory(int option):Memory() {}

void Memory::setMemos(){
    
    for(int i=0;i<50;++i)
        adress[i]=0;
    return;
}
void Memory::setMem(int i, int number){
    if(i<0 || i>49)
    {
        cerr << i << " adres numarası, 0-49 olabilir" << endl;
        exit(1);
    }    
    adress[i]=number;
    return;
}
int Memory::getMem(int number)const{
    if(number<0 || number>49)
    {
        cerr << number << " adres numarası, 0-49 olabilir" << endl;
        exit(1);
    }
    return adress[number];
}
void Memory::printAll(){
    cout << "Memory printAll" << endl;
    for(int i=0;i<50;++i)
        cout<< '[' << i << ']' << " -> " << getMem(i) << endl;
    return;
}
