#include <iostream>
#include <math.h>
#include "../derivative_pricer.hpp"
#include "gtest/gtest.h"

class DerivativePricerTest : public ::testing::Test {
};

class DerivativePricerTestWithParam : public ::testing::TestWithParam<double>{
};


// The price of a call minus the price of a put should equal the forward price.
TEST(DerivativePricerTest,PutCallParity){
  DerivativePricer pricer(forward_contract, 2, 0.05, 0.02, 90, 100, 0.05);
  double forward_price = pricer.getPrice();

  pricer.setType(call);
  double call_price = pricer.getPrice();

  pricer.setType(put);
  double put_price = pricer.getPrice();

  EXPECT_FLOAT_EQ(forward_price, call_price - put_price);
}


// The price of a call should be monotone decreasing with strike.
TEST_P(DerivativePricerTestWithParam,Strike){
  DerivativePricer pricer(call, 2, 0.05, 0.02, GetParam(), 100, 0.05);
  EXPECT_EQ(1,10);
  // TODO No way to get the 'previous' value of the test to ensure value decreases
}
INSTANTIATE_TEST_CASE_P(CallDecreasingWithStrike,
  DerivativePricerTestWithParam,
  ::testing::Values(0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100)
);



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
