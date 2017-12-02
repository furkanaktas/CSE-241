/* 
 * File:   BigramDyn.cpp
 * Author: furkan
 * 
 * Created on 23 Aralık 2016 Cuma, 18:08
 */
#include <fstream>
#include <iostream>
#include "BigramDyn.h"
#include "exceptions.h"
using namespace std;

template <class T>
BigramDyn<T>::BigramDyn() {
    array = nullptr;
}

template <class T>
BigramDyn<T>::BigramDyn(int num):BigramDyn() {}


template <class T>
void BigramDyn<T>::readFile(const char* filename){
    
    fstream dosya;
    dosya.open(filename);
    int key =0;
    T value;
    
    if( !dosya.is_open() ) 
        throw exceptions(1); // dosya  açılamaz ise 
    else
    {
        while(!dosya.eof())
        {
            dosya >> value;
                
            if( !dosya.eof() && dosya.fail() ) // farklı tipte veriler varsa
                throw exceptions(3);
            
            key++;
        }
        key--;
    }
    if(key <=1)         // eğer 1 veya daha az değer varsa (Bigram için en az 2) 
        throw exceptions(2);
    
    size=key;
    dosya.close();
    dosya.open(filename);
    
    array = new T[key];
    for(int i=0;i<key;++i)
    {    
        dosya >> value;
        array[i]=value;
    }
    
    return;
}

template <class T>
int BigramDyn<T>::numGrams()const {
    return (size-1);        // tüm bigram sayısı
}

template <class T>
int BigramDyn<T>::numOfGrams(T first, T second){
    
    int number=0;
    
    for(int i=0;i< size;++i)
        if((i+1 != size) && (array[i] == first) && (array[i+1] == second))
            number++;       // istenilen Bigramın kaç kez tekrarlandığı bulundu
    
    return number;
}

template <class T>
ostream& BigramDyn<T>::print(ostream& out) {
    
    T **temp = new T*[size-1];
    
    for(int i=0;i<size-1;++i)
        temp[i]=new T[2];
    
    for(int i=0;i< size-1;++i)
    {    
        temp[i][0]=array[i];
        temp[i][1]=array[i+1];
    }                       // bigramlar 2 dimensional array'de tutuldu.
    
    int* repeat= new int[size-1];
    
    for(int i=0; i<size-1;++i)
        repeat[i]= numOfGrams(temp[i][0],temp[i][1]);
                // Bigram larla aynı index te , tekrar sayıları tutuldu
    
    int* index=new int[size-1];
    
    for(int i=0;i<size-1;++i)
        index[i]=i;
    
    for(int i=0;i<size-2;++i)   
    {                   //tekrar sayısına göre index bazlı sıralama yapıldı
        for(int j=i+1;j<size-1;++j)
        {
            int temp;
            
            if(repeat[index[i]] < repeat[index[j]])
            {
                temp=index[i];
                index[i]=index[j];
                index[j]=temp;
            }    
        }    
    }    
    
        
    for(int i=0; i<size-1;++i)
    {
        bool type=true;
        
        for(int k=0;k<i;k++)
        {   // değerin önceden print edilip edilmediğinin kontrolü
            if( temp[index[k]][0]==temp[index[i]][0] && 
                                           temp[index[k]][1]==temp[index[i]][1])
            {    
                type=false;
                k=i;
            }
            else
                type=true;
        }    
        if(type)
            out << temp[index[i]][0] <<" , "<<temp[index[i]][1]
                                         <<"  repeat: "<<repeat[index[i]]<<endl;
    }    
    
    for(int i=0;i<size-1;++i)
        delete [] temp[i];
        
    delete [] temp;    // alınan yerler geri verildi(gerekli değil, scope sonu)
    delete [] index;
    delete [] repeat;
    
    return out;
}

template <class T>
pair<T,T> BigramDyn<T>::maxGrams(){
    
    T value1,value2;
    value1=array[0];
    value2=array[1];
    int max = numOfGrams(value1, value2);  //ilk bigramın kaç kez tekrarlandığı
    
    for(int i=0;i+1< size;++i)
    {
        if( max< numOfGrams(array[i],array[i+1]) )
        {                                  // en çok tekrarlanan Bigram bulundu
            max = numOfGrams(array[i],array[i+1]);
            value1=array[i];
            value2=array[i+1];
        }    
    }
    pair<T,T> value;
    value= make_pair(value1,value2);
    return value;
}



template <class T>
BigramDyn<T>::~BigramDyn(){

    delete[] array;
}



