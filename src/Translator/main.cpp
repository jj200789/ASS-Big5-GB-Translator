//
//  main.cpp
//
//  Created by Sam Lam on 30/4/2017.
//  Copyright © 2017年 LamSam. All rights reserved.
//

#include "Translator.hpp"
#include "Codec.hpp"

#include <iostream>

using namespace std;

void help() {
    cout << "Help: " << endl;
    cout << "translator [options]" << endl;
    cout << "-m [ass/txt]" << endl;
    cout << "-c config file" << endl;
    cout << "-s source file" << endl;
    cout << "-d destination file" << endl;
    exit(0);
}

int main(int argc, char *argv[]) {
    if (argc < 9)
        help();
    Translator *t = new Translator();
    
    for(int i = 1; i < argc; i++) {
        if(strcmp(argv[i], "-m") == 0)
            t->setMode(argv[++i]);
        else if(strcmp(argv[i], "-c") == 0)
            t->setConfig(argv[++i]);
        else if(strcmp(argv[i], "-s") == 0)
            t->setInputFilePath(argv[++i]);
        else if(strcmp(argv[i], "-d") == 0)
            t->setOutputFilePath(argv[++i]);
        else
            help();
    }
    t->translate();
    return 0;
}
