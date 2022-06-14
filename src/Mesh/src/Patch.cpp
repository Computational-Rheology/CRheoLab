#include "Patch.h"


Patch::Patch(std::string name, std::string type, int nFaces, int startFace, int ID)
:   name_(name),
    type_(type),
    nFaces_(nFaces),
    startFace_(startFace),
    index_(ID)
{

}


const std::string& Patch::name() const
{
    return name_;
}

int Patch::startFace() const
{
    return startFace_;
}

int Patch::nFaces() const
{
    return nFaces_;
}

int Patch::index() const
{
    return index_;
}
