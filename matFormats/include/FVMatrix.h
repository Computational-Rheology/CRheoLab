#ifndef FVMATRIX_H
#define FVMATRIX_H

#include "Mesh.h"
#include "SJacobi.h"
#include "SGaussSiedel.h"
#include "SSOR.h"
#include "Reader.h"
#include "lilSpmat.h"
#include "csrSpmat.h"

class FVMatrix
{
    public:

        // Default constructor
        // normResidual - should contain the current normalized residual value
        // normResidualIni - should contain the current normalized residual value when the solver method was called
        // absNormResidual - maximum value allowed for the normResidual, if the normResidual < absNormResidual the iteration process should end
        // relNormResidual - minimum reduction required for the normResidual, if normResidual/normResidualIni < relNormResidual the iteration process should end
        FVMatrix(const Mesh& mesh, vector<double>& xVector);

        // Destructor
        virtual ~FVMatrix();

        // Member Functions
        
        inline double axMultiplication(const unsigned int& i);
    /*    inline double normalizedResidualValue();*////////////////////////////////////////////////25/2/2022


        inline double residualValue();///////////////////////////////////////////////25/2/2022
        inline double residualNormFactor();///////////////////////////////////////////////25/2/2022
        inline double axAverageMultiplication(const unsigned int &i);///////////////////////////////////////////////25/2/2022

        void createRandomFullaMatrixbVector();
        void createRandomSparseaMatrixbVector(const Mesh &mesh);
        void printaMatrix(std::vector<double>& mat, int n, int m);
        void resetxVector();
        void setSolver(std::string solvername);
                 
        std::vector<double> solve();

    private:
        std::vector<double> bVector_;
        std::vector<double> xVector_;
        unsigned int nCells_;
        spmat* aMatrix_;
        std::string matrixFormat_;
        std::string matrixType_;
        double absNormResidual_;
        double relNormResidual_;
        double normResidual_;
        double residualNormFactor_;
        FVMatrixSolver* Solver_;     
        std::string solverModel_;
        Reader readParameter_;
        double xAverage_;     ///////////////////////////////////////////////25/2/2022
        double nNormalize_;///////////////////////////////////////////////25/2/2022     
};

#endif
