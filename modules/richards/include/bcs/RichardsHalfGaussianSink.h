/*****************************************/
/* Written by andrew.wilkins@csiro.au    */
/* Please contact me if you make changes */
/*****************************************/

#ifndef RICHARDSHALFGAUSSIANSINK
#define RICHARDSHALFGAUSSIANSINK

#include "IntegratedBC.h"
#include "RichardsVarNames.h"

// Forward Declarations
class RichardsHalfGaussianSink;

template<>
InputParameters validParams<RichardsHalfGaussianSink>();

/**
 * Applies a fluid sink to the boundary.
 * The sink has strength
 * _maximum*exp(-(0.5*(p - c)/_sd)^2)*_m_func for p<c
 * _maximum*_m_func for p>=c
 * This is typically used for modelling evapotranspiration
 * from the top of a groundwater model
 */
class RichardsHalfGaussianSink : public IntegratedBC
{
public:
  RichardsHalfGaussianSink(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  /// maximum of the Gaussian sink
  Real _maximum;

  /// standard deviation of the Gaussian sink
  Real _sd;

  /// centre of the Gaussian sink
  Real _centre;

  /// multiplying function: all fluxes will be multiplied by this
  Function & _m_func;

  /**
   * holds info regarding the names of the Richards variables
   * and methods for extracting values of these variables
   */
  const RichardsVarNames & _richards_name_UO;

  /**
   * the index of this variable in the list of Richards variables
   * held by _richards_name_UO.  Eg
   * if richards_vars = 'pwater pgas poil' in the _richards_name_UO
   * and this kernel has variable = pgas, then _pvar = 1
   * This is used to index correctly into _viscosity, _seff, etc
   */
  unsigned int _pvar;

  /// porepressure (or porepressure vector for multiphase problems)
  MaterialProperty<std::vector<Real> > & _pp;

  /// d(porepressure_i)/dvariable_j
  MaterialProperty<std::vector<std::vector<Real> > > & _dpp_dv;
};

#endif //RICHARDSHALFGAUSSIANSINK
