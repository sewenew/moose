#ifndef JINTEGRAL_H
#define JINTEGRAL_H

#include "ElementIntegralPostprocessor.h"
#include "CrackFrontDefinition.h"

//Forward Declarations
class JIntegral;

template<>
InputParameters validParams<JIntegral>();

/**
 * This postprocessor computes the J-Integral
 *
 */
class JIntegral: public ElementIntegralPostprocessor
{
public:
  JIntegral(const std::string & name, InputParameters parameters);
  virtual Real getValue();

protected:
  virtual void initialSetup();
  virtual Real computeQpIntegral();
  VariableValue & _scalar_q;
  /// The gradient of the scalar q field
  VariableGradient & _grad_of_scalar_q;
  const CrackFrontDefinition * const _crack_front_definition;
  bool _has_crack_front_node_index;
  const unsigned int _crack_front_node_index;
  bool _treat_as_2d;
  MaterialProperty<ColumnMajorMatrix> & _Eshelby_tensor;
  MaterialProperty<RealVectorValue> * _J_thermal_term_vec;
  bool _convert_J_to_K;
  bool _has_symmetry_plane;
  Real _poissons_ratio;
  Real _youngs_modulus;

};

#endif //JINTEGRAL3D_H
