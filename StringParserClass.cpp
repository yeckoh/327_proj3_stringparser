/*
 * StringParserClass.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include <iostream>
#include "../327_proj3_test/includes/StringParserClass.h"
#include "../327_proj3_test/includes/constants.h"

using namespace std;
using namespace KP_StringParserClass;

		// constructor
		StringParserClass::StringParserClass() {
			pStartTag = NULL;
			pEndTag = NULL;
			areTagsSet = false;

		}

		//call cleanup to release any allocated memory
		// destructor
		StringParserClass::~StringParserClass() {
			cleanup();
		}

		//these are the start tag and the end tags that we want to find,
		//presumably the data of interest is between them, please make a
		//COPY of what pStartTag and pEndTag point to.  In other words
		//DO NOT SET pStartTag = pStart
		//returns:
		//SUCCESS
		//ERROR_TAGS_NULL if either pStart or pEnd is null
		int StringParserClass::setTags(const char *pStart, const char *pEnd) {
			if(!pStart || !pEnd)
				return ERROR_TAGS_NULL;

			int length = sizeof(pStart);
			pStartTag = new char[length];
			strcpy(pStartTag, pStart);

			length = sizeof(pEnd);
			pEndTag = new char[length];
			strcpy(pEndTag, pEnd);

			//pStartTag = new char(*pStart); // this works on VS_2017
			//pEndTag = new char(*pEnd);
			areTagsSet = true;
			return SUCCESS;
		}

		//First clears myVector
		//going to search thru pDataToSearchThru, looking for info bracketed by
		//pStartTag and pEndTag, will add that info only to myVector
		//returns
		//SUCCESS  finished searching for data between tags, results in myVector (0 or more entries)
		//ERROR_TAGS_NULL if either pStart or pEnd is null
		//ERROR_DATA_NULL pDataToSearchThru is null
		int StringParserClass::getDataBetweenTags(char *pDataToSearchThru, vector<string> &myVector) {
			myVector.clear();
			if(!areTagsSet)	// confirm order of fail conditions during testing
				return ERROR_TAGS_NULL;
			if(!pDataToSearchThru)
				return ERROR_DATA_NULL;

			string data = pDataToSearchThru;

			// take all data and get desired subset
			int start = data.find(pStartTag) + strlen(pStartTag);
			int end = data.find(pEndTag);
			data = data.substr(start, (end-start));
			stringstream ss(data);

			// remove newlines
			// happens in fileIO already, Oof

			// add tokens to vector
			string line = "";
			while(ss >> line) {
				myVector.push_back(line);
			}

			return SUCCESS;
		}


		void StringParserClass::cleanup() {
			if(areTagsSet){
				delete[] pStartTag;
				delete[] pEndTag;
			}
			pStartTag = pEndTag = NULL;
			areTagsSet = 0;
		}

		//Searches a string starting at pStart for pTagToLookFor
		//returns:
		//SUCCESS  found pTagToLookFor, pStart points to beginning of tag and pEnd points to end of tag
		//FAIL did not find pTagToLookFor and pEnd points to 0
		//ERROR_TAGS_NULL if either pStart or pEnd is null
		int StringParserClass::findTag(char *pTagToLookFor, char *&pStart, char *&pEnd) {
			if(!pStart || !pEnd)
				return ERROR_TAGS_NULL;

			string look_in = pStart;
			unsigned int finder = look_in.find(pTagToLookFor);
			if(finder == string::npos)
				return FAIL;
			*pStart = *pStart + finder;
			pEnd = pStart + strlen(pTagToLookFor);
			return SUCCESS;
		}




		// args: "../data/testdata_full.txt" "<to>" "</to>" "../output/outfile.txt"
