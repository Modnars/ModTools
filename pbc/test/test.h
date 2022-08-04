/*
 * @Author: modnarshen
 * @Date: 2022/05/10 18:55:27
 * @LastEditors: modnarshen
 * @Description:
 */
#pragma once

#include <functional>
#include <iostream>
#include <map>
#include <string>

#include "util/macro.h"
#include "util/singleton.h"

class FuncTester : public pbc::Singleton<FuncTester> {
public:
    using TestFunc = std::function<bool()>;

public:
    bool RegisterTestCase(const std::string &name, TestFunc func) {
        COND_RET(test_cases_.find(name) != test_cases_.end(), false);
        test_cases_.insert({name, func});
        return true;
    }

private:
    std::map<std::string, TestFunc> test_cases_;
};

// #define TEST_CASE(case_name)
//     bool check_##case_name();
//     if (!FuncTester::GetInst().RegisterTestCase(#case_name, check_##case_name)) {
//         std::cerr << "register test func failed|case_name:" << #case_name << std::endl;
// }
