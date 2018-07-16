//
//  ASSParser.hpp
//  qqq
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
    map<string, vector<ASSContent*>> getContents();
private:
    map<string, vector<ASSContent*>> contents;
};

#endif /* ASSParser_hpp */
