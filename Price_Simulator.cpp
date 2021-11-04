#include "Price_Simulator.h"
#include "Stock.h"
#include "Option.h"
#include "Price_Option.h"
#include <random>
#include <fstream>
#include <iostream>

using namespace std;

Price_Simulator::Price_Simulator(){
    //constructor
}

Price_Simulator::~Price_Simulator(){
    //destructor
}

double Price_Simulator::simulate_and_save_results(Stock &stock, Option& option, int period, int total_paths, double time_to_maturity) {
    std::default_random_engine generator;
    std::normal_distribution<double> normal(0.0,1.0);

    Price_Option op{};

	double dT = time_to_maturity/period;
    double simulated_price[period+1], call_price[period+1], delta[period+1], hedging_error[period+1], portfolio[period+1];
    simulated_price[0] = stock.Getspot();
    call_price[0] = op.Black_Scholes_Option_Price(option, stock, time_to_maturity);
    delta[0] = op.Black_Scholes_Option_Delta(option, stock, time_to_maturity);
    hedging_error[0] = call_price[0] - delta[0]*simulated_price[0];
    std::ofstream myFile;
    myFile.open("hedging_error.csv", std::ios_base::app);
    std::ofstream sample_path_file;
    sample_path_file.open("stock_path.csv", std::ios_base::app);
    std::ofstream option_file;
    option_file.open("option_path.csv", std::ios_base::app);

    std::ofstream pfolio;
    pfolio.open("pfolio.csv", std::ios_base::app);

    cout << delta[0] << " " << call_price[0] << " " << simulated_price[0] << endl;
    while (total_paths--) {
        for(int i = 1; i <= period ;i++) {

            double normalVar = normal(generator);
            simulated_price[i] = simulated_price[i-1]*(1.0 + stock.Getdrift()*dT + option.Getsigma()*sqrt(dT)*normalVar);
            stock.Setspot(simulated_price[i]);
            call_price[i] = op.Black_Scholes_Option_Price(option, stock, time_to_maturity - (i+1)*dT);
            delta[i] = op.Black_Scholes_Option_Delta(option, stock, time_to_maturity - (i+1)*dT);
            hedging_error[i] = delta[i-1]*simulated_price[i] + hedging_error[i-1]*exp(stock.Getrate()*dT) - delta[i]*simulated_price[i];
            portfolio[i] = delta[i-1]*simulated_price[i] + hedging_error[i-1]*exp(stock.Getrate()*dT) - call_price[i];
            sample_path_file << to_string(simulated_price[i]) << ",";
            option_file<<to_string(call_price[i]) <<",";
            myFile<<to_string(portfolio[i])<<",";
        }
        sample_path_file << std::endl;
        option_file<<std::endl;
        myFile<<std::endl;
        pfolio << to_string(portfolio[period-1]) << std::endl;
    }
}
