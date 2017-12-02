/* 
 * File:   CPU.cpp
 * Author: furkan
 * 
 * Created on 22 Ekim 2016 Cumartesi, 13:24
 */

#include "CPU.h"
#include <iostream>

int CPU::PC = 1;

CPU::CPU(char name, int lineSize) {
    arg = name;
    sizeOfLines = lineSize;
    setRegisters();    
}

void CPU::setRegisters() {
    for(int i=0;i<5;++i)
        setReg(i,0);    //5 register'a da 0 atandı.
    return;
}
void CPU::execute(string line){
    
    string info1,info2,info3;           // instruction
    info1 = line.substr(0,3);
            
    if(info1 == "MOV" || info1 == "ADD" || info1 == "SUB" )
        moveAddSub(line, info1, &info2, &info3);    		
            
    else if( info1 == "PRN")
        print(line,&info2);
            
    else if(info1 == "JMP" )
        jump(line, &info1, &info2, &info3); 
                
    else if(info1 == "HLT"){
        if(arg =='1' )   	
            cout << info1 << "        - ";       
            
        halt(line);
    }
    else{ 
        cerr << info1 <<" syntax error" << endl; 
        exit(1);
    }
                        
    if( arg =='1' ){               
        if(info1 == "JMP" && info2[0] != 'R')
            cout << info1 <<' '<< info3 << "      - ";
        else if(info1 != "PRN" && info1 != "HLT")
            cout << info1 <<' '<< info2<<", "<< info3 << " - ";
        else if(info1 == "PRN")
            cout << info1 <<' '<< info2 << "     - ";
                
        if(info1 != "HLT"){
            for(int i=0;i<5;++i){
                cout << "R" << (i+1) << "=" << getReg(i);
                if(i != 4)
                    cout << ", " ;
            }
            cout << endl;
        }
    }    
    return;
}
void CPU::moveAddSub(string line, string info1,string* info2, string* info3){
    
    *info2 = line.substr(3,2);   // 2. bilgi(ilk register) 3. index'ten başlar 
    
    int j = lastInfoSizer(6, line);
    *info3 = line.substr(6,j);  // 3. bilgi (2. register)  6. index ten başlar
      
    int i;
    for(i=0;i<5;++i)
    {
        if(*info2 == regS[i])      /* ilk register belirleme*/
        {   
            if(line[5] != ','){         // 5. index'te   ',' olmalı
                cerr << "syntax error" <<endl;
                exit(1);
            }
            int k; 
            for(k=0;k<5;++k)	/* 2. register belirleme*/
            {
                if(*info3 == regS[k])
                {   
                    if(info1 == "MOV")
                        setReg(k,getReg(i));//regI[k] = regI[i];
                    else if (info1 == "ADD")
                        setReg(i,getReg(i)+getReg(k));//regI[i] += regI[k];
                    else		
                        setReg(i,getReg(i)-getReg(k));//regI[i] -= regI[k];
                    k=6;                             
                }
            }
            if (k==5 && (*info3)[0] == 'R'){
                cerr << "syntax error "<< endl;
                exit(1);
            }
            else if(k==5)	/* 2. değer constant olduğunda*/
            {	
                int sabit = strToInt(*info3);
                if(info1 == "MOV")
                    setReg(i,sabit);              //regI[i] = sabit;
                else if (info1 == "ADD")
                    setReg(i,getReg(i)+sabit);    //regI[i] += sabit;
                else		
                    setReg(i,getReg(i)-sabit);    //regI[i] -= sabit;
            }
            i=6;    // ilk register doğru eşleştiyse               
        }
    }
    if(i==5){           // ilk register sıkıntılıysa
        cerr << "syntax error "<< endl;
        exit(1);
    }        
    return;
}
void CPU::jump(string line, string* info1, string* info2, string* info3 ){
    
    *info2 = line.substr(3,1);    
    if((*info2)[0] == 'R')
    {   
        *info2 = line.substr(3,2);                // JMP, R* durumu için
        
        int j=0;
        if(line[5]==',')
            j = lastInfoSizer(6, line);
        
        else 
        {
            cerr <<  "syntax error" << endl;
            exit(1);
        }
     
        *info3 = line.substr(6,j);
        
        int i,satir = strToInt(*info3);   
        if(satir <= 0 || satir > sizeOfLines){     // negatif satıra jump olmaz
            cerr << "syntax error (JMP has number which is negative "
                                                    "or out of range)"<< endl;
            exit(1);
        }
        for(i=0; i<5;++i)
            if(*info2 == regS[i])
            {    
                if(*info1=="JMP" && getReg(i) == 0)
                    PC = satir-1; // main'de PC 1 artırıldığı için burda gerçek  
                                  //değerin 1 eksiği verildi.
                i=6;    //register eşleşme kontrolü
            }
        if(i==5){       // register olması gerekirken eşleşme yoksa
            cerr << *info2 << " syntax error"<< endl;
            exit(1);
        }
    }
    else                // JMP const  durumu
    {
        int j =lastInfoSizer(3, line);                
        *info3 = line.substr(3,j);
        
        int satir = strToInt(*info3);  
        if(satir <= 0 || satir > sizeOfLines){     // negatif satıra jump olmaz
            cerr << "syntax error (JMP has number which is negative "
                                                    "or out of range)"<< endl;
            exit(1);
        }
        PC = satir-1;       // main'de PC 1 artırıldığı için burda gerçek
    }                       //değerin 1 eksiği verildi.
    return;
}
void CPU::print(string line, string* info2 ){
    
    int j =lastInfoSizer(3, line);                              
    *info2 = line.substr(3,j); // instruction'dan sonraki değer(register||const)       
    
    if((*info2).size() == 0){			// boş çağrılırsa
    	cerr << *info2 << "prn syntax error " << endl;
        exit(1);
    }                
    else if((*info2)[0] == 'R'){     // register ise
        int i;
        for(i=0;i<5;++i)
            if(*info2 == regS[i]){   // registerlar la eşleşme(string) kontrolü
                cout << getReg(i) << endl;
                i=6;
            }
        
        if(i==5){     //register olması gerekirken eşleşme yoksa 
            cerr << *info2 << " prn syntax error " << endl;
            exit(1);
        }
    }    
    else
    {               // constant değer için
        int sabit = strToInt(*info2);
        cout << sabit << endl;
    } 
    return;
}
int CPU::halt(string line ){
    
    int j =lastInfoSizer(3, line);
        
    if( j != 0 ){		// eğer hlt komutundan sonra yazı varsa 
    	cerr << "syntax error on halt line" << endl;        
    	exit(1);
    }
    for(int i=0;i<5;++i){
        cout << "R" << (i+1) << "=" << getReg(i);
        if(i != 4)
            cout << ", ";
    }
    cout << endl;
    
    return 0;
}
int CPU::strToInt(string info){
    
    int l;
    if(info[0] == '-')  // sayının negatif sayı olma durumu
        l=1;
    else
        l=0;
        
    int j=0;                   //i=(0+l) negatif sayıda 0.index '-' olduğu için 
    for(int i=l;i< info.size();++i) //l' ye göre 0. veya 1. indexten başlar        
        if( !(info[i] >= '0' && info[i] <= '9')) 
            j=1;    // string içinde sayı karakterleri dışında eleman varsa 
    
    if(j==1){
        cerr << "syntax error" << endl;
        exit(1);
    }
    
    int number=0,k=1;
    for(int i=(info.size()-1);i>=(0+l);--i){    //string son elemanı i'ye atandı        
        number += (info[i]-'0')*k; 
        k *=10;                // her basamak 10'la çarpılarak number'a eklendi
    }                   // string sayı int çevrilmiş oldu
    
    if(l == 1)                      // x-2x yapılarak negatif sayıya çevrildi
        number = (number -(2*number));
    
    return number;
}
int CPU::lastInfoSizer(int i, string line){
    
    int kontrol=0, temp=i;// i'nin değeri değiştiği için ilk değer temp'e atandı             
    for(i; i < line.size();++i)
        if(line[i] == ';')           // yorum satırı  varsa kontrol == 1
            kontrol =1;            
       
    int j=0;
    i=temp;
    if(kontrol == 1)
        for(i; line[i] != ';';++i)   // yorum başlangıcına kadar 
            ++j;
    else
        for(i; i < line.size();++i) // satır(line) sonuna kadar
            ++j;
    
    return j;
}
bool CPU::halted(){
    if(PC >= sizeOfLines)
        return true;
    else
        return false;
}
void CPU::setReg(int i, int number){
    regI[i]=number;
    return;
}
void CPU::print(){
    for(int i=0;i<5;++i)
        cout<<'R'<<(i+1)<<"="<<getReg(i)<<' ';
    
    cout << endl<<"PC=" << getPC() << endl;
    return;
}



