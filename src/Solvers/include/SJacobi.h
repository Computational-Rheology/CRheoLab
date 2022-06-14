#ifndef JACOBI_H
#define JACOBI_H

#include "FVMatrixSolver.h"
#include "lilSpmat.h"


class SJacobi: public FVMatrixSolver
{
    public:

        //Constructor
        SJacobi( spmat* aMatrix, std::vector<double> &bVector,std::vector<double> &xVector, const int nCells);

        // Destructor
        virtual ~SJacobi();

        std::vector<double> doSolverStep() const override;

    private:
                       
};

#endif
