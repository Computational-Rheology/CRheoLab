#ifndef CELL_H
#define CELL_H

class Face;

class Cell
{
    public:

        // Constructor  
        Cell();

        // Destructor
        virtual  ~Cell(){};

        // Setters
        void setCellFaces(const vector<Face*>& );
        void setCellID(const int& );
        void setCenterOfMass(const vector3&);
        void setNonOrthogonality(const double&);
        void setSkewness(const double&);

        // Getters
        const vector3& getCenterOfMass() const;
        const double&  getVolume() const;
        const double& getNonOrthogonality() const;
        const double& getSkewness() const;

        // Computations
        void computeCenter();
        void computeVolume();
        double computepyrVol (const vector3&, const vector3&, const vector3&) const;
        vector3 computeGeometricCenter() const;
        void computeMaxNonOrthogonality();
        void computeSkewness();

    //private: vhanged by Group 1
    public:
    
        // cellID
        int ID_;

        // Cell Volume
        double volume_;

        // Cell center of Mass
        vector3 centerOfMass_; 

        // Cell skewness
        double skewness_;

        // Faces that make up a cell
        vector<Face*> cellFaces_;

        double maxNonOrthogonality_;

};

#endif // CELL_H
