/*
 * @Author: modnarshen
 * @Date: 2022/05/17 16:09:25
 * @LastEditors: modnarshen
 * @Description: 封装的宏定义
 */
#pragma once

#include "printer.h"

#define COND_EXP(condition, expr, ...) \
    {                                  \
        if (condition) {               \
            expr;                      \
        }                              \
    }

#define COND_EXP_DLOG(condition, expr, ...) \
    {                                       \
        if (condition) {                    \
            OUTPUT_DEBUG(__VA_ARGS__);      \
            expr;                           \
        }                                   \
    }

#define COND_EXP_ILOG(condition, expr, ...) \
    {                                       \
        if (condition) {                    \
            OUTPUT_INFO(__VA_ARGS__);       \
            expr;                           \
        }                                   \
    }

#define COND_EXP_ELOG(condition, expr, ...) \
    {                                       \
        if (condition) {                    \
            OUTPUT_ERROR(__VA_ARGS__);      \
            expr;                           \
        }                                   \
    }

#define COND_RET(condition, ...) \
    {                            \
        if (condition) {         \
            return __VA_ARGS__;  \
        }                        \
    }

#define COND_RET_DLOG(condition, ret_code, ...) \
    {                                           \
        if (condition) {                        \
            OUTPUT_DEBUG(__VA_ARGS__);          \
            return ret_code;                    \
        }                                       \
    }

#define COND_RET_ILOG(condition, ret_code, ...) \
    {                                           \
        if (condition) {                        \
            OUTPUT_INFO(__VA_ARGS__);           \
            return ret_code;                    \
        }                                       \
    }

#define COND_RET_ELOG(condition, ret_code, ...) \
    {                                           \
        if (condition) {                        \
            OUTPUT_ERROR(__VA_ARGS__);          \
            return ret_code;                    \
        }                                       \
    }
