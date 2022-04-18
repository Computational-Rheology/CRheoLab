#include "RunTime.h"


RunTime::RunTime()
:
    path_( getExecutablePath() ),
    folder_( getTimeFolder() )
{}


std::string RunTime::Path() const
{
    std::string tmp (path_ + folder_ + '/');
    return tmp;
}

const std::string& RunTime::Folder() const
{
    return folder_;
}

void RunTime::setFolder(std::string& newFolder)
{
    folder_ = newFolder;
}
