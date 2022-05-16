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
        VolField(const IOObject& IO);

        // Constructor with a default value passed by argument
        VolField(const IOObject& IO, const typename vectorType::value_type& defaultValue);

        VolField(const VolField& vf);

        // Destructor
        virtual ~VolField(){} ;

        // Member Functions
        vectorType readInternalField();

        // Read Data
        template <typename primitiveType>
        primitiveType readData(std::ifstream& in_file, std::istringstream& iss, std::string& line, int& lineCounter);

        // Give access to the boundary entities
        BoundaryField<vectorType>& boundaryField();

        vectorType& internalFieldRef();
        const vectorType& internalField() const;

        VolField& operator=(const VolField &vf);

    private:
        
        vectorType internalField_;
        BoundaryField<vectorType> boundaryField_;
        

};

#include "VolFieldI.h"
#include "VolFieldOperations.h"
#endif
