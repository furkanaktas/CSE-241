/* 
 * File:   CPUProgramDyn.cpp
 * Author: furkan
 * 
 * Created on 27 Kasım 2016 Pazar, 20:25
 */

#include <fstream>
#include <iostream>
#include "CPUProgramDyn.h"

namespace dynamic{

    CPUProgramDyn::CPUProgramDyn(int option):CPUProgramDyn(){}

    CPUProgramDyn::CPUProgramDyn():sizeOfLines(0){ array=nullptr;}

    CPUProgramDyn::CPUProgramDyn(const CPUProgramDyn& obj)
                                                  :sizeOfLines(obj.sizeOfLines){
        array = new string[sizeOfLines];
        for(int i=0;i<sizeOfLines;++i)
            array[i]=obj.array[i];
    }

    CPUProgramDyn::~CPUProgramDyn(){
        delete[] array; 
    }

    void CPUProgramDyn::ReadFile(const char* name) {

        fstream dosya;
        int satir=0;
        dosya.open(name);

        if( !dosya.is_open() ) 
            cerr<< "Dosya açılamadı" << endl;

        else{
            string line;
            while(!dosya.eof()) // dosya sonuna gelene kadar 
            {                           // her satırı vectore ekledi
                getline(dosya,line);
                satir++;
            }
            satir -=1;          // satır sayısı bulundu.
            sizeOfLines = satir;
            array = new string[satir];  // satır sayısı kadar yer alındı.
            dosya.close();
            dosya.open(name);   //dosya tekrar okunmak için kapanıp açıldı.
            int i=0;
            while(i<satir) // satır sayısı kadar 
            {                           // her satırı array'e ekledi
                getline(dosya,line);
                array[i]=line;
                ++i;
            }
        }
        return;
    }
    string CPUProgramDyn::getLine(int line){       
        if(line < 0 || line >= this->size())
            return "Out of index error!";  
            
        return array[line];
    }

    const string CPUProgramDyn::operator [](int line)const{  // overload []

        if(line < 0 || line >= this->size()){
            return "Out of index error!";  
        }    
        return array[line];
    }

    const CPUProgramDyn CPUProgramDyn::operator +(const string line)const{ 
                                                                  // overload +
        if(line =="\0")
        {
            cerr << "You can't add empty string to program" << endl;
            return *this; //boş satır eklenmeye çalıştığında kendisini döndürür.
        }    
        CPUProgramDyn temp;

        temp.sizeOfLines = sizeOfLines+1;

        temp.array = new string[temp.sizeOfLines];

        for(int i=0;i<sizeOfLines;++i)
            temp.array[i]=array[i];     
                                    // this objesine yeni satır eklenmiş hali 
        temp.array[sizeOfLines]=line;                   // temp objesine atandı.

        return CPUProgramDyn(temp);
    }

    const CPUProgramDyn& CPUProgramDyn::operator +=(string line){  //overload +=
        if(line =="\0")
        {
            cerr << "You can't add empty string to program" << endl;
            return *this; //boş satır eklenmeye çalıştığında kendisini döndürür.
        }    
        int temp =sizeOfLines;
        sizeOfLines +=1;    // size 1 artırıldı.
        string* tempArr= new string[temp+1];

        for(int i=0;i<temp;++i)
            tempArr[i]=array[i];
                                    //array temp'e atıldı, yeni satır eklendi.
        tempArr[temp]=line;

        delete [] array;
        array = new string[temp+1]; // yeni yer alındı.

        for(int i=0;i<temp+1;++i)
            array[i]=tempArr[i];    //temp array, asıl array'e atıldı.

        delete [] tempArr;     
        return *this;
    }

    const CPUProgramDyn CPUProgramDyn::operator +(const CPUProgramDyn& other){

        CPUProgramDyn temp;
        temp.sizeOfLines = sizeOfLines + other.sizeOfLines;
        temp.array = new string[temp.sizeOfLines];

        for(int i=0;i<sizeOfLines;++i) // temp objesine iilk obje eklendi
            temp.array[i]=array[i];

        for(int i=0;i<other.sizeOfLines;++i) // temp objesine 2. obje eklendi
            temp.array[i+sizeOfLines]=other.array[i];

        return CPUProgramDyn(temp);
    }

    bool CPUProgramDyn::operator ==(const CPUProgramDyn& other)const{
        if(this->size() == other.size())
            return true;
        else
            return false;
    }
    bool CPUProgramDyn::operator !=(const CPUProgramDyn& other)const{
        if(this->size() != other.size())
            return true;
        else
            return false;
    }
    bool CPUProgramDyn::operator < (const CPUProgramDyn& other)const{
        if(this->size() < other.size())
            return true;
        else
            return false;
    }
    bool CPUProgramDyn::operator > (const CPUProgramDyn& other)const{
        if(this->size() > other.size())
            return true;
        else
            return false;
    }
    bool CPUProgramDyn::operator <=(const CPUProgramDyn& other)const{
        if(this->size() <= other.size())
            return true;
        else
            return false;
    }
    bool CPUProgramDyn::operator >=(const CPUProgramDyn& other)const{
        if(this->size() >= other.size())
            return true;
        else
            return false;
    }

    ostream& operator <<(ostream& out,const CPUProgramDyn& prog){
        for(int i=0;i< prog.size();++i)
            out<< prog.array[i]<< endl;
        return out;
    }

    const CPUProgramDyn CPUProgramDyn::operator --(int ignorMe){ //postfix
        
        CPUProgramDyn tempObj=*this;  // değişiklik olmadan obje kopyalandı
        
        int temp =sizeOfLines;
        sizeOfLines -=1;
        string* tempArr= new string[temp-1];

        for(int i=0;i<temp-1;++i)
            tempArr[i]=array[i];

        delete [] array;
        array = new string[temp-1];

        for(int i=0;i<temp-1;++i)
            array[i]=tempArr[i];        
                            //this objesi değiştirilmiş oldu.(son satır silindi)
        delete [] tempArr;

        return CPUProgramDyn(tempObj);  // objenin ilk hali return edildi.
    }
    const CPUProgramDyn& CPUProgramDyn::operator --(){  //prefix
        int temp =sizeOfLines;
        sizeOfLines -=1;        // size 1 azaltıldı
        string* tempArr= new string[temp-1];   // temp array oluşturldu 

        for(int i=0;i<temp-1;++i)
            tempArr[i]=array[i];    // son eleman hariç temp array'e atıldı

        delete [] array;
        array = new string[temp-1];     //asıl array'in gösterdiği yer silindi
                                        // yeni yer alındı.
        for(int i=0;i<temp-1;++i)       //temp array, asıl array e atıldı.
            array[i]=tempArr[i];
        
        delete [] tempArr;  // temp array silindi.(aslında gerek yok,scope sonu)

        return *this;
    }

    const CPUProgramDyn CPUProgramDyn::operator()(int a,int b)const{

        CPUProgramDyn temp;
        int size= this->size();
        if(a<0 || b>= size || a>b) // a==b tek elemanlık program döndürür.
        {
            cout<<"You entered wrong indices!" << endl;
            return temp;
        }
        temp.sizeOfLines = b-a+1; //ilk ve son index dahil olacak şekilde size
        temp.array = new string[temp.sizeOfLines];
        for(int i=0;i < temp.sizeOfLines;++i)
            temp.array[i] = array[i+a];

        return CPUProgramDyn(temp);
    }

    CPUProgramDyn& CPUProgramDyn::operator=(const CPUProgramDyn& other){

        if (sizeOfLines != other.sizeOfLines) {
            delete [] array;    // size'lar eşit değilse yeni yer alındı
            array = new string[other.sizeOfLines];
        }

        sizeOfLines = other.sizeOfLines;

        for(int i=0;i<sizeOfLines;++i)
            array[i]=other.array[i];

        return *this;
    }
} // namespace dynamic

    
