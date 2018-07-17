//
//  translator.hpp
//
//  Created by Sam Lam on 15/7/2018.
//  Copyright © 2018 LamSam. All rights reserved.
//

#ifndef translator_h
#define translator_h

#include <opencc/opencc.h>
#include <opencc/SimpleConverter.hpp>

#include "ASSParser.hpp"

using namespace std;

class Translator {
public:
    void translate();
    void setMode(string mode);
    void setConfig(string config);
    void setInputFilePath(string inputFilePath);
    void setOutputFilePath(string outputFilePath);
    void setIsGBK(string isGBK);
    
private:
    opencc::SimpleConverter *sc;
    ASSParser *ass;
    string mode;
    string config;
    string inputFilePath;
    string outputFilePath;
    bool isGBK;
    vector<string> gojuon = {
        u8"あ", u8"か", u8"さ", u8"た", u8"な", u8"は", u8"ま", u8"や", u8"ら", u8"わ", u8"ん",
        u8"い", u8"き", u8"し", u8"ち", u8"に", u8"ひ", u8"み", u8"り",
        u8"う", u8"く", u8"す", u8"つ", u8"ぬ", u8"ふ", u8"む", u8"ゆ", u8"る",
        u8"え", u8"け", u8"せ", u8"て", u8"ね", u8"へ", u8"め", u8"れ",
        u8"お", u8"こ", u8"そ", u8"と", u8"の", u8"ほ", u8"も", u8"よ", u8"ろ", u8"を",
        u8"ア", u8"カ", u8"サ", u8"タ", u8"ナ", u8"ハ", u8"マ", u8"ャ", u8"ラ", u8"ヮ", u8"ン",
        u8"イ", u8"キ", u8"シ", u8"チ", u8"ニ", u8"ヒ", u8"ミ", u8"リ",
        u8"ウ", u8"ク", u8"ス", u8"ツ", u8"ヌ", u8"フ", u8"ム", u8"ュ", u8"ル",
        u8"エ", u8"ヶ", u8"セ", u8"テ", u8"ネ", u8"ヘ", u8"メ", u8"レ",
        u8"オ", u8"コ", u8"ソ", u8"ト", u8"ノ", u8"ホ", u8"モ", u8"ョ", u8"ロ", u8"ヲ",
        u8"が", u8"ざ", u8"だ", u8"ば", u8"ぱ",
        u8"ぎ", u8"じ", u8"ぢ", u8"び", u8"ぴ",
        u8"ぐ", u8"ず", u8"づ", u8"ぶ", u8"ぷ",
        u8"げ", u8"ぜ", u8"で", u8"べ", u8"ぺ",
        u8"ご", u8"ぞ", u8"ど", u8"ぼ", u8"ぽ",
        u8"ガ", u8"ザ", u8"ダ", u8"バ", u8"パ",
        u8"ギ", u8"ジ", u8"ジ", u8"ビ", u8"ピ",
        u8"グ", u8"ズ", u8"ズ", u8"ブ", u8"プ",
        u8"ゲ", u8"ゼ", u8"デ", u8"ベ", u8"ペ",
        u8"ゴ", u8"ゾ", u8"ド", u8"ボ", u8"ポ"
    };
    vector<string> splitString(string &str, string &sym);
    string hasEffect(string &line);
    bool checkGojuon(string &line);
    int translateASS();
    int translateTXT();
    void readFile();
    void writeASS();
};

#endif /* translator_h */
