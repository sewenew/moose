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

#ifndef LINEMATERIALTENSORSAMPLER_H
#define LINEMATERIALTENSORSAMPLER_H

#include "LineMaterialSamplerBase.h"
#include "MaterialTensorCalculator.h"

//Forward Declarations
class LineMaterialSymmTensorSampler;

template<>
InputParameters validParams<LineMaterialSymmTensorSampler>();

/**
 * This class samples SymmTensor material properties for the integration points
 * in all elements that are intersected by a user-defined line.  It provides
 * access to the full set of options for reducing the SymmTensor to a scalar.
 */
class LineMaterialSymmTensorSampler :
  public LineMaterialSamplerBase<SymmTensor>,
  public MaterialTensorCalculator
{
public:
  /**
   * Class constructor
   * Sets up variables for output based on the properties to be output
   * @param name The name of the class
   * @param parameters The input parameters
   */
  LineMaterialSymmTensorSampler(const std::string & name, InputParameters parameters);

  virtual ~LineMaterialSymmTensorSampler() {}

  /**
   * Reduce the material property to a scalar for output
   * Call through to getTensorQuantity to access the full set of options for reducing
   * the SymmTensor to a scalar quantity.
   * @param property The material property
   * @param curr_point The point corresponding to this material property
   * @return A scalar value from this material property to be output
   */
  virtual Real getScalarFromProperty(SymmTensor &property, const Point * curr_point);
};

#endif
