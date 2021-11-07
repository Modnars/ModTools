#!/usr/bin/env python3
# -*- coding: UTF-8 -*-

def ReadCsv(file_path):
    all_data = []
    with open(file_path, 'r', encoding='UTF-8') as f:
        for line in f:
            all_data.append(list(map(lambda x: x.strip(), line[:-1].split(','))))
    return all_data

def main():
    print(ReadCsv('test.csv'))

if __name__ == '__main__':
    main()
