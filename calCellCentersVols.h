#ifndef CALCELLCENTERSVOLS_H
#define CALCELLCENTERSVOLS_H

#include "Mesh.h"
#include "Point.h"
#include "Cell.h"
#include "Face.h"
#include <vector>

class calCellCentersVols {

  private:
       const vectorField            cellCenters_;
       const vector<double>         cellVols_;
       const vector<vector<Face*>>  facesPerCells_;   

  public:
       
        const vectorField&  getCellCenters() const
            {
                return cellCenters_;
            }

        const vector<double>&  getCellVols() const
            {
                return cellVols_; 
            }
        const vector<vector<Face*>> getFacesPerCells() const
            {
                return facesPerCells_;
            }
        

        // Constructor
        calCellCentersVols(Mesh M);
        //calCellCentersVols();
        // Destructor 
        virtual ~calCellCentersVols(){};
   
};


#endif // CALCELLCENTERSVOLS_H
