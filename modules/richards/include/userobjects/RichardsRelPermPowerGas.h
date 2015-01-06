/*****************************************/
/* Written by andrew.wilkins@csiro.au    */
/* Please contact me if you make changes */
/*****************************************/

#ifndef RICHARDSRELPERMPOWERGAS_H
#define RICHARDSRELPERMPOWERGAS_H

#include "RichardsRelPerm.h"

class RichardsRelPermPowerGas;


template<>
InputParameters validParams<RichardsRelPermPowerGas>();

/**
 * PowerGas form of relative permeability
 * Define s = (seff - simm)/(1 - simm).
 * Then relperm = 1 - (n+1)(1-s)^n + n(1-s)^(n+1) if s<simm, otherwise relperm=1
 */
class RichardsRelPermPowerGas : public RichardsRelPerm
{
public:
  RichardsRelPermPowerGas(const std::string & name, InputParameters parameters);

  /**
   * Relative permeability
   * @param seff effective saturation
   */
  Real relperm(Real seff) const;

  /**
   * Derivative of relative permeability wrt seff
   * @param seff effective saturation
   */
  Real drelperm(Real seff) const;

  /**
   * Second derivative of relative permeability wrt seff
   * @param seff effective saturation
   */
  Real d2relperm(Real seff) const;

protected:

  /// immobile saturation
  Real _simm;

  /// exponent
  Real _n;

};

#endif // RICHARDSRELPERMPOWERGAS_H
