#ifndef REALDATA_PORTFOLIO_H
#define REALDATA_PORTFOLIO_H
#include <map>
#include "vector"

using namespace std;

class RealData_Portfolio
{
    public:
        RealData_Portfolio();
        virtual ~RealData_Portfolio();
        void pnl(vector<double> interest_rates, vector<double> stock_prices, vector<double> option_prices, vector<double> time_to_maturity, double strike, bool isCall, map<string, double> rates_map);

    protected:

    private:
};

#endif // REALDATA_PORTFOLIO_H

