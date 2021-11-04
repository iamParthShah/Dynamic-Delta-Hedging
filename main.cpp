#include <iostream>
#include <fstream>
#include <ctime>
#include <map>
#include "Option.h"
#include "Stock.h"
#include "Price_Simulator.h"
#include <string>
#include "vector"
#include "Price_Option.h"
#include <bits/stdc++.h>
#include "RealData_Portfolio.h"
#include "testUnit.h"

using namespace std;

int date_check(string date){
// returns 1 if date is in correct format or range
//returns 0 if date is in incorrect format or range
    if (date.size() !=10)
        return 0;

    int delimiter = date.find("-");
    if (delimiter==std::string::npos)
        return 0;

    try {
        int year = stoi(date.substr(0, 4));                         // converts string to integer of the year part
        int month = stoi(date.substr(5, 7));                        // converts string to integer of the month part
        int day = stoi(date.substr(8, 10));                         // converts string to integer of the day part
        if (year < 1919 || year > 2020)                             // year should be from 1919 to 2020
            return 0;
        if (month < 1 || month > 12)                                // month should be between 1 and 12
            return 0;
        if (day <= 1 || day > 31)                                   // day should be from 1 to 31
            return 0;

        return 1;
    } catch (const std::invalid_argument&) {
         return false;
    }
}

double yearsBetweenDates(string date1, string date2){
    stringstream ss(date1 + "-" + date2);
    int year, month, day;
    char hyphen;

    ss >> year >> hyphen >> month >> hyphen >> day;     // Parse the first date into seconds
    struct tm starttm = { 0, 0, 0, day,
                          month - 1, year - 1900 };
    time_t start = mktime(&starttm);

    ss >> hyphen >> year >> hyphen >> month >> hyphen >> day;   // Parse the second date into seconds
    struct tm endtm = { 0, 0, 0, day,
                        month - 1, year - 1900 };
    time_t end_d = mktime(&endtm);
    // Find out the difference and divide it by 86400 to get the number of days
    // divide by 365 to get the difference in years

    return std::difftime(end_d, start) / (31536000);
}

vector<double> maptoVector(map<string, double> anyMap){
    vector<double> returnMap;
    map<string, double>::iterator itr;
    for (itr = anyMap.begin(); itr != anyMap.end(); ++itr){
        returnMap.push_back(itr->second);
    }
    return returnMap;
}

vector<double> getExpiry(map<string, double> anyMap, string expiry){
    vector<double> tmts;
    map<string, double>::iterator itr;
    for (itr = anyMap.begin(); itr != anyMap.end(); ++itr) {
        tmts.push_back(yearsBetweenDates(itr->first, expiry));  // Here will come the getBusinessDay difference function
    }
    return tmts;
}

map<string, double> priceReader(string startDate, string endDate, string path) {
    //Assuming yyyy-mm-dd
    map<string,double> rate_map;
    ifstream infile(path);

    string line;
    getline( infile, line );
    while (getline( infile, line )){
        stringstream current_line(line);
        string token;
        getline(current_line, token, ',');
        string cur_date = token;
        if (yearsBetweenDates(startDate, cur_date) < 0){
            continue;
        }

        if (yearsBetweenDates(endDate, cur_date) > 0){
            break;
        }
        getline(current_line, token, ',');
        rate_map.insert(make_pair(cur_date, stod(token)));
    }
    infile.close();
    return rate_map;
}


map<string, double> optionChainReader(string startDate, string endDate, string expiry, string option_flag, string strike) {
    map<string,double> option_map;
    ifstream infile("./data/op_GOOG.csv");

    string line;
    getline( infile, line );
    while (getline( infile, line )){

        stringstream current_line(line);
        string token;
        getline(current_line, token, ',');
        string cur_date = token;
        if (yearsBetweenDates(startDate, cur_date) < 0){
            continue;
        }

        if (yearsBetweenDates(endDate, cur_date) > 0){
            break;
        }
        getline(current_line, token, ',');
        string ex_date = token;
        getline(current_line, token, ',');
        string op_flag = token;
        getline(current_line, token, ',');
        if (yearsBetweenDates(ex_date, expiry) == 0 && op_flag == option_flag && token == strike) {
            getline(current_line, token, ',');
            double bid = stod(token);
            getline(current_line, token, ',');
            double ask = stod(token);
            option_map.insert(make_pair(cur_date, (bid+ask)/2));

        } else {
            continue;
        }
    }
    infile.close();
    return option_map;
}

int main(){
    cout<<"TESTING...."<<endl;

    testUnit t{};
    t.testing_func();

    cout << "Part 1:" << endl;
    cout << "Simulating Prices and Portfolio PnL" << endl;

    // Stock: Spot price, drift, dividend, rate
    Stock stock{100,0.05, 0.0, 0.025};
    // Option: Strike, volatility, cal//put
    Option option{105,0.24,true};
    int period = 100;
    int paths = 1000;
    double expiry = 0.4;

    // Price simulator object
    Price_Simulator ps{};
    // simulate and store output
    ps.simulate_and_save_results(stock, option, period, paths, expiry);

    cout << "Part 1 completed" << endl;
    cout << "Stock_paths.csv and hedging_errors.csv generated successfully" << endl;
    cout << "\n***********************" << endl;
    cout << "\nPart 2: Testing BSM validity and hedging PNL" << endl;

    std::string window_start;
    std::string window_end;
    std::string expiry_option;
    std::string strike_price;

    cout << "Enter the dates in following format yyyy-mm-dd format without space:" << endl;
    cout << "Enter the start date: " <<endl;
    while(getline(cin, window_start)) {
        if (date_check(window_start) == 0)
            cout << "Please put YYYY-MM-DD format" << endl;
        else{break;}
    }

    cout << "Enter the end date: "<<endl;
    while(getline(cin, window_end)) {

        if (date_check(window_end) == 0)
            cout << "Please put YYYY-MM-DD format" << endl;
        else{break;}
    }

    cout << "Enter the expiry date: "<<endl;
    while(getline(cin, expiry_option)) {
        if (date_check(expiry_option) == 0)
            cout << "Please put YYYY-MM-DD format" << endl;
        else{break;}
    }

    std::cout << "Enter the strike price: "<<endl;
    std::cin >> strike_price;

    map<string, double> stock_prices = priceReader(window_start, window_end, "./data/sec_GOOG.csv");
    map<string, double> option_prices = optionChainReader(window_start,window_end,expiry_option,"C",strike_price);
    map<string, double> interest_rates = priceReader(window_start, window_end, "./data/interest.csv");

    RealData_Portfolio pfolio{};
    pfolio.pnl(maptoVector(interest_rates), maptoVector(stock_prices), maptoVector(option_prices), getExpiry(interest_rates,expiry_option),
                                        stod(strike_price), true, interest_rates);

    cout<< "End of Part 2" <<endl;
    cout<< "Output generated in results.csv"<<endl;
    cout<< "Ending Program..."<<endl;
    return 0;
}
