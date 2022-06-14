#ifndef MATHOPERATIONS_H
#define MATHOPERATIONS_H
#include<vector>
#include <array>


typedef std::array<double, 3>   vector3;
typedef std::array<double, 6>   symmTensor;
typedef std::array<double, 9>   tensor;

typedef std::vector<double>     scalarField;
typedef std::vector<vector3>    vectorField;
typedef std::vector<symmTensor> symmTensorField;
typedef std::vector<tensor>     tensorField;

#include <cmath>   
#include "fieldOperations.h"
#include "scalarOperations.h"
#include "vectorOperations.h"
#include "tensorOperations.h"
#endif


