/* 
 * File:   CPUProgram.h
 * Author: furkan
 *
 * Created on 27 Kasım 2016 Pazar, 20:25
 */

#ifndef CPUProgramDyn_H
#define CPUProgramDyn_H

#include <iostream>
using namespace std;

namespace dynamic{
    class CPUProgramDyn 
    {
    public:

        CPUProgramDyn(int option);
        CPUProgramDyn();
        CPUProgramDyn(const CPUProgramDyn& obj);
        ~CPUProgramDyn();

        /*Function getLine                                                    */
        /*-------------------                                                 */
        /*Bu fonksiyon verilen istenilen satırı return eder.                  */
        string getLine(int line);

        /*Function size                                                       */
        /*-------------------                                                 */
        /*Bu fonksiyon dosyadaki satır sayısını return eder.                  */
        int size()const{return sizeOfLines;} 

        /*Function ReadFile                                                   */
        /*-------------------                                                 */
        /*Bu fonksiyon dosyadan okunan veriyi array değişkenine atar.         */
        void ReadFile(const char* name);

        const string operator [](int line)const;

        const CPUProgramDyn operator +(const string line)const;
        const CPUProgramDyn& operator +=(string line);
        const CPUProgramDyn operator +(const CPUProgramDyn& other);

        bool operator ==(const CPUProgramDyn& other)const;
        bool operator !=(const CPUProgramDyn& other)const;
        bool operator < (const CPUProgramDyn& other)const;
        bool operator > (const CPUProgramDyn& other)const;
        bool operator <=(const CPUProgramDyn& other)const;
        bool operator >=(const CPUProgramDyn& other)const;

        friend ostream& operator <<(ostream& out,const CPUProgramDyn& prog);

        const CPUProgramDyn operator --(int ignorMe);  //postfix
        const CPUProgramDyn& operator --();			   //prefix

        const CPUProgramDyn operator()(int a,int b)const;

        CPUProgramDyn& operator=(const CPUProgramDyn& other);

    private:
        string* array;
        int sizeOfLines;
    };
} // dynamic
#endif /* CPUProgramDyn_H */

