#include "calCellCentersVols.h"
#include <vector>

//Function to calculate volumes and centers of the elements(polyhedrons)

calCellCentersVols::calCellCentersVols(Mesh M)
{
   vector<vector<Face*>>               facesPerCells(M.nCells_);
   vectorField                         cellCenters(M.nCells_, {0,0,0}); // cellCenters, a array of cordinate points
   vector<double>                      cellVols(M.nCells_,0.0);   //cell Volumes, a array of doubles all as zero by default  

  // 1.0e-37 is the value of VSMALL constant in OpenFOAM it will be used in the sequel to avoid Zero Volumes ---> Zero Divisors
  double VSMALL = 1.0e-37;

//---*****************************Computing the estimated cells***************************---//
/*
Now notice that:
- The number of owners  =  total number of faces = interior + boundary faces 
- The number of neighbours  =  number of interior faces
*/
//Listing adresses of the owners and the neighbours
  //---owners----//

vector <const Cell*> own ; // (cell) owners addresses array
vector <const Cell*> nei; //  (cell)neighbours addresses array

for (int i = 0 ; i < M.nFaces_; i++){
    own[i] = M.faceList_[i].getOwner();
    nei[i] = M.faceList_[i].getNeighbour();
}

//Allocating the CellFaces per cell 

for (int i = 0; M.nCells_; i++ ){
    for (int j = 0; M.nFaces_; j++){
       if (own[i] == M.faceList_[j].getOwner() || nei[i] == M.faceList_[j].getNeighbour())
       {
        facesPerCells[i]={};
        facesPerCells[i].push_back(&(M.faceList_[j]));
       }
    }
    M.cellList_[i].setCellFaces(facesPerCells[i]);                                          
}

//Listing the geometric centers X_G
vectorField cEst(M.nCells_,{0,0,0});

vector<int> nCellFaces(M.nCells_,0);           
        
for(int cell_index = 0; cell_index < M.nCells_; cell_index++)
 {          
    for(int face_index = 0; face_index < facesPerCells[cell_index].size(); face_index++)
    {     
     cEst[cell_index] =  cEst[cell_index] + facesPerCells[cell_index][face_index]->getCenterOfMass(); 
    }
                                                                       
 }

for(int cell_index = 0; cell_index < cEst.size();cell_index++)
    {  
     nCellFaces[cell_index] = facesPerCells[cell_index].size() ;     
     cEst[cell_index] = cEst[cell_index]/nCellFaces[cell_index];
 }


//---*****************************Calculating cell centers and volumes***************************---//


for(int cell_index = 0; cell_index < M.nCells_; cell_index++)
 {          
    for(int face_index = 0; face_index < facesPerCells[cell_index].size(); face_index++)
    {     
      // Each pyramid volume 
      // & stands for the inner product 
      // max is to avoid zero volumes 
      double pyrVol = std:: max(facesPerCells[cell_index][face_index]->getAreaVector() & (cEst[cell_index] - facesPerCells[cell_index][face_index]->getCenterOfMass()), VSMALL)/3;
      //To Calculate face-pyramid centre 
      vector3 pyrc = (0.75)*facesPerCells[cell_index][face_index]->getCenterOfMass() + (0.25)*cEst[cell_index];
     
      //Accumulate volume-weighted face-pyramid center
      cellCenters[cell_index] = cellCenters[cell_index] + pyrVol*pyrc;

      cellVols[cell_index]+= pyrVol;
    }
 }



 //-------------------********************* Notice that ************************************-----//

/*
In the above code, fCtrs stands for the X_CE . "cEst-fCtrs" corresponds to the distance vector d_Gf .
*/


//---*************************-The final values of cells centroids (and volumes)***************************---//
    cellCenters  = cellCenters/cellVols;
   //cellVols are already the final volumes of the cells .
}



