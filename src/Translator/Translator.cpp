//
//  main.cpp
//  cctest
//
//  Created by LamSam on 6/6/2017.
//  Copyright © 2017年 LamSam. All rights reserved.
//


#include "Translator.hpp"
#include "Codec.hpp"

void Translator::setMode(string mode) {
    this->mode = mode;
}

void Translator::setConfig(string config) {
    this->config = config;
    sc = new opencc::SimpleConverter(config);
}

void Translator::setInputFilePath(string inputFilePath) {
    this->inputFilePath = inputFilePath;
    readFile();
}

void Translator::setOutputFilePath(string outputFilePath) {
    this->outputFilePath = outputFilePath;
}

void Translator::setIsGBK(string isgbk) {
    if (isgbk.find("gbk") != string::npos)
        isGBK = true;
    else
        isGBK = false;
}

void Translator::readFile() {
    Codec c;
    string code = c.detect(inputFilePath);
    if(code != "UTF-8") {
        if(c.convertToUTF8(inputFilePath, code) != 0) {
            cout << "Error in code transfrom" << endl;
            exit(0);
        }
    }
    
    if(mode == "txt") return;
    
    ass = new ASSParser();
    ass->parse(inputFilePath);
}

/*
	classify the effect part and extract them
	it has four situations:
	effect part contains chinese
	{}XXX
	XXX{}XXX
	{}XXX{}XXX
 */
string Translator::hasEffect(string &line) {
    
    // effect part does not contain chinese
    if(line.find("\\fn") == string::npos)
        return sc->Convert(line);
    
    string splitedLine;
    vector<int> subStrLen;
    vector<string> pattern;
    int lineIndex = 0;
    boost::regex reg{ "({\\\\*fn[^}]*})" };
    
    // extract effect part
    boost::sregex_token_iterator patterns(line.begin(), line.end(), reg, 0);
    boost::sregex_token_iterator end;
    for(; patterns != end; patterns++)
        pattern.push_back(*patterns);
    
    // extract statement part
    boost::sregex_token_iterator split(line.begin(), line.end(), reg, -1);
    while(split != end) {
        splitedLine += *split++;
        if (splitedLine.compare("") == 0)
            continue;
        subStrLen.push_back((int)splitedLine.length() - lineIndex);
        lineIndex = (int)splitedLine.length();
    }
    
    splitedLine = sc->Convert(splitedLine);
    
    // {}XXX
    if (subStrLen.size() == 1)
        return pattern.at(0) + splitedLine;
    // XXX{}XXX
    else if (pattern.size() < subStrLen.size()) {
        lineIndex = 0;
        string trablatedLine;
        for(int index = 0; index < pattern.size(); index++) {
            trablatedLine += splitedLine.substr(lineIndex, subStrLen[index]) + pattern[index];
            lineIndex += subStrLen[index];
        }
        trablatedLine += splitedLine.substr(lineIndex, subStrLen[subStrLen.size() - 1]);
        return trablatedLine;
    }
    // {}XXX{}XXX
    else if (pattern.size() == subStrLen.size()) {
        lineIndex = 0;
        string trablatedLine;
        for(int index = 0; index < pattern.size(); index++) {
            trablatedLine += pattern[index] + splitedLine.substr(lineIndex, subStrLen[index]);
            lineIndex += subStrLen[index];
        }
        return trablatedLine;
    }
    return sc->Convert(line);
}

vector<string> Translator::splitString(string &str, string &sym) {
    vector<string> containor;
    string::size_type pos1, pos2;
    pos2 = str.find(sym);
    pos1 = 0;
    while (std::string::npos != pos2) {
        containor.push_back(str.substr(pos1, pos2 - pos1));
        pos1 = pos2 + sym.size();
        pos2 = str.find(sym, pos1);
    }
    if (pos1 != str.length())
        containor.push_back(str.substr(pos1));
    return containor;
}

/*
	define statement is japanese or chinese
	if has more than 20% is GoJuon, it is defined as japanese
 */
bool Translator::checkGojuon(string &line) {
    bool hasGojuon = true;
    float count = 0.0;
    int len = (int)line.size()/6+1;
    for(vector<string>::iterator g_i = gojuon.begin();
        g_i != gojuon.end() && hasGojuon; g_i++) {
        if (line.find(*g_i) != string::npos)
            count += 1;
    }
    if(count / len > 0.2)
        return true;
    else
        return false;
}

void Translator::writeASS() {
    fstream output;
    output.open(outputFilePath, ios::out);
    
    output << "[Script Info]" << '\r' << endl;
    vector<ASSContent*> contents = (ass->getContents())["Script Info"];
    for(int i = 0; i < contents.size(); i++)
        output << contents[i]->toString() << endl;
    output << '\r' << endl;
    
    output << "[Aegisub Project Garbage]" << '\r' << endl;
    contents = (ass->getContents())["Aegisub Project Garbage"];
    for(int i = 0; i < contents.size(); i++)
        output << contents[i]->toString() << endl;
    output << '\r' << endl;
    
    output << "[V4+ Styles]" << '\r' << endl;
    contents = (ass->getContents())["V4+ Styles"];
    for(int i = 0; i < contents.size(); i++)
        output << contents[i]->toString() << endl;
    output << '\r' << endl;
    
    output << "[Events]" << '\r' << endl;
    contents = (ass->getContents())["Events"];
    for(int i = 0; i < contents.size(); i++)
        output << contents[i]->toString() << endl;
    
    output.close();
}

/*
	convert sc to tc in ass/ssa subtitle file
 */
int Translator::translateASS() {
    string line;
    boost::regex reg { "({[^}]*})" };
    boost::smatch found;
    vector<ASSContent*> contents = (ass->getContents())["Events"];
    for(int i = 0; i != contents.size(); i++) {
        ASSEventContent *content = (ASSEventContent *)contents[i];
        
        if(content->tag != "Dialogue") {
            continue;
        }
        
        // cut the timecode and information part of dialogue statement
        if(checkGojuon(content->text) ||
           (content->style).find("JP") != string::npos ||
           (content->style).find("jp") != string::npos) {
            continue;
        }
        
        try {
            // chech has subtitle effect or not
            if (boost::regex_search(line, found, reg))
                content->text = hasEffect(content->text);
            else
                content->text = sc->Convert(content->text);
        }
        catch (exception &e) {
            return -1;
        }
    }
    writeASS();
    return 0;
}

/*
	convert sc to tc in text file
 */
int Translator::translateTXT() {
    string line;
    fstream input, output;
    input.open(inputFilePath, ios::in);
    output.open(outputFilePath, ios::out);
    while(getline(input, line)) {
        if(checkGojuon(line)) {
            output << line << endl;
            continue;
        }
        
        try {
            output << sc->Convert(line) << endl;
        } catch (exception &e) {
            output << "error" << endl;
            input.close();
            output.close();
            return -1; 
        }
    }
    input.close();
    output.close();
    return 0;
}

void Translator::translate() {
    if(mode == "ass")
        translateASS();
    else if(mode == "txt")
        translateTXT();
    else
        return;
}

void Translator::dump() {
    cout << mode << " " << config << " " << inputFilePath << " " << outputFilePath << endl;
}
