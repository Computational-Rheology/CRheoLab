#include "SSOR.h"

    //Constructor
    SSOR::SSOR(spmat* aMatrix,  std::vector<double> &bVector,std::vector<double> &xVector, const int nCells, double wSOR)
    :
    FVMatrixSolver(aMatrix,bVector,xVector, nCells),
    wSOR_(wSOR)
    {}

    // Destructor
    SSOR::~SSOR()
    {}

    std::vector<double> SSOR::doSolverStep() const 
    {        
        std::vector<double> result(nCells_);    

        for(unsigned int lineI = 0; lineI < nCells_; lineI++)
        {
            //result[lineI] = ((*bVector_)[lineI] -  axMultiplicationNoDiagonal(lineI))/(*aMatrix_)[lineI*nCells_+lineI];
            result[lineI] = ((*bVector_)[lineI] - aMatrix_->vecMulNoDiagonal(lineI,(*xVector_)))/aMatrix_->getValue(lineI,lineI);
            (*xVector_)[lineI] =  (*xVector_)[lineI] * (1-wSOR_) + wSOR_*result[lineI];       
        }      
        return result;
    }

        


                  



