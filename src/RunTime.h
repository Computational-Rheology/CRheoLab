#ifndef RunTime_H
#define RunTime_H

#include <string>
#include "findFiles.h"

class RunTime
{
    public:
        // Default constructor
        RunTime();
        
        // Destructor
        virtual ~RunTime(){} ;

    std::string Path() const;
    const std::string& Folder() const;
    void setFolder(std::string& newFolder);
    const std::string constant ();
    const std::string system ();
    const std::string timeName ();

    private:
        std::string path_;
        std::string folder_;
};

#endif 