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

#ifndef ELEMENTUSEROBJECT_H
#define ELEMENTUSEROBJECT_H

// MOOSE includes
#include "UserObject.h"
#include "BlockRestrictable.h"
#include "MaterialPropertyInterface.h"
#include "UserObjectInterface.h"
#include "Coupleable.h"
#include "ScalarCoupleable.h"
#include "MooseVariableDependencyInterface.h"
#include "TransientInterface.h"
#include "PostprocessorInterface.h"
#include "RandomInterface.h"
#include "ZeroInterface.h"

// Forward Declarations
class ElementUserObject;

namespace libMesh
{
class Elem;
class QBase;
}

template<>
InputParameters validParams<ElementUserObject>();

class ElementUserObject :
  public UserObject,
  public BlockRestrictable,
  public MaterialPropertyInterface,
  public UserObjectInterface,
  public Coupleable,
  public ScalarCoupleable,
  public MooseVariableDependencyInterface,
  public TransientInterface,
  protected PostprocessorInterface,
  public RandomInterface,
  public ZeroInterface
{
public:
  ElementUserObject(const InputParameters & parameters);

  /**
   * This function will get called on each geometric object this
   * postprocessor acts on (ie Elements, Sides or Nodes).  This will
   * most likely get called multiple times before getValue() is
   * called.
   *
   * Someone somewhere has to override this.
   */
  virtual void execute() = 0;

  /**
   * Must override.
   *
   * @param uo The UserObject to be joined into _this_ object.  Take the data from the uo object and "add" it into the data for this object.
   */
  virtual void threadJoin(const UserObject & uo) = 0;

protected:
  MooseMesh & _mesh;

  /// The current element pointer (available during execute())
  const Elem * & _current_elem;

  /// The current element volume (available during execute())
  const Real & _current_elem_volume;

  const MooseArray< Point > & _q_point;
  QBase * & _qrule;
  const MooseArray<Real> & _JxW;
  const MooseArray<Real> & _coord;
};

#endif
