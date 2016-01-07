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

#ifndef COMPUTEDIRACTHREAD_H
#define COMPUTEDIRACTHREAD_H

// Moose Includes
#include "ParallelUniqueId.h"
#include "ThreadedElementLoop.h"

// libMesh includes
#include "libmesh/elem_range.h"

// Forward declarations
class NonlinearSystem;
class DiracKernel;

typedef StoredRange<std::set<const Elem *>::const_iterator, const Elem *> DistElemRange;


class ComputeDiracThread : public ThreadedElementLoop<DistElemRange>
{
public:
  ComputeDiracThread(FEProblem & feproblem, NonlinearSystem & system, SparseMatrix<Number> * jacobian = NULL);

  // Splitting Constructor
  ComputeDiracThread(ComputeDiracThread & x, Threads::split);

  virtual ~ComputeDiracThread();

  virtual void subdomainChanged();
  virtual void pre();
  virtual void onElement(const Elem *elem);
  virtual void postElement(const Elem * /*elem*/);
  virtual void post();

  void join(const ComputeDiracThread & /*y*/);

protected:
  SparseMatrix<Number> * _jacobian;
  NonlinearSystem & _sys;

  /// Storage for DiracKernel objects
  const MooseObjectWarehouse<DiracKernel> & _dirac_kernels;
};

#endif //COMPUTEDIRACTHREAD_H
