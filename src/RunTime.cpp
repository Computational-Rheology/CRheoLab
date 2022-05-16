#include "RunTime.h"


RunTime::RunTime()
:
    path_( getExecutablePath() ),
    folder_( getTimeFolder() )
{}


std::string RunTime::Path() const
{
   // std::string tmp (path_ + folder_ + '/');
   //return tmp;
   return path_;
}

const std::string& RunTime::Folder() const
{
    return folder_;
}

void RunTime::setFolder(std::string& newFolder)
{
    folder_ = newFolder;
}

const std::string RunTime::constant() 
{
    return Path()+ "constant/";
}
    
const std::string RunTime::system ()
{
    return Path()+ "system/";
}

const std::string RunTime::timeName ()
{
    return Path()+ getTimeFolder();
}
