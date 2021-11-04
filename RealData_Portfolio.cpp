#include "RealData_Portfolio.h"
#include <map>
#include <ctime>
#include "Price_Option.h"
#include "vector"
#include "math.h"
#include <fstream>
#include <iostream>

using namespace std;

RealData_Portfolio::RealData_Portfolio(){
    //constructor
}

RealData_Portfolio::~RealData_Portfolio(){
    //destructor
}

void RealData_Portfolio::pnl(vector<double> interest_rates, vector<double> stock_prices , vector<double> option_prices, vector<double> time_to_maturity,
                                        double strike, bool isCall, map<string, double> rates_map)
{
    vector<double> implied_volatility;
    vector<double> delta;
    vector<double> hedging_error;
    vector<double> pnl;
    vector<double> pnl_with_hedge;
    vector<double> portfolio;

    double dT = 1/252.0;

    hedging_error.push_back(0);
    pnl_with_hedge.push_back(0);

    Price_Option op{};

    for (int i = 0; i < interest_rates.size(); ++i){

        interest_rates[i] = interest_rates[i]/100;
        implied_volatility.push_back(op.implied_volatility(option_prices[i], strike, stock_prices[i], interest_rates[i], time_to_maturity[i], isCall));

        std::cout<<"Price :" <<option_prices[i]<<"\tstrike:  "<<strike<<"\tstock: "<< stock_prices[i] <<"\tIV: " << \
        op.implied_volatility(option_prices[i], strike, stock_prices[i], interest_rates[i], time_to_maturity[i], isCall)\
        << "\tinterest: "<<interest_rates[i]<< "\ttime: "<<time_to_maturity[i]<< endl;

        double bsm_delta = op.Black_Scholes_Option_Delta(stock_prices[i], time_to_maturity[i], implied_volatility[i], interest_rates[i], strike, isCall);
        delta.push_back(bsm_delta);
        pnl.push_back(option_prices[0] - option_prices[i]);
        double portfolioVal;

        if(i < 1)
            portfolioVal = option_prices[i] - delta[i]*stock_prices[i];

        else {
            portfolioVal = delta[i-1]*stock_prices[i] + portfolio[i-1]*exp(interest_rates[i]*dT) - delta[i]*stock_prices[i];
            double hedge_error = delta[i-1]*stock_prices[i] + portfolio[i-1]*exp(interest_rates[i-1]*dT) - option_prices[i];

            hedging_error.push_back(hedge_error);
            pnl_with_hedge.push_back(hedge_error);

        }
        portfolio.push_back(portfolioVal);
    }

    std::ofstream output;
    output.open("results.csv", std::ios_base::app);

    map<string, double>::iterator itr;
    output << "Date,Stock Price, Option Price, Implied Volatility, Delta, Hedging Error, PNL, PNL with hedge (Total Wealth)" << endl;
    int i = 0;
    for (itr = rates_map.begin(); itr != rates_map.end(); ++itr, i++) {
        output << itr->first << "," << stock_prices[i] << "," << option_prices[i] << "," << implied_volatility[i] << "," << delta[i] << "," << hedging_error[i] << "," << pnl[i]<< "," <<pnl_with_hedge[i] << endl;
    }
}

