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

#ifndef MOOSEPARSEDFUNCTION_H
#define MOOSEPARSEDFUNCTION_H

// std includes
#include <iostream>
#include <string>
#include <map>

// MOOSE includes
#include "Function.h"
#include "MooseParsedFunctionBase.h"

//Forward declarations
class MooseParsedFunction;
class MooseParsedFunctionWrapper;

template<>
InputParameters validParams<MooseParsedFunction>();

/**
 * This class is used to evaluate symbolic equations passed in to Moose through
 * the input file. It supports symbolic variables that you can change by putting
 * a different value in a reference returned by getVarAddr().
 *
 * Documentation for the Function Parser can be found at:
 * http://warp.povusers.org/FunctionParser/fparser.html
 */
class MooseParsedFunction :
  public Function,
  public MooseParsedFunctionBase
{
public:

  /**
   * Created from MooseSystem via the FunctionFactory.
   * @param parameters The input parameters
   */
  MooseParsedFunction(const InputParameters & parameters);

  /**
   * Destructor, it cleans up the libMesh::ParsedFunction object
   */
  virtual ~MooseParsedFunction();

  /**
   * Evaluate the equation at the given location. For 1-D and 2-D equations
   * x and y are optional.
   * @param t The evaluation time
   * @param pt The current point (x,y,z)
   * @return The result of evaluating the function
   */
  virtual Real value(Real t, const Point & pt);

  /**
   * Evaluate the gradient of the function. This is computed in libMesh
   * through automatic symbolic differentiation.
   */
  virtual RealGradient gradient(Real t, const Point & p);

  /**
   * Evaluate the time derivative of the function. This is computed in libMesh
   * through automatic symbolic differentiation.
   * \param t The time
   * \param p The point in space (x,y,z)
   * \return The time derivative of the function at the specified time and location
   */
  virtual Real timeDerivative(Real t, const Point & p);

  /**
   * Method invalid for ParsedGradFunction
   * @see ParsedVectorFunction
   */
  virtual RealVectorValue vectorValue(Real t, const Point & p);

  /**
   * Creates the parsed function.
   */
  virtual void initialSetup();

protected:

  /// The function defined by the user
  std::string _value;

  /// Pointer to the wrapper object for the function
  MooseParsedFunctionWrapper * _function_ptr;

  friend class ParsedFunctionTest;

};
#endif //MOOSEPARSEDFUNCTION_H
