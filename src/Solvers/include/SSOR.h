#ifndef SOR_H
#define SOR_H

#include "FVMatrixSolver.h"
#include "lilSpmat.h"


class SSOR: public FVMatrixSolver
{
    public:

        //Constructor
        SSOR( spmat* aMatrix, std::vector<double> &bVector,std::vector<double> &xVector, const int nCells, double wSOR = 0.0);

        // Destructor
        virtual ~SSOR();

        std::vector<double> doSolverStep() const override ;

    private:
    double wSOR_;
                       
};

#endif
