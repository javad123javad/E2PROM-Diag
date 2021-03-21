/* AUTOGENERATED FILE. DO NOT EDIT. */

/*=======Automagically Detected Files To Include=====*/
#include "unity.h"
#include "cmock.h"
#include "mock_i2c_e2p.h"
#include "mock_i2c_ll.h"

int GlobalExpectCount;
int GlobalVerifyOrder;
char* GlobalOrderError;

/*=======External Functions This Runner Calls=====*/
extern void setUp(void);
extern void tearDown(void);
extern void test_i2c_e2p_open(void);
extern void test_i2c_e2p_close(void);
extern void test_i2c_e2p_read(void);
extern void test_i2c_e2p_write(void);
extern void test_i2c_e2p_read_write(void);


/*=======Mock Management=====*/
static void CMock_Init(void)
{
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
  GlobalOrderError = NULL;
  mock_i2c_e2p_Init();
  mock_i2c_ll_Init();
}
static void CMock_Verify(void)
{
  mock_i2c_e2p_Verify();
  mock_i2c_ll_Verify();
}
static void CMock_Destroy(void)
{
  mock_i2c_e2p_Destroy();
  mock_i2c_ll_Destroy();
}

/*=======Test Reset Options=====*/
void resetTest(void);
void resetTest(void)
{
  tearDown();
  CMock_Verify();
  CMock_Destroy();
  CMock_Init();
  setUp();
}
void verifyTest(void);
void verifyTest(void)
{
  CMock_Verify();
}

/*=======Test Runner Used To Run Each Test=====*/
static void run_test(UnityTestFunction func, const char* name, UNITY_LINE_TYPE line_num)
{
    Unity.CurrentTestName = name;
    Unity.CurrentTestLineNumber = line_num;
#ifdef UNITY_USE_COMMAND_LINE_ARGS
    if (!UnityTestMatches())
        return;
#endif
    Unity.NumberOfTests++;
    UNITY_CLR_DETAILS();
    UNITY_EXEC_TIME_START();
    CMock_Init();
    if (TEST_PROTECT())
    {
        setUp();
        func();
    }
    if (TEST_PROTECT())
    {
        tearDown();
        CMock_Verify();
    }
    CMock_Destroy();
    UNITY_EXEC_TIME_STOP();
    UnityConcludeTest();
}

/*=======MAIN=====*/
int main(void)
{
  UnityBegin("test_i2c_e2p.c");
  run_test(test_i2c_e2p_open, "test_i2c_e2p_open", 21);
  run_test(test_i2c_e2p_close, "test_i2c_e2p_close", 30);
  run_test(test_i2c_e2p_read, "test_i2c_e2p_read", 35);
  run_test(test_i2c_e2p_write, "test_i2c_e2p_write", 55);
  run_test(test_i2c_e2p_read_write, "test_i2c_e2p_read_write", 58);

  CMock_Guts_MemFreeFinal();
  return UnityEnd();
}
