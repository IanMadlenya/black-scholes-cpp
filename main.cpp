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
    int T;                    // Time to maturity.
    float r;                  // Continuously compounding rate.
    float d;                  // Dividend rate.
    float K;                  // Strike price.
    float S;                  // Spot price.
    float sigma;              // Volatility.
    double func_d(int sign);   // Needed in black-scholes formula. Takes -1 or 1.
    double cum_norm(double x);  // Cumulative normal function.

  public:
    DerivativePricer(InstrumentType ins_type, float T, float r, float d, float K, float S, float sigma);
    float getPrice();
};

DerivativePricer::DerivativePricer(InstrumentType _ins_type, float _T, float _r, float _d, float _K, float _S, float _sigma){
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

  double K = 1.0 / (1.0 + 0.2316419 * fabs(d));

  double cnd = RSQRT2PI * exp(- 0.5 * d * d) *
        (K * (A1 + K * (A2 + K * (A3 + K * (A4 + K * A5)))));

  if (d > 0)
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
    return S * exp(r * T) - ((S*d) * exp(r * T) );
  }

  /*
   * Call option pricing.
   */
  if (ins_type == call) {
    return S * cum_norm(func_d(1)) - K * exp(-r * T) * cum_norm(func_d(-1));
  }
  return 1.0;
}


int main(int argc, char const *argv[]) {
  DerivativePricer fwd(forward_contract, 1, 0.05, 0.02, 90, 100, 0.1);
  DerivativePricer call_opt(call, 1, 0.05, 0.02, 90, 100, 0.1);

  std::cout << "Forward Price: " << fwd.getPrice() << std::endl;
  std::cout << "Call Option: " << call_opt.getPrice() << std::endl;

  return 0;
}