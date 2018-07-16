//
//  ASSContent.hpp
//  qqq
//
//  Created by Sam Lam on 15/7/2018.
//  Copyright © 2018 LamSam. All rights reserved.
//

#ifndef ASSContent_h
#define ASSContent_h

#include <vector>
#include <string>

using namespace std;

typedef enum _ {
    ContentType,
    CommentType
} ASSContentType;

class ASSContent {
public:
    string line;
    string tag;
    string content;
    virtual void setContent(string &line) {};
    virtual string toString() { return line; };

protected:
    ASSContentType type;
    vector<string> commonProcess(string &line) {
        this->line = line;
        if(line[0] == ';') {
            type = CommentType;
            return {};
        }
        type = ContentType;
        string sym = ": ";
        return splite(line, sym);
    };
    
    vector<string> splite(string &str, string &sym) {
        vector<string> containor;
        string::size_type pos1 = 0,
        pos2 = str.find(sym);
        while(string::npos != pos2) {
            containor.push_back(str.substr(pos1, pos2 - pos1));
            pos1 = pos2 + sym.size();
            pos2 = str.find(sym, pos1);
        }
        if(pos1 != str.length())
            containor.push_back(str.substr(pos1));
        return containor;
    };
    
    string trim(string &str, string &sym) {
        if (str.empty())
            return str;
        str.erase(0, str.find_first_not_of(sym));
        str.erase(str.find_last_not_of(sym) + 1);
        return str;
    }
    
    string trim(string &str, vector<string> &syms) {
        if (str.empty())
            return str;
        for(string sym : syms) {
            str.erase(0, str.find_first_not_of(sym));
            str.erase(str.find_last_not_of(sym) + 1);
        }
        return str;
    }
};

class ASSCommonContent: public ASSContent {
public:
    void setContent(string &line) override;
    string toString() override;
};

class ASSEventContent: public ASSContent {
public:
    string layer;
    string start;
    string end;
    string style;
    string name;
    string marginL;
    string marginR;
    string marginV;
    string effect;
    string text;
    void setContent(string &line) override;
    string toString() override;
};

#endif /* ASSContent_h */
