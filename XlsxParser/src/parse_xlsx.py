#!/usr/bin/env python3
# -*- coding: UTF-8 -*-
'''
Description: 导表工具
version: 1.0.0
Author: modnarshen
Date: 2021/01/19 21:19:57
LastEditors: modnarshen
LastEditTime: 2021/04/09 10:00:08
'''
import sys
import os

# PYTHON_VERSION
# OS_PLATFORM

NUM_TYPES = set(('int32', 'uint32', 'int64', 'uint64', 'float'))
BASIC_DATA_TYPES = set(('bool', 'int32', 'uint32', 'string'))
EXTEND_DATA_TYPES = set(('struct'))

class Field(object):
    def __init__(self):
        pass

def read_data():
    pass

def main():
    for item in BASIC_DATA_TYPES:
        print(item)
    pass

if __name__ == '__main__':
    main()
