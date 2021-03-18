#include "i2c_e2p_test.h"
#include <unity/unity.h>

int main(void)
{
  UnityBegin("./i2c_e2p_test.h");
  RUN_TEST(test_e2p_write);

  return (UnityEnd());
}