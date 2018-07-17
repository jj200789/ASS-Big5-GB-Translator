//
//  ASSCommonContent.hpp
//
//  Created by Sam Lam on 15/7/2018.
//  Copyright © 2018 LamSam. All rights reserved.
//

#ifndef ASSCommonContent_h
#define ASSCommonContent_h

#include "ASSContent.hpp"

class ASSCommonContent: public ASSContent {
public:
    void setContent(string &line) override;
    string toString() override;
};

#endif /* ASSCommonContent_h */
