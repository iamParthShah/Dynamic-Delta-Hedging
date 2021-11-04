#ifndef PRICE_OPTION_H
#define PRICE_OPTION_H
#include "Stock.h"
#include "Option.h"

class Price_Option
{
    public:
        Price_Option();
        virtual ~Price_Option();
        double cdfFromZ(double x);
        double Black_Scholes_Option_Price(Option& option, Stock& stock, double time_to_maturity);
        double Black_Scholes_Option_Delta(Option& option, Stock& stock, double time_to_maturity);
        double Black_Scholes_Option_Price(double spot, double time, double sigma, double rate, double strike, bool isCall);
        double Black_Scholes_Option_Delta(double spot, double time, double sigma, double rate, double strike, bool isCall);
        double implied_volatility(double target,  double strike, double spot, double interest_rate, double time_to_maturity, bool isCall);
    protected:

    private:
        const double A1 = 0.319381530;
        const double A2 = -0.35653782;
        const double A3 = 1.781477937;
        const double A4 = -1.821255978;
        const double A5 = 1.330274429;
        const double B = 0.2316419;
        const double NORMALIZER = 0.39894228;
};

#endif // PRICE_OPTION_H
