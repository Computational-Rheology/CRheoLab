@page usefullFunctions Useful Functions
@tableofcontents

----


This page is dedicated to the useful Functions for the volSacalarField

### General Information (Miguel)

The useful functions created for the volField Class aim at providing a set of utilities to manipulate objects of the class and/or create new objects based on previously created objects of the class.

----
### Tensor Invariants (Miguel v3)
The volField class can comprise fields of type tensor and symmetric tensor. For these the 3 invariants invariants can be calculated.

For **tensors**
\f[
\mathbf{T}=\begin{bmatrix}
T_{11} & T_{12} & T_{13} \\ 
T_{21} & T_{22} & T_{23}\\ 
T_{31} & T_{32} & T_{33}
\end{bmatrix}
\f]

The invariants are the following:
\f[
I_{1}=T_{11}+T_{22}+T_{33}
\f]
\f[
I_{2}=T_{11}T_{22}+T_{11}T_{33}+T_{22}T_{33}-T_{12}T_{21}-T_{23}T_{32}-T_{13}T_{31}
\f]
\f[
I_{3}=-T_{13}T_{22}T_{31}+T_{12}T_{23}T_{31}+T_{13}T_{21}T_{32}-T_{11}T_{23}T_{32}-T_{12}T_{21}T_{33}+T_{11}T_{22}T_{33}
\f]

For **symmetric tensors**
\f[
\mathbf{T}=\begin{bmatrix}
T_{11} & T_{12} & T_{13} \\ 
T_{12} & T_{22} & T_{23}\\ 
T_{13} & T_{23} & T_{33}
\end{bmatrix}
\f]

The invariants are the following:
\f[
I_{1}=T_{11}+T_{22}+T_{33}
\f]
\f[
I_{2}=T_{11}*T_{22}+T_{11}T_{33}+T_{22}T_{33}-T_{12}^2-T_{23}^2-T_{13}^2
\f]
\f[
I_{3}=-T_{13}^2 T_{22}+T_{12}T_{23}T_{31}+T_{13}T_{12}T_{23}-T_{11}T_{23}^2-T_{12}^2 T_{33}+T_{11}T_{22}T_{33}
\f]

----
### Max and Min from a Field (Miguel)
For operations like shift field, the shift can be performed with the maximum or minimum value of the field

The calculation of the minimum or maximum value of the field depends on the type of field:

* **Scalar fields**: are the maximum of minimum of the field
* **Vector fields**: are the maximum of minimum of the vector magnitude
* **Tensor and Symmetric Tensor fields**: are the maximum of minimum of the second invariant of the tensor


----
### Shift Field (Paulo)
line1

line2

line3

Shift the field with a constant (scalar, vector, symTensor and tensor)
The constant is the
minimum value
maximum value


----
### Scale Field (Paulo)
line1

line2

line3

Scale the field with a constant scalar (same documentation as Shift)


----
### Vector Field related (Karinate)
line1

line2

line3

Project the vectors in one direction
Create a scalarField with the magnitude of the vector


----
### Tensor Field related (Mohamed)
line1

line2



Create a vector field with component of the tensor in one direction
Create a scalarField with the Tensor Invariants (I1, I2 and I3)


----
