#include "Mesh.h"


Mesh::Mesh(const RunTime& time)
: nPoints_(0),
  nFaces_(0),
  nInteriorFaces_(0),
  nBoundaryFaces_(0),
  nCells_(0),
  nPatches_(0),
  dataBase_(),
  time_(time)
{ 
  readMesh();
}


void Mesh::readMesh()
{
    std::string filePoints (getExecutablePath()+std::string("constant/")+std::string("polyMesh/points"));
    std::cout << filePoints << std::endl;
    readPoints(filePoints);

    std::string fileFaces (getExecutablePath()+std::string("constant/")+std::string("polyMesh/faces"));
    readFaces(fileFaces);

    std::string fileOwners(getExecutablePath()+std::string("constant/")+std::string("polyMesh/owner"));

    std::string  fileNeighbours(getExecutablePath()+std::string("constant/")+std::string("polyMesh/neighbour"));

    updateCellAndFaceData(fileOwners, fileNeighbours);

    std::string fileBoundary(getExecutablePath()+std::string("constant/")+std::string("polyMesh/boundary"));
    readBoundary(fileBoundary);

    std::cout << "Mesh was read successfully!" << std::endl;
}


unsigned int Mesh::getNEntitites(std::ifstream& file)
{
  unsigned int nPoints ;
  bool findNPoints (true);
  std::string line;

  while (findNPoints)
  {
    std::getline(file, line );
    if ( std::stringstream( line ) >> nPoints) 
      findNPoints=false;
  }
  return nPoints;
}

void Mesh::readPoints(std::string path)
{
  // Passes the path of points into a ifsteam
  std::ifstream in_file(path.c_str());
    
  // Checks if file is to be open correctly
  if(!in_file.is_open())
  {
      std::cerr << "The input file was not open correctly!" << std::endl;
      //return 1;
  }

  std::string line;

  // Gets number of points in file
  nPoints_ = getNEntitites(in_file);

  pointList_.resize(nPoints_);

  // Loop over the points to fill the vector 
  // Check if next line is a '('
  getline(in_file, line );
  bool catchParenthesis = (line.find('(')!= std::string::npos);

  if (catchParenthesis)
  {
    char c; // Variable to catch "("
    double x, y, z; // Variables to store the x,y,z position of the points
    
    for ( unsigned int i = 0; i < nPoints_; i++ )
    {
      std::getline( in_file, line );

      std::stringstream(line) >> c >> x >> y >> z;
      
      pointList_[i]= Point(x,y,z); // Node list
    }
  }
  else
  {
    in_file.close();
    throw std::runtime_error("Problem reading points File");
  }

  // Close the file
  in_file.close();
}


void Mesh::readFaces(std::string path)
{
  // Passes the path of points into a ifsteam
  std::ifstream in_file(path.c_str());
    
  // Checks if file is to be open correctly
  if(!in_file.is_open())
  {
      std::cerr << "The input file was not open correctly!" << std::endl;
      //return 1;
  }

  std::string line;

  // Gets number of faces in file
  nFaces_ = getNEntitites(in_file);

  // Resize the vectors according to the number of faces
  faceList_.resize(nFaces_);

  // Check if next line is a '('
  getline(in_file, line );
  bool catchParenthesis = (line.find('(')!= std::string::npos);

  if (catchParenthesis)
  {
    // Loop over the points to fill the vector
    int nPointsInFace; // catch number of points in each Face
    char c; // Variable to catch "("

    for ( unsigned int i = 0; i < nFaces_; i++ )
    {
      std::getline( in_file, line );
      std::stringstream line_2(line);
      line_2 >> nPointsInFace >> c;

      std::vector<Point*> listOfPoints (nPointsInFace); // array to store the list of points
      int counter(0);
      int tmp;

      while(line_2 >> tmp)
      {
        listOfPoints[counter]=&pointList_[tmp];
        counter++;
      } 

      faceList_[i]=Face(nPointsInFace,listOfPoints);
      faceList_[i].setID(i);
    }
  }
  else
  {
    in_file.close();
    throw std::runtime_error("Problem reading owner File");
  }
  // Close the file
  in_file.close();
}


vector<int> Mesh::readOwners(std::string path)
{
  // Passes the path of points into a ifsteam
  std::ifstream in_file(path.c_str());
    
  // Checks if file is to be open correctly
  if(!in_file.is_open())
  {
      std::cerr << "The input file was not open correctly!" << std::endl;
      //return 1;
  }

  // String to catch the file input
  std::string line;

  // Gets number of owners in file
  unsigned int nOwners = getNEntitites(in_file);

  // Check if next line is a '('
  getline(in_file, line );
  bool catchParenthesis = (line.find('(')!= std::string::npos);

  vector<int> tmp_OwnersList(nOwners);

  if (catchParenthesis)
  {
    int tmp(0); // catch number of owner
    for ( unsigned int i = 0; i < nOwners; i++ )
    {
      std::getline( in_file, line );
      std::stringstream line_2(line);
      line_2 >> tmp;
      tmp_OwnersList[i]=tmp; 
    }
  }
  else
  {
    in_file.close();
    throw std::runtime_error("Problem reading owner File");
  }

  // Close the file
  in_file.close();

  return tmp_OwnersList;

}

vector<int> Mesh::readNeighbours(std::string path)
{
  // Passes the path of points into a ifsteam
  std::ifstream in_file(path.c_str());
    
  // Checks if file is to be open correctly
  if(!in_file.is_open())
  {
      std::cerr << "The input file was not open correctly!" << std::endl;
      //return 1;
  }

  // String to catch the file input
  std::string line;

  // Gets number of faces in file
  unsigned int nNeighbours = getNEntitites(in_file);

  vector<int> tmp_NeighboursList(nNeighbours);

    // Check if next line is a '('
    getline(in_file, line );
    bool catchParenthesis = (line.find('(')!= std::string::npos);

  if (catchParenthesis)
  {
    int tmp(0); // catch number of cell neighbour

    for ( unsigned int i = 0; i < nNeighbours; i++ )
    {
      std::getline( in_file, line );
      std::stringstream line_2(line);
      line_2 >> tmp;
      tmp_NeighboursList[i]=tmp;
    } 
  }
  else
  {
    in_file.close();
    throw std::runtime_error("Problem reading neighbour File");
  }

  // Close the file
  in_file.close();

  return tmp_NeighboursList;
}


void Mesh::updateCellAndFaceData(std::string pathOwners, std::string pathNeighbours)
{
  // Reads owners
  const vector<int> ownersList = readOwners(pathOwners);
  
  // Reads neighbours
  const vector<int> neighboursList = readNeighbours(pathNeighbours);
  
  // Updates the number of interior faces and boundary faces
  nInteriorFaces_ = neighboursList.size();
  nBoundaryFaces_ = nFaces_ - nInteriorFaces_;
  
  // Updates the number of cells in the mesh
  nCells_ = *std::max_element(std::begin(neighboursList), std::end(neighboursList)) + 1 ;
  
  // Updates the size of cellList_
  cellList_.resize(nCells_);

  // Gets faces that constitute each cell
  vector<vector<Face*> > cellFaces(nCells_);

  // Loops over the interior faces
  for( unsigned int i = 0 ; i < nInteriorFaces_ ; i++)
  {    
    int tmp_owner = ownersList[i];
    int tmp_neighbour = neighboursList[i];

    cellFaces[tmp_owner].push_back(&faceList_[i]);
    cellFaces[tmp_neighbour].push_back(&faceList_[i]);
  }

  // Loops over the boundary faces
  for (unsigned int i = nInteriorFaces_; i < nFaces_; i++)
  {
    int tmp_owner = ownersList[i];
    
    cellFaces[tmp_owner].push_back(&faceList_[i]);
  }
  
  // Updates the vector<Face*> in for each cell
  for(unsigned int cellI = 0; cellI<cellList_.size(); cellI++)
  {
    cellList_[cellI].setCellFaces(cellFaces[cellI]);
    cellList_[cellI].setCellID(cellI);
  }

  // Assign the pointers to cell owners and neighbours for each face
  // Loops over the interior faces
  for(unsigned int faceI = 0; faceI< nFaces_; faceI++)
  {
    int tmp_owner = ownersList[faceI];
    faceList_[faceI].setOwner( cellList_[tmp_owner]  );

    if (faceI < nInteriorFaces_)
    {
      int tmp_neighbour = neighboursList[faceI];
      faceList_[faceI].setNeighbour( cellList_[tmp_neighbour]  );
    }

    // Update face parameters
    faceList_[faceI].computeArea();
    faceList_[faceI].computeCenterOfMass();
    faceList_[faceI].computeAreaVector();
  }

  //Update Cell Centers and Volume
  for (unsigned int cellI = 0; cellI< nCells_; cellI++)
  {
      cellList_[cellI].computeVolume();
      cellList_[cellI].computeCenter();
  }

  // Update face weighting factors
  for (unsigned int faceI = 0; faceI < nFaces_; faceI++)
  {
    faceList_[faceI].computeWeightingFactor();
    faceList_[faceI].computeNonOrthogonality();
    faceList_[faceI].computeSkewness(); 
  }

  for (unsigned int cellI = 0; cellI < nCells_; cellI++)
  {
    cellList_[cellI].computeMaxNonOrthogonality();    
    cellList_[cellI].computeSkewness(); 
  }

}


void Mesh::readBoundary(std::string path)
{
  // Passes the path of points into a ifsteam
  std::ifstream in_file(path.c_str());
    
  // Checks if file is to be open correctly
  if(!in_file.is_open())
  {
      std::cerr << "The input file was not open correctly!" << std::endl;   
  }

  std::string line;

  // Booleans to check file reading
  bool endInnerLoop = false;
  bool firstCurly = false;
  bool secondCurly = false;

  bool checkBoundaryName = false;
  bool checkType = false;
  bool checkNFaces = false;
  bool checkStartFace = false;

  std::string words;
  std::string words2;
  int values(-1);
  int countCurly (0);

  std::string name;
  std::string type;

  int nFaces;
  int startFace;

  nPatches_ = getNEntitites(in_file);

  // Check if next line is a '('
  getline(in_file, line );
  bool catchParenthesis = (line.find('(')!= std::string::npos);

  if (catchParenthesis)
  {
    for (unsigned int i = 0; i < nPatches_; i++ )
    {
      endInnerLoop = false;

      while(!endInnerLoop && !in_file.eof())
      {
        std::getline( in_file, line );
        std::stringstream line_2(line); 

        // Extracts word from line
        line_2 >> words;

        if (words.at(0) == '{')
        {
          firstCurly = true;
          countCurly++;
        }

        if (firstCurly && words.back() == '}' && countCurly < 2)
        {
          secondCurly = true;
          countCurly = 0;
        }
        
        if (firstCurly && secondCurly)
          endInnerLoop = true;

        if(!checkBoundaryName && !firstCurly)
        {
          name = words;
          checkBoundaryName = true;
        }

        if(words == "type" && (line_2 >> words2) && words2.back() == ';' )
        {
          type = words2.substr(0, words2.size()-1);
          checkType = true;
          words2.clear();
        }

        if(words == "nFaces" && (line_2 >> values) && ( (line_2 >>  words2) && words2.back() == ';') )
        {
          nFaces = values;
          checkNFaces = true;
          words2.clear();
        }

        if(words == "startFace" && (line_2 >> values) && ( (line_2 >>  words2) && words2.back() == ';'))
        {
          startFace = values;
          checkStartFace = true;
        }

        // If the stringstream reaches the end of file some parameters are missing. 
        // Implement later
        if (endInnerLoop)
        {
            if ( !(checkBoundaryName  && checkType && checkNFaces && checkStartFace) )
            {
                throw  std::runtime_error("Some error in the boundaries");
            } 
        }

        if (in_file.eof() && !endInnerLoop)
        {
              throw  std::runtime_error("End of file!! You probably have problems with parentheses");
              
        }  
      }

      patchList_.push_back(Patch(name, type, nFaces, startFace)); //add a Patch object to the list

      checkBoundaryName = false;
      checkType = false;
      checkNFaces = false;
      checkStartFace = false;

      firstCurly = false;
      secondCurly = false;
    }
  }
  
  else
  {
    in_file.close();
    throw std::runtime_error("Problem reading boundary File");
  }

  // Close the file
  in_file.close();
}


bool Mesh::addToDataBase(IOObject* obj)
{
  dataBase_.push_back(obj);
  return true;
}

std::vector <IOObject*>& Mesh::dataBaseRef() 
{
    return dataBase_;
}

const std::vector <IOObject*>& Mesh::dataBase() const
{
    return dataBase_;
}





