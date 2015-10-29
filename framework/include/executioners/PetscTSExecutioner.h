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

#ifndef PETSCTSEXECUTIONER_H
#define PETSCTSEXECUTIONER_H

#include "libmesh/petsc_macro.h"
#if defined(LIBMESH_HAVE_PETSC) && !PETSC_VERSION_LESS_THAN(3,4,0)
#if 0 // This seems to be broken right now -- Moose::TimeSteppingScheme undefined

#include "Executioner.h"
#include "InputParameters.h"

// System includes
#include <string>

// Forward Declarations
class PetscTSExecutioner;
class TimeStepper;
class FEProblem;



enum TimeStepperStatus {
  STATUS_ITERATING                = 0,
  STATUS_CONVERGED_TIME           = 1,
  STATUS_CONVERGED_ITS            = 2,
  STATUS_DIVERGED_NONLINEAR_SOLVE = -1,
  STATUS_DIVERGED_STEP_REJECTED   = -2
};

template<>
InputParameters validParams<PetscTSExecutioner>();

/**
 * Transient executioners solve time steps sequentially.
 */
class PetscTSExecutioner: public Executioner
{
public:
  /**
   * Constructor
   *
   * @param parameters The parameters object holding data for the class to use.
   * @return Whether or not the solve was successful.
   */
  PetscTSExecutioner(const InputParameters & parameters);

  virtual ~PetscTSExecutioner();

  virtual void execute();

protected:
  TimeStepper *_time_stepper;
  bool keepGoing(TimeStepperStatus status, Real time) const;
};
#endif // This seems to be broken right now -- Moose::TimeSteppingScheme undefined
#endif
#endif // PETSCTSEXECUTIONER_H
