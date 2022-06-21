#ifndef Dictionary_H
#define Dictionary_H

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream> 
#include <algorithm>
#include <regex>
#include "IOObject.h"


class Dictionary
:
public IOObject
{

    public:
        Dictionary(const IOObject& IO);
        Dictionary(const Dictionary& dict, bool append);

        
        std::string stripSingleComment(std::string& line);
        std::string stripBlockComment(std::ifstream& in_file, std::string& line, unsigned int& lineCounter);
        std::string stripComments(std::ifstream& in_file, std::string& line, unsigned int& lineCounter);
        void newLineAndUpdateSStream(std::ifstream& in_file, std::istringstream& iss, std::string& line, unsigned int& lineCounter, bool updateStringStream=false);

        void errorMessage(std::ifstream& in_file, const std::string& message, const unsigned int& lineCounter=0, bool turnOffLinePrinting=false);
        bool checkCharacter(std::ifstream& in_file, std::istringstream& iss, const char& C);

        bool checkExactMatch(const std::string& line, const std::string& keyWord) const;

        void stripString(std::string& line, const std::string& word) const;

        void rightTrimWhiteSpaces(std::string& line);
        void leftTrimWhiteSpaces(std::string& line);
        void trimWhiteSpaces(std::string& line);

        std::vector<std::string> splitStringByChar(const std::string& line, const char& C);

        bool read();
        bool clear();
        void bracketsTest(std::ifstream& in_file);
        void readSubDict(Dictionary& tmp, std::ifstream& in_file, std::istringstream& iss, std::string& line, unsigned int& lineCounter, const std::string& key);
        void parseString (std::string& line, std::istringstream& iss, std::ifstream& in_file, Dictionary& tmp2, unsigned int& lineCounter);

        // Utility function
        const Dictionary& subDict(const std::string& dictName) const;
        
        template <typename T>
        T lookup(const std::string& keyWord) const;

    private:
        int  nOpenParenthesis_;
        bool finishedReadingSubDicts_;

       std::vector<std::string> localData_;
       std::map<std::string, Dictionary> data_;

};

#include "DictionaryI.h"

#endif 

