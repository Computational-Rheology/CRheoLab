#include "IOobject.h"

IOObject::IOObject 
( 
    const std::string& name,
    const std::string& fileLocation,
    const Mesh& mesh,
    fileAction read,
    fileAction write
)
:
name_(name),
fileLocation_(fileLocation),
path_(fileLocation_ + name_),
mesh_(mesh),
read_(read),
write_(write)
{}



const std::string& IOObject::name() const
{
    return name_;
}

const std::string& IOObject::file() const
{
    return fileLocation_;
}


const std::string& IOObject::path() const
{
    return path_;
}

const Mesh& IOObject::mesh() const
{
    return mesh_;
}