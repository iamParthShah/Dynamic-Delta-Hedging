#include "Option.h"

Option::Option(){
    //constructor
}

Option::~Option(){
    //destructor
}

Option::Option(double strike_price, double sigma, bool isCall){
    this->strike_price = strike_price;
    this->sigma = sigma;
    this->isCall = isCall;
}

void Option::init(){
    strike_price = 100;
    sigma = 0.05;
}
