#include <stdio.h>
#include <iostream>
#include "testUnit.h"
#include "math.h"
#include "Stock.h"
#include "Option.h"
#include "Price_Option.h"

using namespace std;

testUnit::testUnit(){
    //ctor
}

testUnit::~testUnit(){
    //dtor
}

void testUnit::testCallPrice(){

    Stock stock{100,0, 0.0, 0.01};
    Option option{80,0.3,true};
    Price_Option op{};

    // calculating for the same values from online calculator
    // gives call value of $20.2 and delta value of 0.998

    if((round(op.Black_Scholes_Option_Price(option, stock, 0.136) *10)/10)==20.2) {
        std::cout << "Passed Call Price Test" << endl;
     }
      else{
        std::cout << "Failed Call Price Test" << endl;
     }

    if((round(op.Black_Scholes_Option_Delta(option, stock, 0.136) *100)/100) == 0.98) {
        std::cout << "Passed Call Delta Value Test" << endl;
    }
    else{
        std::cout << "Failed Call Delta Value Test" << endl;
     }
    //stock price is way more then strike price, the delta of call option approaches 1
    Stock stock1{100000,0, 0.0, 0.01};
    Option option1{80,0.3,true};
    Price_Option op1{};

    if(op1.Black_Scholes_Option_Delta(option1, stock1, 0.136)== 1.0) {
        std::cout << "Passed Call Delta Value Test S>>K should be 1" << endl;
    }
    else{
        std::cout << "Failed Call Delta Value Test S>>K should be 1" << endl;
     }

     //stock price is way less then strike price, the delta of call option approaches 0
    Stock stock2{1,0, 0.0, 0.01};
    Option option2{80,0.3,true};
    Price_Option op2{};

    if(op2.Black_Scholes_Option_Delta(option2, stock2, 0.136)== 0.0) {
        std::cout << "Passed Call Delta Value Test S<<K  should be 0" << endl;
    }
    else{
        std::cout << "Failed Call Delta Value Test S<<K  should be 0" << endl;
     }

    //stock price goes to 0, price of call option approaches 0
    Stock stock3{0,0, 0.0, 0.01};
    Option option3{80,0.3,true};
    Price_Option op3{};

    if(op3.Black_Scholes_Option_Price(option3, stock3, 0.136)== 0.0) {
        std::cout << "Passed Call Delta Value Test S==0  should be 0" << endl;
    }
    else{
        std::cout << "Failed Call Delta Value Test S==0  should be 0" << endl;
    }

}

void testUnit::testCallImpliedVol(){
    std::cout << "Stock Price=100, Strike Price=80, volatility=0.3, Time to Maturity=0.136, Riskfree Rate=1%" <<endl;
    std::cout << "Call Value 20.18"<< endl;
    Stock stock{100,0, 0.0, 0.01};
    Option option{80,0.3,true};
    Price_Option op{};
    double vol1;
	vol1 = op.implied_volatility(20.1862, 80,100,0.01, 0.136,true);

	std::cout << "With corresponding value of Call, it should give nearly same volatility which we used as 0.3" << endl;
    std::cout << "using Call the Bisection Method gives the volatility as:" << vol1 << endl;
}
int testUnit::testing_func(){

    std::cout <<"TestCases for the Call Price and Delta Functionality"<< endl;
    testCallPrice();
    std::cout <<"Test cases done for the Call Price and Delta Functionality"<<endl;
    std::cout << "\n***********************" << endl;

    std::cout <<"TestCases for the Implied Volatility Functionality"<< endl;
    testCallImpliedVol();
    std::cout <<"Test cases done for the Implied Volatility Functionality"<<endl;
    std::cout << "\n***********************" << endl;


    return 0;
}
