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

#ifndef ADAPTIVITY_H
#define ADAPTIVITY_H

#include "libmesh/libmesh_config.h"

#ifdef LIBMESH_ENABLE_AMR

#include "Moose.h"
#include "MooseError.h"
#include "ConsoleStreamInterface.h"
#include "MooseTypes.h"

// libMesh
#include "libmesh/mesh_refinement.h"

class FEProblem;
class MooseMesh;
class DisplacedProblem;
class MooseVariable;
class MooseEnum;

// Forward declare classes in libMesh
namespace libMesh
{
class SystemNorm;
class ErrorVector;
class ErrorEstimator;
}

/**
 * Takes care of everything related to mesh adaptivity
 *
 */
class Adaptivity : public ConsoleStreamInterface
{
public:
  Adaptivity(FEProblem & subproblem);
  virtual ~Adaptivity();

  /**
   * Initialize the initial adaptivity ;-)
   *
   * @param steps TODO: describe me
   * @param initial_steps number of steps to do in the initial adaptivity
   */
  void init(unsigned int steps, unsigned int initial_steps);

  /**
   * Set adaptivity parameter
   *
   * @param param_name the name of the parameter
   * @param param_value the value of parameter
   */
  template<typename T>
  void setParam(const std::string & param_name, const T & param_value);

  /**
   * Set the error estimator
   *
   * @param error_estimator_name the name of the error estimator (currently: Laplacian, Kelly, and PatchRecovery)
   */
  void setErrorEstimator(const MooseEnum & error_estimator_name);

  /**
   * Set the error norm (FIXME: improve description)
   */
  void setErrorNorm(SystemNorm &sys_norm);

  /**
   *
   */
  void setPrintMeshChanged(bool state = true) { _print_mesh_changed = state; }

  /**
   * Pull out the number of initial steps previously set by calling init()
   *
   * @return the number of initial steps
   */
  unsigned int getInitialSteps() const { return _initial_steps; }

  /**
   * Pull out the number of steps previously set by calling init()
   *
   * @return the number of steps
   */
  unsigned int getSteps() const { return _steps; }

  /**
   * Pull out the number of cycles_per_step previously set through the AdaptivityAction
   *
   * @return the number of cycles per step
   */
  unsigned int getCyclesPerStep() const { return _cycles_per_step; }

  /**
   * Set the number of cycles_per_step
   * @param num The number of cycles per step to execute
   */
  void setCyclesPerStep(const unsigned int & num){ _cycles_per_step = num; }

  /**
   * Adapts the mesh based on the error estimator used
   *
   * @return a boolean that indicates whether the mesh was changed
   */
  bool adaptMesh();

  /**
   * Used during initial adaptivity.
   */
  void initialAdaptMesh();

  /**
   * Performs uniform refinement of the passed Mesh object. The
   * number of levels of refinement performed is stored in the
   * MooseMesh object. No solution projection is performed in this
   * version.
   */
  static void uniformRefine(MooseMesh *mesh);

  /**
   * Performs uniform refinement on the meshes in the current
   * object. Projections are performed of the solution vectors.
   */
  void uniformRefineWithProjection();

  /**
   * Is adaptivity on?
   *
   * @return true if we do mesh adaptivity, otherwise false
   */
  bool isOn() { return _mesh_refinement_on; }

  /**
   * Sets the time when the adaptivity is active
   * @param start_time The time when adaptivity starts
   * @param stop_time The time when adaptivity stops
   */
  void setTimeActive(Real start_time, Real stop_time);

  /**
   * Tells this object we're using the "new" adaptivity system.
   */
  void setUseNewSystem();

  /**
   * Sets the name of the field variable to actually use to flag elements for refinement / coarsening.
   * This must be a CONSTANT, MONOMIAL Auxiliary Variable Name that contains values
   * corresponding to libMesh::Elem::RefinementState.
   *
   * @param marker_field The name of the field to use for refinement / coarsening.
   */
  void setMarkerVariableName(std::string marker_field);

  /**
   * Sets the name of the field variable to actually use to flag elements for initial refinement / coarsening.
   * This must be a CONSTANT, MONOMIAL Auxiliary Variable Name that contains values
   * corresponding to libMesh::Elem::RefinementState.
   *
   * @param marker_field The name of the field to use for refinement / coarsening.
   */
  void setInitialMarkerVariableName(std::string marker_field);

  /**
   * Set the maximum refinement level (for the new Adaptivity system).
   */
  void setMaxHLevel(unsigned int level) { _max_h_level = level; }

  /**
   * Get the MooseVariable corresponding to the Marker Field Name that is actually going to be used
   * to refine / coarsen the mesh.
   *
   * @return The MooseVariable
   */
  MooseVariable & getMarkerVariable();

  /**
   * Get an ErrorVector that will be filled up with values corresponding to the
   * indicator field name passed in.
   *
   * Note that this returns a reference... and the return value should be stored as a reference!
   *
   * @param indicator_field The name of the field to get an ErrorVector for.
   */
  ErrorVector & getErrorVector(std::string indicator_field);

  /**
   * Update the ErrorVectors that have been requested through calls to getErrorVector().
   */
  void updateErrorVectors();

protected:
  FEProblem & _subproblem;
  MooseMesh & _mesh;

  /// on/off flag reporting if the adaptivity is being used
  bool _mesh_refinement_on;
  /// A mesh refinement object to be used either with initial refinement or with Adaptivity.
  MeshRefinement * _mesh_refinement;
  /// Error estimator to be used by the apps.
  ErrorEstimator * _error_estimator;
  /// Error vector for use with the error estimator.
  ErrorVector * _error;

  MooseSharedPointer<DisplacedProblem> _displaced_problem;

  /// A mesh refinement object for displaced mesh
  MeshRefinement * _displaced_mesh_refinement;

  /// the number of adaptivity steps to do at the beginning of simulation
  unsigned int _initial_steps;
  /// steps of adaptivity to perform
  unsigned int _steps;

  /// True if we want to print out info when mesh has changed
  bool _print_mesh_changed;

  /// Time
  Real & _t;
  /// When adaptivity start
  Real _start_time;
  /// When adaptivity stops
  Real _stop_time;
  /// The number of adaptivity cycles per step
  unsigned int _cycles_per_step;

  /// Whether or not to use the "new" adaptivity system
  bool _use_new_system;

  /// Name of the marker variable if using the new adaptivity system
  std::string _marker_variable_name;

  /// Name of the initial marker variable if using the new adaptivity system
  std::string _initial_marker_variable_name;

  /// The maximum number of refinement levels
  unsigned int _max_h_level;

  /// Stores pointers to ErrorVectors associated with indicator field names
  std::map<std::string, ErrorVector *> _indicator_field_to_error_vector;
};

template<typename T>
void
Adaptivity::setParam(const std::string &param_name, const T &param_value)
{
  if (param_name == "refine fraction")
  {
    _mesh_refinement->refine_fraction() = param_value;
    if (_displaced_mesh_refinement)
      _displaced_mesh_refinement->refine_fraction() = param_value;
  }
  else if (param_name == "coarsen fraction")
  {
    _mesh_refinement->coarsen_fraction() = param_value;
    if (_displaced_mesh_refinement)
      _displaced_mesh_refinement->coarsen_fraction() = param_value;
  }
  else if (param_name == "max h-level")
  {
    _mesh_refinement->max_h_level() = param_value;
    if (_displaced_mesh_refinement)
      _displaced_mesh_refinement->max_h_level() = param_value;
  }
  else if (param_name == "cycles_per_step")
    _cycles_per_step = param_value;
  else
    mooseError("Invalid Param in adaptivity object");
}
#endif //LIBMESH_ENABLE_AMR

#endif /* ADAPTIVITY_H */
