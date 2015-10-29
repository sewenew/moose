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

#ifndef CREATEPROBLEMACTION_H
#define CREATEPROBLEMACTION_H

#include "MooseObjectAction.h"

class CreateProblemAction;

template<>
InputParameters validParams<CreateProblemAction>();

class CreateProblemAction : public MooseObjectAction
{
public:
  CreateProblemAction(InputParameters parameters);

  virtual void act();

protected:
  std::vector<SubdomainName> _blocks;
  MultiMooseEnum _coord_sys;
  bool _fe_cache;
};

#endif /* CREATEPROBLEMACTION_H */
