#ifndef ELASTICENERGYMATERIAL_H
#define ELASTICENERGYMATERIAL_H

#include "DerivativeBaseMaterial.h"

// Forward Declaration
class ElasticEnergyMaterial;
class RankTwoTensor;
class ElasticityTensorR4;

template<>
InputParameters validParams<DerivativeBaseMaterial>();

/**
 * Material class to compute the elastic free energy and its derivatives
 */
class ElasticEnergyMaterial : public DerivativeBaseMaterial
{
public:
  ElasticEnergyMaterial(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeF();
  virtual Real computeDF(unsigned int);
  virtual Real computeD2F(unsigned int, unsigned int);

  std::string _base_name;

  /// Stress tensor
  const MaterialProperty<RankTwoTensor> & _stress;
  // std::vector<const MaterialProperty<RankTwoTensor> *> _dstress;
  // std::vector<std::vector<const MaterialProperty<RankTwoTensor> *> > _d2stress;

  ///@{ Elasticity tensor derivatives
  const MaterialProperty<ElasticityTensorR4> & _elasticity_tensor;
  std::vector<const MaterialProperty<ElasticityTensorR4> *> _delasticity_tensor;
  std::vector<std::vector<const MaterialProperty<ElasticityTensorR4> *> > _d2elasticity_tensor;
  ///@}

  ///@{ Strain and derivatives
  const MaterialProperty<RankTwoTensor> & _strain;
  std::vector<const MaterialProperty<RankTwoTensor> *> _dstrain;
  std::vector<std::vector<const MaterialProperty<RankTwoTensor> *> > _d2strain;
  ///@}
};

#endif //ELASTICENERGYMATERIAL_H
