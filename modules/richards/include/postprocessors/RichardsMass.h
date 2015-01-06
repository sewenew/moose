/*****************************************/
/* Written by andrew.wilkins@csiro.au    */
/* Please contact me if you make changes */
/*****************************************/

#ifndef RICHARDSMASS_H
#define RICHARDSMASS_H

#include "ElementIntegralVariablePostprocessor.h"
#include "RichardsVarNames.h"

//Forward Declarations
class RichardsMass;

template<>
InputParameters validParams<RichardsMass>();

/**
 * This postprocessor computes the fluid mass by integrating the density over the volume
 *
 */
class RichardsMass: public ElementIntegralVariablePostprocessor
{
public:
  RichardsMass(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeQpIntegral();

  /// userobject that holds Richards variable names
  const RichardsVarNames & _richards_name_UO;

  /// Richards variable number that we want the mass for
  unsigned int _pvar;

  /// Mass, or vector of masses in multicomponent situation
  MaterialProperty<std::vector<Real> > & _mass;
};

#endif
