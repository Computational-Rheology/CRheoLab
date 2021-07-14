
#include <iostream>
#include <math.h> 
#include <cstring>
#include <string>
#include <limits.h>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm> 
#include <assert.h>
#include <memory>

#include "mathOperations.h"
#include "Mesh.cpp"
#include "findFiles.h"

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v)
{
    os << "[ \n";
    for (int i = 0; i < v.size(); ++i) {
        os << v[i] << std::endl;
    }
    os << "]\n";
    return os;
}

using namespace std;


int main()
{
      
   checkCaseStructure();
    
    Mesh polyMesh;

    //for (unsigned int i = 0; i< polyMesh.nFaces_ ; i++)
    //{
      //  std::cout << polyMesh.faceList_[i].getWeightingFactor() << std::endl;;
    //}
    
    std::cout << "\n\n Cell Volumes" <<"            "<<"Cell Centers\n "<< std::endl;
    for (unsigned int i = 0; i< polyMesh.nCells_ ; i++)
    {
        polyMesh.cellList_[i].computeVolume();
        polyMesh.cellList_[i].computeCenter();
        std::cout << polyMesh.cellList_[i].getVolume() <<"          " << polyMesh.cellList_[i].getCenterOfMass() << std::endl;
    }


    /*// Print single point
    cout << polyMesh.pointList_[0] << endl;

    // Sums points coordinates between two meshes
    auto a = polyMesh.pointList_ + polyMesh.pointList_;

    cout << "my directory is " << getExecutablePath() << endl;

*/

    std::cout << "I am done\n\n\n" << std::endl;



    //polyMesh.faceList_[0].owner()=2;
    //std::cout << polyMesh.faceList_[0].owner() << std::endl;
    return 0;
}


