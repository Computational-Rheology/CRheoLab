#ifndef MESH_H
#define MESH_H

#include <vector>
#include <string>
#include <limits.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <algorithm> 

#include "Point.h"
#include "Face.h"
#include "Cell.h"
#include "Patch.h"
#include "findFiles.h"
#include "IOObject.h"

#include "RunTime.h"

class Mesh {

public:

  // Constructor
  Mesh(const RunTime& time);

  // Destructor
  virtual ~Mesh(){};

 const RunTime& time() const {return time_;}
              
  std::vector<Point> pointList_;

  std::vector<Face>  faceList_;

  std::vector<Cell>  cellList_;

  std::vector<Patch> patchList_;

  unsigned int nPoints_;

  unsigned int nFaces_;

  unsigned int nInteriorFaces_;

  unsigned int nBoundaryFaces_;
  
  unsigned int nCells_;

  unsigned int nPatches_;

  std::vector <IOObject*>& dataBaseRef();
  const std::vector <IOObject*>& dataBase() const;
  bool addToDataBase(IOObject* obj);

  template<typename T>
  T& lookup(const std::string& seeking) const;

  std::vector<IOObject*> dataBase_;

private:

  void readMesh();

  unsigned int getNEntitites(std::ifstream& file);

  void readPoints(std::string path);

  void readFaces(std::string path);

  vector<int> readOwners(std::string path);

  vector<int> readNeighbours(std::string path);

  void updateCellAndFaceData(std::string pathOwners, std::string pathNeighbours);

  void readBoundary(std::string path);

  const RunTime& time_;

  

  
} ;

#include "MeshI.h"

#endif // MESH_H


