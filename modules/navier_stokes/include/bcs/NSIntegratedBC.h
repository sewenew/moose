/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef NSINTEGRATEDBC_H
#define NSINTEGRATEDBC_H

#include "IntegratedBC.h"

// Forward Declarations
class NSIntegratedBC;

template<>
InputParameters validParams<NSIntegratedBC>();

/**
 * This class couples together all the variables
 * for the compressible Navier-Stokes equations to
 * allow them to be used in derived IntegratedBC
 * classes.  This prevents duplication of lines
 * of code between e.g. the momentum and energy
 * equations, since they have a lot in common.
 */
class NSIntegratedBC : public IntegratedBC
{
public:
  NSIntegratedBC(const InputParameters & parameters);

  virtual ~NSIntegratedBC(){}

protected:
  /**
   * Not defined here, need to be defined in derived classes.
   */
  // virtual Real computeQpResidual();
  // virtual Real computeQpJacobian();
  // virtual Real computeQpOffDiagJacobian(unsigned jvar);

  // Coupled variables
  const VariableValue & _u_vel;
  const VariableValue & _v_vel;
  const VariableValue & _w_vel;

  const VariableValue & _rho;
  const VariableValue & _rho_u;
  const VariableValue & _rho_v;
  const VariableValue & _rho_w;
  const VariableValue & _rho_e;

  // Gradients
  const VariableGradient & _grad_rho;
  const VariableGradient & _grad_rho_u;
  const VariableGradient & _grad_rho_v;
  const VariableGradient & _grad_rho_w;
  const VariableGradient & _grad_rho_e;

  // Variable numberings
  unsigned _rho_var_number;
  unsigned _rhou_var_number;
  unsigned _rhov_var_number;
  unsigned _rhow_var_number;
  unsigned _rhoe_var_number;

  // Integrated BC can use Mat. properties...
  const MaterialProperty<Real> & _dynamic_viscosity;
  const MaterialProperty<RealTensorValue> & _viscous_stress_tensor; // Includes _dynamic_viscosity

  // Required parameters
  Real _gamma;
  Real _R;

  // Helper function for mapping Moose variable numberings into
  // the "canonical" numbering for the compressible NS equations.
  unsigned map_var_number(unsigned var);
};


#endif // NSINTEGRATEDBC_H
