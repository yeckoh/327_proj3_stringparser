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

			pStartTag = new char(*pStart); // this works on VS_2017
			pEndTag = new char(*pEnd);
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

			int start = data.find(pStartTag);
			int end = data.find(pEndTag);
			data = data.substr(start, (end-start));
			stringstream ss(data);
			char val;
			data = ""; // reuse data as single word string

			do {	// will produce lots of empty strings and include the tag word
				val = ss.get();
				if(val == ' ' || val == '/' || val == '<' || val == '>') {
				//if(val == ' ') {
					myVector.push_back(data);
					data = "";
				}
				else
					data += val;
			}
			while(!ss.eof());

			for(int i = 0;i < myVector.size();++i) {
				if(myVector[i] == ""){
					myVector[i].erase();
					--i;
				}
			}
			return SUCCESS;
		}


		void StringParserClass::cleanup() {
			if(areTagsSet){
				delete pStartTag;
				delete pEndTag;
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
			if(!areTagsSet)
				return ERROR_TAGS_NULL;
			string look_in = pTagToLookFor;
			int start = look_in.find(pStart);
			int end = look_in.find(pEnd,start);
			if(end == string::npos)
				return FAIL;
			look_in = look_in.substr(start, (end-start));
			return SUCCESS;
		}

