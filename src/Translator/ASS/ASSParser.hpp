//
//  ASSParser.hpp
//
//  Created by Sam Lam on 15/7/2018.
//  Copyright © 2018 LamSam. All rights reserved.
//

#ifndef ASSParser_hpp
#define ASSParser_hpp

#include <map>

#include "ASSContent.hpp"

using namespace std;

class ASSParser {
public:
    void parse(string &path);
    vector<ASSContent *> getContents();
    vector<ASSContent *> getContent(string &section);
    vector<ASSContent *> getContent(const char *section);
private:
    ASSContent *currentSection;
    map<string, int> sectionMap;
    vector<ASSContent *> contents;
    void addSection(string &section);
};

#endif /* ASSParser_hpp */
