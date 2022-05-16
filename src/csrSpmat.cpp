#include "csrSpmat.h"
#include "Mesh.h"
#include <iostream>

// Constructor
// Constructs an empty sparse matrix and allocates memory for the rows
csrSpmat::csrSpmat(Mesh &mesh)
{
  // Store number of rows and columns
  numRows_ = mesh.nCells_;
  numCols_ = mesh.nCells_;

  // Declaration of variables
  unsigned int nz;
  const Cell* neigh_ptr;
  const Cell* owner_ptr;

  // Determine the total number of non-zeros values (number of cells plus its neighbours)
  nz = 0;
  for (unsigned int i=0;i<mesh.nCells_;i++)
  {
    nz += 1;
    for (unsigned int j=0;j<mesh.cellList_[i].cellFaces_.size();j++) // getter?
    {
      neigh_ptr = mesh.cellList_[i].cellFaces_[j]->getNeighbour();
      if(neigh_ptr != NULL)
      {
         nz += 1;
      }
    }
  }

  // Store number of non-null values
  numNZ_ = nz;

  // Allocate memory for the values
  values_.resize(nz);
  columns_.resize(nz);
  row_ptr_.resize(numRows_+1);

  // Clean memory for the values
  // values_ = 0.0;

  // Fill-in the sparse matrix with the positions of the non-null values
  // (number of cells plus their neighbours)
  nz = 0;
  for (unsigned int i=0;i<mesh.nCells_;i++)
  {
    row_ptr_[i] = nz;
    columns_[nz] = i;
    nz += 1;
    for (unsigned int j=0;j<mesh.cellList_[i].cellFaces_.size();j++) // getter?
    {
      neigh_ptr = mesh.cellList_[i].cellFaces_[j]->getNeighbour();
      owner_ptr = mesh.cellList_[i].cellFaces_[j]->getOwner();
      if(neigh_ptr != NULL)
      {
        if(neigh_ptr->ID_ == i)
        {
          columns_[nz] = owner_ptr->ID_;
          nz += 1;
        }
        else //if(owner_ptr.ID_ == i)
        {
          columns_[nz] = neigh_ptr->ID_;
          nz += 1;
        }
      }
    }
    // order columns in each row
    //
  }
  row_ptr_[numRows_] = nz;
}

// Returns the sparsity of the matrix
double csrSpmat::sparsity()
{
  return (1.0 - ((double)numNZ_ / ((double)(numRows_ * numCols_))));
}

// Adds a value to position (i,j) if exists, otherwise inserts a new value
void csrSpmat::addValue(unsigned int i, unsigned int j, double val)
{
  for (unsigned int k=row_ptr_[i];k<row_ptr_[i+1];k++)
  {
    if (columns_[k] == j)
    {
      values_[k] += val;
      return;
    }
  }
  std::cout << "Error: invalid column for sparse structure matrix" << std::endl;
  exit(0);
}

// Subtracts a value to position (i,j) if exists, otherwise inserts a new value
void csrSpmat::subValue(unsigned int i, unsigned int j, double val)
{
  for (unsigned int k=row_ptr_[i];k<row_ptr_[i+1];k++)
  {
    if (columns_[k] == j)
    {
      values_[k] -= val;
      return;
    }
  }
  std::cout << "Error: invalid column for sparse structure matrix" << std::endl;
  exit(0);
}

// Deletes the value in position (i,j) if exists, otherwise does nothing
void csrSpmat::delValue(unsigned int i, unsigned int j)
{
  for (unsigned int k=row_ptr_[i];k<row_ptr_[i+1];k++)
  {
    if (columns_[k] == j)
    {
      values_[k] = 0.0;
      return;
    }
  }
  std::cout << "Error: invalid column for sparse structure matrix" << std::endl;
  exit(0);
}

// Returns the value in position (i,j) if exists, otherwise returns 0
double csrSpmat::getValue(unsigned int i, unsigned int j)
{
  for (unsigned int k=row_ptr_[i];k<row_ptr_[i+1];k++)
  {
    if (columns_[k] == j)
    {
      return values_[k];
    }
  }
  return 0.0;
}

// Returns the sparse matrix in a dense format as a vector of vectors
std::vector< std::vector<double> > csrSpmat::dense()
{
  std::vector< std::vector<double> > denseMatrix(numRows_);
  std::vector<double> temp(numCols_);
  unsigned int id_column = 0;
  for(unsigned int i=0;i<numRows_;i++)
  {
    denseMatrix[i] = temp;
  }
  for (unsigned int i=0;i<numRows_;i++)
  {
    for (unsigned int j=row_ptr_[i];j<row_ptr_[i+1];j++)
    {
      id_column = columns_[j];
      denseMatrix[i][id_column] = values_[j];
    }
  }
  return denseMatrix;
}

// Function that returns the product matrix-vector as a vector
std::vector<double> csrSpmat::matMul(const std::vector<double> &vecPhi)
{
  std::vector<double> v(vecPhi.size());
  unsigned int j = 0;
  for (unsigned int i=0;i<numRows_;i++)
  {
    v[i] = 0.0;
    while (j<row_ptr_[i+1])
    {
      v[i] += values_[j] * vecPhi[columns_[j]];
      j += 1;
    }
  }
  return v;
}

// Returns the product (row-of-matrix)-vector for a specific row of the matrix as a double
double csrSpmat::vecMul(const unsigned int i, const std::vector<double> &vecPhi)
{
  double sumProdRow = 0.0;
  unsigned int j = row_ptr_[i];
  while (j<row_ptr_[i+1])
  {
    sumProdRow += values_[j] * vecPhi[columns_[j]];
    j += 1;
  }
  return sumProdRow;
}
