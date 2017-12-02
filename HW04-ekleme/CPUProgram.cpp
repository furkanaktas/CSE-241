/* 
 * File:   CPUProgram.cpp
 * Author: furkan
 * 
 * Created on 22 Ekim 2016 Cumartesi, 13:25
 */

#include <fstream>
#include <iostream>
#include "CPUProgram.h"


CPUProgram::CPUProgram(int option) {}

CPUProgram::CPUProgram(){}

void CPUProgram::ReadFile(const char* name) {
        
    fstream dosya;
    dosya.open(name);
    vector<string>file;    
    if( !dosya.is_open() ) 
        cerr<< "Dosya açılamadı" << endl;
    
    else{
        string line;
        
        while(!dosya.eof())
        {
            getline(dosya,line);
            array.push_back(line);
        }
    }
    return;
}


