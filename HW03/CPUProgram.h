/* 
 * File:   CPUProgram.h
 * Author: furkan
 *
 * Created on 22 Ekim 2016 Cumartesi, 13:25
 */

#ifndef CPUProgram_H
#define CPUProgram_H

#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class CPUProgram {
public:

    CPUProgram(char* name);
    
    /*Function getLine                                                        */
    /*-------------------                                                     */
    /*Bu fonksiyon verilen istenilen satırı return eder.                      */
    string getLine(int line){return array[line-1];}
    
    /*Function size                                                           */
    /*-------------------                                                     */
    /*Bu fonksiyon dosyadaki satır sayısını return eder.                      */
    int size(){return array.size();}
private:
    
    vector<string> array; // dosyadaki satırları tutan değişken
    
    /*Function ReadFile                                                       */
    /*-------------------                                                     */
    /*Bu fonksiyon dosyadan okunan veriyi düzenler ve array değişkenine atar. */
    void ReadFile(char* name);
};

#endif /* CPUPROGRAM_H */


