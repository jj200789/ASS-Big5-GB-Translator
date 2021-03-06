//
//  ASSParser.cpp
//
//  Created by Sam Lam on 15/7/2018.
//  Copyright © 2018 LamSam. All rights reserved.
//

#include "ASSParser.hpp"

#include <fstream>
#include <iostream>

void ASSParser::parse(string &path) {
    fstream file;
    file.open(path, ios::in);
    file.seekg(3, file.beg);
    string line;
    string section;
    while(getline(file, line)) {
        if(line[0] == '[' && line[line.length()-2] == ']') {
            section = line.substr(1, line.length()-3);
            addSection(section);
        } else if(line.length() < 3) {
            continue;
        } else {
            ASSContent *ass;
            if(section == "Events") ass = new ASSEventContent();
            else ass = new ASSCommonContent();

            ass->setContent(line);
            currentSection->addASSContent(ass);
        }
    }
    file.close();
}

vector<ASSContent *> ASSParser::getContents() {
    return contents;
}

vector<ASSContent *> ASSParser::getContent(string &section) {
    return contents[sectionMap[section]]->getContents();
}

vector<ASSContent *> ASSParser::getContent(const char *section) {
    string str = string(section);
    return getContent(str);
}

void ASSParser::addSection(string &section) {
    sectionMap[section] = (int)sectionMap.size();
    ASSContent *sectionContent = new ASSContent();
    sectionContent->setContent(section);
    contents.push_back(sectionContent);
    currentSection = sectionContent;
}
