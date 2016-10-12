#include "../derivative_pricer.hpp"
#include "gtest/gtest.h"

class DerivativePricerTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }
  virtual void TearDown() {
  }
};

TEST(DerivativePricerTest,PutCallParity){
  DerivativePricer pricer(forward_contract, 2, 0.05, 0.02, 90, 100, 0.05);
  double forward_price = pricer.getPrice();

  pricer.setType(call);
  double call_price = pricer.getPrice();

  pricer.setType(put);
  double put_price = pricer.getPrice();

  EXPECT_EQ(forward_price, call_price - put_price);
}
