#ifndef SPMAT_H
#define SPMAT_H

#include <vector>

// Class to implement an abstract class of a sparse matrix

class spmat {

public:

  // Number of rows of the stored matrix
  unsigned int numRows_;

  // Number of columns of the stored matrix
  unsigned int numCols_;

public:

  // Returns the sparsity of the matrix
  double virtual sparsity() const = 0;

  // Returns the number of rows
  unsigned int getNumRows() const
  {
    return numRows_;
  }

  // Returns the number of columns
  unsigned int getNumCols() const
  {
    return numCols_;
  }

  // Returns the number of non-zero values in row i
  virtual unsigned int getNbNZ(const unsigned int &i) const = 0;

  // Returns the j-th non-zero value in row i (j is not the column)
  virtual double getNZValue(const unsigned int &i, const unsigned int &j) const = 0;

  // Returns the column of the j-th non-zero value in row i (j is not the column)
  virtual unsigned int getNZColumn(const unsigned int &i, const unsigned int &j) const = 0;

  // Sets a value to position (i,j) if exists, otherwise inserts a new value
  virtual void setValue(const unsigned int &i, const unsigned int &j, const double &val) = 0;

  // Adds a value to position (i,j) if exists, otherwise inserts a new value
  virtual void addValue(const unsigned int &i, const unsigned int &j, const double &val) = 0;

  // Subtracts a value to position (i,j) if exists, otherwise inserts a new value with oposite sign
  virtual void subValue(const unsigned int &i, const unsigned int &j, const double &val) = 0;

  // Deletes the value in position (i,j) if exists, otherwise does nothing
  virtual void delValue(const unsigned int &i, const unsigned int &j) = 0;

  // Returns the value in position (i,j) if exists, otherwise returns 0
  virtual double getValue(const unsigned int &i, const unsigned int &j) const = 0;

  // Returns the sparse matrix in a dense format as a vector of vectors
  virtual std::vector< std::vector<double> > dense() const = 0;

  // Returns the product matrix-vector as a vector
  virtual std::vector<double> matMul(const std::vector<double> &vecPhi) const = 0;

  // Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double
  virtual double vecMul(const unsigned int &i, const std::vector<double> &vecPhi) const = 0;

  // Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double excluding the diagonal
  virtual double vecMulNoDiagonal(const unsigned int &i, const std::vector<double> &vecPhi) const = 0;

  // Returns a double given by the sum of the products of xValue (a double) for the elements of the iRow matrix row
  virtual double xValueProduct(const unsigned int &i, const double &xValue) const = 0;

  // Addition operator
  // virtual spmat& operator+(const spmat& A,const spmat& B) = 0;
  //
  // Subtraction operator
  // virtual spmat& operator-(const spmat& A,const spmat& B) = 0;

};

#endif // SPMAT_H
