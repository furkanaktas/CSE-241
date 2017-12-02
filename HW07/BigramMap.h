/* 
 * File:   BigramMap.h
 * Author: furkan
 *
 * Created on 23 Aralık 2016 Cuma, 18:08
 */

#ifndef BIGRAMMAP_H
#define BIGRAMMAP_H
#include <string>
#include <map>
#include "Bigram.h"

using namespace std;

template <class T>
class BigramMap : public Bigram<T> {
public:
    
    BigramMap();
    BigramMap(int num);
    void readFile(const char* filename)  override;
    int numGrams()const  override;
    int numOfGrams(T first, T second)  override;
    pair<T,T> maxGrams()  override; 
    ostream& print(ostream& out)   override;

private:
    map<int,T>temp;
};
#endif /* BIGRAMMAP_H */


