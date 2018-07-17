//
//  ASSEventContent.cpp
//
//  Created by Sam Lam on 15/7/2018.
//  Copyright © 2018 LamSam. All rights reserved.
//

#include "ASSContent.hpp"

void ASSEventContent::setContent(string &line) {
    vector<string> temp = commonProcess(line);
    if(temp.size() < 1) return;
    tag = temp[0];
    content = temp[1];
    
    size_t sfound = 0;
    size_t found = content.find(",");
    string t[] = {"","","","","","","","","",""};

    for(int i = 0; i < 9; i++) {
        t[i] = content.substr(sfound, found-sfound);
        sfound = found + 1;
        found = content.find(",", sfound);
    }
    t[9] = content.substr(sfound, content.length()-sfound);
    
    layer = t[0];
    start = t[1];
    end = t[2];
    style = t[3];
    name = t[4];
    marginL = t[5];
    marginR = t[6];
    marginV = t[7];
    effect = t[8];
    text = t[9];
}

string ASSEventContent::toString() {
    if(type == CommentType)
        return line;
    else
        return tag + ": " +  layer + "," +
               start + "," + end + "," + style + "," + name + "," +
               marginL + "," + marginR + "," + marginV + "," +
               effect + "," + text;
}
