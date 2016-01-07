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

#ifndef PIECEWISELINEAR_H
#define PIECEWISELINEAR_H

#include "Piecewise.h"

// Forward declarations
class PiecewiseLinear;

template<>
InputParameters validParams<PiecewiseLinear>();

/**
 * Base class for function objects.  Functions override value to supply a
 * value at a point.
 */
class PiecewiseLinear : public Piecewise
{
public:
  PiecewiseLinear(const InputParameters & parameters);
  virtual ~PiecewiseLinear();

  /**
   * Get the value of the function (based on time only)
   * \param t The time
   * \param pt The point in space (x,y,z) (unused)
   * \return The value of the function at the specified time
   */
  virtual Real value(Real t, const Point & pt);

  /**
   * Get the time derivative of the function (based on time only)
   * \param t The time
   * \param pt The point in space (x,y,z) (unused)
   * \return The time derivative of the function at the specified time
   */
  virtual Real timeDerivative(Real t, const Point & pt);

  virtual Real integral();

  virtual Real average();
};

#endif
