#ifndef VOLFIELD_H
#define VOLFIELD_H

#include "IODictionary.h"
#include "RunTime.h"
#include "BoundaryField.h"

typedef std::array<double, 3> vector3;
typedef std::array<double, 6> symmTensor;
typedef std::array<double, 9> tensor;

typedef std::vector<double> scalarField;
typedef std::vector<vector3> vectorField;
typedef std::vector<symmTensor> symmTensorField;
typedef std::vector<tensor> tensorField;

template< typename vectorType>
class VolField
:
    public IODictionary
{
    public:

        // Default constructor
        VolField(std::string fileName, const Mesh& mesh, const RunTime& time, fileAction action);

        // Constructor with a default value passed by argument
        VolField(std::string fileName, const Mesh& mesh, const RunTime& time, fileAction action, const typename vectorType::value_type& defaultValue);

        // Destructor
        virtual ~VolField(){} ;

        // Member Functions
        vectorType readInternalField();

        // Read Data
        template <typename primitiveType>
        primitiveType readData(std::ifstream& in_file, std::istringstream& iss, std::string& line, int& lineCounter);

        // Give access to the boundary entities
        BoundaryField<vectorType>& boundaryField();

    private:
        const Mesh& mesh_;
        const RunTime& runTime_;
        vectorType internalField_;
        BoundaryField<vectorType> boundaryField_;
        fileAction action_;

};

#include "VolFieldI.h"

#endif
