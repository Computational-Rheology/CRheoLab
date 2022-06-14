#ifndef READER_H
#define READER_H
#include<iostream>
#include<fstream>


class Reader
{
    public:

        // Default constructor
        Reader(std::string fileName);

        // Destructor
        virtual ~Reader();

        // Member Functions
        std::string ReadString(std::string str);
        double ReadDouble(std::string str);
        int ReadInt(std::string str);
            
    protected:
    
    private:
    std::string fileName_;
     
};

#endif
