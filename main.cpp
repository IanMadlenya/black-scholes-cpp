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

float get_price(
    InstrumentType ins_type,
    int T,        // Time to maturity.
    float r,      // Continuously compounding rate.
    float d,      // Dividend rate.
    float K,      // Strike price.
    float S,      // Spot price.
    float sigma   // Volatility.
  ) {

  /*
   * Forward contract pricing.
   * Formula for fwd pricing: F = S * e^(rT) - sum( d[i] * e^(r(T-t[i])) )
   * However, this assumes that the dividend is continuous.
   */
  if (ins_type == forward_contract) {
    return S * exp(r * T) - ((S*d) * exp(r * T) );
  }

  return 0.00;
}

int main(int argc, char const *argv[]) {
  float fwd_price = get_price(forward_contract, 1, 0.05, 0.02, 90, 100, 0.1);
  std::cout << "fwd: " << fwd_price << std::endl;
  return 0;
}
