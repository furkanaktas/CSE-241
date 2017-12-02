/* 
 * File:   CPUProgram.cpp
 * Author: furkan
 * 
 * Created on 22 Ekim 2016 Cumartesi, 13:25
 */

#include <fstream>
#include <iostream>
#include "CPUProgram.h"


CPUProgram::CPUProgram(char* name) {
    ReadFile(name);
}

void CPUProgram::ReadFile(char* name) {
        
    fstream dosya;
    dosya.open(name);
    vector<string> file;
    
    if( !dosya.is_open() ) 
        cerr<< "Dosya açılamadı" << endl;
    
    else{
        string line;
        while(!dosya.eof())
        {
            getline(dosya,line);
            for(int i=0;i< line.size();++i){        // her harf büyük yapıldı
                if( line[i] >= 'a' && line[i] <= 'z')
                    line[i] += 'A'-'a';
            }         
            for(int i=0; i < line.size();++i)   //stringteki boşluklar atıldı
            {   
                size_t index = line.find_first_of(' ');
                if(index != -1)
                    line.erase(index, 1);
            }
            file.push_back(line);
        }
        int size = file.size();
        for(int i=0;i<size;++i)
            array.push_back(file[i]);
        
    }
    return;
}


