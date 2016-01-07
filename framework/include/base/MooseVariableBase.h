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

#ifndef MOOSEVARIABLEBASE_H
#define MOOSEVARIABLEBASE_H

#include "MooseTypes.h"
#include "MooseArray.h"

// libMesh includes
#include "libmesh/tensor_value.h"
#include "libmesh/vector_value.h"

// libMesh forward declarations
namespace libMesh
{
class DofMap;
class Variable;
}

typedef MooseArray<Real>               VariableValue;
typedef MooseArray<RealGradient>       VariableGradient;
typedef MooseArray<RealTensor>         VariableSecond;

typedef MooseArray<std::vector<Real> >         VariableTestValue;
typedef MooseArray<std::vector<RealGradient> > VariableTestGradient;
typedef MooseArray<std::vector<RealTensor> >   VariableTestSecond;

typedef MooseArray<std::vector<Real> >         VariablePhiValue;
typedef MooseArray<std::vector<RealGradient> > VariablePhiGradient;
typedef MooseArray<std::vector<RealTensor> >   VariablePhiSecond;

class Assembly;
class SubProblem;
class SystemBase;


class MooseVariableBase
{
public:
  MooseVariableBase(unsigned int var_num, SystemBase & sys, Assembly & assembly, Moose::VarKindType var_kind);
  virtual ~MooseVariableBase();

  /**
   * Get variable number coming from libMesh
   * @return the libmesh variable number
   */
  unsigned int number() const { return _var_num; }

  /**
   * Get the system this variable is part of.
   */
  SystemBase & sys() { return _sys; }

  /**
   * Get the variable number
   */
  const std::string & name() const;

  /**
   * Kind of the variable (Nonlinear, Auxiliary, ...)
   */
  Moose::VarKindType kind() const { return _var_kind; }

  /**
   * Set the scaling factor for this variable
   */
  void scalingFactor(Real factor) { _scaling_factor = factor; }

  /**
   * Get the scaling factor for this variable
   */
  Real scalingFactor() const { return _scaling_factor; }

  /**
   * Get the order of this variable
   */
  unsigned int order() const;

  /**
   * The DofMap associated with the system this variable is in.
   */
  const DofMap & dofMap() { return _dof_map; }

  std::vector<dof_id_type> & dofIndices() { return _dof_indices; }

  unsigned int numberOfDofs() { return _dof_indices.size(); }

  /**
   * Is this variable nodal
   * @return true if it nodal, otherwise false
   */
  virtual bool isNodal() const = 0;

protected:
  /// variable number (from libMesh)
  unsigned int _var_num;
  /// variable number within MOOSE
  unsigned int _index;
  Moose::VarKindType _var_kind;
  /// Problem this variable is part of
  SubProblem & _subproblem;
  /// System this variable is part of
  SystemBase & _sys;

  /// libMesh variable object for this variable
  const Variable & _variable;

  /// Assembly data
  Assembly & _assembly;
  /// DOF map
  const DofMap & _dof_map;
  /// DOF indices
  std::vector<dof_id_type> _dof_indices;

  /// scaling factor for this variable
  Real _scaling_factor;
};

#endif /* MOOSEVARIABLEBASE_H */
