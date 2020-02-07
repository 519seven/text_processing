// Copyright 2018 FireEye, Inc.

/*
  Include directly the different
  headers from cppconn/ and mysql_driver.h + mysql_util.h
  (and mysql_connection.h). This will reduce your build time!
*/
#include "mysql++/mysql++.h"
#include "mysql_connection.h"

#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"

#include <iostream>
#include <exception>
#include <string>
#include <limits>

#include "replacer.h"

using namespace sql::mysql;

// Prototype the functions
void runProgram();
std::string checkInputStr(std::string m, std::string i);

void runProgram() {
	std::string iname;
	std::string oname;
	std::string fline;

	Replacer r;
	// Scrub the text file removing spaces and replacing with commas
	try {
		do {
			// Get user input
			iname = checkInputStr("Enter file to convert to csv", iname);
			oname = checkInputStr("Enter filename of your new file", oname);
			fline = checkInputStr("Would you like to process the first line? [y/n]", fline);
			const char *i = iname.c_str();
			const char *o = oname.c_str();
			const char *f = fline.c_str();
			try {
				r = Replacer(i, o, f);
				break;
			} catch(...) {
				std::cout << "Try again..." << std::endl;
			}
		} while (true);
		// Now, take scrub the input and write the output
		r.replaceText(' ', ',');
		std::cout << "Finished processing!" << std::endl;
	} catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}
	// Next, connect to mysql and import into its own table
	//try {
	//	sql::Driver *driver;
	//	sql::Connection *con;
	//	sql::Statement *stmt;
	//	sql::ResultSet *res;

		// Create a connection
		//driver = get_driver_instance();
		//con = driver->connect("tcp://127.0.0.1:3306", "root", "!sd5hg8u!");
		// Connect to the MySQL cve database;
		//con->setSchema("cve");

		//stmt = con->createStatement();
		//res = stmt->executeQuery("SELECT * from product;");
		//while (res->next()) {
		//	std::cout << "\t... MySQL replies: ";
			/* Access column data by alias or column name */
		//	std::cout << res->getString("_message") << std::endl;
		//	std::cout << "\t... MySQL says it again: ";
			/* Access column data by numeric offset, 1 is the first column */
		//	std::cout << res->getString(1) << std::endl;
		//}
		//delete res;
		//delete stmt;
		//delete con;
	//} catch (sql::SQLException &e) {
	//	std::cout << "# ERR: SQLException in " << __FILE__;
	//	std::cout << "(" << __FUNCTION__ << ") on line "
	//			<< __LINE__ << std::endl;
	//	std::cout << "# ERR: " << e.what();
	//	std::cout << " (MySQL error code: " << e.getErrorCode();
	//	std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	//}

}

int main () {
	runProgram();
}

std::string checkInputStr(std::string strMsg, std::string iStr) {
	std::string i;
	while (true) {
		std::cout << strMsg;
		if (iStr != "") { std::cout << " [" << iStr << "]"; }
		std::cout << ": ";
		std::cin >> i;
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "The value entered does not appear to be a valid string.\n"
						<< "Try again.\n"
						<< std::endl;
		} else {
			return i;
		}
	}
}
