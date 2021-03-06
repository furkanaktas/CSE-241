/* 
 * File:   main.cpp
 * Author: furkan
 *
 * Created on 13 Ekim 2016 Perşembe, 16:32
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*Function moveAddSub                                                         */
/*-------------------                                                         */
/*Bu fonksiyon atama, ekleme ve çıkarma işlemlerini gerçekleştirir.           */
void moveAddSub(string line, string info1, string* regS, int* regI, 
                            unsigned int* adress,string* info2, string* info3);
/*Function jump                                                               */
/*-------------                                                               */
/*Bu fonksiyon dosyayı kapatıp açarak işaretçiyi istenilen satıra getirir.    */
void jump(string line, fstream& dosya , string* regS, int* regI, string* info1, 
                  string* info2, string* info3, int satirSayisi, char** argv );
/*Function print                                                              */
/*--------------                                                              */
/*Bu fonksiyon istenilen bilgiyi ekrana basar.                                */                  
void print(string line, string* regS, int* regI,unsigned int* adress,
                                                                string* info2 );
/*Function halt                                                               */
/*-------------                                                               */
/*Bu fonksiyon ekrana registerları ve adresleri basar ve programı sonlandırır.*/
int halt(int* arr,unsigned int* adress, string line ,char** argv);

/*Function strToInt                                                           */
/*-----------------                                                           */
/*Bu fonksiyon verilen stringi integera çevirir.                              */
int strToInt(string info);

/*Function lastInfoSizer                                                      */
/*----------------------                                                      */
/*Bu fonksiyon verilen indexten itibaren dosya sonuna veya yorum satırına     */
/*kadar olan karakter sayısını return eder.                                   */
int lastInfoSizer(int i, string line); 

int main(int argc, char** argv) {
    
    string line,regS[5]={"R1","R2","R3","R4","R5"}; 
                                // regS , register string dizi
    int regI[5];                // regI , register integer dizi ,
    for(int i=0; i<5 ; ++i)     // heryerde aynı kullanım
	regI[i]=0;
    
    unsigned int adress[50];
    for(int i=0; i<50 ;++i)
        adress[i]=0;
    
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
            getline(dosya,temp);                // temp öylesine okundu
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
            
            if(info1 == "MOV" || info1 == "ADD" || info1 == "SUB" )
                moveAddSub(line, info1, regS, regI, adress, &info2, &info3);    		
            
            else if( info1 == "PRN")
                print(line,regS,regI,adress,&info2);
            
            else if(info1 == "JMP" || info1 == "JPN" )
                jump(line, dosya, regS, regI, &info1, &info2, &info3,
                                                            toplamSatir, argv); 
                
            else if(info1 == "HLT"){
                if(argv[2][0] =='1' || argv[2][0] =='2')   	
                    cout << info1 << "        - ";       
            
                halt(regI,adress,line,argv);
            }
            else{ 
                cerr << info1 <<" syntax error" << endl; 
                exit(0);
            }
                        
            if( argv[2][0] =='1' || argv[2][0] =='2'){               
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
                if(argv[2][0] =='2')
                {
                    if(info1 != "HLT"){
                        for(int i=0;i<50;++i){
                            cout << "#" << i << "=" << adress[i];
                            if(i != 49)
                                cout << ", " ;
                            if(i % 10 ==9)
                                cout << endl;
                        }
                        cout << endl;
                    }
                }    
            }                      	   
        }
    }        
    return 0;
}
void moveAddSub(string line, string info1, string* regS, int* regI, 
                            unsigned int* adress, string* info2, string* info3){
    
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
                exit(0);
            }
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
                exit(0);
            }
            else if(k == 5 && (*info3)[0] == '#'){
                string info = line.substr(7,(j-1)); //6. index '#' bu yüzden
                
                if((j-1)==0){   // '#' ten sonra sayı yoksa
                    cerr << "syntax error" << endl;
                    exit(0);
                }
                int sabit = strToInt(info);         //7.'den itibaren okuduk 
                    //j-1 'in  sebebi de # nedeniyle okunacak verinin 1 azalması
                if(sabit < 0 || sabit > 49){
                    cerr << sabit << " adres numarası, 0-49 olabilir" << endl;
                    exit(0);
                }
                if(info1 == "MOV")
                    adress[sabit] = regI[i];
                else if (info1 == "ADD")
                    regI[i] += adress[sabit];
                else		
                    regI[i] -= adress[sabit];
            
            }
            else if(k==5)	/* 2. değer constant olduğunda*/
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
    if(i==5 && (*info2)[0] == '#'){
        
        int kontrol=0;
        for (int i = 3; i < line.size(); ++i)// '#' 3. index'te olduğu için i=3
            if(line[i] == ',')
                kontrol=1;
        
        if(kontrol == 0){
            cerr << "syntax error" << endl;
            exit(0);
        }
                
        int j=0,i=4;        // '#' 3. index'te olduğu için i=4
        for(i; line[i] != ',';++i)
            j++;
        
        if(j==0){       // '#' ten sonra sayı yoksa
            cerr << "syntax error" << endl;
            exit(0);
        } 
        *info2 = line.substr(3,(j+1));
        string info = line.substr(4,j);  // '#' ile ',' arasını okudum
        int sabit = strToInt(info);      // hangi adress olduğu bulundu
        if(sabit < 0 || sabit > 49){
            cerr << sabit << " adres numarası, 0-49 olabilir" << endl;
            exit(0);
        }
        
        i=i+1; // ',' den sonraki index
        *info3 = line.substr(i,2); // R* 2 karakterli, bu yüzden 2 tane okuduk
        if((*info3)[0] == 'R'){
            int k; 
            for(k=0;k<5;++k)	/* 2. register belirleme*/
            {
                if(*info3 == regS[k])
                {   
                    if(info1 == "MOV")
                        regI[k] = adress[sabit];
                    k=6;                             
                }
            }
            if (k==5 && (*info3)[0] == 'R'){
                cerr << "syntax error "<< endl;
                exit(0);
            }
        }
        else{
            int j = lastInfoSizer(i,line);   
            *info3 = line.substr(i,j);      // son bilgi okundu (constant)
            int sabit2 = strToInt(*info3);   // string const , int'e cevrildi
            adress[sabit] = sabit2;
        }
        
    }
    else if(i==5 || *info3 == "\0"){           // ilk register sıkıntılıysa
        cerr << "syntax error "<< endl;
        exit(0);
    }        
    return ;
}
void jump(string line, fstream& dosya , string* regS, int* regI, string *info1, 
                  string* info2, string* info3, int satirSayisi, char** argv ){
            
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
                if(*info1=="JMP" && regI[i] == 0)
                {
                    dosya.close();
                    dosya.open(argv[1]);
                    for(int k=0;k<(satir-1);++k)
                        getline(dosya,line);
                }
                else if(*info1=="JPN" && regI[i] <= 0)
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
        int j =lastInfoSizer(3, line);                
        *info3 = line.substr(3,j);
        
        int satir = strToInt(*info3);  
        if(satir <= 0 || satir > satirSayisi){     // negatif satıra jump olmaz
            cerr << "syntax error (JMP has number which is negative "
                                                    "or out of range)"<< endl;
            exit(0);
        }
        dosya.close();                         // dosya kapanıp tekrar 
        dosya.open(argv[1]);                   // açılarak işaretçi 
        for(int k=0;k<(satir-1);++k)           //istenilen satıra getirildi
            getline(dosya,line);
    }
    return;
}
void print(string line, string* regS, int* regI, unsigned int* adress, 
                                                                string* info2 ){
    
    int j =lastInfoSizer(3, line);                              
    *info2 = line.substr(3,j); // instruction'dan sonraki değer(register||const)       
    
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
    else if((*info2)[0] == '#'){
        j =lastInfoSizer(4, line); // # 3.indexte bu yüzden 4.indexten itibaren
        
        if(j==0){       // '#' ten sonra sayı yoksa
            cerr << "syntax error" << endl;
            exit(0);
        }
        string info = line.substr(4,j);                
        int sabit = strToInt(info);
        if(sabit < 0 || sabit > 49){
            cerr << sabit << " adres numarası, 0-49 olabilir" << endl;
            exit(0);
        }
        cout << adress[sabit] << endl;
    }
    else
    {               // constant değer için
        int sabit = strToInt(*info2);
        cout << sabit << endl;
    } 
    
    return;
}
int halt(int* arr, unsigned int* adress, string line ,char** argv){
    
    int j =lastInfoSizer(3, line);
        
    if( j != 0 ){		// eğer hlt komutundan sonra yazı varsa 
    	cerr << "syntax error on halt line" << endl;        
    	exit(0);
    }
    for(int i=0;i<5;++i){
        cout << "R" << (i+1) << "=" << arr[i];
        if(i != 4)
            cout << ", ";
    }
    cout << endl;
    
    if(argv[2][0] == '0' || argv[2][0] == '2' ){
        for(int i=0;i<50;++i){
            cout << "#" << i << "=" << adress[i];
            if(i != 49)
                cout << ", ";
            if(i % 10 ==9)
                cout << endl;
        }
        cout << endl;
    }
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
int lastInfoSizer(int i, string line){
    
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
