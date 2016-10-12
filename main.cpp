#include <iostream>
#include "derivative_pricer.hpp"

int main(int argc, char const *argv[]) {
  DerivativePricer pricer(forward_contract, 2, 0.05, 0.02, 90, 100, 0.05);

  std::cout << "Forward Price: " << pricer.getPrice() << std::endl;
  pricer.setType(call);
  std::cout << "Call Option: " << pricer.getPrice() << std::endl;
  pricer.setType(put);
  std::cout << "Put Option: " << pricer.getPrice() << std::endl;

  return 0;
}
