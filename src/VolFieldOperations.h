#ifndef VOLFIELDOPERATIONS_H
#define VOLFIELDOPERATIONS_H

typedef std::array<double, 3> vector3;
typedef std::array<double, 6> symmTensor;
typedef std::array<double, 9> tensor;

typedef std::vector<double> scalarField;
typedef std::vector<vector3> vectorField;
typedef std::vector<symmTensor> symmTensorField;
typedef std::vector<tensor> tensorField;
typedef VolField<scalarField> volScalarField;

#include "fieldOperations.h"


//volField operations

template <typename T1>
inline void checkVolSize(const VolField<T1>& v1, const VolField<T1>& v2)
{
    if(v1.internalField().size() != v2.internalField().size() )
    {
        throw std::length_error("Volume fields do not have the same dimensions");
    }
}

inline volScalarField operator+(const volScalarField& v1, const volScalarField& v2)
{

   checkVolSize(v1,v2);

   volScalarField result (v1);

   for(unsigned int i = 0 ; i < v1.internalField().size(); i++)
   {
      result.internalFieldRef()[i] = v1.internalField()[i] + v2.internalField()[i];
   }

   return result;

}


#endif
