#include "Dictionary.h"

Dictionary::Dictionary(const IOObject& IO)
:
IOObject(IO),
nOpenParenthesis_(0),
finishedReadingSubDicts_(false)
{
   read();
}

void Dictionary::bracketsTest(std::ifstream& in_file)            
{
    
    int openedBracketCounter(0);

    int closedBracketCounter(0);

    unsigned int lineCounter(0);

    std::string line;

    std::istringstream iss(line);

    while (!in_file.eof())
    {
        newLineAndUpdateSStream(in_file, iss, line, lineCounter);
        openedBracketCounter += std::count(line.begin(), line.end(),'{');
        closedBracketCounter += std::count(line.begin(), line.end(),'}');
    }

    if (openedBracketCounter != closedBracketCounter)
    {
        in_file.close();
        std::string message = "Unbalanced number of brackets in the dictionary: " + this->name();
        throw std::runtime_error(message);
    }

    in_file.clear();
    in_file.seekg(0);
}

Dictionary::Dictionary(const Dictionary& dict, bool append)
:
IOObject(dict),
nOpenParenthesis_(dict.nOpenParenthesis_),
finishedReadingSubDicts_(dict.finishedReadingSubDicts_)
{
  if (append)
  {
    localData_ = dict.localData_;
    data_ = dict.data_;
  }  
}

std::string Dictionary::stripSingleComment(std::string& line)
{
    // strips from the string '//' onwards
    line=line.substr(0, line.find("//"));
    return line;
}


std::string Dictionary::stripBlockComment(std::ifstream& in_file, std::string& line, unsigned int& lineCounter)
{
    // Booleans to catch line and block comments
    bool findEndOfBlockComment = false;
    
    if((line.find( "*/" ) != std::string::npos))
    {
        std::string lineBackup=line;

        // strips line
        line=line.substr(0, line.find("/*"));
        lineBackup=lineBackup.substr(lineBackup.find("*/") + 2);
        line+= " "+lineBackup;
        return line;
    }
    // looks for the end of block comment
    while (!findEndOfBlockComment && !in_file.eof())
    {
        getline(in_file, line);
        lineCounter++;
        if((line.find( "*/" ) != std::string::npos))
        {
            findEndOfBlockComment=true;
            getline(in_file, line);
            lineCounter++;
        }
        else
        {
            continue;
        }
    }
    return line;
}

std::string Dictionary::stripComments(std::ifstream& in_file, std::string& line, unsigned int& lineCounter)
{
    bool checkComments=false;

    if(line.find( "//" ) != std::string::npos)
    {
        line = stripSingleComment(line);
        checkComments=true;
    }
    else if (line.find( "/*" ) != std::string::npos)
    {
        line = stripBlockComment(in_file, line, lineCounter);
        checkComments=true;
    }

    if (checkComments)
    {
        line = stripComments(in_file, line, lineCounter);
    }

    return line;
}


void Dictionary::newLineAndUpdateSStream(std::ifstream& in_file, std::istringstream& iss, std::string& line, unsigned int& lineCounter, bool updateStringStream)
{
    getline(in_file, line);
    lineCounter++;

    // Avoid empty lines
    while(line.find_first_not_of(' ') == std::string::npos && !in_file.eof())
    {
        getline(in_file, line);
        lineCounter++;
    }

    line = stripComments(in_file, line, lineCounter);

    trimWhiteSpaces(line);

    if (updateStringStream)
    {
        // Update string stream
        iss.clear();
        iss.str(line);
    }
}

bool Dictionary::checkExactMatch(const std::string& line,const std::string& keyWord) const
{
    // Check if string has a partial match
    const std::size_t index = line.find(keyWord);

    // If it doesn't, return false
    if (index == std::string::npos)
    {
        return false;
    }

    // Create a lambda function to check if there are characters before or after the match string
    // [&line] means to pass line as a reference to the lambda function
   auto not_part_of_word = [&line](unsigned int index)
   {
        if (index < 0 || index >= line.size())
        {
            return true;
        } 
        if (std::isspace(line[index]) || std::ispunct(line[index]))
        {
            return true;
        } 

        return false;
    };

    bool checkCharactersBefore = not_part_of_word( index - 1 );
    bool checkCharactersAfter =  not_part_of_word( index + keyWord.size() );
   
    return checkCharactersBefore && checkCharactersAfter;
}


bool Dictionary::checkCharacter(std::ifstream& in_file, std::istringstream& iss, const char& C)
{
    char c1;

    iss >> c1;

    if (iss.fail() || c1 != C)
    {
        return false;
    }

    return true;
}

void Dictionary::errorMessage(std::ifstream& in_file, const std::string& message, const unsigned int& lineCounter, bool turnOfLinePrinting)
{
    // Error message to the user
    std::string errorMessage = message ;

    if (!turnOfLinePrinting)
    {
        errorMessage += "in line " + std::to_string(lineCounter);
    }

    // Closes the file
    in_file.close();

    // Throws exception to stop the program.
    throw std::runtime_error(errorMessage);
}

void Dictionary::stripString(std::string& line, const std::string& word) const
{
    const std::size_t index = line.find(word);
    if (index != std::string::npos)
    {
        line.erase(index, word.length() );
    }
}

void Dictionary::rightTrimWhiteSpaces(std::string& line)
{
    line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char ch)
    {
        return !std::isspace(ch);
    }).base(), line.end());
}

void Dictionary::leftTrimWhiteSpaces(std::string& line)
{
    line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](unsigned char ch) 
    {
        return !std::isspace(ch);
    }));
}

void Dictionary::trimWhiteSpaces(std::string& line)
{
    leftTrimWhiteSpaces(line);
    rightTrimWhiteSpaces(line);
}

void Dictionary::readSubDict(Dictionary& tmp, std::ifstream& in_file, std::istringstream& iss, std::string& line, unsigned int& lineCounter,const std::string& key)
{
    Dictionary tmp2(tmp, false);

    std::string keyword;

    while ( !tmp2.finishedReadingSubDicts_  && !in_file.eof() )
    {
        int newOpenParenthesis = nOpenParenthesis_; // update number of open parenthesis

        if (line.empty() || std::all_of(line.begin(),line.end(),isspace) ) // If line is empty or with only white spaces
        { 
            newLineAndUpdateSStream(in_file, iss, line, lineCounter, true);
        }
        
        if (!line.empty() 
            && std::count(line.begin(), line.end(), ' ') == 0  
            && line[0] != '}' 
            && line.back() != ';'
            )
        {
            std::string keyword = line;
            newLineAndUpdateSStream(in_file, iss, line, lineCounter, true);
            if (line[0] == '{')
            {
                line.erase(line.find("{"), 1); // erase from the string
                iss.clear(); // clear string stream
                iss.str(line); // update string stream
                nOpenParenthesis_++; // update number of open parenthesis
                readSubDict(tmp2, in_file, iss, line, lineCounter, keyword); // read dictionary
            }
            else
            {
                errorMessage(in_file, "Error while reading dictionary, on line: ", lineCounter);
            }
        }

        // Parse the string
        parseString(line, iss, in_file, tmp2, lineCounter);

        if (nOpenParenthesis_ < newOpenParenthesis)
        {
            newOpenParenthesis = nOpenParenthesis_;
            tmp2.finishedReadingSubDicts_ = true;
        }
    }    

    tmp.data_.emplace(key, tmp2);
}


const Dictionary& Dictionary::subDict(const std::string& dictName) const
{
    if(data_.count(dictName))
    {
        return data_.at(dictName);
    }
    else
    {
        throw std::runtime_error("subdict does not exist!");
    }
}


std::vector<std::string> Dictionary::splitStringByChar(const std::string& line, const char& C)
{
    std::string subString (line);
    std::stringstream ss(line);
    std::vector<std::string> vectorList;

    while(getline(ss, subString, C))
    {
        vectorList.push_back(subString);
    }

    return vectorList;
}

bool Dictionary::read()
{

    // Passes the file location path into a ifsteam
    std::ifstream in_file(this->path().c_str());

    // Checks if file is to be open correctly
    if(!in_file.is_open())
    {
        std::cerr << "The input file was not open correctly!" << std::endl;
        return false;
    }

    bracketsTest(in_file);



    std::string line;

    unsigned int lineCounter(0);

    std::istringstream iss (line);

    nOpenParenthesis_ = 0;

    // Read file
    while ( (nOpenParenthesis_ == 0) && !in_file.eof() )
    { 
    
        newLineAndUpdateSStream(in_file, iss, line, lineCounter);

        if (line.find('{') != std::string::npos)
        {
            nOpenParenthesis_ ++;
        }
        
        if (nOpenParenthesis_ != 0)
        {

            std::string keyword;

            // Split by curly
            std::vector<std::string> vList (splitStringByChar(line,'{'));

            if(vList[0].empty())
            {
                keyword = localData_.back();
                localData_.pop_back();
                line.erase(line.find("{"), 1);
                iss.clear();
                iss.str(line);
            }
            else
            {
                keyword = vList[0];    

                line.clear();

                for(unsigned int i = 1; i<vList.size(); i ++)
                {
                    if (i == 1)
                    {
                        line += vList[i];
                    }
                    else
                    {
                        line += '{' + vList[i];
                    }
                }
                iss.str(line);    
            }
            
            // Remove whitespaces
            trimWhiteSpaces(keyword);
            
            readSubDict(*this, in_file, iss, line, lineCounter, keyword);
        }
        else
        {
            if (!line.empty())
            {
                localData_.push_back(line);
            }
        }
    }

    return true;
}





void Dictionary::parseString (std::string& line, std::istringstream& iss, std::ifstream& in_file, Dictionary& tmp2, unsigned int& lineCounter)
{
    std::string subString;

    std::string lineToAppend;

    int countWords{0};

    bool foundSemicolon (false);
    bool foundEndOfDict (false);

    while( getline(iss, subString, ' ') )
    {
        if (!subString.empty() && !std::all_of(subString.begin(),subString.end(), isspace ) )
        {
            if (subString.find('(') != std::string::npos)
            {
                std::size_t found = line.find('(');

                subString.clear();

                bool foundClosingParenthesis (false);
                for (int i = found; i< line.size(); i++)
                {
                    char c = line[i];
                    if (c != ')')
                    {
                        subString += c;
                    }
                    else
                    {
                        foundClosingParenthesis = true;
                        subString += c;
                        if (std::count(subString.begin(), subString.end(), ')') > 1 || std::count(subString.begin(), subString.end(), '(') > 1) 
                        {
                            std::string message = "Unbalanced number of parenthesis in: " + subString + " ";
                            errorMessage(in_file, message, lineCounter);
                        }
                    }
                }

                if(!foundClosingParenthesis)
                {
                    errorMessage(in_file, "I have an error");
                }
            }
            
            // trim string until semicolon
            if (subString.find(';') != std::string::npos) 
            {
                subString =  subString.substr(0, subString.find(";"));
                line.erase(line.find(subString), subString.length() + 1);
                iss.clear();
                iss.str(line);
                foundSemicolon = true;
            }

            // Catch inline dictionary
            if (subString.find('{') != std::string::npos)
            {
                subString =  subString.substr(0, subString.find('{'));
                if (subString.empty()) // '{' is the first char in the string
                {
                    line.erase(0, line.find('{') + 1);
                    // check valid keyword
                    rightTrimWhiteSpaces(lineToAppend);
                    subString = lineToAppend;
                }
                else
                {
                    line.erase(line.find(subString), subString.length() + 1);
                }
                iss.clear();
                iss.str(line);
                nOpenParenthesis_++;
                readSubDict(tmp2, in_file, iss, line, lineCounter, subString); // read dictionary
                subString=line;
                countWords=0;
            }

            // Catch end of dictionary
            if (subString.find('}') != std::string::npos)
            {
                subString =  subString.substr(0, subString.find('}'));
                if (subString.empty()) // '}' is the first char in the string
                {
                    line.erase(0, line.find('}') + 1);
                }
                else
                {
                    line.erase(line.find(subString), subString.length() + 1);
                }

                iss.clear();
                iss.str(line);
                foundEndOfDict = true;
            }

            // Append to variable and trim from string stream
            if (!subString.empty())
            {
                lineToAppend.append(subString + ' ');
                if(!foundSemicolon)
                {
                    line.erase(line.find(subString), subString.length());
                    iss.clear();
                    iss.str(line);
                }

                countWords++;
            }

            if (countWords == 2)
            {
                if(foundSemicolon)
                {
                    trimWhiteSpaces(lineToAppend);
                    tmp2.localData_.push_back( lineToAppend );
                    countWords=0;
                    foundSemicolon = false;
                    lineToAppend.clear();
                }
                else 
                {
                    // try to catch ; in the next char
                    iss >> std::ws; // remove whitespace from string stream
                    getline(iss, subString, ' ');
                    if (subString[0]==';')
                    {
                        line.erase(0, line.find(';') + 1);
                        tmp2.localData_.push_back( lineToAppend );
                        countWords=0;
                        foundSemicolon = false;
                        lineToAppend.clear();
                    }
                    else
                    {
                        std::string message = "Lack of semicolumn in: " + lineToAppend + " on line ";
                        errorMessage(in_file,  message, lineCounter);
                    }
                }
            }

            if (foundEndOfDict)
            {
                nOpenParenthesis_--;
                return;
            }

        }
    }

    if(countWords == 1)
    {
        if (!foundSemicolon && line.back() != ';')
        {
            // check for dictionary
            std::string keyword = lineToAppend;
            newLineAndUpdateSStream(in_file, iss, line, lineCounter, true);
            if (line[0] == '{')
            {
                line.erase(line.find("{"), 1); // erase from the string
                iss.clear(); // clear string stream
                iss.str(line); // update string stream
                nOpenParenthesis_++; // update number of open parenthesis
                readSubDict(tmp2, in_file, iss, line, lineCounter, keyword); // read dictionary
                countWords=0;
            }
            else
            {
                errorMessage(in_file, "Error while reading dictionary, on line: ", lineCounter);
            }
        }
        else
        {
            std::string message = "Keyword: " + lineToAppend + "without value, on line: ";
            errorMessage(in_file, message, lineCounter);
        }
    }
    
}