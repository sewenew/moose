/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef RANKTWOSCALARAUX_H
#define RANKTWOSCALARAUX_H

#include "AuxKernel.h"
#include "RankTwoTensor.h"

class RankTwoScalarAux;

/**
 * RankTwoScalarAux provides scalar values of RankTwoTensor
 * Currently supported are VonMisesStress, EquivalentPlasticStrain, Hydrostatic, L2norm,
 * MaxPrincipal, MidPrincipal, MinPrincipal
 */

template<>
InputParameters validParams<RankTwoScalarAux>();

class RankTwoScalarAux : public AuxKernel
{
public:
  RankTwoScalarAux(const InputParameters & parameters);
  virtual ~RankTwoScalarAux() {}

protected:
  virtual Real computeValue();
  Real calcEigenValues();

  const MaterialProperty<RankTwoTensor> & _tensor;
  MooseEnum _scalar_type;

private:
};

#endif //RANKTWOSCALARAUX_H
