/* 
 * File:   exceptions.cpp
 * Author: furkan
 * 
 * Created on 28 Aralık 2016 Çarşamba, 12:32
 */

#include "exceptions.h"


const char* exceptions::what()const throw(){
    
    if(option==1)
        return "Dosya açılamadı";
    else if(option ==2)
        return "Bigram olabilecek sayıda(2) yeterli veri bulunamadı. ";
    else if(option ==3)
        return "Farklı tiplerde veri var";
}
