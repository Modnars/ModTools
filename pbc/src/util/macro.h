/*
 * @Author: modnarshen
 * @Date: 2022/05/17 16:09:25
 * @LastEditors: modnarshen
 * @Description:
 */
#pragma once

#define COND_EXP(condition, expr, ...) \
    {                                  \
        if (condition) {               \
            expr;                      \
        }                              \
    }

#define COND_RET(condition, ...) \
    {                            \
        if (condition) {         \
            return __VA_ARGS__;  \
        }                        \
    }
