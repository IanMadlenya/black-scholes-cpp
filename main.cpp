#include <iostream>
#include <math.h>

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
    double T;                    // Time to maturity.
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

DerivativePricer::DerivativePricer(InstrumentType _ins_type, double _T, double _r, double _d, double _K, double _S, double _sigma){
  ins_type = _ins_type;
  T = _T;
  r = _r;
  d = _d;
  K = _K;
  S = _S;
  sigma = _sigma;
}

double DerivativePricer::cum_norm(double x) {
  const double       A1 = 0.31938153;
  const double       A2 = -0.356563782;
  const double       A3 = 1.781477937;
  const double       A4 = -1.821255978;
  const double       A5 = 1.330274429;
  const double RSQRT2PI = 0.39894228040143267793994605993438;

  double K = 1.0 / (1.0 + 0.2316419 * fabs(x));

  double cnd = RSQRT2PI * exp(- 0.5 * x * x) *
        (K * (A1 + K * (A2 + K * (A3 + K * (A4 + K * A5)))));

  if (x > 0)
      cnd = 1.0 - cnd;

  return cnd;
}

double DerivativePricer::func_d(int sign) {
  return (log(S/K)+(r+((0.5 * sigma * sigma)*sign)*T)) / (sigma*sqrt(T));
}

float DerivativePricer::getPrice() {
  /*
   * Forward contract pricing.
   */
  if (ins_type == forward_contract) {
    return exp(-r*T) * (exp((r-d)*T)*S-K);
  }

  /*
   * Call option pricing.
   */
  if (ins_type == call) {
    return S * cum_norm(func_d(1)) - K * exp(-r * T) * cum_norm(func_d(-1));
  }

  /*
   * Put option ppricing.
   */
  if (ins_type == put) {
    return -S * cum_norm(-func_d(1)) + K * exp(-r * T) * cum_norm(-func_d(-1));
  }

  return 1.0;
}

void DerivativePricer::setType(InstrumentType _ins_type) {
  ins_type = _ins_type;
}

int main(int argc, char const *argv[]) {
  DerivativePricer pricer(forward_contract, 2, 0.05, 0.02, 90, 100, 0.05);

  std::cout << "Forward Price: " << pricer.getPrice() << std::endl;
  pricer.setType(call);
  std::cout << "Call Option: " << pricer.getPrice() << std::endl;
  pricer.setType(put);
  std::cout << "Put Option: " << pricer.getPrice() << std::endl;

  return 0;
}
