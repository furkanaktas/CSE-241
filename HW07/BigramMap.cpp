/* 
 * File:   BigramMap.cpp
 * Author: furkan
 * 
 * Created on 23 Aralık 2016 Cuma, 18:08
 */
#include <vector>
#include <fstream>
#include <iostream>
#include "BigramMap.h"
#include "exceptions.h"

template <class T>
BigramMap<T>::BigramMap() {}

template <class T>
BigramMap<T>::BigramMap(int num):BigramMap(){}
    

template <class T>
void BigramMap<T>::readFile(const char* filename) {
    
    fstream dosya;
    dosya.open(filename);
    
    if( !dosya.is_open() ) 
        throw exceptions(1);        // dosya  açılamaz ise 
    else
    {
        T value;
        int key =0;
        while(!dosya.eof())
        {
            dosya >> value;
            
            if( !dosya.eof() && dosya.fail() ) // farklı tipte veriler varsa
                throw exceptions(3);
            
            temp[key]=value;
            key++;
        }
        temp.erase(temp.size()-1);
        
        if(temp.size() <=1) 
            throw exceptions(2);
        // eğer 1 veya daha az değer varsa (Bigram için en az 2)
    }  
}

template <class T>
int BigramMap<T>::numGrams()const{
    return temp.size()-1;  // tüm bigram sayısı
}

template <class T>
int BigramMap<T>::numOfGrams(T first, T second){
    
    int number=0;
    
    for(int i=0;i<temp.size();++i) 
        if((i+1 != temp.size()) && (temp[i] == first) && (temp[i+1] == second))
            number++;       // istenilen Bigramın kaç kez tekrarlandığı bulundu
    
    return number;
}

template <class T>
pair<T,T> BigramMap<T>::maxGrams(){
    
    T value1,value2;
    value1=temp[0];
    value2=temp[1];
    
    int max = numOfGrams(value1, value2);  //ilk bigramın kaç kez tekrarlandığı
    
    for(int i=0;i<temp.size();++i)
    {
        if( (i+1 !=temp.size()) && (max< numOfGrams(temp[i],temp[i+1])) )
        {                                  // en çok tekrarlanan Bigram bulundu
            max = numOfGrams(temp[i],temp[i+1]);
            value1=temp[i];
            value2=temp[i+1];
        }    
    }
    pair<T,T> value;
    value= make_pair(value1,value2);
    return value;
}

template <class T>
ostream& BigramMap<T>::print(ostream& out) {
    
    vector < vector<T> > arr;
    
    arr.resize(temp.size()-1);
    for(int i=0;i< temp.size()-1;++i)
        arr[i].resize(2);
                                
    for(int i=0;i< temp.size()-1;++i)
    {    
        arr[i][0]=temp[i];  // bigramlar 2 dimensional vector'de tutuldu.
        arr[i][1]=temp[i+1];
    }
    
    vector <int>repeat;
    
    for(int i=0; i<temp.size()-1;++i)
        repeat.push_back(numOfGrams(arr[i][0],arr[i][1]));
        // Bigram larla aynı index te , tekrar sayıları tutuldu
    
    vector <int> index;
    
    for(int i=0;i<temp.size()-1;++i)
        index.push_back(i);
    
    for(int i=0;i<temp.size()-2;++i)    
    {                       //tekrar sayısına göre index bazlı sıralama yapıldı
        for(int j=i+1;j<temp.size()-1;++j)
        {
            int arr;
            
            if(repeat[index[i]] < repeat[index[j]])
            {
                arr=index[i];
                index[i]=index[j];
                index[j]=arr;
            }    
        }    
    }    
    
    for(int i=0; i<temp.size()-1;++i)
    {
        bool type=true;
        
        for(int k=0;k<i;k++)
        {   // değerin önceden print edilip edilmediğinin kontrolü 
            if( arr[index[k]][0]==arr[index[i]][0] && 
                                           arr[index[k]][1]==arr[index[i]][1])
            {    
                type=false;
                k=i;
            }
            else
                type=true;
        }    
        if(type)
            out << arr[index[i]][0] <<" , "<<arr[index[i]][1]
                                        <<"  repeat: "<<repeat[index[i]]<<endl;
    }    
            
    return out;
}

