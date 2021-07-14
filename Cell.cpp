#include "Face.h"

Cell::Cell()
:
ID_(-1),
volume_(-1),
centerOfMass_({-1,-1,-1}),
skewness_(-1),
cellFaces_()
{

    
}


void Cell::setCellID(const int& ID)
{
    ID_ = ID;
}

void Cell::setCellFaces(const vector<Face*>& cellFaces)
{
    // Deep copy of points
    cellFaces_=cellFaces;   
}

const vector3& Cell::getCenterOfMass() const
{
    return centerOfMass_;
}

const double& Cell::getVolume() const
{
    return volume_;
}
 
void Cell::computeVolume()
{
    double VSMALL = 1.0e-37;
    vector3 CEst {0,0,0};
    double cellVolume = 0;

    for(int face_index = 0; face_index <cellFaces_.size(); face_index++)
    {     
      CEst = CEst +  cellFaces_[face_index]-> getCenterOfMass();
    }
    CEst/cellFaces_.size(); 
    
    for(int face_index = 0; face_index < cellFaces_.size(); face_index++)
    {     
      // Each pyramid volume 
      // & stands for the inner product 
      // max is to avoid zero volumes 
      double pyrVol = std:: max(cellFaces_[face_index]->getAreaVector() & (CEst - cellFaces_[face_index]->getCenterOfMass()), VSMALL)/3;
     
      //Accumulate volume-weighted face-pyramid center
      cellVolume += pyrVol;
    }

    volume_ = cellVolume;
                                                                          
}


void Cell::computeCenter(){
        
    double VSMALL = 1.0e-37;
    vector3 CEst {0,0,0};
    vector3 cellCenter {0,0,0};

    for(int face_index = 0; face_index <cellFaces_.size(); face_index++)
    {     
      CEst = CEst +  cellFaces_[face_index]-> getCenterOfMass();
    }
    CEst/cellFaces_.size(); 

    for(int face_index = 0; face_index < cellFaces_.size(); face_index++)
    {     
      // Each pyramid volume 
      // & stands for the inner product 
      // max is to avoid zero volumes 
      double pyrVol = std:: max(cellFaces_[face_index]->getAreaVector() & (CEst - cellFaces_[face_index]->getCenterOfMass()), VSMALL)/3;
      vector3 pyrc = (0.75)*cellFaces_[face_index]->getCenterOfMass() + (0.25)*CEst;
      //Accumulate volume-weighted face-pyramid center
      cellCenter = pyrc*pyrVol;
      
    }

   centerOfMass_ = cellCenter/volume_;
}