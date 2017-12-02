/* 
 * File:   CPU.h
 * Author: furkan
 *
 * Created on 22 Ekim 2016 Cumartesi, 13:24
 */

#ifndef CPU_H
#define CPU_H

#include <cstdlib>
#include <string>
using namespace std;

class CPU {
public:
    CPU(char name, int lineSize);
    
    /*Function halted                                                         */
    /*-------------------                                                     */
    /*Bu fonksiyon PC son satır olduğu zaman true değerini çevirir, else false*/
    bool halted();
    
    /*Function execute                                                        */
    /*-------------------                                                     */
    /*Bu fonksiyon verilen string'i parçalar ve gerekli fonksiyonları çağırır */
    void execute(string line);
    
    /*Function getPC                                                          */
    /*-------------------                                                     */
    /*Bu fonksiyon PC anlık değerini return eder.                             */
    int getPC()const {return PC;}
    
    /*Function setPC                                                          */
    /*-------------------                                                     */
    /*Bu fonksiyon PC değerini 1 artırır.                                     */
    int setPC(){return PC +=1;}
    
    /*Function print                                                          */
    /*-------------------                                                     */
    /*Bu fonksiyon register ve PC değerlerinin anlık değerini print eder.     */
    void print();
private:
    static int PC;  // satır konumunu tutar
    int regI[5];    // registerların tutulduğu array
    string regS[5]={"R1","R2","R3","R4","R5"};
                                    //regS:string register karşılaştırması için
    /*Function setRegisters                                                   */
    /*-------------------                                                     */
    /*Bu fonksiyon register'lara ilk değer olarak 0 atar.                     */
    void setRegisters();
    
    /*Function setReg                                                         */
    /*-------------------                                                     */
    /*Bu fonksiyon verilen indexteki register'a verilen değeri atar.          */
    void setReg(int i, int number);
    
    /*Function getReg                                                         */
    /*-------------------                                                     */
    /*Bu fonksiyon verilen indexteki register'ı return eder.                  */
    int getReg(int i){return regI[i];} 
    
    /*Function moveAddSub                                                     */
    /*-------------------                                                     */
    /*Bu fonksiyon atama, ekleme ve çıkarma işlemlerini gerçekleştirir.       */
    void moveAddSub(string line, string info1,string* info2, string* info3);
    
    /*Function jump                                                           */
    /*-------------                                                           */
    /*Bu fonksiyon dosya işaretçisini istenilen satıra getirir.               */
    void jump(string line, string* info1, string* info2, string* info3 );
    
    /*Function print                                                          */
    /*--------------                                                          */
    /*Bu fonksiyon dosyada istenilen bilgiyi ekrana basar.                    */                  
    void print(string line, string* info2 );
    
    /*Function halt                                                           */
    /*-------------                                                           */
    /*  Bu fonksiyon ekrana registerları basar ve programı sonlandırır.       */
    int halt(string line );
    
    /*Function strToInt                                                       */
    /*-----------------                                                       */
    /*Bu fonksiyon verilen stringi integera çevirir.                          */
    int strToInt(string info);
    
    /*Function lastInfoSizer                                                  */
    /*----------------------                                                  */
    /*Bu fonksiyon verilen indexten itibaren satır sonuna veya yorum satırına */
    /*kadar olan karakter sayısını return eder.                               */
    int lastInfoSizer(int i, string line);
    
    char arg;  // mainden gönderilen komutu tutan değişken (0 yada 1)
    int sizeOfLines;    // dosya satır sayısını tutan değişken
};

#endif /* CPU_H */


