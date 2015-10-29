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

#ifndef EIGENKERNEL_H
#define EIGENKERNEL_H

#include "KernelBase.h"

//Forward Declarations
class EigenKernel;
class EigenSystem;

template<>
InputParameters validParams<EigenKernel>();

/*
 * The behavior of this kernel is controlled by one problem-wise global parameter
 *    eigen_on_current - bool, to indicate if this kernel is operating on the current solution or old solution
 * This kernel also obtain the postprocessor for eigenvalue by one problem-wise global parameter
 *    eigen_postprocessor - string, the name of the postprocessor to obtain the eigenvalue
 */
class EigenKernel : public KernelBase
{
public:
  // See KernelBase base for documentation of these overridden methods
  virtual void computeResidual();
  virtual void computeJacobian();
  virtual void computeOffDiagJacobian(unsigned int /*jvar*/) {}
  virtual void computeOffDiagJacobianScalar(unsigned int /*jvar*/) {}

  EigenKernel(const InputParameters & parameters);
  virtual bool isActive();

protected:
  virtual Real computeQpResidual() = 0;
  virtual Real computeQpJacobian();

  /// Holds the solution at current quadrature points
  VariableValue & _u;

  /// Holds the solution gradient at the current quadrature points
  VariableGradient & _grad_u;

  /// flag for as an eigen kernel or a normal kernel
  bool _eigen;

  /// EigenKernel always lives in EigenSystem
  EigenSystem * _eigen_sys;

  /// A pointer to the eigenvalue that is stored in a postprocessor
  // This is a pointer so that the method for retrieval (old vs current) may be changed
  const Real * _eigenvalue;
};

#endif //EIGENKERNEL_H
