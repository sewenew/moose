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

#ifndef COMPUTERESIDUALTHREAD_H
#define COMPUTERESIDUALTHREAD_H

#include "ThreadedElementLoop.h"

// libMesh includes
#include "libmesh/elem_range.h"

// Forward declarations
class FEProblem;
class NonlinearSystem;
class MaterialWarehouse;
class MaterialPropertyStorage;
class MaterialData;
class Assembly;

class ComputeMaterialsObjectThread : public ThreadedElementLoop<ConstElemRange>
{
public:
  ComputeMaterialsObjectThread(FEProblem & fe_problem, NonlinearSystem & sys,
                               std::vector<MooseSharedPointer<MaterialData> > & material_data,
                               std::vector<MooseSharedPointer<MaterialData> > & bnd_material_data,
                               std::vector<MooseSharedPointer<MaterialData> > & neighbor_material_data,
                               MaterialPropertyStorage & material_props,
                               MaterialPropertyStorage & bnd_material_props,
                               std::vector<Assembly *> & assembly);

  // Splitting Constructor
  ComputeMaterialsObjectThread(ComputeMaterialsObjectThread & x, Threads::split split);

  virtual ~ComputeMaterialsObjectThread();

  virtual void subdomainChanged();
  virtual void onElement(const Elem *elem);
  virtual void onBoundary(const Elem *elem, unsigned int side, BoundaryID bnd_id);
  virtual void onInternalSide(const Elem *elem, unsigned int side);

  void join(const ComputeMaterialsObjectThread & /*y*/);

protected:
  FEProblem & _fe_problem;
  NonlinearSystem & _sys;
  std::vector<MooseSharedPointer<MaterialData> > & _material_data;
  std::vector<MooseSharedPointer<MaterialData> > & _bnd_material_data;
  std::vector<MooseSharedPointer<MaterialData> > & _neighbor_material_data;
  MaterialPropertyStorage & _material_props;
  MaterialPropertyStorage & _bnd_material_props;

  ///@{
  /// References to the various Material object warehouses
  const MooseObjectWarehouse<Material> & _materials;
  const MooseObjectWarehouse<Material> & _face_materials;
  const MooseObjectWarehouse<Material> & _neighbor_materials;
  ///@}

  std::vector<Assembly *> & _assembly;
  bool _need_internal_side_material;

  const bool _has_stateful_props;
  const bool _has_bnd_stateful_props;
};

#endif //COMPUTERESIDUALTHREAD_H
