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

#ifndef COMPUTENODALKERNELBCSTHREAD_H
#define COMPUTENODALKERNELBCSTHREAD_H

#include "NodalKernelWarehouse.h"
#include "MooseMesh.h"
#include "ThreadedNodeLoop.h"

class AuxiliarySystem;

class ComputeNodalKernelBcsThread : public ThreadedNodeLoop<ConstBndNodeRange, ConstBndNodeRange::const_iterator>
{
public:
  ComputeNodalKernelBcsThread(FEProblem & fe_problem, AuxiliarySystem & sys, std::vector<NodalKernelWarehouse> & nodal_kernels);
  // Splitting Constructor
  ComputeNodalKernelBcsThread(ComputeNodalKernelBcsThread & x, Threads::split split);

  virtual void pre();

  virtual void onNode(ConstBndNodeRange::const_iterator & node_it);

  void join(const ComputeNodalKernelBcsThread & /*y*/);

protected:
  AuxiliarySystem & _sys;

  std::vector<NodalKernelWarehouse> & _nodal_kernels;

  //Number of contributions cached up
  unsigned int _num_cached;
};

#endif //COMPUTENODALKERNELBCSTHREAD_H
