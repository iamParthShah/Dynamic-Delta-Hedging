#include "Price_Option.h"
#include "Stock.h"
#include "Option.h"
#include "math.h"
#include "time.h"

Price_Option::Price_Option(){
    //constructor
}

Price_Option::~Price_Option(){
    //destructor
}
double Price_Option::cdfFromZ(double x){   double z = 0, Rz = 0, N = 0;
     if (x < 0) {
        x = -x;
        z = 1.0 / (1.0 + B * x);
        Rz = A1 * z + A2 * pow(z, 2) + A3 * pow(z, 3) + A4 * pow(z, 4) + A5 * pow(z, 5);
        N =  NORMALIZER * exp(-0.5 * pow(x, 2)) * Rz;
    } else {
        z = 1.0 / (1.0 + B * x);
        Rz = A1 * z + A2 * pow(z, 2) + A3 * pow(z, 3) + A4 * pow(z, 4) + A5 * pow(z, 5);
        N = 1 - NORMALIZER * exp(-0.5 * pow(x, 2)) * Rz;
    }
    return N;
}


double Price_Option::Black_Scholes_Option_Price(Option& option, Stock& stock, double time_to_maturity) {
    double spot = stock.Getspot();
    double time = time_to_maturity;
    double sigma = option.Getsigma();
    double rate = stock.Getrate();
    double strike = option.Getstrike_price();
    double price;

    double d1 = (1 / (sigma * sqrt(time))) * (log(spot / strike) + (rate + sigma * sigma / 2) * time);
    double d2 = d1 - sigma * sqrt(time);

    if (option.GetisCall()) {
        return price = cdfFromZ(d1) * spot - cdfFromZ(d2) * strike * exp(-rate * time);
    }
    else {
        return price = cdfFromZ(-d2) * strike * exp(-rate * time) - cdfFromZ(-d1) * spot;
    }
}

double Price_Option::Black_Scholes_Option_Delta(Option& option, Stock& stock, double time_to_maturity) {
    double spot = stock.Getspot();
    double time = time_to_maturity;
    double sigma = option.Getsigma();
    double rate = stock.Getrate();
    double strike = option.Getstrike_price();
    double price;

    double d1 = (1 / (sigma * sqrt(time))) * (log(spot / strike) + (rate + sigma * sigma / 2) * time);
    double d2 = d1 - sigma * sqrt(time);

    if (option.GetisCall())
        return cdfFromZ(d1);
    else
        return cdfFromZ(d1)-1;
}

// Temporary functions, just to get around with volatility as of now
double Price_Option::Black_Scholes_Option_Price(double spot, double time, double sigma, double rate, double strike, bool isCall) {

    double price;

    double d1 = (1 / (sigma * sqrt(time))) * (log(spot / strike) + (rate + sigma * sigma / 2) * time);
    double d2 = d1 - sigma * sqrt(time);

    if (isCall) {
        return price = cdfFromZ(d1) * spot - cdfFromZ(d2) * strike * exp(-rate * time);
    }
    else {
        return price = cdfFromZ(-d2) * strike * exp(-rate * time) - cdfFromZ(-d1) * spot;
    }
}

double Price_Option::Black_Scholes_Option_Delta(double spot, double time, double sigma, double rate, double strike, bool isCall) {

    double price;

    double d1 = (1 / (sigma * sqrt(time))) * (log(spot / strike) + (rate + sigma * sigma / 2) * time);
    double d2 = d1 - sigma * sqrt(time);

    if (isCall) {
        return cdfFromZ(d1);
    }
    else {
        return cdfFromZ(d1)-1;
    }
}

double Price_Option::implied_volatility(double target,  double strike, double spot, double interest_rate, double time_to_maturity, bool isCall) {
    double epsilon = 0.000001;
    double a = 0, b = 1;

    Price_Option op{};
    double x = 0.5 * (a + b);
    double BSMprice = op.Black_Scholes_Option_Price(spot, time_to_maturity, x, interest_rate, strike, isCall);

    int n=0;
    double y = BSMprice;
    while (abs(y-target) > epsilon){
        n++;
        if(n>1000000){
            return x;
        }
        if (y < target) {
            a = x;
        }
        if (y > target) {
            b = x;
        }

        x = 0.5 * (a + b);
        y = op.Black_Scholes_Option_Price(spot, time_to_maturity, x, interest_rate, strike, isCall);
    }

        return x;
}

