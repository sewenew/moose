/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef BNDSCALCAUX_H
#define BNDSCALCAUX_H

#include "AuxKernel.h"

//Forward Declarations
class BndsCalcAux;

template<>
InputParameters validParams<BndsCalcAux>();

/**
 * Visualize the location of grain boundaries in a polycrystalline simulation.
 */
class BndsCalcAux : public AuxKernel
{
public:
  BndsCalcAux(const InputParameters & parameters);

protected:
  virtual Real computeValue();

  unsigned int _ncrys;
  std::vector<VariableValue *> _vals;
};

#endif //BNDSCALCAUX_H
