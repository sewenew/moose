/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef TENSORMECHANICSACTION_H
#define TENSORMECHANICSACTION_H

#include "Action.h"

class TensorMechanicsAction;

template<>
InputParameters validParams<TensorMechanicsAction>();

class TensorMechanicsAction : public Action
{
public:
  TensorMechanicsAction(const InputParameters & params);

  virtual void act();
  virtual void addkernel(const std::string & name, InputParameters & params);
};

#endif //TENSORMECHANICSACTION_H
