//
//  ASSCommonContent.cpp
//  qqq
//
//  Created by Sam Lam on 15/7/2018.
//  Copyright © 2018 LamSam. All rights reserved.
//

#include "ASSContent.hpp"

void ASSCommonContent::setContent(string &line) {
    vector<string> temp = commonProcess(line);
    if(temp.size() < 1) return;
    tag = temp[0];
    content = temp[1];
}

string ASSCommonContent::toString() {
    if(type == CommentType)
        return line;
    else
        return tag + ": " + content;
}
