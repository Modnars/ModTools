/*
 * @version: UAMobile 2022.0715
 * @Author: modnarshen
 * @Date: 2022/05/09 14:44:24
 * @LastEditors: modnarshen
 * @Description:
 */
#include <iomanip>
#include <iostream>
#include <memory>

#include "pbc.h"
#include "pbc_printer.h"
#include "util/timer.h"

void InitSharedPtr(std::shared_ptr<int> &p) {
    p = std::make_shared<int>(100);
    std::cout << "local p: " << p << std::endl;
}

int main(int argc, char *argv[]) {
    pbc::Timer timer;
    timer.begin();
    for (uint32_t i = 0; i < 1'000'000U; ++i)
        ;
    // $A µs.
    std::cout << "use time: " << timer.use_time<pbc::time::microseconds>().count() << " µs." << std::endl;
    for (uint32_t i = 0; i < 1'000'000U; ++i)
        ;
    timer.end();
    // $B µs.
    std::cout << "use time: " << timer.use_time<pbc::time::microseconds>().count() << " µs." << std::endl;
    for (uint32_t i = 0; i < 1'000'000U; ++i)
        ;
    // $B µs.
    std::cout << "use time: " << timer.use_time<pbc::time::microseconds>().count() << " µs." << std::endl;
    timer.end();
    // $C µs.
    std::cout << "use time: " << timer.use_time<pbc::time::microseconds>().count() << " µs." << std::endl;

    std::cout << "use time: "
              << std::chrono::duration_cast<pbc::time::seconds>(timer.use_time<pbc::time::microseconds>()).count()
              << " s." << std::endl;

    std::shared_ptr<int> p = nullptr;
    InitSharedPtr(p);
    std::cout << p << std::endl;
    if (p)
        std::cout << "p->val: " << *p << std::endl;

    timer.begin();
    auto tt = std::time(nullptr);
    std::cout << std::put_time(std::localtime(&tt), "%F %T") << std::endl;
    std::cout << timer.use_time<std::chrono::microseconds>().count() << " µs." << std::endl;

    return 0;
}
