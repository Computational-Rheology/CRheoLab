#ifndef IODictionary_H
#define IODictionary_H

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream> 
#include <algorithm>


enum fileAction {
     //Read signature
      MUST_READ=1,
      NO_READ=2
};


class IODictionary
{
    public:
        // Constructor
        IODictionary(std::string path, std::string fileName);
        
        // Destructor
        virtual ~IODictionary(){} ;

        bool setPath (std::string& newPath);
        
    protected:
	
	
	/*!@brief 
	* 
	* This function counts characters in a string:
	*
	* Loops over the string lenght summing all characters if they are not blank spaces. 
	*/     
        int countCharactersInString(const std::string& line);

    /*!@brief 
	* This function splits a string by a delimiter character.
	* 
	* It passes the string into a stringstream() and uses the  getline() function to collect the string (word) sepated by chosen delimiter
	*/  

        std::vector<std::string> splitString(const std::string& line, char delimiter);
    
    /*!@brief 
	* This function presents an error message to the user and throws a runtime_error().
	*
	* It has a boolean argument (named turnOffLinePrinting) that when is defined as "false", will print the line number where the error occured to the user.
	* 
	* The function will close the ifstream before throwing the runTime_error().
	*/  
        void errorMessage(std::ifstream& in_file, std::string message, int lineCounter=0, bool turnOffLinePrinting=false);
        

    /*!@brief 
	* This function checks the existance of semicolons at the end of a line. If it does not find a semicolon, the errorMessage() function will be executed.
	*   
	* It uses the find() function to try to find the semicolon. If it does not find, uses the errorMessage() function to warn the user.
	*/

        void checkSemiColon (std::ifstream& in_file, std::string& line, const int& lineCounter);

    /*!@brief 
	* This function tries to read an character from a stringStream.
	*
	* If there is a problem trying to retrive a character an error will be thrown through the errorMessage() function.   
	*/
        void readCharacter(std::ifstream& in_file, std::istringstream& iss, const char C, const int& lineCounter);
    

    /*!@brief 
	* This function strips single comments from lines. Single comments in a line start with '//'.
	*
	* It finds the location of the first '//' and recovers the string behing it through the function substr()   
	*/
       
        std::string stripSingleComment(std::string& line);
    
    /*!@brief 
	* This function strips block comments which are identified by starting with '/\*' and ending with '\*\/'
	* 
	* This block comments can be made in a single line or through multiple lines
	* 
	* In the line given by the user it will check for the charactes '\*\/'. It it finds it in the same string, the line will be stripped from '\/*' to '*\/' and returned to the user.
	* 
	* If the '*\/' is not found in the line supplyed by the user, the function will keep on getting new lines until it finds the '*\/'. Afterwards it will return the NEXT line.
	* */
		std::string stripBlockComment(std::ifstream& in_file, std::string& line, int& lineCounter);
	
	
	
	
	
	
    /*!@brief 
     * Selector function to strip comments. 
     * Will choose stripSingleComment() or stripBlockComment() depending on the function \p line argument.
     * */
        std::string stripComments(std::ifstream& in_file, std::string& line, int& lineCounter);
        
    /*! @brief 
     * - Get a new line from \p ifstream, \n
     * - Increments the line counter variable (\p lineCounter), \n
     * - Strips empty lines from stream, \n
     * - If the user decides to pass \p updateString as \p true, the \p istringstream stream will be updated after getting a new line*/
        void newLineAndUpdateSStream(std::ifstream& in_file, std::istringstream& iss, std::string& line, int& lineCounter, bool updateStringStream=true);
        
    /*! @brief
     * - Function closes the current \p ifstream \n
     * - Throws a \p runTime_error with the line number supplied by the user
     * */
        void vectorFormatError(std::ifstream& in_file, int lineCounter);
        
    /*! @brief
     * Checks for an exact match of \p keyWord in a \p string \n
     * Starts by catching a partial match with the find() method \n
     * - Afterwards, checks the existance of chatacters before and after the location of the partial match.
     * If there are non, returns \p true, otherwise returns \p false
     * */
        bool checkExactMatch(const std::string& line,const std::string& keyWord);

    /*! @brief
     * Reads scalar from line. \n
     * This function starts by stripping comments from the input \p line.
     * Afterwards, it will update the stream and try to collect a scalar from it.
     * If the operation fails, the function errorMessage() is called to close the \p ifstream and throw a \p runTime_error.
     * */
        double readScalarData(std::ifstream& in_file, std::istringstream& iss, std::string& line, int lineCounter);

    /*! @brief
     * Reads string from line  \n
     * Starts by stripping comments from the stream \n
     * If the user decides to call the function with \p semiColumCheck = \p true, it will check if the semiColon exists at the end of the line through the checkSemiColon() function. \n
     * Afterwards, it will remove the semicolon from the stream as well as empty spaces.
     * It will try to read a \p string from the stream. If this operation fails it will throw an error through the function errorMessage()
     * */
        std::string readString(std::ifstream& in_file, std::istringstream& iss, std::string& line, int lineCounter, bool semiColumCheck);
        
    /*! @brief
     * Finds a \p keyword in a file and returns the corresponding \p scalar value. \n
     * This function starts by opening a file at the location \p path + \p filename \n
     * It will loop through the file until the checkExactMatch() function detects the \p keyword. \n
     * If it does not find the \p keyword, the file will be closed and a \p runTime_error will be thrown through the funcion errorMessage(). \n
     * If it finds the \p keyword, the stream will be checked for semicolon syntax through the function checkSemiColon() \n
     * If the check is Ok, it will remove the semicolon and \p keyword from the stream and try to read a scalar through the function readScalarData().
     * */
        double findScalar( const std::string& path, const std::string& fileName, const std::string& keyword);


        std::string findAsString( const std::string& path, const std::string& fileName, const std::string& keyword);
        std::map<std::string, std::string> readHeader( const std::string& path, const std::string& fileName);
        
        template <typename primitiveType>
        primitiveType readVectorTensorData(std::ifstream& in_file, std::istringstream& iss, std::string& line, int lineCounter);

        const std::string& Path() const;
        const std::string& Name() const;

    private:
        std::string path_;
        std::string fileName_;
};


#include "IODictionaryI.h"

#endif 
