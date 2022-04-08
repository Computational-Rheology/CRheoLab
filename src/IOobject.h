#ifndef IOObject_H
#define IOObject_H

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <sstream> 
#include <algorithm>

#include "Mesh.h"


enum fileAction
{
    // Read signature
    MUST_READ = 1,
    NO_READ   = 2,

    MUST_WRITE = 3,
    NO_WRITE = 4
};



class IOObject
{

    private:
        std::string name_;
        std::string fileLocation_;
        std::string path_;
        const Mesh& mesh_;
        fileAction read_;
        fileAction write_;


    public:
        IOObject
        (
            const std::string& name,
            const std::string& fileLocation,
            const Mesh& mesh,
            fileAction read,
            fileAction write
        );

        const std::string& name() const;
        const std::string& file() const;
        const std::string& path() const;
        const Mesh& mesh() const;


};
#endif 
