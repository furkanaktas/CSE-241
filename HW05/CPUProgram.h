/* 
 * File:   CPUProgram.h
 * Author: furkan
 *
 * Created on 22 Ekim 2016 Cumartesi, 13:25
 * Reworked on 11 Kasım 2016 Cuma, 16:23
 */

#ifndef CPUProgram_H
#define CPUProgram_H

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class CPUProgram {
public:

    CPUProgram(int option);
    CPUProgram();
    /*Function getLine                                                        */
    /*-------------------                                                     */
    /*Bu fonksiyon verilen istenilen satırı return eder.                      */
    string getLine(int line);
    
    /*Function size                                                           */
    /*-------------------                                                     */
    /*Bu fonksiyon dosyadaki satır sayısını return eder.                      */
    int size()const{return array.size();}
    
    /*Function ReadFile                                                       */
    /*-------------------                                                     */
    /*Bu fonksiyon dosyadan okunan veriyi düzenler ve array değişkenine atar. */
    void ReadFile(const char* name);
    
    const string& operator [](int line)const;
    
    const CPUProgram operator +(const string line)const;
    const CPUProgram operator +=(string line);
    const CPUProgram operator +(const CPUProgram& other);
    
    bool operator ==(const CPUProgram& other)const;
    bool operator !=(const CPUProgram& other)const;
    bool operator < (const CPUProgram& other)const;
    bool operator > (const CPUProgram& other)const;
    bool operator <=(const CPUProgram& other)const;
    bool operator >=(const CPUProgram& other)const;
    
    friend ostream& operator <<(ostream& out,const CPUProgram& prog);
    
    const CPUProgram operator --(int ignorMe);
    const CPUProgram operator --();
    
    const CPUProgram operator()(int a, int b)const;
    
private:
    
    vector<string> array; // dosyadaki satırları tutan değişken
};

#endif /* CPUPROGRAM_H */


