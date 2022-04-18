#include "IODictionary.h"


IODictionary::IODictionary(std::string path, std::string fileName)
:
    path_(path),
    fileName_(fileName)
{}


const std::string& IODictionary::Path() const
{
    return path_;
}

const std::string& IODictionary::Name() const
{
    return fileName_;
}

bool IODictionary::setPath (std::string& newPath)
{
    path_ = newPath;

    return true;
}

int  IODictionary::countCharactersInString(const std::string& line)
{
    int nchars{0};

    for (unsigned i = 0; i < line.length(); i++)
    {
        if (line[i] != ' ') 
        {
            nchars++;
        }
    }

    return nchars;
}


std::vector<std::string> IODictionary::splitString(const std::string& line, char delimiter) {
    
    std::stringstream ss(line);

    std::string word;

    std::vector<std::string> result;

    while (getline(ss, word, delimiter))
    {
        if (word.size() != 0)
        {
            // Remove white spaces
            word.erase(remove_if(word.begin(), word.end(), isspace), word.end());
            
            // push to vector
            result.push_back(word);
        }

    }
    return result;
}


void IODictionary::errorMessage(std::ifstream& in_file, std::string message, int lineCounter, bool turnOfLinePrinting)
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


void IODictionary::checkSemiColon (std::ifstream& in_file, std::string& line, const int& lineCounter)
{
        // Check if ; it at the end of the sentance
    if ((line.find( ';' ) == std::string::npos))
    {
        errorMessage(in_file, "Missing ';' ", lineCounter);
    }
}


void IODictionary::readCharacter(std::ifstream& in_file, std::istringstream& iss, const char C, const int& lineCounter)
{
    char c1;

    iss >> c1;

    // If something is wrong, warn the user and shutdown program
    if (iss.fail() || c1 != C)
    {

        std::string message = "Missing ";
        message += C;
        message += " ";

        errorMessage(in_file, message, lineCounter);
    }
}


std::string IODictionary::stripSingleComment(std::string& line)
{
    // strips from the string '//' onwards
    line=line.substr(0, line.find("//"));

    return line;
}


std::string IODictionary::stripBlockComment(std::ifstream& in_file, std::string& line, int& lineCounter)
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


std::string IODictionary::stripComments(std::ifstream& in_file, std::string& line, int& lineCounter)
{
    if(line.find( "//" ) != std::string::npos)
    {
        line = stripSingleComment(line);
    }
    else if (line.find( "/*" ) != std::string::npos)
    {
        line = stripBlockComment(in_file, line, lineCounter);
    }

    return line;
}

void IODictionary::newLineAndUpdateSStream(std::ifstream& in_file, std::istringstream& iss, std::string& line, int& lineCounter, bool updateStringStream)
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

    if (updateStringStream)
    {
        // Update string stream
        iss.clear();
        iss.str(line);
    }
}


void IODictionary::vectorFormatError(std::ifstream& in_file, int lineCounter)
{
    std::string errorMessage = "Problem with vector format on line ";
    errorMessage +=  std::to_string(lineCounter);

    // Closes the file
    in_file.close();

    // Throws exception to stop the program.
    throw std::runtime_error(errorMessage);
};

double IODictionary::readScalarData(std::ifstream& in_file, std::istringstream& iss, std::string& line, int lineCounter)
{

    line = stripComments(in_file, line, lineCounter);

    // update string stream
    iss.clear();
    iss.str(line);

    // Store data
    double scalar;

    iss >> scalar;

    // If something is wrong with string stream warn the user
    if (iss.fail())
    {
        errorMessage(in_file, "Problem reading scalar ", lineCounter);
    }
    
    return scalar;
}

std::string IODictionary::readString(std::ifstream& in_file, std::istringstream& iss, std::string& line, int lineCounter, bool semiColumCheck = true)
{

    if (semiColumCheck)
    {
        checkSemiColon(in_file, line, lineCounter);
        
        // Remove semicolum
        line.erase(std::remove(line.begin(), line.end(), ';'), line.end());

    }

    line = stripComments(in_file, line, lineCounter);

    // Remove empty spaces
    line.erase(remove_if(line.begin(), line.end(), isspace), line.end());

    // update string stream
    iss.clear();
    iss.str(line);

    // Store data
    std::string store;

    iss >> store;

    // If something is wrong with string stream warn the user
    if (iss.fail())
    {
        errorMessage(in_file, "Problem reading scalar ", lineCounter);
    }
    
    return store;
}

bool IODictionary::checkExactMatch(const std::string& line,const std::string& keyWord){
    
    // Check if string has a partial match
    std::size_t index = line.find(keyWord);

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

    bool checkCharactersBefore = not_part_of_word(index-1);
    bool checkCharactersAfter =  not_part_of_word(index+keyWord.size());
   
    return checkCharactersBefore && checkCharactersAfter;
}


double IODictionary::findScalar( const std::string& path, const std::string& fileName, const std::string& keyword)
{
    double scalar{-1};

    // File location path
    std::string fileLocation = path+fileName;

    // Passes the file location path into a ifsteam
    std::ifstream in_file(fileLocation.c_str());

    // Checks if file is to be open correctly
    if(!in_file.is_open())
    {
        std::cerr << "The input file was not open correctly!" << std::endl;
        //return 1;
    }

    // Line to store input from file
    std::string line;

    // Line counter for error reporting
    int lineCounter=0;

    // Sets a stringstream to get information from string
    std::istringstream iss (line);

    bool foundKeyWord = false;

    // Read file
    while (!in_file.eof() && !foundKeyWord)
    { 
        // Updates lines 
        newLineAndUpdateSStream(in_file, iss, line, lineCounter);

        if(checkExactMatch(line, keyword))
        {
            // check ; syntax
            checkSemiColon(in_file,line, lineCounter);
            // Remove semicolum
            line.erase(std::remove(line.begin(), line.end(), ';'), line.end());

            // Remove keyword from string
            line = line.substr(line.find(keyword) + keyword.length()); 

            // Read scalar
            scalar = readScalarData(in_file, iss, line, lineCounter);

            foundKeyWord = true;
        }
    }

    if(in_file.eof() )
    {
        std::string message = "Keyword " + keyword + " not found in " + fileName;
        errorMessage(in_file, message, 0, true);
    }

    return scalar;
}

std::string IODictionary::findAsString( const std::string& path, const std::string& fileName, const std::string& keyword)
{
    std::string store;

    // File location path
    std::string fileLocation = path+fileName;

    // Passes the file location path into a ifsteam
    std::ifstream in_file(fileLocation.c_str());

    // Checks if file is to be open correctly
    if(!in_file.is_open())
    {
        std::cerr << "The input file was not open correctly!" << std::endl;
        //return 1;
    }

    // Line to store input from file
    std::string line;

    // Line counter for error reporting
    int lineCounter=0;

    // Sets a stringstream to get information from string
    std::istringstream iss (line);

    bool foundKeyWord = false;

    // Read file
    while (!in_file.eof() && !foundKeyWord)
    { 
        // Updates lines 
        newLineAndUpdateSStream(in_file, iss, line, lineCounter);
        
        if(checkExactMatch(line, keyword))
        {

            // Remove keyword from string
            line = line.substr(line.find(keyword) + keyword.length()); 

            // Read scalar
            store = readString(in_file, iss, line, lineCounter);

            foundKeyWord = true;
        }
    }

    if(in_file.eof() )
    {
        std::string message = "Keyword " + keyword + " not found in " + fileName;
        errorMessage(in_file, message, 0, true);
    }

    return store;
}

std::map<std::string, std::string> IODictionary::readHeader( const std::string& path, const std::string& fileName)
{
    std::map<std::string, std::string> store;

    // File location path
    std::string fileLocation = path+fileName;

    // Passes the file location path into a ifsteam
    std::ifstream in_file(fileLocation.c_str());

    // Checks if file is to be open correctly
    if(!in_file.is_open())
    {
        std::cerr << "The input file was not open correctly!" << std::endl;
        //return 1;
    }

    // Line to store input from file
    std::string line;

    // Line counter for error reporting
    int lineCounter=0;

    // Sets a stringstream to get information from string
    std::istringstream iss (line);

    bool endCycle = false;

    // Read file
    while (!endCycle && !in_file.eof() )
    { 
        // Updates lines 
        newLineAndUpdateSStream(in_file, iss, line, lineCounter);
        
        if(checkExactMatch(line, std::string("FoamFile")))
        {

            // Updates lines 
            newLineAndUpdateSStream(in_file, iss, line, lineCounter);

            // check if parenthesis exists '('
            char c1;
            iss >> c1;

            // If something is wrong, warn the user and shutdown program
            if (iss.fail() || c1 != '{')
            {
                errorMessage(in_file, "Missing '{' ", lineCounter);
            }

            bool endCurlyBraces = false;

            while (!endCurlyBraces && !in_file.eof() )
            {
                // Updates lines 
                newLineAndUpdateSStream(in_file, iss, line, lineCounter, true);

                iss >> c1;
                if (c1 == '}')
                {
                    endCurlyBraces = true;
                    endCycle = true;
                    continue;
                }

                if (checkExactMatch(line, "dimensions") || checkExactMatch(line, "internalField") || checkExactMatch(line, "boundaryField") || c1 =='{' )
                {
                    errorMessage(in_file, "Missing '}' at the end of 'FoamFile' header", lineCounter, true);
                }

                checkSemiColon(in_file, line, lineCounter);

                // Remove ';' at the end
                line.erase(std::remove(line.begin(), line.end(), ';'), line.end());
                
                // Split string by spaces
                std::vector<std::string> tmp =  splitString(line, ' ');

                if(tmp.size() > 2)
                {
                    errorMessage(in_file, "More than entries on header ", lineCounter);
                }

                store.insert ( std::pair<std::string, std::string>(tmp[0] ,tmp[1] ) );
            }
        }
    }

    if(in_file.eof() )
    {
        std::string message = "There is no header in " + fileName;
        errorMessage(in_file, message, 0, true);
    }

    return store;
}



