/*============================================================================
Name        : StringParserClass.cpp
Author      : wchang 00960978
Prof        : K. Perkins @ CNU
Version     : 26 Oct 2k19
Project	    : cs327 - p4: classes, pointers, libraries
testing args: "../data/testdata_full.txt" "<to>" "</to>" "../output/outfile.txt"
============================================================================*/

#include <string>
#include <string.h>
#include <vector>
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

			string data = pDataToSearchThru;
			int start = 0;
			int end = 0;

			while (start != string::npos) {
				start = data.find(pStartTag, start + 1);
				end = data.find(pEndTag, start + 1);
				if (start != string::npos & end != string::npos)
					myVector.push_back(data.substr(start + strlen(pStartTag), (end - (start + strlen(pStartTag)))));
			}
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


		int StringParserClass::findTag(char *pTagToLookFor, char *&pStart, char *&pEnd) {
			// this function never gets used/tested
			// return values make it a useless helper function
			if(!pStart || !pEnd)
				return ERROR_TAGS_NULL;

			string look_in = pStart;
			int finder = look_in.find(pTagToLookFor);
			if(finder == string::npos)
				return FAIL;
			pStart = pStart + finder;
			pEnd = pStart + strlen(pTagToLookFor);
			return SUCCESS;
		}

