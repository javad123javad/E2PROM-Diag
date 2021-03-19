#include "test/i2c_e2p_test.h"




int main(void)

{

  UnityBegin("./i2c_e2p_test.h");

  

 UnityDefaultTestRun(

 test_e2p_write

 , 

 "test_e2p_write"

 , 7)

                         ;



  return (UnityEnd());

}
