/*
 * @Description:
 * @version: 1.0.0
 * @Author: modnarshen
 * @Date: 2021/04/20 14:35:34
 * @LastEditors: modnarshen
 * @LastEditTime: 2021/04/20 14:56:56
 */

#include <cstring>

#include "http_utils.h"

std::string HttpUtils::UrlEncode(const std::string &url) {
    std::string res;
    for (size_t ix = 0; ix < url.size(); ix++) {
        unsigned char buf[4];
        memset(buf, 0, 4);
        if (('0' <= url[ix] && url[ix] <= '9') || ('a' <= url[ix] && url[ix] <= 'z') ||
            ('A' <= url[ix] && url[ix] <= 'Z') || '.' == url[ix] || '-' == url[ix] || '_' == url[ix]) {
            buf[0] = url[ix];
        } else {
            buf[0] = '%';
            buf[1] = toHex((unsigned char)url[ix] >> 4);
            buf[2] = toHex((unsigned char)url[ix] % 16);
        }
        res += (char *)buf;
    }
    return res;
}

std::string HttpUtils::UrlDecode(const std::string &url) {
    std::string res;
    for (size_t ix = 0; ix < url.size();) {
        if (url[ix] == '%' && ix + 2 < url.size()) {
            char c = fromHex(url[ix + 1]);
            c = c * 16 + fromHex(url[ix + 2]);
            res += c;
            ix += 3;
        } else {
            res += url[ix];
            ix += 1;
        }
    }
    return res;
}
