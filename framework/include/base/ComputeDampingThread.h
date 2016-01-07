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

#ifndef COMPUTEDAMPINGTHREAD_H
#define COMPUTEDAMPINGTHREAD_H

// MOOSE includes
#include "ThreadedElementLoop.h"
#include "MooseObjectWarehouse.h"

// libMesh includes
#include "libmesh/elem_range.h"

// Forward declarations
class NonlinearSystem;
class Damper;

class ComputeDampingThread : public ThreadedElementLoop<ConstElemRange>
{
public:
  ComputeDampingThread(FEProblem & feproblem, NonlinearSystem & sys);

  // Splitting Constructor
  ComputeDampingThread(ComputeDampingThread & x, Threads::split split);

  virtual ~ComputeDampingThread();

  virtual void onElement(const Elem *elem);

  void join(const ComputeDampingThread & /*y*/);

  Real damping();

protected:
  Real _damping;
  NonlinearSystem & _nl;
  const MooseObjectWarehouse<Damper> & _dampers;
};

#endif //COMPUTEDAMPINGTHREAD_H
