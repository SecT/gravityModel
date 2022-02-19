#include <vector>

#include <gtest/gtest.h>
#include "myLib.h"

using std::vector;

//GS note: it seems that tests can't be found/run if the file contains main().
// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");

  //fun2();
  vector<float> exampleConfig;
  readFromFile(exampleConfig, "testReadFile_input.txt");

  EXPECT_EQ(exampleConfig[0], 1);
  EXPECT_EQ(exampleConfig[1], 2);
  EXPECT_EQ(exampleConfig[2], 5);
  EXPECT_EQ(exampleConfig[3], 7);
  EXPECT_EQ(exampleConfig[4], 7);
  EXPECT_EQ(exampleConfig[5], 9);
  EXPECT_EQ(exampleConfig[6], 11);

  // Expect equality.
  //EXPECT_EQ(7 * 6, 42);
}
