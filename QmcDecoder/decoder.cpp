// Name   : QmcDecoder/decoder.cpp
// Author : Modnar
// Date   : 2020/02/18
// Copyrights (c) 2020 Modnar. All rights reserved.

#include <map>
#include <ctime>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>

namespace {
    const std::map<std::string, std::string> __SUFFIX = {
        {"qmc0", "mp3"},
        {"qmcogg", "ogg"},
        {"qmcflac", "flac"}
    };
    const std::vector<unsigned char> __MAP = {
        0x77, 0x48, 0x32, 0x73, 0xDE, 0xF2, 0xC0, 0xC8, 0x95, 0xEC, 
        0x30, 0xB2, 0x51, 0xC3, 0xE1, 0xA0, 0x9E, 0xE6, 0x9D, 0xCF, 
        0xFA, 0x7F, 0x14, 0xD1, 0xCE, 0xB8, 0xDC, 0xC3, 0x4A, 0x67, 
        0x93, 0xD6, 0x28, 0xC2, 0x91, 0x70, 0xCA, 0x8D, 0xA2, 0xA4, 
        0xF0, 0x08, 0x61, 0x90, 0x7E, 0x6F, 0xA2, 0xE0, 0xEB, 0xAE, 
        0x3E, 0xB6, 0x67, 0xC7, 0x92, 0xF4, 0x91, 0xB5, 0xF6, 0x6C, 
        0x5E, 0x84, 0x40, 0xF7, 0xF3, 0x1B, 0x02, 0x7F, 0xD5, 0xAB, 
        0x41, 0x89, 0x28, 0xF4, 0x25, 0xCC, 0x52, 0x11, 0xAD, 0x43, 
        0x68, 0xA6, 0x41, 0x8B, 0x84, 0xB5, 0xFF, 0x2C, 0x92, 0x4A, 
        0x26, 0xD8, 0x47, 0x6A, 0x7C, 0x95, 0x61, 0xCC, 0xE6, 0xCB, 
        0xBB, 0x3F, 0x47, 0x58, 0x89, 0x75, 0xC3, 0x75, 0xA1, 0xD9, 
        0xAF, 0xCC, 0x08, 0x73, 0x17, 0xDC, 0xAA, 0x9A, 0xA2, 0x16, 
        0x41, 0xD8, 0xA2, 0x06, 0xC6, 0x8B, 0xFC, 0x66, 0x34, 0x9F, 
        0xCF, 0x18, 0x23, 0xA0, 0x0A, 0x74, 0xE7, 0x2B, 0x27, 0x70, 
        0x92, 0xE9, 0xAF, 0x37, 0xE6, 0x8C, 0xA7, 0xBC, 0x62, 0x65, 
        0x9C, 0xC2, 0x08, 0xC9, 0x88, 0xB3, 0xF3, 0x43, 0xAC, 0x74, 
        0x2C, 0x0F, 0xD4, 0xAF, 0xA1, 0xC3, 0x01, 0x64, 0x95, 0x4E, 
        0x48, 0x9F, 0xF4, 0x35, 0x78, 0x95, 0x7A, 0x39, 0xD6, 0x6A, 
        0xA0, 0x6D, 0x40, 0xE8, 0x4F, 0xA8, 0xEF, 0x11, 0x1D, 0xF3, 
        0x1B, 0x3F, 0x3F, 0x07, 0xDD, 0x6F, 0x5B, 0x19, 0x30, 0x19,
        0xFB, 0xEF, 0x0E, 0x37, 0xF0, 0x0E, 0xCD, 0x16, 0x49, 0xFE, 
        0x53, 0x47, 0x13, 0x1A, 0xBD, 0xA4, 0xF1, 0x40, 0x19, 0x60, 
        0x0E, 0xED, 0x68, 0x09, 0x06, 0x5F, 0x4D, 0xCF, 0x3D, 0x1A, 
        0xFE, 0x20, 0x77, 0xE4, 0xD9, 0xDA, 0xF9, 0xA4, 0x2B, 0x76, 
        0x1C, 0x71, 0xDB, 0x00, 0xBC, 0xFD, 0x0C, 0x6C, 0xA5, 0x47, 
        0xF7, 0xF6, 0x00, 0x79, 0x4A, 0x11 
    };
}

inline
unsigned char mapmap(std::vector<unsigned char>::size_type i) {
    i = (i > 0x8000) ? i%0x7FFF : i;
    return __MAP[(i*i+80923)%256];
}

void string_replace(std::string &source, const std::string &srcstr, 
        const std::string &dststr) {
    std::string::size_type pos = 0, srclen = srcstr.size(), dstlen = dststr.size();
    while ((pos = source.find(srcstr, pos)) != std::string::npos) {
        source.replace(pos, srclen, dststr);
        pos += dstlen;
    }
}

inline 
std::string file_full_name(const std::string &file_path) {
    std::string local_file_path = std::string(file_path);
    string_replace(local_file_path, "\\", "/");
    auto pos = local_file_path.find_last_of('/') + 1;
    return local_file_path.substr(pos);
}

int decode(const std::string &file_path, const std::string &output_dir) {
    std::ifstream ins(file_path, std::ios::in | std::ios::binary);
    if (!ins)
        return EXIT_FAILURE;
    std::vector<unsigned char> data;
    for (std::vector<unsigned char>::size_type i = 0; ins; ++i) {
        data.push_back(ins.get());
        data[i] ^= mapmap(i);
    }
    ins.close();
    std::string file_name = file_full_name(file_path);
    std::string file_suffix = file_name.substr(file_name.find_last_of('.')+1);
    auto iter = __SUFFIX.find(file_suffix);
    if (iter == __SUFFIX.end())
        return EXIT_FAILURE;
    else
        file_suffix = std::string(".") + iter->second;
    file_name = file_name.substr(0, file_name.find_last_of('.'));
    std::string output_file_path = (output_dir.back() == '/') ?
        output_dir+file_name+file_suffix : output_dir+"/"+file_name+file_suffix;
    std::ofstream ous(output_file_path, std::ios::binary);
    if (!ous)
        return EXIT_FAILURE;
    ous.write((char *)&data[0], data.size()*sizeof(unsigned char));
    ous.close();
    return EXIT_SUCCESS;
}

int main(int argc, const char *argv[]) {
    if (argc == 2) {
        std::string line = "", 
            src_path = argv[1],
            logging_path = src_path.substr(0, src_path.find_last_of('.')) + ".log";
        std::ifstream ins(src_path);
        std::ofstream ous(logging_path);
        std::vector<std::string> filenames;
        int exit_status = EXIT_SUCCESS;
        while (std::getline(ins, line)) {
            if (line.size() == 0)
                break;
            if (line[0] == '#')
                continue;
            filenames.push_back(line);
        }
        if (filenames.size() == 0) {
            std::cerr << "Please make sure the input files!" << std::endl;
            exit_status = EXIT_FAILURE;
        }
        while (std::getline(ins, line)) {
            if (line.size() > 0 && line[0] != '#')
                break;
        }
        if (line.size() == 0 || line[0] == '#') {
            std::cerr << "Please choose the output directory!" << std::endl;
            exit_status = EXIT_FAILURE;
        }
        for (const std::string &file_path : filenames) {
            ous << "Decoding file: " << file_full_name(file_path) << std::endl;
            auto start_time = (unsigned)time(nullptr);
            exit_status |= decode(file_path, line);
            ous << "Done. (Used " << (unsigned)time(nullptr)-start_time 
                      << " seconds)" << std::endl;
        }
        return exit_status;
    } else if (argc == 3) {
        return decode(argv[1], argv[2]);
    } else {
        std::cerr << "Error! Please check the parameters!"
                  << "Usage: " << argv[0] << " source_file destination_dir" 
                  << std::endl;
    }
    return EXIT_FAILURE;
}
