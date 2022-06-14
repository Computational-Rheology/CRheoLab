
#include "FVMatrix.h"
#include <vector>
#include <random>
#include <chrono>

FVMatrix::FVMatrix(const Mesh &mesh, vector<double> &xVector) : xVector_(xVector),
                                                                nCells_(mesh.nCells_),
                                                                residualNormFactor_(-1.0),
                                                                readParameter_("constant/modelParameter")
                                                                   
{
    //aMatrix_.resize(nCells_ * nCells_);
    bVector_.resize(nCells_);
  
    solverModel_ = readParameter_.ReadString("solverModel");
    absNormResidual_ = readParameter_.ReadDouble("absNormResidual");
    relNormResidual_ = readParameter_.ReadDouble("relNormResidual");
    matrixFormat_ = readParameter_.ReadString("matrixFormat");
    matrixType_ = readParameter_.ReadString("matrixType");

    if (matrixFormat_== "lOLists")
        aMatrix_ = new lilSpmat(nCells_,nCells_);
    else if (matrixFormat_== "CSR")
        if (matrixType_== "full"){
            aMatrix_ = new csrSpmat(nCells_);    
        }
        else if (matrixType_== "sparse") {
            aMatrix_ = new csrSpmat(mesh);
        }
        else {
            std::cout << "ERROR: Unindentified Matrix type";
            exit(0);
        }

    else {
        std::cout << "ERROR: Unindentified Matrix format";
        exit(0);
    }

    if (matrixType_== "full"){
       createRandomFullaMatrixbVector();  
    }
    else if (matrixType_== "sparse") {
       createRandomSparseaMatrixbVector(mesh);
    }
    else {
        std::cout << "ERROR: Unindentified Matrix type";
        exit(0);
    }

    setSolver(solverModel_);

    std::cout << "Reading done" << std::endl;
    std::cout << "ncells:" << nCells_ << std::endl;
}

FVMatrix::~FVMatrix()
{
    delete Solver_;
    delete aMatrix_;
}

// inline double FVMatrix::axMultiplication(const unsigned int &lineI)
// {
//     double x = 0.0;

//     for (unsigned int j = 0; j < nCells_; j++)
//     {
//         x += aMatrix_[j + lineI * nCells_] * xVector_[j];
//     }

//     return x;
// }




///////////////////////////////////////////////25/2/2022
// inline double FVMatrix::axAverageMultiplication(const unsigned int &lineI)
// {
//     double x = 0.0;

//     for (unsigned int j = 0; j < nCells_; j++)
//     {
//         x += aMatrix_[j + lineI * nCells_] * xAverage_;
//     }

//     return x;
// }


inline double FVMatrix::residualValue()
{
    double residualMagnitude = 0.0;

    for (unsigned int i = 0; i < nCells_; i++)
    {
        //residualMagnitude += fabs(bVector_[i] - axMultiplication(i));
        residualMagnitude += fabs(bVector_[i] - aMatrix_->vecMul(i,xVector_));
    }
    return residualMagnitude;
}

///////////////////////////////////////////////25/2/2022
inline double FVMatrix::residualNormFactor()
{
    
    xAverage_=0.0;
    for (unsigned int i = 0; i < nCells_; i++)
    {
        xAverage_ += xVector_[i];
    }
    xAverage_ = xAverage_ / nCells_;


    nNormalize_=0.0 ;
    for (unsigned int i = 0; i < nCells_; i++)
    {
        //nNormalize_ += fabs(axMultiplication(i) -  axAverageMultiplication(i)) + fabs(bVector_[i] - axAverageMultiplication(i));
        double xValueProduct = aMatrix_->xValueProduct(i,xAverage_);
        nNormalize_ += fabs(aMatrix_->vecMul(i,xVector_) -  xValueProduct) + fabs(bVector_[i] - xValueProduct);
    }
    return nNormalize_;
}

///////////////////////////////////////////////25/2/2022
/*
inline double FVMatrix::normalizedResidualValue()
{
    double residualMagnitude = 0.0;

    for (unsigned int i = 0; i < nCells_; i++)
    {
        residualMagnitude += fabs(bVector_[i] - axMultiplication(i));
    }

    if (residualNormFactor_ > 0.0) // in the constructor is initilized with -1.0 then we can check if it was initialized or not.
        return (residualMagnitude / residualNormFactor_);
    else
    {
        residualNormFactor_ = residualMagnitude;
        return 1.0;
    }
}*/

void FVMatrix::printaMatrix(std::vector<double> &mat, int n, int m)
{
    int k = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            std::cout << mat[i + k + j + k] << " ";
        }
        std::cout << std::endl;
        k = k + m;
    }
}

void FVMatrix::createRandomFullaMatrixbVector()
{
    std::cout << ">> entered create Full aMatrix and bVector" << std::endl;

    int maxValue = 10;
    srand(time(0));

    for (unsigned int lineI = 0; lineI < nCells_; lineI++)
    {
        double diagValue = 0.0;
        for (unsigned int j = 0; j < lineI; j++)
        {
            aMatrix_->addValue(lineI,j, static_cast<double>(rand() % maxValue) * (-1));
            diagValue += fabs(aMatrix_->getValue(lineI,j));
        }

        for (unsigned int j = lineI + 1; j < nCells_; j++)
        {
            aMatrix_->addValue(lineI,j, static_cast<double>(rand() % maxValue) * (-1));
            diagValue += fabs(aMatrix_->getValue(lineI,j));
        }
        aMatrix_->addValue(lineI,lineI, 1.1 * diagValue);
        bVector_[lineI] = (static_cast<double>(rand() % maxValue));
        //std::cout << "LineI" << lineI << std::endl;
    }
    std::cout << ">> leaving create FullaMatrix and bVector " << std::endl;
}

void FVMatrix::createRandomSparseaMatrixbVector(const Mesh &mesh)
{
    std::cout << ">> entered create Sparse aMatrix and bVector" << std::endl;

    int maxValue = 10;
    srand(time(0));
  
    for (unsigned int iFace=0;iFace<mesh.nInteriorFaces_;iFace++)
    {
        unsigned int iNeighbour = mesh.faceList_[iFace].getNeighbour()->ID_;
        unsigned int iOwner = mesh.faceList_[iFace].getOwner()->ID_;
        
        double mCoef = (static_cast<double>(rand() % maxValue))+1.0;

        aMatrix_->addValue(iNeighbour,iOwner, -mCoef); // Add mCoef to line iNeighbour column iOwner
        aMatrix_->addValue(iOwner,iNeighbour, -mCoef); // Add mCoef to line iOwner column iNeighbour
        aMatrix_->addValue(iNeighbour,iNeighbour, mCoef); // Add mCoef to Diagonal iNeighbour ,iNeighbour
        aMatrix_->addValue(iOwner,iOwner, mCoef); // Add mCoef to Diagonal iOwner ,iOwner
        // std::cout << aMatrix_->getValue(iNeighbour,iOwner) << std::endl;
        // std::cout << aMatrix_->getValue(iOwner,iNeighbour) << std::endl;
        // std::cout << aMatrix_->getValue(iNeighbour,iNeighbour) << std::endl;
        // std::cout << aMatrix_->getValue(iOwner,iOwner) << std::endl;


    }

    //Loop for cells
    for (unsigned int iCell = 0; iCell < nCells_; iCell++)
    {
        // add a factor to diagonal
        aMatrix_->addValue(iCell,iCell, 1.1 *  aMatrix_->getValue(iCell,iCell));
        bVector_[iCell] = (static_cast<double>(rand() % maxValue));
    }

    std::cout << ">> leaving create Sparse aMatrix and bVector " << std::endl;
}


// reset class xVector to zeros
void FVMatrix::resetxVector()
{
    std::fill(xVector_.begin(), xVector_.end(), 0.);
}

// select a solver
void FVMatrix::setSolver(std::string solvername)
{
     
     solverModel_ = solvername;
    
    std::cout << std::string(90, '#') << std::endl;

     if(solverModel_ == "Jacobi")
    {
        std::cout << ">>> Solving by Jacobi <<<<<" << std::endl;
        Solver_ = new SJacobi(aMatrix_, bVector_, xVector_, nCells_);
    }
    else if(solverModel_ == "GaussSiedel")
    {
        std::cout << ">>> Solving by Gauss Siedel <<<<<" << std::endl;
        Solver_ = new SGaussSiedel(aMatrix_, bVector_, xVector_, nCells_);
    }
    else if(solverModel_ == "SOR")
    {        
        std::cout << ">>> Solving by SOR <<<<<" << std::endl;
        double wSOR = readParameter_.ReadDouble("wSOR");
        Solver_ = new SSOR(aMatrix_, bVector_, xVector_, nCells_, wSOR);
    } 
}
///////////////////////////////////////////////25/2/2022
std::vector<double> FVMatrix::solve()
{
    std::vector<double> result(nCells_);

    double residualNormFactorValue =residualNormFactor();
    double residual = residualValue()/residualNormFactorValue;
    double residualFirst = residual;
    double relResidual = 1.0;


    
    int count = 0;
    auto start = std::chrono::high_resolution_clock::now();

    while (residual > absNormResidual_ && relResidual > relNormResidual_)
    {
        
        result = Solver_->doSolverStep();
        xVector_ = result;

        residual = residualValue()/residualNormFactorValue; 
        relResidual = residual/residualFirst;

        count++;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << std::string(120, '#') << std::endl;
    std::cout << "Number of Iterations: " << count << std::endl;
    std::cout << "Initial Residual: " << std::scientific << residualFirst << " -> Final Residual: " << std::scientific << residual << std::endl;
    std::cout << "Elapsed time:" << duration.count() << " ms" << std::endl;
    return result;
}