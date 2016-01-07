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

#ifndef SPLITBASEDPRECONDITIONER_H
#define SPLITBASEDPRECONDITIONER_H

// MOOSE includes
#include "MoosePreconditioner.h"

// Forward declarations
class NonlinearSystem;
class SplitBasedPreconditioner;

template<>
InputParameters validParams<SplitBasedPreconditioner>();

/**
 * Implements a preconditioner designed to map onto PETSc's PCFieldSplit.
 */
class SplitBasedPreconditioner :  public MoosePreconditioner
{
public:
  /**
   *  Constructor. Initializes SplitBasedPreconditioner data structures
   */
  SplitBasedPreconditioner(const InputParameters & parameters);

  /**
   * Destructor.
   */
  virtual ~SplitBasedPreconditioner(){};

  /**
   * Sets up internals.
   */
  void setup();

protected:
  /// The nonlinear system this FSP is associated with (convenience reference)
  NonlinearSystem & _nl;
};

#endif //SPLITBASEDPRECONDITIONER_H
