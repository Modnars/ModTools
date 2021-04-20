/*
 * @Description:
 * @version: 1.0.0
 * @Author: modnarshen
 * @Date: 2021/04/20 14:26:00
 * @LastEditors: modnarshen
 * @LastEditTime: 2021/04/20 14:47:31
 */

#include <string>

class HttpUtils {
public:
    static std::string UrlEncode(const std::string &url);
    static std::string UrlDecode(const std::string &url);

private:
    static unsigned char toHex(const unsigned char &x) { return x > 9 ? x + 55 : x + 48; }
    static unsigned char fromHex(char c) {
        if ('0' <= c && c <= '9') {
            return c - '0';
        }
        if ('a' <= c && c <= 'f') {
            return c - 'a' + 10;
        }
        if ('A' <= c && c <= 'F') {
            return c - 'A' + 10;
        }
        return 0;
    }
};
