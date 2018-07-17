//
//  ASSEventContent.h
//
//  Created by Sam Lam on 15/7/2018.
//  Copyright © 2018 LamSam. All rights reserved.
//

#ifndef ASSEventContent_h
#define ASSEventContent_h

#include "ASSContent.hpp"

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

#endif /* ASSEventContent_h */
