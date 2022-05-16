#ifndef CSRSPMAT_H
#define CSRSPMAT_H

#include "spmat.h"
#include "Mesh.h"
#include <vector>

// Class to implement a list of lists for a sparse matrix
class csrSpmat : public spmat {

public: // change to private later

  // Number of non-null values
  unsigned int numNZ_;

  // Vector of vector for the values
  std::vector<double> values_;

  // Vector of vector for the columns
  std::vector<unsigned int> columns_;

  // Vector of vector for the row pointers
  std::vector<unsigned int> row_ptr_;

public:

  // Constructor
  csrSpmat(){}

  // Constructor
  csrSpmat(Mesh &mesh);

  // Destructor
  virtual ~csrSpmat(){};

  // Returns the sparsity of the matrix
  double sparsity() override;

  // Adds a value to position (i,j) if exists, otherwise throws an error
  void addValue(unsigned int i, unsigned int j, double val) override;

  // Subtracts a value to position (i,j) if exists, otherwise throws an error
  void subValue(unsigned int i, unsigned int j, double val) override;

  // Deletes the value in position (i,j) if exists, otherwise throws an error
  void delValue(unsigned int i, unsigned int j) override;

  // Returns the value in position (i,j) if exists, otherwise returns 0
  double getValue(unsigned int i, unsigned int j) override;

  // Returns the sparse matrix in a dense format as a vector of vectors
  std::vector< std::vector<double> > dense() override;

  // Returns the product matrix-vector as a vector
  std::vector<double> matMul(const std::vector<double> &vecPhi) override;

  // Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double
  double vecMul(const unsigned int i, const std::vector<double> &vecPhi) override;

  // // Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double excluding the diagonal
  // //double vecMulNoDiagonal(const unsigned int iRow, const std::vector<double> &vecPhi);
  // double vecMulNoDiagonal(const unsigned int iRow, const std::vector<double> &vecPhi) override;
  //
  // // Returns a double given by the sum of the products of xValue (a double) for the elements of the iRow matrix row
  // double xValueProduct(const unsigned int& iRow, const double &xValue) override;

};

#endif // CSRSPMAT_H
