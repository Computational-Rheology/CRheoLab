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
  csrSpmat(Mesh& mesh);

  // Destructor
  virtual ~csrSpmat(){};

  //
  unsigned int getNbNZ(const unsigned int &i) const override;

  //
  double getNZValue(const unsigned int &i, const unsigned int &j) const override;

  //
  unsigned int getNZColumn(const unsigned int &i, const unsigned int &j) const override;

  // Returns the sparsity of the matrix
  double sparsity() const override;

  // Sets a value to position (i,j) if exists, otherwise inserts a new value
  void setValue(const unsigned int& i, const unsigned int& j, const double& val) override;

  // Adds a value to position (i,j) if exists, otherwise throws an error
  void addValue(const unsigned int& i, const unsigned int& j, const double& val) override;

  // Subtracts a value to position (i,j) if exists, otherwise throws an error
  void subValue(const unsigned int& i, const unsigned int& j, const double& val) override;

  // Deletes the value in position (i,j) if exists, otherwise throws an error
  void delValue(const unsigned int& i, const unsigned int& j) override;

  // Returns the value in position (i,j) if exists, otherwise returns 0
  double getValue(const unsigned int& i, const unsigned int& j) const override;

  // Returns the sparse matrix in a dense format as a vector of vectors
  std::vector< std::vector<double> > dense() const override;

  // Returns the product matrix-vector as a vector
  std::vector<double> matMul(const std::vector<double>& vecPhi) const override;

  // Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double
  double vecMul(const unsigned int& i, const std::vector<double>& vecPhi) const override;

  // Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double excluding the diagonal
  double vecMulNoDiagonal(const unsigned int& i, const std::vector<double>& vecPhi) const override;

  // Returns a double given by the sum of the products of xValue (a double) for the elements of the iRow matrix row
  double xValueProduct(const unsigned int& i, const double& xValue) const override;

};

//
csrSpmat operator+(const csrSpmat& A,const csrSpmat& B);

//
csrSpmat operator-(const csrSpmat& A,const csrSpmat& B);

#endif // CSRSPMAT_H
