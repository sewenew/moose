/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#ifndef FAUXGRAINTRACKER_H
#define FAUXGRAINTRACKER_H

#include "FeatureFloodCount.h"
#include "GrainTrackerInterface.h"

class FauxGrainTracker;

template<>
InputParameters validParams<FauxGrainTracker>();


/**
 * This class is a fake grain tracker object, it will not actually track grains nor remap them
 * but will provide the same interface as the grain tracker and can be used as a lightweight
 * replacement when neither of those methods are needed. You may safely use this object anytime
 * you have at least as many order parameters as you do grains.
 */
class FauxGrainTracker : public FeatureFloodCount, public GrainTrackerInterface
{
public:
  FauxGrainTracker(const InputParameters & parameters);
  virtual ~FauxGrainTracker();

  virtual void initialize();

  virtual void finalize() {}

  virtual Real getValue();

  virtual void execute();

  /**
   * Accessor for retrieving nodal field information (unique grains or variable indices)
   * @param node_id the node identifier for which to retrieve field data
   * @param var_idx when using multi-map mode, the map number from which to retrieve data.
   * @param show_var_coloring pass true to view variable index for a region, false for unique grain information
   * @return the nodal value
   */
  virtual Real getNodalValue(dof_id_type node_id, unsigned int var_idx=0, bool show_var_coloring=false) const;

  /**
   * Accessor for retrieving either nodal or elemental information (unique grains or variable indicies)
   * @param entity_id the node identifier for which to retrieve field data
   * @param var_idx when using multi-map mode, the map number from which to retrieve data.
   * @param show_var_coloring pass true to view variable index for a region, false for unique grain information
   * @return the entity value
   */
  virtual Real getEntityValue(dof_id_type entity_id, unsigned int var_idx=0, bool show_var_coloring=false) const;

  /**
   * Accessor for retrieving elemental field data (grain centroids).
   * @param element_id the element identifier for which to retrieve field data
   * @return the elemental value
   */
  virtual Real getElementalValue(dof_id_type /*element_id*/) const;

  /**
   * Returns a list of active unique grains for a particular elem based on the node numbering.  The outer vector
   * holds the ith node with the inner vector holds the list of active unique grains.
   * (unique_grain_id, variable_idx)
   */
  virtual const std::vector<std::pair<unsigned int, unsigned int> > & getElementalValues(dof_id_type elem_id) const;

private:
  /// The mapping of entities to grains, in this case always the order parameter
  LIBMESH_BEST_UNORDERED_MAP<dof_id_type, unsigned int> _entity_id_to_var_num;

  /// Used as the lightweight grain counter
  std::set<unsigned int> _variables_used;

  /// Used to emulate the tracking step of the real grain tracker object
  const int _tracking_step;

  std::vector<std::pair<unsigned int, unsigned int> > _faux_data;
};

#endif
