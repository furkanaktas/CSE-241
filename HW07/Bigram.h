/* 
 * File:   Bigram.h
 * Author: furkan
 *
 * Created on 23 Aralık 2016 Cuma, 16:12
 */

#ifndef BIGRAM_H
#define BIGRAM_H
#include <string>

using namespace std;

template <class T>
class Bigram {
public:
    
    virtual void readFile(const char* filename)=0;
    virtual int numGrams()const=0;
    virtual int numOfGrams(T first, T second)=0;
    virtual pair<T,T> maxGrams()=0;
    
    virtual  ostream& print(ostream& out)=0 ;
    friend ostream& operator << (ostream& out, Bigram<T>& obj)
    {
        return obj.print(out);
    }
};

#endif /* BIGRAM_H */


