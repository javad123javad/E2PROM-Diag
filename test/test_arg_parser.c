#define TEST
#ifdef TEST

#include "unity/unity.h"

#include "arg_parser.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_parse_opt(void)
{
    struct argp_state state;
    arguments_t args= {0};
    state.arg_num=2;
    state.input = &args;

    parse_opt('r',NULL,&state);
    TEST_ASSERT_EQUAL(1, args.read);
    parse_opt('w',NULL,&state);
    TEST_ASSERT_EQUAL(0, args.write);

    args.read = 0;
    args.write = 0;

    parse_opt('w',NULL,&state);
    TEST_ASSERT_EQUAL(1, args.write);
    parse_opt('r',NULL,&state);
    TEST_ASSERT_EQUAL(0, args.read);

}
void test_gen_args(void)
{
    TEST_IGNORE_MESSAGE("Need to Implement arg_parser");
}

#endif // TEST
