/*
 * @Author: modnarshen
 * @Date: 2022/05/09 14:45:51
 * @LastEditors: modnarshen
 * @Description:
 */
#include "test.h"

#include "util/timer.h"

bool TestPbcUtil() {
    std::cout << "test pbc util" << std::endl;
    return true;
}

static auto ret = FuncTester::GetInst().RegisterTestCase("test_pbc_util", TestPbcUtil);
