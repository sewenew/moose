/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef COMPUTESTRAINBASE_H
#define COMPUTESTRAINBASE_H

#include "Material.h"
#include "RankTwoTensor.h"
#include "ElasticityTensorR4.h"
#include "RotationTensor.h"
#include "DerivativeMaterialInterface.h"

/**
 * ComputeStrainBase is the base class for strain tensors
 */
class ComputeStrainBase : public DerivativeMaterialInterface<Material>
{
public:
  ComputeStrainBase(const InputParameters & parameters);
  virtual ~ComputeStrainBase() {}

protected:
  virtual void initQpStatefulProperties();
  virtual void computeProperties() = 0;

  /// Coupled displacement variables
  unsigned int _ndisp;
  std::vector<VariableValue *> _disp;
  std::vector<VariableGradient *> _grad_disp;
  std::vector<VariableGradient *> _grad_disp_old;

  VariableValue & _T;
  const Real _T0;
  const Real _thermal_expansion_coeff;

  std::string _base_name;

  MaterialProperty<RankTwoTensor> & _mechanical_strain;

  MaterialProperty<RankTwoTensor> & _total_strain;

  const bool _stateful_displacements;
};

#endif //COMPUTESTRAINBASE_H
