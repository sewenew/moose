/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef NSMOMENTUMCONVECTIVEWEAKSTAGNATIONBC_H
#define NSMOMENTUMCONVECTIVEWEAKSTAGNATIONBC_H

#include "NSWeakStagnationBC.h"

// Forward Declarations
class NSMomentumConvectiveWeakStagnationBC;

template<>
InputParameters validParams<NSMomentumConvectiveWeakStagnationBC>();


/**
 * The convective part (sans pressure term) of the momentum equation
 * boundary integral evaluated at specified stagnation temperature,
 * stagnation pressure, and flow direction values.
 */
class NSMomentumConvectiveWeakStagnationBC : public NSWeakStagnationBC
{

public:
  NSMomentumConvectiveWeakStagnationBC(const InputParameters & parameters);

  virtual ~NSMomentumConvectiveWeakStagnationBC(){}

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
  virtual Real computeQpOffDiagJacobian(unsigned jvar);

  // Required parameters
  unsigned _component;
};

#endif // NSMOMENTUMCONVECTIVEWEAKSTAGNATIONBC_H
