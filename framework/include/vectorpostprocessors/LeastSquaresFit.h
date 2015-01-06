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

#ifndef LEAST_SQUARES_FIT_H
#define LEAST_SQUARES_FIT_H

#include "GeneralVectorPostprocessor.h"

//Forward Declarations
class LeastSquaresFit;

template<>
InputParameters validParams<LeastSquaresFit>();

/**
 *  LeastSquaresFit is a VectorPostprocessor that performs a least squares
 *  fit on data calculated in another VectorPostprocessor.
 */

class LeastSquaresFit :
  public GeneralVectorPostprocessor
{
public:
  /**
    * Class constructor
    * @param name The name of the object
    * @param parameters The input parameters
    */
  LeastSquaresFit(const std::string & name, InputParameters parameters);

  /**
   * Destructor
   */
  virtual ~LeastSquaresFit() {}

  /**
   * Initialize, clears old results
   */
  virtual void initialize();

  /**
   * Perform the least squares fit
   */
  virtual void execute();

  ///@{
  /**
   * no-op because the other VectorPostprocessor is already parallel consistent
   */
  virtual void finalize() {}
  virtual void threadJoin(const UserObject &) {}
  ///@}

protected:
  /// The name of the VectorPostprocessor on which to perform the fit
  VectorPostprocessorName _vpp_name;

  /// The order of the polynomial fit to be performed
  unsigned int _order;

  /// The name of the variables storing the x, y data
  const std::string _x_name;
  const std::string _y_name;

  /// The variables with the x, y data to be fit
  const VectorPostprocessorValue & _x_values;
  const VectorPostprocessorValue & _y_values;

  /// The type of output
  const MooseEnum _output_type;

  /// The number of samples to be taken
  unsigned int _num_samples;

  /// The variables used to write out samples of the least squares fit
  VectorPostprocessorValue * _sample_x;
  VectorPostprocessorValue * _sample_y;

  /// The variable used to write out the coefficients of the fit
  VectorPostprocessorValue * _coeffs;

};

#endif
