/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef NAVIERSTOKESMATERIAL_H
#define NAVIERSTOKESMATERIAL_H

#include "Material.h"


//Forward Declarations
class NavierStokesMaterial;

template<>
InputParameters validParams<NavierStokesMaterial>();

/**
 * This is the base class all materials should use if you are trying
 * to use the Navier-Stokes Kernels.
 *
 * Note that the derived class just needs to compute dynamic_viscocity
 * then call this class's computeProperties() function.
 *
 * Also make sure that the derived class's validParams function just
 * adds to this class's validParams.
 *
 * Finally, note that this Material _isn't_ registered with the
 * MaterialFactory.  The reason is that by itself this material
 * doesn't work!  You _must_ derive from this material and compute
 * dynamic_viscocity!
 */
class NavierStokesMaterial : public Material
{
public:
  NavierStokesMaterial(const InputParameters & parameters);

protected:

  /**
   * Must be called _after_ the child class computes dynamic_viscocity.
   */
  virtual void computeProperties();

  const unsigned int _mesh_dimension;

  VariableGradient& _grad_u;
  VariableGradient& _grad_v;
  VariableGradient& _grad_w;

  MaterialProperty<RealTensorValue>& _viscous_stress_tensor;
  MaterialProperty<Real>&            _thermal_conductivity;
  MaterialProperty<Real>&            _dynamic_viscosity;

  // Also store the "cal A" matrices at each quadrature point as material
  // poperties.  These are defined in the compns notes and are needed for
  // computing strong and weak residual values and Jacobian entries, so it's
  // good if we reuse them...
  MaterialProperty<std::vector<RealTensorValue> >& _calA;

  // The "velocity column" matrices.  _calC[_qp][k] is a tensor with the
  // velocity vector in the k'th column.  See notes for additional details.
  MaterialProperty<std::vector<RealTensorValue> >& _calC;

  // The energy equation inviscid flux matrix components.  There are n_vars of
  // these for each dimension, so in 3D, 3*5=15 different matrices.
  // See notes for additional details.
  MaterialProperty<std::vector<std::vector<RealTensorValue> > >& _calE;

  // Convenient storage for all of the velocity gradient components so
  // we can refer to them in a loop.
  std::vector<VariableGradient*> _vel_grads;

  // Specific heat at constant volume, treated as single
  // constant values.
  Real _R;
  Real _gamma;
  Real _Pr;

  // Coupled values needed to compute strong form residuals
  // for SUPG stabilization...
  VariableValue& _u_vel;
  VariableValue& _v_vel;
  VariableValue& _w_vel;

  // Temperature is needed to compute speed of sound
  VariableValue& _temperature;

  // Enthalpy is needed in computing energy equation strong residuals
  VariableValue& _enthalpy;

  // Main solution variables are all needed for computing strong residuals
  VariableValue& _rho;
  VariableValue& _rho_u;
  VariableValue& _rho_v;
  VariableValue& _rho_w;
  VariableValue& _rho_e;

  // Time derivative values for dependent variables
  VariableValue& _drho_dt;
  VariableValue& _drhou_dt;
  VariableValue& _drhov_dt;
  VariableValue& _drhow_dt;
  VariableValue& _drhoe_dt;

  // Gradients
  VariableGradient& _grad_rho;
  VariableGradient& _grad_rho_u;
  VariableGradient& _grad_rho_v;
  VariableGradient& _grad_rho_w;
  VariableGradient& _grad_rho_e;

  // The real-valued material properties representing the element stabilization
  // parameters for each of the equations.
  MaterialProperty<Real>& _hsupg;
  MaterialProperty<Real>& _tauc;
  MaterialProperty<Real>& _taum;
  MaterialProperty<Real>& _taue;

  // The (vector-valued) material property which is the strong-form
  // residual at each quadrature point.
  MaterialProperty<std::vector<Real> > & _strong_residuals;

private:
  // To be called from computeProperties() function to compute _hsupg
  void compute_h_supg(unsigned qp);

  // To be called from computeProperties() function to compute _tauc, _taum, _taue
  void compute_tau(unsigned qp);

  // To be called from computeProperties() function to compute the strong residual of each equation.
  void compute_strong_residuals(unsigned qp);
};

#endif //NAVIERSTOKESMATERIAL_H
