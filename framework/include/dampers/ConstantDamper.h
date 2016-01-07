/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef CONSTANTDAMPER_H
#define CONSTANTDAMPER_H

// Moose Includes
#include "Damper.h"

//Forward Declarations
class ConstantDamper;

template<>
InputParameters validParams<ConstantDamper>();

/**
 * Simple constant damper.
 *
 * Modifies the non-linear step by applying a constant damping factor
 */
class ConstantDamper : public Damper
{
public:
  ConstantDamper(const InputParameters & parameters);

protected:

  /**
   * Return the constant damping value.
   */
  virtual Real computeQpDamping();

  /// The constant amount of the Newton update to take.
  Real _damping;
};

#endif //CONSTANTDAMPER_H
