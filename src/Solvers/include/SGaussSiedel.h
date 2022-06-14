#ifndef GAUSSSIEDEL_H
#define GAUSSSIEDEL_H

#include "FVMatrixSolver.h"
#include "lilSpmat.h"


class SGaussSiedel: public FVMatrixSolver
{
    public:

        //Constructor
        SGaussSiedel( spmat* aMatrix, std::vector<double> &bVector,std::vector<double> &xVector, const int nCells);

        // Destructor
        virtual ~SGaussSiedel();

        std::vector<double> doSolverStep()  const override ;

    private:
                       
};

#endif
