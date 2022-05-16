#include "IOObject.h"
#include "Mesh.h"

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
{
    std::cout << " Constructor" << std::endl; 
}

IOObject::IOObject 
( 
    const IOObject& IO
)
:
name_(IO.name_),
fileLocation_(IO.fileLocation_),
path_(IO.fileLocation_ + IO.name_),
mesh_(IO.mesh_),
read_(IO.read_),
write_(IO.write_)
{
    std::cout << " Copy Constructor" << std::endl; 
}


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