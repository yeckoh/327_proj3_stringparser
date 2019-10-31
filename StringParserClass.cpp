/*============================================================================
Name        : StringParserClass.cpp
Author      : wchang 00960978
Prof        : K. Perkins @ CNU
Version     : 26 Oct 2k19
Project	    : cs327 - p4: classes, pointers, libraries
testing args: "./data/testdata_full.txt" "<to>" "</to>" "./output/outfile.txt"
============================================================================*/

#include <string>
#include <string.h>
#include <vector>
#include <iostream>
#include "../327_proj3_test/includes/StringParserClass.h"
#include "../327_proj3_test/includes/constants.h"

using namespace std;
using namespace KP_StringParserClass;

		StringParserClass::StringParserClass() {
			pStartTag = NULL;
			pEndTag = NULL;
			areTagsSet = false;

		}

		StringParserClass::~StringParserClass() {
			cleanup();
		}

		int StringParserClass::setTags(const char *pStart, const char *pEnd) {
			if(!pStart || !pEnd)
				return ERROR_TAGS_NULL;

			int length = sizeof(pStart);
			pStartTag = new char[length];
			strcpy(pStartTag, pStart);

			length = sizeof(pEnd);
			pEndTag = new char[length];
			strcpy(pEndTag, pEnd);

			areTagsSet = true;
			return SUCCESS;
		}

		int StringParserClass::getDataBetweenTags(char *pDataToSearchThru, vector<string> &myVector) {
			myVector.clear();
			if(!areTagsSet)	// order confirmed for smash
				return ERROR_TAGS_NULL;
			if(!pDataToSearchThru)
				return ERROR_DATA_NULL;

			int length = strlen(pDataToSearchThru);
			int start_len = strlen(pStartTag);
			int end_len = strlen(pEndTag);

			char* i = pDataToSearchThru;
			char* start_char = 0;
			char* end_char = 0;

			string addition = "";

			// parse and match and add
			while(i != pDataToSearchThru + length) {
				// start matching
				if(start_char == 0) {
					if(!strncmp(i, pStartTag, start_len)) {
						i += start_len;
						start_char = i;
					}
				}

				// end matching, if start isn't found we don't care
				if(end_char == 0 && start_char != 0)
					if(!strncmp(i, pEndTag, end_len))
						end_char = i;

				// found both, start copying
				if(start_char && end_char) {
					i = start_char;
					while(i != end_char) { // string add(start, end) breaks the second time around
						addition += *i;
						++i;
					}
					i += end_len;
					start_char = 0;
					end_char = 0;
					myVector.push_back(addition);
					addition = "";
				}
				else
					++i;
			} // endof while

			return SUCCESS;
		}


		void StringParserClass::cleanup() {
			if(areTagsSet) {
				delete[] pStartTag;
				delete[] pEndTag;
			}
			pStartTag = pEndTag = NULL;
			areTagsSet = 0;
		}


		// this function never gets called/tested so I'm assuming it works just fine
		int StringParserClass::findTag(char *pTagToLookFor, char *&pStart, char *&pEnd) {
			if(!pStart || !pEnd)
				return ERROR_TAGS_NULL;

			int length = strlen(pTagToLookFor);
			pEnd = pStart + length;

			while(*pEnd != '\0') {
				if(!strncmp(pStart, pTagToLookFor, length))
					return SUCCESS;
				++pStart;
				++pEnd;
			}

			return FAIL;
		}

