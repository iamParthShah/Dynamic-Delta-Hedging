#include "Stock.h"

Stock::Stock(){
    //constructor
}

Stock::~Stock(){
    //destructor
}

Stock::Stock(double spot, double drift, double dividend, double rate){
    this -> spot = spot;
    this -> drift = drift;
    this -> dividend = dividend;
    this -> rate = rate;
}
