#include <gtest/gtest.h>
#include "Body.h"

//GS note: it seems that tests can't be found/run if the file contains main(). 
// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  
  //fun2();
  
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}