/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef COMPUTE2DFINITESTRAIN_H
#define COMPUTE2DFINITESTRAIN_H

#include "ComputeFiniteStrain.h"

/**
 * Compute2DFiniteStrain defines a strain increment and a rotation increment
 * for finite strains in 2D geometries, handling the out of plane strains.
 * Compute2DFiniteStrain contains a virtual method to define the strain_zz
 * as a nonzero value in the inherited classes ComputePlaneFiniteStrain
 * ComputeGeneralizedPlaneFiniteStrain and ComputeAxisymmetricRZFiniteStrain.
 */
class Compute2DFiniteStrain : public ComputeFiniteStrain
{
public:
  Compute2DFiniteStrain(const InputParameters & parameters);

protected:
  virtual void computeProperties();
  virtual Real computeDeformGradZZ() = 0;
  virtual Real computeDeformGradZZold() = 0;
};

#endif //COMPUTE2DFINITESTRAIN_H
