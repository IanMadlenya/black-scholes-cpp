#ifndef DERIVATIVE_PRICER_H
#define DERIVATIVE_PRICER_H

enum InstrumentType {
  forward_contract,
  call,
  put,
  binary_call,
  binary_put,
  zero_coupon_bond
};

class DerivativePricer {
private:
  InstrumentType ins_type;
  double T;                  // Time to maturity.
  double r;                  // Continuously compounding rate.
  double d;                  // Dividend rate.
  double K;                  // Strike price.
  double S;                  // Spot price.
  double sigma;              // Volatility.
  double func_d(int sign);   // Needed in black-scholes formula. Takes -1 or 1.
  double cum_norm(double x);  // Cumulative normal function.
public:
  DerivativePricer(InstrumentType ins_type, double T, double r, double d, double K, double S, double sigma);
  float getPrice();
  void setType(InstrumentType ins_type);
};

#endif
