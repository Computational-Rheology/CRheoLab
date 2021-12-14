
@page usefullFunctions Useful Functions
@tableofcontents

----


This page is dedicated to the useful Functions for the volScalarField

### General Information (Miguel)

The useful functions created for the volField Class aim at providing a set of utilities to manipulate objects of the class and/or create new objects based on
previously created objects of the class. That will include for example calculating the maximum and minimum of a field, the shift and scale of a field, 
the projection of a vector, and the tensor invariants.

----
### Max and Min from a Field (Miguel)
For operations like shift field, the shift can be performed with the maximum or minimum value of the field

The calculation of the minimum or maximum value of the field depends on the type of field:

* **Scalar fields**: are the maximum or minimum of the field
* **Vector fields**: are the maximum or minimum of the vector magnitude
* **Tensor and Symmetric Tensor fields**: are the maximum or minimum of the second invariant of the tensor


----
### Shift Field (Paulo)

Shift the field with a constant (scalar, vector, symTensor and tensor) The constant is the minimum value maximum value

To perform this operation, there are two strategies:
1- As a volField class methods:
receiving a constant as shift quantity parameter; using maximum or minimum value of the field (using instead shiftMaxField and shiftMixField methods).
2- As a function application: 
overloading the + and - operators, to perform addition or subtraction between a volField object and a constant.


----
### Scale Field (Paulo)

Scale the field with a constant scalar (same documentation as Shift)

To perform this operation a volField class method is available, that receives a constant as scale quantity parameter.


----

### Project a VectorField (Karinate) 

1- We need to compute the projection of a vectorField to determine the component of a vector in a given direction.
 
The documentation for calculating the vector projection is adapted from \cite  Greenshields (2015). OpenFoam Programmers Guide.

A Scalar is any property that can be represented by a single real number or a one-component quantity that is invariant under rotations of the coordinate system i.e. mass m, volume V.

A vector is a quantity (entity) that has both magnitude and direction i.e. velocity, acceleration.

To project a vectorField, we must first perform 2 algebraic operations;scalar multiplication and vector multiplication (inner product)	

 Scalar multiplication of the 3-Dimensional vector \f$ \vec{V}= \ {V}_x\hat{i}\ + \ {V}_y\hat{j}\ + {V}_z\hat{k}\f$ by scalar \f$ S \f$ 

*    \f$ \ {S}{V}= \ {S}{V}_x\hat{i}\ + \ {S}{V}_y\hat{j}\ + {S}{V}_z\hat{k} \f$ 
	
Scalar multiplication is commutative (order independent) and is performed by multiplying (scaling) all the vector components by the scalar to obtain a vector product. 


 Vector (Inner product) multiplication of two vectors \f$ \vec{V} and \:\vec{U} \f$  

*     \f$ \vec{V}= \ {V}_x\hat{i}\ + \ {V}_y\hat{j}\ + {V}_z\hat{k} \f$ 

*     \f$ \vec{U}= \ {U}_x\hat{i}\ + \ {U}_y\hat{j}\ + {U}_z\hat{k} \f$ 


*     \f$ \vec{V}\cdot\vec{U}= \ {V}_x{U}_x + \ {V}_y{U}_y + \ {V}_z{U}_z \f$ 

The dot product of two vectors is non-commutative (order dependent) and produces a scalar.

----

### To compute the magnitude of a vector (Karinate)

2- We need to compute the magnitude of a vectorField

The documentation for calculating the vector magnitude is adapted from \cite  Gradshteyn and Ryzhik (2000). Tables of Integrals, Series and Products.

To calculate the magnitude of a vectorField, we have to perform two algebraic operations; magnitude squared of a 3-Dimensional vector and magnitude (square root of the magnitude squared)

Magnitude squared of a 3-Dimensional vector \f$ \vec{V} \f$ is the inner product of the vector with itself;

*     \f$ \vec{V}= \ {V}_x\hat{i}\ + \ {V}_y\hat{j}\ + {V}_z\hat{k} \f$

*     \f$ |V|^2 = \ {V}:{V} = \ {V}_x{V}_x + \ {V}_y{V}_y + \ {V}_z{V}_z \f$ 


Magnitude for the vector, which is the square root of the magnitude squared \f$ |V|^2 \f$ for a vector 

*      \f$ |V| = \sqrt {|V|^2} = \sqrt {V:V} \f$ 


*     \f$ |V| = \sqrt {{V}_x{V}_x + \ {V}_y{V}_y + \ {V}_z{V}_z} \f$ 

----

### Tensor Field related (Mohamed)
1- Create a vector field with component of the tensor in one direction

The component of the tensor in one direction is obtained by multiplying the transpose of the tensor by the unity vector in that direction. As for example for the direction of x, the mathematical operation takes the following form as shown in Eq(1): 

\begin{equation}
\begin{pmatrix}
\sigma _{xx} & \sigma _{xy} & \sigma _{xz}\\ 
\newline
\sigma _{yx}& \sigma _{yy} &\sigma _{yz} \\ 
\newline
\sigma _{zx}& \sigma _{zy} & \sigma _{zz}\ 
\end{pmatrix}^{t}\begin{pmatrix}
1\\ 
\newline
0\\ 
\newline
0
\end{pmatrix}
\end{equation}

That could be achieved in the CrheoLab using the function projectTensorField, where a general vector direction is avaiable.


2- Create a scalarField with the Tensor Invariants (I1, I2 and I3)

The first tensor invariant (I1) is calculated as the trace of the tensor (T) i.e. the summation of the main diagonal. The second tensor invariant (I2) is calculated as half the extraction of the square of the tensor’s trace and the trace of the square of the tensor. The third tensor invariant (I3) is calculated as the determine of the tensor. The mathematical description is as shown in Eqs(2)-(4) for I1, I2, and I3 respectively:

\begin{equation}
I1 =  tr\left [ T \right ] = \sigma _{xx} +\sigma _{yy} +\sigma _{zz}
\end{equation}

\begin{equation}
I2 = \frac{1}{2} {\left [ \left [ \sigma _{xx} +\sigma _{yy} +\sigma _{zz}  \right ]^{2} -tr\left [ T .T \right ]\right ]= \sigma _{xx}\sigma _{yy}+\sigma _{yy}\sigma _{zz}+\sigma _{xx}\sigma _{zz}-\sigma _{xy}\sigma _{yx}-\sigma _{yz}\sigma _{zy}-\sigma _{xz}\sigma _{zx}}
\end{equation}

\begin{equation}
I3 = \left | T \right | =\sigma _{xx} \left [\sigma _{yy}\sigma _{zz}-\sigma _{yz}\sigma _{zy}  \right ] - \sigma _{xy} \left [ \sigma _{yx}\sigma _{zz}-\sigma _{yz}\sigma _{zx} \right ]+\sigma _{xz}\left [ \sigma _{yx}\sigma _{zy}-\sigma _{yy}\sigma _{zx} \right ]
\end{equation}

In the CrheoLab, they are calculated using the functions I1, I2, and I3 respectively.

----
