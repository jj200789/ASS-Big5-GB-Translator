//
//  Codec.cpp
//
//  Created by Sam Lam on 15/7/2018.
//  Copyright © 2018 LamSam. All rights reserved.
//

#include "Codec.hpp"

#include <uchardet/uchardet.h>

#include <fstream>
#include <codecvt>

extern "C" {
    #include <stdio.h>
    #include <string.h>
}

namespace conv {
    #include <iconv.h>
}


#define BUFFER_SIZE 4096

char *fileToBytes(string &path, long &size, size_t offset) {
    FILE *f = fopen(path.c_str(), "rb");
    fseek(f, 0, SEEK_END);
    size = ftell(f) - offset;
    fseek(f, offset, SEEK_SET);
    
    char *dst = (char *)malloc(size + 1);
    fread(dst, size, 1, f);
    fclose(f);
    return dst;
}

void byteToFile(string &path, char *content, size_t offset) {
    unsigned char utf8BOM[] = { 0xEF,0xBB,0xBF };
    
    string out;
    out.assign(content, offset);
    
    fstream f;
    f.open(path.c_str(), ios::out|ios::binary);
    f.write((char*)utf8BOM, sizeof(utf8BOM));
    f << out;
    f.close();
}

string Codec::detect(string path) {
    FILE *f = fopen(path.c_str(), "r");
    if(f == NULL) { return string("Cannot open file"); }

    string result = checkFromBOM(f);
    if(result != "")
        return result;

    result = checkFromSta(f);

    return result;
}

string Codec::checkFromBOM(FILE *f) {
    for(map<string, vector<char>>::iterator it = codes.begin(); it != codes.end(); it++) {
        const size_t size = (it->second).size();
        char header[5] = {0};
        fseek(f, 0, SEEK_SET);
        fread(header, 1, size, f);
        if(strcmp(header, (it->second).data()) == 0)
            return it->first;
    }
    return "";
}

string Codec::checkFromSta(FILE *f) {
    char buffer[BUFFER_SIZE];
    fseek(f, 0, SEEK_SET);
    uchardet_t handle = uchardet_new();
    while(1) {
        if(feof(f)) break;
        size_t len = fread(buffer, 1, BUFFER_SIZE, f);
        int retval = uchardet_handle_data(handle, buffer, len);
        if (retval != 0)
            return string("error");
    }
    uchardet_data_end(handle);
    
    const char *charset = uchardet_get_charset(handle);
    string result;
    if(*charset)
        result = string(charset);
    else
        result = string("error");
    
    uchardet_delete(handle);
    
    return result;
}

int Codec::convertToUTF8(string &path, string &fromCode) {
    conv::iconv_t cv = conv::iconv_open("UTF-8", fromCode.c_str());
    if(cv == (conv::iconv_t)-1)
//        cout << "Fail to convert UTF-8 from " << fromCode << endl;
        return -1;

    long fsize;
    char *content = fileToBytes(path, fsize, codes[fromCode].size());
    
    size_t in_bytes_left = fsize;
    size_t out_bytes_left = in_bytes_left * 2 + 1;
    
    std::string out(out_bytes_left, '\0');
    char* out_buf_start = const_cast<char*>(out.c_str());
    char* out_buf_ptr = out_buf_start;
    
    int rc = conv::iconv(cv, &content, &in_bytes_left, &out_buf_ptr, &out_bytes_left);
    if(rc == -1)
        return -1;

    conv::iconv_close(cv);
    
    byteToFile(path, out_buf_start, fsize * 3 + 1 - out_bytes_left);
    
    return 0;
}
