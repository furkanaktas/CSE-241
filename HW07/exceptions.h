/* 
 * File:   exceptions.h
 * Author: furkan
 *
 * Created on 28 Aralık 2016 Çarşamba, 12:32
 */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>

using namespace std;

class exceptions:  public exception {
public:
    exceptions(int option):option(option){}
    virtual const char* what() const throw()  override;

private:
    int option;
};

#endif /* EXCEPTIONS_H */


