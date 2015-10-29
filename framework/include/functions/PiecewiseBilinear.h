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

#ifndef PIECEWISEBILINEAR_H
#define PIECEWISEBILINEAR_H

#include "MooseTypes.h"
#include "Function.h"
#include "BilinearInterpolation.h"
#include "ColumnMajorMatrix.h"

class PiecewiseBilinear;

template<>
InputParameters validParams<PiecewiseBilinear>();

/**
 * Base class for function objects.  Functions override value to supply a
 * value at a point.
 */
class PiecewiseBilinear : public Function
{
public:
  PiecewiseBilinear(const InputParameters & parameters);
  virtual ~PiecewiseBilinear();

  /**
   * This function will return a value based on the first input argument only.
   */
  virtual Real value(Real t, const Point & pt);



private:
  MooseSharedPointer<BilinearInterpolation> _bilinear_interp;
  const std::string _data_file_name;
  const int _axis;
  const int _yaxis;
  const int _xaxis;
  const bool _axisValid;
  const bool _yaxisValid;
  const bool _xaxisValid;
  const Real _scale_factor;
  const bool _radial;


  void parse( std::vector<Real> & x,
              std::vector<Real> & y,
              ColumnMajorMatrix & z);
};

#endif //PIECEWISEBILINEAR_H
