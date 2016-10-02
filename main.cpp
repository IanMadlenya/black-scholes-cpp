#include <iostream>
#include <math.h>

class DerivativePricer {
  enum InstrumentType {
    forward_contract,
    call,
    put,
    binary_call,
    binary_put,
    zero_coupon_bond
  };

  private:
    InstrumentType ins_type;
    int T;        // Time to maturity.
    float r;      // Continuously compounding rate.
    float d;      // Dividend rate.
    float K;      // Strike price.
    float S;      // Spot price.
    float sigma;  // Volatility.

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

float DerivativePricer::getPrice(){
  return 1.00;
}


int main(int argc, char const *argv[]) {
  // float fwd_price = get_price(forward_contract, 1, 0.05, 0.02, 90, 100, 0.1);
  // std::cout << "fwd: " << fwd_price << std::endl;
  std::cout << "yo" << std::endl;
  return 0;
}
