#ifndef FACE_H
#define FACE_H

#include "Point.h"
#include <vector>
using std::vector;

#include "Cell.h"

class Face
{
    public:

        // Constructor  
        Face(int, vector<Point*>);
        Face();

        // Destructor
        virtual  ~Face(){};
       
        // Member Functions
        // Setters      
        void setOwner(const Cell&);
        void setNeighbour(const Cell&);
        void setID(const int&);
        void setWeightingFactor(const double&);
        void setNonOrthogonalityFace(const double&); 
        void setSkewness(const double&);

        // Getters
        const Cell* getOwner() const;
        const Cell* getNeighbour() const;
        const vector3& getCenterOfMass() const;
        const vector3& getAreaVector() const;
        const double& getWeightingFactor() const;
        const double& getNonOrthogonality() const; 
        const double& getSkewness() const;
        const vector3& getIntersectionPoint() const;

        // Computations
        void computeArea();
        
        /// @brief Computes the face area vector \f$\vec{S}_f\f$
        void computeAreaVector();

        void computeCenterOfMass();
        /// @brief Computation of cells face weighting factor, \f$g_{c}\f$.
        /// @brief \f[ g_{c} =  \frac{ \left | \vec{d}_{fF} \cdot \vec{S}_f \right | }{ \left | \vec{d}_{Cf} \cdot \vec{S}_f \right | + \left | \vec{d}_{fF} \cdot \vec{S}_f \right |} \f]
        
        void computeWeightingFactor();
        
        void computeNonOrthogonality();
        
        void computeIntersectionPoint();
        
        void computeSkewness();

        // Write to stream
        friend std::ostream& operator<<(std::ostream& , const Face& );

    private:
        int ID_;

        int nPointsInFace_;
        vector<Point*> facePoints_;

        const Cell* owner_;
        const Cell* neighbour_;

        // Area
        double area_;

        // Center of mass
        vector3 centerOfMass_; 

        /// Area vector, \f$\vec{S}_f\f$
        vector3 areaVector_; 

        // Weighting factor
        double weightingFactor_;

        // Non-orthogonality angle
        double nonOrthogonalityAngle_;

        // Face Skewness
        double skewness_;

        // Intersection point (IP)
        vector3 intersectionPoint_; 
};

#endif // FACE_H
