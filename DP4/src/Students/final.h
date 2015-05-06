/*
 * final.h
 *
 *  Created on: May 5, 2015
 *      Author: aldgoff
 */

#ifndef DP4_SRC_STUDENTS_FINAL_H_
#define DP4_SRC_STUDENTS_FINAL_H_

string to_string(int n) {
	char str[80];
	sprintf(str, "%d", n);
	return str;
}
int stoi(const string& str) {
	return atoi(str.c_str());
}

						// Note: typically what they missed.
#include "carlos.h"		// Excellent - punctuation, runSize, Poly, Synthetics, dtors.
#include "jason.h"		// Perfect - dtors.
//#include "roger.h"		// Folder
#include "jasonr.h"		// Used shared_ptr, unique_ptr, etc.
#include "srujan.h"		// Perfect - duplicated hello/aloha, dtors.
//#include "norm.h"		// Folder
#include "sergio.h"		// Excellent - minor white space, dtors.
#include "jeff.h"		// Used unique_ptr.
#include "mohamed.h"	// Fails - on order #3, even after fixing 4 warnings.
#include "chao.h"		// Used shared_ptr.
#include "solti.h"		// Used unique_ptr.
#include "rohit.h"		// Used shared_ptr.
#include "yong.h"		// Excellent - missed 'separate', PET cleaning, propcorn, oiled, but caught Null Observers, dtors.


#endif /* DP4_SRC_STUDENTS_FINAL_H_ */
