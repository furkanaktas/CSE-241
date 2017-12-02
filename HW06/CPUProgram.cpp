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
        while(!dosya.eof()) // dosya sonuna gelene kadar 
        {                           // her satırı vectore ekledi
            getline(dosya,line);
            array.push_back(line);
        }
        array.pop_back();
    }
    return;
}
string CPUProgram::getLine(int line){       // eski fonk
    if(line < 0 || line >= array.size())
        return "Out of index error!";   
    
    return array[line];
}

const string CPUProgram::operator [](int line)const{  // overload []
    
    if(line < 0 || line >= array.size())
        return "Out of index error!";    
    
    return array[line];
}

const CPUProgram CPUProgram::operator +(const string line)const{ // overload +
    
    if(line =="\0")
    {
        cerr << "You can't add empty string to program" << endl;
        return *this;  // boş satır eklenmeye çalıştığında kendisini döndürür.
    }    
    CPUProgram temp;
    temp=*this;
    temp.array.push_back(line);
    return temp;
}

const CPUProgram CPUProgram::operator +=(string line){  // overload +=
    if(line =="\0")
    {
        cerr << "You can't add empty string to program" << endl;
        return *this; // boş satır eklenmeye çalıştığında kendisini döndürür.
    }    
    array.push_back(line);
    return *this;
}

const CPUProgram CPUProgram::operator +(const CPUProgram& other){
    
    CPUProgram temp;
    
    for(int i=0;i<this->size();++i) // temp objesine iilk obje eklendi
        temp.array.push_back(array[i]);
    
    for(int i=0;i<other.size();++i) // temp objesine 2. obje eklendi
        temp.array.push_back(other.array[i]);
    
    return temp;
}

bool CPUProgram::operator ==(const CPUProgram& other)const{
    if(array.size() == other.size())
        return true;
    else
        return false;
}
bool CPUProgram::operator !=(const CPUProgram& other)const{
    if(array.size() != other.size())
        return true;
    else
        return false;
}
bool CPUProgram::operator < (const CPUProgram& other)const{
    if(array.size() < other.size())
        return true;
    else
        return false;
}
bool CPUProgram::operator > (const CPUProgram& other)const{
    if(array.size() > other.size())
        return true;
    else
        return false;
}
bool CPUProgram::operator <=(const CPUProgram& other)const{
    if(array.size() <= other.size())
        return true;
    else
        return false;
}
bool CPUProgram::operator >=(const CPUProgram& other)const{
    if(array.size() >= other.size())
        return true;
    else
        return false;
}

ostream& operator <<(ostream& out,const CPUProgram& prog){
    for(int i=0;i< prog.size();++i)
        out<< prog.array[i]<< endl;
    return out;
}

const CPUProgram CPUProgram::operator --(int ignorMe){
    CPUProgram temp =*this;
    array.pop_back();
    return temp;
}
const CPUProgram CPUProgram::operator --(){
    array.pop_back();
    return *this;
}

const CPUProgram CPUProgram::operator()(int a,int b)const{
    
    CPUProgram temp;
    int size= array.size();
    if(a<0 || b>= size || a>b) // a==b tek elemanlık program döndürür.
    {
        cout<<"You entered wrong indices!" << endl;
        return temp;
    }    
    for(int i=a;i<=b;++i)
        temp.array.push_back(array[i]);
    
    return temp;
}
    
