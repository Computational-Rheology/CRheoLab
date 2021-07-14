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
        //void setVolume(const double&);

        // Getters
        const vector3& getCenterOfMass() const;
        const double&  getVolume() const;

        void computeCenter();
        void computeVolume();
         
    protected:

    private:

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


};

#endif // CELL_H
