/* 
 * File:   main.cpp
 * Author: furkan
 *
 * Created on 01 Ekim 2016 Cumartesi, 10:53
 */

#include <iostream>
#include <fstream>
#include <string>


using namespace std;

void moveAddSub(string line, string info1, string* regS, int* regI,
        string* info2, string* info3);

void jump(string line, fstream& dosya , string* regS, int* regI, 
                  string* info2, string* info3, int satirSayisi, char** argv );
                  
void print(string line, string* regS, int* regI, string* info2 );
int halt(int* arr, string line);
int strToInt(string info);

int main(int argc, char** argv) {
    
    string line,regS[5]={"R1","R2","R3","R4","R5"}; 
                    // regS , register string dizi
    int regI[5];    // regI , register integer dizi ,heryerde aynı kullanım
    for(int i=0;i<5;++i)
	regI[i]=0;
    
    fstream dosya;
    dosya.open(argv[1]);
    
    if( !dosya.is_open() ) 
        cerr<< "açılamadı" << endl;
   
    else
    {   string temp;
        int toplamSatir=-1;
        dosya.close();
        dosya.open(argv[1]);
        while( !dosya.eof()){
            getline(dosya,temp);    
            toplamSatir +=1;			// toplam satır bulundu
        }
        dosya.close();
        
        dosya.open(argv[1]);
        while(!dosya.eof())
        {
            getline(dosya,line);        // dosyanın satırı alındı
            for(int i=0;i< line.size();++i){        // her harf büyük yapıldı
                if( line[i] >= 'a' && line[i] <= 'z')
                    line[i] += 'A'-'a';
            }         
            for(int i=0; i < line.size();++i)   //stringteki boşluklar atıldı
            {   
                size_t index = line.find_first_of(' ');
                if(index != -1)
                    line.erase(index, 1);
            }    
            string info1,info2,info3;           // instruction
            info1 = line.substr(0,3);
            
            int sayi = strToInt(argv[2]);    
            if(info1 == "MOV" || info1 == "ADD" || info1 == "SUB" )
                moveAddSub(line, info1, regS, regI, &info2, &info3);    		
            
            else if( info1 == "PRN")
                print(line,regS,regI, &info2);
            
            else if(info1 == "JMP")
                jump(line, dosya, regS,regI, &info2, &info3, toplamSatir, argv); 
                
            else if(info1 == "HLT"){
                if(sayi == 1)   		// argv[2] 1 olarak çağrılırsa
                    cout << info1 << "        - ";
            
                halt(regI,line);
            }
            else{ 
                cerr << info1 <<" syntax error" << endl; 
                exit(0);
            }
            
            
            if( sayi ==1){          		// argv[2] 1 olarak çağrılırsa               
                if(info1 == "JMP" && info2[0] != 'R')
                    cout << info1 <<' '<< info3 << "      - ";
                else if(info1 != "PRN" && info1 != "HLT")
                    cout << info1 <<' '<< info2<<", "<< info3 << " - ";
                else
                    cout << info1 <<' '<< info2 << "     - ";
                
                if(info1 != "HLT"){
                    for(int i=0;i<5;++i){
                        cout << "R" << (i+1) << "=" << regI[i];
                        if(i != 4)
                            cout << ", " ;
                    }
                    cout << endl;
                }  
            }                      	   
        }
   }        
    return 0;
}
void moveAddSub(string line, string info1, string* regS, int* regI,
                                                string* info2, string* info3){
    
    *info2 = line.substr(3,2);   // 2. bilgi(ilk register) 3. index'ten başlar 
                
    int kontrol=0;              
    for(int i=6;i<line.size();++i)
        if(line[i] == ';')              // yorum satırı  varsa kontrol == 1
            kontrol =1;
               
    int j=0;
    if(kontrol == 1){
        for(int i=6;line[i]!=';';++i)
            if(line[i] != ';')
                ++j; 
    }    
    else
        for(int i=6;i<line.size();++i)
            ++j;
        
    if(line[5] != ','){         // 5. index'te   ',' olmalı
        cerr << "syntax error" <<endl;
        exit(1);
    }    
    
    *info3 = line.substr(6,j);  // 3. bilgi (2. register)  6. index ten başlar
                
    int i;
    for(i=0;i<5;++i)
    {
        if(*info2 == regS[i])      /* ilk register belirleme*/
        {
            int k; 
            for(k=0;k<5;++k)	/* 2. register belirleme*/
            {
                if(*info3 == regS[k])
                {   
                    if(info1 == "MOV")
                        regI[k] = regI[i];
                    else if (info1 == "ADD")
                        regI[i] += regI[k];
                    else		
                        regI[i] -= regI[k];
                    k=6;                             
                }
            }
            if (k==5 && (*info3)[0] == 'R'){
                cerr << "syntax error "<< endl;
                exit(1);
            }
            else if(k == 5)	/* 2. değer constant olduğunda*/
            {	
                int sabit = strToInt(*info3);
                if(info1 == "MOV")
                    regI[i] = sabit;
                else if (info1 == "ADD")
                    regI[i] += sabit;
                else		
                    regI[i] -= sabit;
            }
            i=6;    // ilk register doğru eşleştiyse               
        }
    }
    if(i==5 || *info3 == "\0"){           // ilk register sıkıntılıysa
        cerr << "syntax error "<< endl;
        exit(0);
    }
        
    return ;
}

void jump(string line, fstream& dosya , string* regS, int* regI, 
                  string* info2, string* info3, int satirSayisi, char** argv ){
            
        
    *info2 = line.substr(3,1);
    
    if((*info2)[0] == 'R')
    {   
        *info2 = line.substr(3,2);                // JMP, R* durumu için
        
        int j=0;
        if(line[5]==',')
        {
            int kontrol=0;      // yorum satırı  varsa kontrol == 1
            for(int i=6;i<line.size();++i)
                if(line[i] == ';')
                    kontrol =1;                        
            
            if(kontrol == 1)
                for(int i=6;line[i]!=';';++i)
                    ++j;            
            else
                for(int i=6;i<line.size();++i)
                    ++j;
        }
        else 
        {
            cerr <<  "syntax error" << endl;
            exit(0);
        }
     
        *info3 = line.substr(6,j);
        int i,satir = strToInt(*info3);
        
   
        if(satir <= 0 || satir > satirSayisi){     // negatif satıra jump olmaz
            cerr << "syntax error (JMP has number which is negative "
                                                    "or out of range)"<< endl;
            exit(0);
        }
        for(i=0; i<5;++i)
            if(*info2 == regS[i])
            {    
                if(regI[i] == 0)
                {
                    dosya.close();
                    dosya.open(argv[1]);
                    for(int k=0;k<(satir-1);++k)
                        getline(dosya,line);
                }
                i=6;    //register eşleşme kontrolü
            }
        if(i==5){       // register olması gerekirken eşleşme yoksa
            cerr << *info2 << " syntax error"<< endl;
            exit(0);
        }
    }
    else                // JMP const  durumu
    {
        int kontrol=0;      // yorum satırı  varsa kontrol == 1
        for(int i=3;i<line.size();++i)
            if(line[i] == ';')
                kontrol =1;
               
        int j=0;
        if(kontrol == 1)
            for(int i=3;line[i]!=';';++i)
                ++j;                    
        else
            for(int i=3;i<line.size();++i)
                ++j;
                
        *info3 = line.substr(3,j);
        int satir = strToInt(*info3);
  
        if(satir <= 0 || satir > satirSayisi){     // negatif satıra jump olmaz
            cerr << "syntax error (JMP has number which is negative "
                                                    "or out of range)"<< endl;
            exit(0);
        }
        dosya.close();                             // dosya kapanıp tekrar 
        dosya.open(argv[1]); // açılarak işaretçi 
        for(int k=0;k<(satir-1);++k)               //istenilen satıra getirildi
            getline(dosya,line);
            
    }
    return;
}

void print(string line, string* regS, int* regI, string* info2 ){
    
    int kontrol=0;              
    for(int i=3;i<line.size();++i)
        if(line[i] == ';')           // yorum satırı  varsa kontrol == 1
            kontrol =1;
               
    int j=0;
    if(kontrol == 1)
        for(int i=3;line[i]!=';';++i)   // yorum başlangıcına kadar 
            ++j;
    else
        for(int i=3;i< line.size();++i) // satır(line) sonuna kadar
            ++j;               
                              // instruction'dan sonraki değer(register,const)
    *info2 = line.substr(3,j);       
    
    if((*info2).size() == 0){			// boş çağrılırsa
    	cerr << *info2 << "prn syntax error " << endl;
        exit(0);
    }
                
    else if((*info2)[0] == 'R'){     // register ise
        int i;
        for(i=0;i<5;++i)
            if(*info2 == regS[i]){   // registerlar la eşleşme kontrolü
                cout << regI[i] << endl;
                i=6;
            }
        
        if(i==5){     //register olması gerekirken eşleşme yoksa 
            cerr << *info2 << "prn syntax error " << endl;
            exit(0);
        }
    }   
    else
    {               // constant değer için
        int sabit = strToInt(*info2);
        cout << sabit << endl;
    } 
    
    return;
}
int halt(int* arr, string line){
    
    int kontrol=0;              
    for(int i=3;i<line.size();++i)
        if(line[i] == ';')           // yorum satırı  varsa kontrol == 1
            kontrol =1;            
    int j=0;
    if(kontrol == 1)
        for(int i=3;line[i]!=';';++i)   // yorum başlangıcına kadar 
            ++j;
    else
        for(int i=3;i< line.size();++i) // satır(line) sonuna kadar
            ++j;
       
    if( j != 0 ){			// eğer hlt komutundan sonra yazı varsa 
    	cerr << "syntax error on halt line" << endl;        
    	exit(0);
    }
    for(int i=0;i<5;++i){
        cout << "R" << (i+1) << "=" << arr[i];
        if(i != 4)
            cout << ", ";
    }
    cout << endl;
    exit(0);
}
int strToInt(string info){
    
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
        exit(0);
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
