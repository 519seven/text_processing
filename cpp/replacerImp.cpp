// Copyright 2018 FireEye, Inc.

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <sys/stat.h>

#include "replacer.h"

// Function: fileExists
/*
   Check if a file exists
@param[in] filename - the name of the file to check

@return true if the file exists, else false
*/
bool Replacer::fileExists(const char *fileName) {
	struct stat buf;
	if (stat(fileName, &buf) != -1) {
		return true;
	}
	return false;
}

void Replacer::replaceText(const char iCh, const char oCh) {
	// iCh is the character I'm looking to replace
	// oCh is the character that is going in its place
	char ch;

	std::ifstream oldFile(inFile.c_str(), std::ios::in);
	std::ofstream newFile(outFile.c_str(), std::ios::out);

	std::string dummy;
	if ( dumpFirstLine ) {
		getline(oldFile, dummy);      // Skip header
	}

	oldFile.get(ch);

	do {
		if (ch == iCh) {
			// if it's a space, replace ALL spaces (loop) with oCh
			while(oldFile.get(ch)) {
				if (ch != iCh) {
					newFile.put(oCh);
					newFile.put(ch);
					break;
				}
			}
		} else {
			newFile.put(ch);
		}
	} while(oldFile.get(ch));
}

// Default constructor
Replacer::Replacer(){
	dumpFirstLine = false;
	inFile = '\0';
	outFile = '\0';
}  // End default constructor

// Constructor
Replacer::Replacer(const char *i, const char *o, const char *dfl) {
	bool endProg = false;

	if (*dfl == 'y' || *dfl == 'Y' || *dfl == '\0')
		dumpFirstLine = false;
	else
		dumpFirstLine = true;

	if (!fileExists(i)) {
		std::cout << "unable to find input file" << std::endl;
		endProg = true;
	}
	if (fileExists(o)) {
		std::cout << "destination filename already exists" << std::endl;
		endProg = true;
	}
	if ( dumpFirstLine != false && dumpFirstLine != true ) {
		std::cout << "unable to validate 'do not process first line' response" << std::endl;
		endProg = true;
	}
	if ( endProg )
		throw std::exception();

	inFile = i;
	outFile = o;
}
// End constructor

// Begin destructor
Replacer::~Replacer() {
	inFile = "";
	outFile = "";
	dumpFirstLine = false;
}
// End desctructor

