#include "Face.h"

Face::Face(int nPointsInFace, vector<Point*> facePoints, int owner=-1, int  neighbour=-1 )
:   nPointsInFace_(nPointsInFace),
    facePoints_(facePoints),
    owner_(owner),
    neighbour_(neighbour),
    areaVector_({-2,-2,-2}),
    centerOfMass_{-2,-2,-2},
    area_(0),
    weightingFactor_(0),
    nonOrthogonalityAngle_(0)
{
    computeFaceAreaVector();
}

Face::Face( )
{


}

void Face::setNeighbour(int neighbour)
{
    neighbour_ = neighbour;
}

void Face::setOwner(int owner)
{
    owner_ = owner;
}

void Face::computeFaceArea()
{
      // face is a triangle
      if(nPointsInFace_ == 3)
      {
            // edges length
            double a = mag(facePoints_[0]->getPoint() - facePoints_[1]->getPoint());
            double b = mag(facePoints_[1]->getPoint() - facePoints_[2]->getPoint());
            double c = mag(facePoints_[2]->getPoint() - facePoints_[0]->getPoint());

            // semi-perimeter
            double s = (a + b + c) / 2.0

            // face area
            area_ = sqrt(s*(s-a)*(s-b)*(s-c));
      }
      else
      {
            // compute face centroid
            vector3 centroid = 0.0;

            for(int i = 0; i < nPointsInFace_; i++)
            {
                  centroid = centroid + facePoints_[i]->getPoint();
            }
            centroid = centroid/nPointsInFace_;

            // face area
            area_ = 0.0;

            // compute area of each subtriangle
            for(int i = 0; i < nPointsInFace_; i++)
            {
                  // all points but the last
                  if(i < nPointsInFace_-1)
                  {
                        // edges length
                        double a = mag(facePoints_[i]->getPoint() - facePoints_[i+1]->getPoint());
                        double b = mag(facePoints_[i]->getPoint() - centroid);
                        double c = mag(facePoints_[i+1]->getPoint() - centroid);
                  }
                  else
                  {
                        // edges length
                        double a = mag(facePoints_[i]->getPoint() - facePoints_[0]->getPoint());
                        double b = mag(facePoints_[i]->getPoint() - centroid);
                        double c = mag(facePoints_[0]->getPoint() - centroid);
                  }

                  // semi-perimeter
                  double s = (a + b + c) / 2.0

                  // face area
                  area_ = area_ + sqrt(s*(s-a)*(s-b)*(s-c));
            }

      }

}

void Face::computeFaceCenterOfMass()
{
      // face is a triangle
      if(nPointsInFace_ == 3)
      {
            // face center of mass
            centerOfMass_ = facePoints_[0]->getPoint() + facePoints_[1]->getPoint() +facePoints_[2]->getPoint();
            centerOfMass_ = centerOfMass_ / 3.0;
      }
      else
      {
            // compute face centroid
            vector3 centroid = 0.0;

            for(int i = 0; i < nPointsInFace_; i++)
            {
                  centroid = centroid + facePoints_[i]->getPoint();
            }
            centroid = centroid/nPointsInFace_;

            // numerator
            double numerator = 0.0;

            // denominator
            double denominator = 0.0;

            // compute area and centroid of each subtriangle
            for(int i = 0; i < nPointsInFace_; i++)
            {
                  // all points but the last
                  if(i < nPointsInFace_ - 1)
                  {
                        // edges length
                        double a = mag(facePoints_[i]->getPoint() - facePoints_[i+1]->getPoint());
                        double b = mag(facePoints_[i]->getPoint() - centroid);
                        double c = mag(facePoints_[i+1]->getPoint() - centroid);

                        // subtriangle centroid
                        vector3 subcentroid = facePoints_[i]->getPoint() + facePoints_[i+1]->getPoint() + centroid;
                        subcentroid = subcentroid / 3.0;
                  }
                  else
                  {
                        // edges length
                        double a = mag(facePoints_[i]->getPoint() - facePoints_[0]->getPoint());
                        double b = mag(facePoints_[i]->getPoint() - centroid);
                        double c = mag(facePoints_[0]->getPoint() - centroid);

                        // subtriangle centroid
                        vector3 subcentroid = facePoints_[i]->getPoint() + facePoints_[0]->getPoint() + centroid;
                        subcentroid = subcentroid / 3.0;
                  }

                  // semi-perimeter
                  double s = (a + b + c) / 2.0;

                  // subtriangle area
                  double subarea = sqrt(s*(s-a)*(s-b)*(s-c));

                  // compute numerator
                  numerator = numerator + subcentroid*subarea;

                  // compute denominator
                  denominator = denominator + subarea;

            }

            // face center of mass
            centerOfMass_ = numerator / denominator;

      }

}

void Face::computeFaceAreaVector()
{
    //Creates two vectors from the center of mass and one of the points in the face
    vector3 tmp_vec1 = facePoints_[0]->getPoint() - centerOfMass_;
    vector3 tmp_vec2 = facePoints_[1]->getPoint() - centerOfMass_;

    // Computes the face normal by doing the cross product of the products (this is not the faceAreaVector)
    vector3 areaVector_tmp = (tmp_vec1^tmp_vec2);

    // Computes the norm of the cross product between two vectors
    double mag_vector_tmp = mag(areaVector_tmp);

    // Calculates the faceAreaVector
    areaVector_ = (areaVector_tmp/mag_vector_tmp)*area_;

}


void Face::setweightingFactor(double g_c)
{
    weightingFactor_ = g_c;
}



int Face::getOwner() const
{
    return owner_;
}

int Face::getNeighbour() const
{
    return neighbour_;
}

vector3 Face::getCenterOfMass() const
{
    return centerOfMass_;
}

vector3 Face::getFaceAreaVector() const
{
    return areaVector_;
}


std::ostream& operator<<(std::ostream& os, const Face& p)
{

    os << "[ " << std::endl;

    for (unsigned int i= 0; i < p.facePoints_.size() ; i++)
    {
        os << *p.facePoints_[i];
    }

    os << "]" << std::endl;

return os;
}
