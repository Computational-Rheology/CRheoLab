#include "SJacobi.h"

    //Constructor
    SJacobi::SJacobi(spmat* aMatrix, std::vector<double> &bVector,std::vector<double> &xVector, const int nCells)
    :
    FVMatrixSolver(aMatrix,bVector,xVector, nCells)
    {}
   
    // Destructor
    SJacobi::~SJacobi()
    {}

    std::vector<double> SJacobi::doSolverStep() const  
    {

        std::vector<double> result(nCells_);    

        for(unsigned int lineI = 0; lineI < nCells_; lineI++)
        {
            //result[lineI] = ((*bVector_)[lineI] -  axMultiplicationNoDiagonal(lineI))/(*aMatrix_)[lineI*nCells_+lineI];            
            result[lineI] = ((*bVector_)[lineI] - aMatrix_->vecMulNoDiagonal(lineI,(*xVector_)))/aMatrix_->getValue(lineI,lineI);
        }      
        return result;
    }

        


                  



