#ifndef FACE_H
#define FACE_H

#include "Point.h"
#include <vector>
using std::vector;

class Face
{
    public:

        // Constructor
        Face(int, vector<Point*> , int , int );
        Face();

        // Destructor
        virtual  ~Face(){};

        // Member Functions
        void setOwner(int);
        void setNeighbour(int);
        void computeFaceArea();
        void computeFaceCenterOfMass();
        void computeFaceAreaVector();
        void setweightingFactor(double);

        int getOwner() const ;
        int getNeighbour() const;
        vector3 getCenterOfMass() const;
        vector3 getFaceAreaVector() const;

        // Write to stream
        friend std::ostream& operator<<(std::ostream& , const Face& );


    protected:

    private:
        int nPointsInFace_;
        vector<Point*> facePoints_;
        int owner_;
        int neighbour_;

        // Area vector
        vector3 areaVector_;

        // Center of mass
        vector3 centerOfMass_;

        // Area
        double area_;

        // Weighting factor
        double weightingFactor_;

        // Non-orthogonality angle
        double nonOrthogonalityAngle_;

};

#endif // FACE_H
