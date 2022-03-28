#ifndef LILSPMAT_H
#define LILSPMAT_H

#include "spmat.h"
#include <vector>

// Class to implement a list of lists for a sparse matrix
// The std::vector structure is used to implement the list

class lilSpmat : public spmat {

public: // change to private later

  // Vector of vector for the columns
  // columns_[i] is the vector for row i
  // columns_[i][j] is the index in position j of the std::vector for row i
  // columns_ always has numRows_ entries
  // columns_[i] has as many entries as non-null values in row i
  std::vector< std::vector<unsigned int> > columns_;

  // vector of vector for the values
  // values_[i] is the vector for row i
  // values_[i][j] is the index in position j of the std::vector for row i
  // values_ always has numRows_ entries
  // values_[i] has as many entries as non-null values in row i
  std::vector< std::vector<double> > values_;

public:

  // Constructor
  lilSpmat(unsigned int numRows, unsigned int numCols);

  // Destructor
  virtual ~lilSpmat(){};

  // Returns the sparsity of the matrix
  double sparsity();

  // Adds a value to position (i,j) if exists, otherwise inserts a new value
  void addValue(unsigned int i, unsigned int j, double val);

  // Subtracts a value to position (i,j) if exists, otherwise inserts a new value with oposite sign
  void subValue(unsigned int i, unsigned int j, double val);

  // Deletes the value in position (i,j) if exists, otherwise does nothing
  void delValue(unsigned int i, unsigned int j);

  // Returns the value in position (i,j) if exists, otherwise returns 0
  double getValue(unsigned int i, unsigned int j);

  // Returns the sparse matrix in a dense format as a vector of vectors
  std::vector< std::vector<double> > dense();

  // Returns the product matrix-vector as a vector
  std::vector<double> matMul(const std::vector<double> &vecPhi);

  // Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double
  double vecMul(const unsigned int i, const std::vector<double> &vecPhi);

  // Group 5
  // Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double excluding the diagonal
  //double vecMulNoDiagonal(const unsigned int iRow, const std::vector<double> &vecPhi);
  double vecMulNoDiagonal(const unsigned int iRow, const std::vector<double> &vecPhi);

  // Group 5
  // Returns a double given by the sum of the products of xValue (a double) for the elements of the iRow matrix row
  double xValueProduct(const unsigned int& iRow, const double &xValue);

};

#endif // LILSPMAT_H
