#include "Reader.h"
#include <boost/lexical_cast.hpp>

    //Constructor
    Reader::Reader( std::string fileName):
    fileName_(fileName)   
    {}

    // Destructor
    Reader::~Reader()
    {}

    // Member Functions
    std::string Reader::ReadString(std::string str)
    {
        std::string line;
        std::string name, value;
        int checkValue = 0;
        std::ifstream readFile(fileName_);
        while (!(readFile.eof()))
        {
            getline (readFile,line);
            readFile >> name >> value;
            if(name == str)
            {
            std::cout << str << ": " << value << std::endl;
            return value;
            checkValue = 1;
            break;
            }
        }
        readFile.close();
        if(checkValue == 0)
        {
            std::cout<< "Unable to find: "<< str << std::endl;
            exit(1);
        } 
    }

    double Reader::ReadDouble(std::string str)
    {
        std::string line;
        std::string name, value;
        double valueDouble;
        int checkValue = 0;
        std::ifstream readFile(fileName_);
        while (!(readFile.eof()))
        {
            getline(readFile,line);
            readFile >> name >> value;
            if(name == str)
            {
            valueDouble =  boost::lexical_cast<double>(value);
            std::cout << str <<": " << valueDouble << std::endl;
            return valueDouble;
            checkValue = 1;
            break;
            }
        }
        readFile.close();
        if(checkValue == 0)
        {
            std::cout<< "Unable to find: "<< str << std::endl;
            exit(1);
        } 
    }

    int Reader::ReadInt(std::string str)
    {
        std::string line;
        std::string name, value;
        int valueInt;
        int checkValue = 0;
        std::ifstream readFile(fileName_);
        while (!readFile.eof())
        {
            getline (readFile,line);
            readFile >> name >> value;
            if(name == str)
            {
            valueInt =  boost::lexical_cast<int>(value);
            std::cout << str << ": " << valueInt << std::endl;
            return valueInt;
            checkValue = 1;
            break;
            }
        }
        readFile.close();
        if(checkValue == 0)
        {
            std::cout<< "Unable to find: "<< str << std::endl;
            exit(1);
        } 
    }

        


     
    

    

                  



