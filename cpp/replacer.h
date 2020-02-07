// Copyright 2018 FireEye, Inc

#ifndef H_REPLACER
#define H_REPLACER

#include <iostream>
#include <fstream>

class Replacer {
 public:
    	// Swap out all spaces with commas
 		// Right now, this class will replace a
 		// string of spaces with a single comma

    bool fileExists(const char *fileName);
    	// Check to be sure the source is legit

    void replaceText(const char innie = ' ', const char outie = ',');
    	// Replace innie with outie

    Replacer();
        // Default constructor

    Replacer(const char *i, const char *o, const char *d);
    	// Constructor

    ~Replacer();
    	// Destructor

 	std::string inFile;
 	std::string outFile;
 	bool dumpFirstLine;
};

#endif
