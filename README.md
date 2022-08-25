# Dynamic-Delta-Hedging

Implementing a dynamic delta hedging strategy for google stock. Delta-hedging is a hedging strategy that aims to replicate the payoff of a financial derivative, written on a traded asset through dynamically updating a the number of shares of the underlying asset and risk free security. The project is implemented in C++ keeping object oriented design considerations in mind. The delta hedging process:

  1. At t0, we sell a European call option contract with expiration date T, strike price K. Assuming the option is written on one share of stock and t0 < tN ≤ T.
  2. To hedge the short position in the European call and replicate a portfolio of similar payoff, we decide to buy δ shares of the underlying stock at t_0, where δ = ∂V      ∂S is the rate of change of option value V with respect to changes in the underlying price S.
  3. As δ changes during the hedging period, we need to re-balance our portfolio everyday. Denoting δi as value of δ on ith day of the trading, Every δi has to be      calculated using implied volatility for each date.
  4. Cumulative hedging error p/l for strategy: HEi = δi−1Si + Bi−1 exp(ri−1∆t) − Vi where Bi = δi−1Si + Bi−1exp(ri−1δt) − δiSi (i ≥ 1) and B0 = V0 − δ0S0. Si, Vi, ri denoting the stock price, option price, risk-free rate at time ti , i. ∆t represents 1 business day, which is 1/252 year.
  5. The model used for pricing option is the Black)Scholes model, where the underlying stock moves in the following fashion: Use the following model to simulate the price series {S0, S∆t, S2∆t, · · · , ST } at N equally-spaced time points over time horizon [0, T] where ∆t = T/N: St+∆t = St + µSt∆t + σSt*(√∆t)*Zt,

With some initial conditions, generate 100 sample paths (simulations), price delta, hedging error for each of them for every day, and calculate a final P/L for each path. (Result generated in the output csv files)
Use the real market data from given files in the data folder, calculate Implied volatility, delta, hedging error everyday for the real time market data everyday for a given observation window.
Calculate implied volatility smile for options with different Strike price
