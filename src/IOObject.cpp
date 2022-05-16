#include "IOObject.h"
#include "Mesh.h"

IOObject::IOObject 
( 
    const std::string& name,
    const std::string& fileLocation,
    const Mesh& mesh,
    fileAction read,
    fileAction write,
    const bool& storeObj
)
:
name_(name),
fileLocation_(fileLocation),
path_(fileLocation_ + name_),
mesh_(mesh),
read_(read),
write_(write),
storeObj_(storeObj)
{std::cout << "IOObject constructor for " << name_ << std::endl;}

IOObject::IOObject 
( 
    const IOObject& obj,
    const bool& store
)
:
name_(obj.name_),
fileLocation_(obj.fileLocation_),
path_(fileLocation_ + name_),
mesh_(obj.mesh_),
read_(obj.read_), //here enters read function
write_(obj.write_),
storeObj_(obj.storeObj_)
{
    if (storeObj_)
    {
        checkIn(this);
    }
    std::cout << "IOObject copy constructor for " << name_ << std::endl;
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

void IOObject::store(const bool& check)
{
    storeObj_ = check;

    if(storeObj_)
    {
        checkIn(this);
    }
}

const bool& IOObject::isStore()
{
    return storeObj_;
}

void IOObject::checkIn(IOObject* obj)
{
    auto found = std::find_if(mesh().dataBase().begin(),mesh().dataBase().end(), 
                            [&](IOObject* item)
                            {
                                return item->name() == obj->name();
                            });  

    if (found == mesh().dataBase().end())
    {
        const_cast<Mesh&>(mesh_).dataBase_.emplace_back(this); //adicionar ao dataBase
    }
}

void IOObject::checkOut(const std::string& name)
{
    
    Mesh& myMesh = const_cast<Mesh&>(mesh_);

    myMesh.dataBaseRef().erase( 
                                std::remove_if( 
                                                myMesh.dataBaseRef().begin(), myMesh.dataBaseRef().end(), 
                                                [name](IOObject* item)
                                                {
                                                    return item->name() == name;
                                                }), myMesh.dataBaseRef().end());
                              
}  

