#include <iostream>
#include <math.h>
#include "../derivative_pricer.hpp"
#include "gtest/gtest.h"

class DerivativePricerTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }
  virtual void TearDown() {
  }
};


// The price of a call minus the price of a put should equal the forward price.
TEST(DerivativePricerTest,PutCallParity){
  DerivativePricer pricer(forward_contract, 2, 0.05, 0.02, 90, 100, 0.05);
  double forward_price = pricer.getPrice();

  pricer.setType(call);
  double call_price = pricer.getPrice();

  pricer.setType(put);
  double put_price = pricer.getPrice();

  EXPECT_EQ(forward_price, call_price - put_price);
}


//TODO value parameterized tests AS PER
//https://github.com/google/googletest/blob/48ee8e98abc950abd8541e15550b18f8f6cfb3a9/googletest/docs/V1_5_AdvancedGuide.md#how-to-write-value-parameterized-tests
// TEST(DerivativePricerTest, CallDecreasingWithStrike){
//   int strike = 3;
//   DerivativePricer pricer(call, 2, 0.05, 0.02, 1, 100, 0.05);
//   double call_price = pricer.getPrice();
//   bool is_price_decreasing = true;
//   while (is_price_decreasing && strike < 10 ) {
//     std::cout << call_price << std::endl;
//     is_price_decreasing = (pricer.getPrice() < call_price);
//     call_price = pricer.getPrice();
//     strike++;
//     pricer.setStrike((double) strike);
//     EXPECT_EQ(true, is_price_decreasing);
//   }
// }
