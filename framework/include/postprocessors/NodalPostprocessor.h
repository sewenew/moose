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

#ifndef NODALPOSTPROCESSOR_H
#define NODALPOSTPROCESSOR_H

// MOOSE includes
#include "Postprocessor.h"
#include "NodalUserObject.h"

// Forward Declarations
class NodalPostprocessor;

template<>
InputParameters validParams<NodalPostprocessor>();

class NodalPostprocessor :
  public NodalUserObject,
  public Postprocessor
{
public:
  NodalPostprocessor(const InputParameters & parameters);

  /**
   * Finalize.  This is called _after_ execute() and _after_
   * threadJoin()!  This is probably where you want to do MPI
   * communication!
   */
  virtual void finalize(){}
};

#endif
