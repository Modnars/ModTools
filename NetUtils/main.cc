/*
 * @Description: 
 * @version: 1.0.0
 * @Author: modnarshen
 * @Date: 2021/04/20 14:49:30
 * @LastEditors: modnarshen
 * @LastEditTime: 2021/04/20 14:53:10
 */
#include <iostream>

#include "libsrc/http_utils.h"

int main(int argc, const char *argv[]) {
    std::cout << HttpUtils::UrlDecode("https://www.google.com.hk/search?q=memset%E5%A4%B4%E6%96%87%E4%BB%B6&ie=utf-8") << std::endl;
    std::cout << HttpUtils::UrlEncode("https://www.google.com.hk/search?q=memset头文件&ie=utf-8") << std::endl;
    return 0;
}
