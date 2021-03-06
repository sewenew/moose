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

// MOOSE includes
#include "Control.h"

template<>
InputParameters validParams<Control>()
{
  InputParameters params = validParams<GeneralUserObject>();
  params += validParams<ControlInterface>();
  params.registerBase("Control");
  return params;
}

Control::Control(const InputParameters & parameters) :
    GeneralUserObject(parameters),
    ControlInterface(parameters)
{
}
