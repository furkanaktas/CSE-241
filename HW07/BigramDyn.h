/* 
 * File:   BigramDyn.h
 * Author: furkan
 *
 * Created on 23 Aralık 2016 Cuma, 18:08
 */

#ifndef BIGRAMDYN_H
#define BIGRAMDYN_H

#include <string>
#include "Bigram.h"


using namespace std;

template <class T>
class BigramDyn : public Bigram<T> {
public:
    
    BigramDyn();
    BigramDyn(int num);
    ~BigramDyn();
    
    void readFile(const char* filename)override;
    int numGrams()const  override;
    int numOfGrams(T first, T second)  override;
    pair<T,T> maxGrams()  override; 
    
    ostream& print(ostream& out)   override;

private:
    T* array;
    int size;
};
#endif /* BIGRAMDYN_H */


