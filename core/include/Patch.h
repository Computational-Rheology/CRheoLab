#ifndef PATCH_H
#define PATCH_H

#include <string>
#include <cstring>

class Patch
{
    public:
        // Constructor
        Patch(std::string, std::string, int, int, int);

        // Destructor
        virtual ~Patch(){};

        const std::string& name() const;

        // Returns the number of faces in the boundary patch
        ///@brief Returns the number of faces that the patch has
        int nFaces() const;

        // Returns the ID for the start face in the patch
        ///@brief Returns the ID for the patch starting faces in the face list of the mesh
        int startFace() const;

        // Returns the index of a patch in the boundary patch list
        ///@brief Returns the index of the patch in the mesh
        int index() const;

    protected:

    private:
        std::string name_;
        std::string type_;
        int nFaces_;
        int startFace_;
        int index_;

};

#endif // PATCH_H
