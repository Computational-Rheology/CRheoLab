#include "FVMatrixSolver.h"
#include <vector>
#include <random>


//Constructor
FVMatrixSolver::FVMatrixSolver(spmat* aMatrix, std::vector<double> &bVector,std::vector<double> &xVector,const int nCells ):
aMatrix_(aMatrix),
bVector_(&bVector),
xVector_(&xVector),
nCells_(nCells)
{}
 
FVMatrixSolver::~FVMatrixSolver()
{}

// double FVMatrixSolver::axMultiplicationNoDiagonal(const unsigned int& lineI) const
// {
//         double x = 0.0;

//         for(unsigned int j = 0; j < lineI ; j++)
//         {
//             x += (*aMatrix_)[j + lineI * nCells_] * (*xVector_)[j];
//         }

//         for(unsigned int j = lineI + 1; j < nCells_ ; j++)
//         {
//             x += (*aMatrix_)[j + lineI * nCells_] * (*xVector_)[j];
//         }
    
//     return x;
// }















