//
//  Codec.hpp
//  qqq
//
//  Created by Sam Lam on 15/7/2018.
//  Copyright © 2018 LamSam. All rights reserved.
//

#ifndef Codec_hpp
#define Codec_hpp

#include <string>
#include <map>
#include <vector>

using namespace std;

class Codec {
public:
    string detect(string path);
    int convertToUTF8(string &path, string &fromCode);
private:
    map<string, vector<char>> codes = {
        {"UTF-8", { (char)0xFF, (char)0xBB, (char)0xBF }},
        {"UTF-16BE", { (char)0xFE, (char)0xFF/*, (char)0x00*/ }},
        {"UTF-16LE", { (char)0xFF, (char)0xFE }},
        {"UTF-32BE", { (char)0x00, (char)0x00, (char)0xFE, (char)0xFF }},
        {"UTF-32LE", { (char)0xFF, (char)0xFE, (char)0x00, (char)0x00 }},
        {"GB18030", { (char)0x84, (char)0x31, (char)0x95, (char)0x33 }}
    };
    string checkFromMap(FILE *f);
    string checkFromLib(FILE *f);
};

#endif /* Codec_hpp */
