// Main file for testing

#include <iostream>
#include "csrSpmat.h"

int main(int argc, char const *argv[]) {

      std::cout << "#############################################################" << std::endl;
      std::cout << "Test csrSpmat class" << std::endl;
      std::cout << "#############################################################" << std::endl;

      std::vector<std::vector<double>> matrix
      {
        {1.0, 0.0, 2.0, 0.0},
        {0.0, 3.0, 0.0, 0.0},
        {0.0, 4.0, 0.0, 5.0},
        {0.0, 0.0, 0.0, 6.0}
      };

      std::cout << "Testing matrix:" << std::endl;
      for (unsigned int i = 0; i < matrix.size(); i++)
      {
            for (unsigned int j = 0; j < matrix[i].size(); j++)
            {
                  std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
      }

      //#############################################################

      std::cout << "#############################################################" << std::endl;
      std::cout << "Test sparse matrix construction" << std::endl;
      std::cout << "#############################################################" << std::endl;

      RunTime time;

      Mesh mesh(time);

      // Declare and initialize a sparse matrix
      csrSpmat spmatA = csrSpmat(mesh);

      std::cout << "#############################################################" << std::endl;
      std::cout << "Test sparse matrix to dense format" << std::endl;
      std::cout << "#############################################################" << std::endl;

      // Vector of vectors to store the sparse matrix in a dense format
      std::vector< std::vector<double> > denseMatrix;

      // Returns the sparse matrix in a dense format as a vector of vectors
      denseMatrix = spmatA.dense();

      std::cout << "Dense matrix:" << std::endl;

      for (unsigned int i = 0; i < denseMatrix.size(); i++)
      {
            for (unsigned int j = 0; j < denseMatrix[i].size(); j++)
            {
                  std::cout << denseMatrix[i][j] << " ";
            }
            std::cout << std::endl;
      }

      std::cout << "#############################################################" << std::endl;
      std::cout << "Test sparse matrix multiplication" << std::endl;
      std::cout << "#############################################################" << std::endl;

      std::vector<double> vecPhi;
      vecPhi.resize(mesh.nCells_);

      std::cout << "Phi vector for multiplication:" << std::endl;
      for (double valuePhi : vecPhi)
            std::cout << valuePhi << std::endl;

      std::vector<double> v;
      v.resize(mesh.nCells_);

      // Call the function that calculates the product matrix-vector as a vector
      v = spmatA.matMul(vecPhi);

      std::cout << "Vector resulting from the matrix-vector product:" << std::endl;
      for (double valueV : v)
            std::cout << valueV << std::endl;

      unsigned int rowMatVecProd = 2;

      // Call the function that calculates the product (row-of-matrix)-vector
      double ProdRowMatVec = spmatA.vecMul(rowMatVecProd, vecPhi);

      std::cout << "Double resulting from the (row-of-matrix)-vector product:" << std::endl;
      std::cout << "For row: " << rowMatVecProd << ", Product: " << ProdRowMatVec << std::endl;

      std::cout << "#############################################################" << std::endl;
      std::cout << "Test sparse matrix addition" << std::endl;
      std::cout << "#############################################################" << std::endl;

      csrSpmat spmatB, spmatC;

      // Create new matrix B with addValue functions

      // Add matrices
      spmatC = spmatA + spmatA;

      // Returns the sparse matrix in a dense format as a vector of vectors
      denseMatrix = spmatC.dense();

      std::cout << "Dense matrix:" << std::endl;

      for (unsigned int i = 0; i < denseMatrix.size(); i++)
      {
            for (unsigned int j = 0; j < denseMatrix[i].size(); j++)
            {
                  std::cout << denseMatrix[i][j] << " ";
            }
            std::cout << std::endl;
      }

      std::cout << "#############################################################" << std::endl;
      std::cout << "Test sparse matrix subtraction" << std::endl;
      std::cout << "#############################################################" << std::endl;

      return 0;
}
