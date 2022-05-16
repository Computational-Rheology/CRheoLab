#ifndef FINDFILES_H
#define FINDFILES_H

#include <iostream>
#include <dirent.h>
#include <cstdio>
#include <errno.h>
#include <boost/filesystem.hpp>

// Function to get the current working directory of the executable file
inline std::string getExecutablePath()
{
 /* char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );

  std::string executablePath ( result, (count > 0) ? count : 0 );

  executablePath=executablePath.substr(0, executablePath.find_last_of("/"));*/
  boost::filesystem::path full_path(boost::filesystem::current_path());

  std::string finalPath = full_path.string() + '/';

  return finalPath;
}

// Function to check if a folder exists withing the executable path
inline void checkFileStructure(std::string folderName,  std::string pathname = getExecutablePath())
{
  std::string fullPath (pathname+folderName);

  DIR* dir = opendir(fullPath.c_str());

  if (dir)
  {
    std::cout << folderName <<" folder exists!" << std::endl;
    closedir(dir);
  }
  else if (ENOENT == errno)
  {
    throw std::runtime_error(folderName + std::string("/ folder does not Exist!"));
  }
  else
  {
    std::cout << "Something is wrong with file structure" << std::endl;
  }
}

// Check if case structure is Ok
inline void checkCaseStructure()
{
  checkFileStructure("constant");

  checkFileStructure("system");

  std::string polyMesh (std::string("constant") + std::string("/") + std::string("polyMesh"));

  checkFileStructure(polyMesh);

  std::cout << "Everything is clear!" << std::endl;
}

inline std::string getTimeFolder()
{
    // Get path location
    boost::filesystem::path path (getExecutablePath());

    // String to catch the current time directory
    std::string currentFolder{"0"};

    bool foundANumericFolder=false;

    if (is_directory(path))
    {
        // Loop through all files in folder
        for (auto&& x : boost::filesystem::directory_iterator(path))
        {
            if (is_directory(x))
            {
                // Name of the curent folder
                std::string tmp (x.path().filename().string());

                // Move it to a string stream to extract numeric value
                char* end = nullptr;
                double val = strtod(tmp.c_str(), &end);

                if (end != tmp.c_str() && *end == '\0')
                {
                    foundANumericFolder = true;
                    // Check if current folder has the highest value
                    double val2 = strtod (currentFolder.c_str(), &end);
                    if (val > val2)
                    {
                        currentFolder = tmp;
                    }
                }
            }
        }

        if(!foundANumericFolder)
        {
            std::string errorMessage = "There are no numerical folders in " + path.string()  + ". Please create a 0 folder.";
            throw std::runtime_error(errorMessage);
        }
    }
    else
    {
        std::string errorMessage = "Path " + path.string()  + " does not exist";
        throw std::runtime_error(errorMessage);
    }

    return currentFolder+"/";
}


#endif
