#include "SGaussSiedel.h"

    //Constructor
    SGaussSiedel::SGaussSiedel(  spmat* aMatrix,  std::vector<double> &bVector,std::vector<double> &xVector, const int nCells)
    :
    FVMatrixSolver(aMatrix,bVector,xVector, nCells)
    {}

    // Destructor
    SGaussSiedel::~SGaussSiedel()
    {}

    std::vector<double> SGaussSiedel::doSolverStep() const
    {
        std::vector<double> result(nCells_);    

        for(unsigned int lineI = 0; lineI < nCells_; lineI++)
        {
            //result[lineI] = ((*bVector_)[lineI] -  axMultiplicationNoDiagonal(lineI))/(*aMatrix_)[lineI*nCells_+lineI]; 
            result[lineI] = ((*bVector_)[lineI] - aMatrix_->vecMulNoDiagonal(lineI,(*xVector_)))/aMatrix_->getValue(lineI,lineI);
            (*xVector_)[lineI] = result[lineI];                   
        }      
        return result;
    }

        


                  



