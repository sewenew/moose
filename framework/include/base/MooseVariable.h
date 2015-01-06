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

#ifndef MOOSEVARIABLE_H
#define MOOSEVARIABLE_H

#include "MooseVariableBase.h"
#include "ParallelUniqueId.h"

// libMesh
#include "libmesh/quadrature.h"
#include "libmesh/dense_vector.h"
#include "libmesh/dense_matrix.h"
#include "libmesh/numeric_vector.h"
#include "libmesh/sparse_matrix.h"
#include "libmesh/elem.h"
#include "libmesh/node.h"

class Assembly;
class SubProblem;
class SystemBase;

/**
 * Class for stuff related to variables
 *
 * Each variable can compute nodal or elemental (at QPs) values.
 */
class MooseVariable : public MooseVariableBase
{
public:
  MooseVariable(unsigned int var_num, const FEType & fe_type, SystemBase & sys, Assembly & assembly, Moose::VarKindType var_kind);
  virtual ~MooseVariable();

  /**
   * Clear out the dof indices.  We do this in case this variable is not going to be prepared at all...
   */
  void clearDofIndices();

  void prepare();

  void prepareNeighbor();
  void prepareAux();
  void prepareIC();

  void reinitNode();
  void reinitNodeNeighbor();
  void reinitAux();
  void reinitAuxNeighbor();

  void reinitNodes(const std::vector<dof_id_type> & nodes);

  const std::set<SubdomainID> & activeSubdomains();

  /**
   * Is the variable active on the subdomain?
   * @param subdomain The subdomain id in question
   * @return true if active on subdomain, false otherwise
   */
  bool activeOnSubdomain(SubdomainID subdomain) const;

  /**
   * Get the type of finite element object
   */
  const FEType feType() const { return _fe_type; }

  /**
   * Get the order of this variable
   */
  Order getOrder() const { return _fe_type.order; }

  /**
   * Is this variable nodal
   * @return true if it nodal, otherwise false
   */
  virtual bool isNodal() const;

  /**
   * Current element this variable is evaluated at
   */
  const Elem * & currentElem() { return _elem; }

  /**
   * Current side this variable is being evaluated on
   */
  unsigned int & currentSide() { return _current_side; }

  /**
   * Current neighboring element
   */
  const Elem * & neighbor() { return _neighbor; }

  /**
   * Whether or not this variable is computing any second derivatives.
   */
  bool computingSecond() { return _need_second || _need_second_old || _need_second_older; }

  const VariablePhiValue & phi();
  const VariablePhiGradient & gradPhi();
  const VariablePhiSecond & secondPhi();

  const VariablePhiValue & phiFace();
  const VariablePhiGradient & gradPhiFace();
  const VariablePhiSecond & secondPhiFace();

  const VariablePhiValue & phiFaceNeighbor();
  const VariablePhiGradient & gradPhiFaceNeighbor();
  const VariablePhiSecond & secondPhiFaceNeighbor();

  const MooseArray<Point> & normals() { return _normals; }

  // damping
  VariableValue & increment() { return _increment; }

  VariableValue & sln() { return _u; }
  VariableValue & slnOld() { _need_u_old = true; return _u_old; }
  VariableValue & slnOlder() { _need_u_older = true;return _u_older; }
  VariableGradient  & gradSln() { return _grad_u; }
  VariableGradient  & gradSlnOld() { _need_grad_old = true; return _grad_u_old; }
  VariableGradient  & gradSlnOlder() { _need_grad_older = true; return _grad_u_older; }
  VariableSecond & secondSln() { _need_second = true; secondPhi(); secondPhiFace(); return _second_u; }
  VariableSecond & secondSlnOld() { _need_second_old = true; secondPhi(); secondPhiFace(); return _second_u_old; }
  VariableSecond & secondSlnOlder() { _need_second_older = true; secondPhi(); secondPhiFace(); return _second_u_older; }

  VariableValue & uDot() { return _u_dot; }
  VariableValue & duDotDu() { return _du_dot_du; }

  const Node * & node() { return _node; }
  dof_id_type & nodalDofIndex() { return _nodal_dof_index; }
  bool isNodalDefined() { return _is_defined; }
  VariableValue & nodalSln() { return _nodal_u; }
  VariableValue & nodalSlnOld() { return _nodal_u_old; }
  VariableValue & nodalSlnOlder() { return _nodal_u_older; }
  VariableValue & nodalSlnDot() { return _nodal_u_dot; }
  VariableValue & nodalSlnDuDotDu() { return _nodal_du_dot_du; }

  VariableValue & nodalValue();
  VariableValue & nodalValueOld();
  VariableValue & nodalValueOlder();

  VariableValue & slnNeighbor() { return _u_neighbor; }
  VariableValue & slnOldNeighbor() { _need_u_old_neighbor = true; return _u_old_neighbor; }
  VariableValue & slnOlderNeighbor() { _need_u_older_neighbor = true; return _u_older_neighbor; }
  VariableGradient & gradSlnNeighbor() { return _grad_u_neighbor; }
  VariableGradient & gradSlnOldNeighbor() { _need_grad_old_neighbor = true; return _grad_u_old_neighbor; }
  VariableGradient & gradSlnOlderNeighbor() { _need_grad_older_neighbor = true; return _grad_u_older_neighbor; }
  VariableSecond & secondSlnNeighbor() { _need_second_neighbor = true; secondPhiFaceNeighbor(); return _second_u_neighbor; }
  VariableSecond & secondSlnOldNeighbor() { _need_second_old_neighbor = true; secondPhiFaceNeighbor(); return _second_u_old_neighbor; }
  VariableSecond & secondSlnOlderNeighbor() { _need_second_older_neighbor = true; secondPhiFaceNeighbor(); return _second_u_older_neighbor; }

  const Node * & nodeNeighbor() { return _node_neighbor; }
  dof_id_type & nodalDofIndexNeighbor() { return _nodal_dof_index_neighbor; }
  bool isNodalNeighborDefined() { return _is_defined_neighbor; }
  VariableValue & nodalSlnNeighbor() { return _nodal_u_neighbor; }
  VariableValue & nodalSlnOldNeighbor() { return _nodal_u_old_neighbor; }
  VariableValue & nodalSlnOlderNeighbor() { return _nodal_u_older_neighbor; }

  /**
   * Compute values at interior quadrature points
   * when this variable's elem dof i is perturbed
   * by h in the current solution. Perturbation h
   * is computed based on the current variable
   * value at i, its size controlled by scale.
   */
  void computePerturbedElemValues(unsigned i, Real scale, Real& h);

  /**
   * Restore the values the variable had before a call to
   * computePerturbedElemValues().
   */
  void restoreUnperturbedElemValues();

  /**
   * Compute values at interior quadrature points
   */
  void computeElemValues();
  /**
   * Compute values at facial quadrature points
   */
  void computeElemValuesFace();
  /**
   * Compute values at facial quadrature points for the neighbor
   */
  void computeNeighborValuesFace();
  /**
   * Compute values at quadrature points for the neighbor
   */
  void computeNeighborValues();
  /**
   * Compute nodal values of this variable
   */
  void computeNodalValues();
  /**
   * Compute nodal values of this variable in the neighbor
   */
  void computeNodalNeighborValues();
  /**
   * Set the nodal value for this variable to keep everything up to date
   */
  void setNodalValue(Number value, unsigned int idx = 0);
  /**
   * Set values for this variable to keep everything up to date
   */
  void setNodalValue(const DenseVector<Number> & value);

  /**
   * Set the neighbor nodal value for this variable
   */
  void setNodalValueNeighbor(Number value);
  /**
   * Set the neighbor values for this variable
   */
  void setNodalValueNeighbor(const DenseVector<Number> & value);

  /**
   * Compute damping for this variable based on increment_vec
   */
  void computeDamping(const NumericVector<Number> & increment_vec);

  /**
   * Get DOF indices for currently selected element
   * @return
   */
  std::vector<dof_id_type> & dofIndicesNeighbor() { return _dof_indices_neighbor; }

  unsigned int numberOfDofsNeighbor() { return _dof_indices_neighbor.size(); }

  void insert(NumericVector<Number> & residual);
  void add(NumericVector<Number> & residual);

  /**
   * Get the value of this variable at given node
   */
  Number getNodalValue(const Node & node);
  /**
   * Get the old value of this variable at given node
   */
  Number getNodalValueOld(const Node & node);
  /**
   * Get the t-2 value of this variable at given node
   */
  Number getNodalValueOlder(const Node & node);

  /**
   * Compute the variable value at a point on an element
   * @param elem The element we are computing on
   * @param phi Evaluated shape functions at a point
   * @return The variable value
   */
  Number getValue(const Elem * elem, const std::vector<std::vector<Real> > & phi) const;

  /**
   * Retrieve the Elemental DOF
   * @param elem The element we are computing on
   * @return The variable value
   */
  Number getElementalValue(const Elem * elem, unsigned int idx=0) const;

  /**
   * Whether or not this variable is actually using the shape function value.
   *
   * Currently hardcoded to true because we always compute the value.
   */
  bool usesPhi() { return true; }

  /**
   * Whether or not this variable is actually using the shape function gradient.
   *
   * Currently hardcoded to true because we always compute the value.
   */
  bool usesGradPhi() { return true; }

  /**
   * Whether or not this variable is actually using the shape function second derivative.
   */
  bool usesSecondPhi() { return _need_second || _need_second_old || _need_second_older; }

protected:
  /**
   * Get dof indices for the variable
   * @param elem Element whose DOFs we are requesting (input)
   * @param dof_indices DOF indices for the given element (output)
   */
  void getDofIndices(const Elem * elem, std::vector<dof_id_type> & dof_indices);

protected:
  /// Thread ID
  THREAD_ID _tid;
  /// The FEType associated with this variable
  FEType _fe_type;

  /// Quadrature rule for interior
  QBase * & _qrule;
  /// Quadrature rule for the face
  QBase * & _qrule_face;
  /// Quadrature rule for the neighbor
  QBase * & _qrule_neighbor;

  /// current element
  const Elem * & _elem;
  /// the side of the current element (valid when doing face assembly)
  unsigned int & _current_side;

  /// neighboring element
  const Elem * & _neighbor;

  /// DOF indices (neighbor)
  std::vector<dof_id_type> _dof_indices_neighbor;


  bool _need_u_old;
  bool _need_u_older;

  bool _need_grad_old;
  bool _need_grad_older;

  bool _need_second;
  bool _need_second_old;
  bool _need_second_older;


  bool _need_u_old_neighbor;
  bool _need_u_older_neighbor;

  bool _need_grad_old_neighbor;
  bool _need_grad_older_neighbor;

  bool _need_second_neighbor;
  bool _need_second_old_neighbor;
  bool _need_second_older_neighbor;

  bool _need_nodal_u;
  bool _need_nodal_u_old;
  bool _need_nodal_u_older;

  // Shape function values, gradients. second derivatives
  const VariablePhiValue & _phi;
  const VariablePhiGradient & _grad_phi;
  const VariablePhiSecond * _second_phi;

  // Values, gradients and second derivatives of shape function on faces
  const VariablePhiValue & _phi_face;
  const VariablePhiGradient & _grad_phi_face;
  const VariablePhiSecond * _second_phi_face;

  // Values, gradients and second derivatives of shape function on faces
  const VariablePhiValue & _phi_face_neighbor;
  const VariablePhiGradient & _grad_phi_face_neighbor;
  const VariablePhiSecond * _second_phi_face_neighbor;

  /// Normals at QPs on faces
  const MooseArray<Point> & _normals;

  VariableValue _u, _u_bak;
  VariableValue _u_old, _u_old_bak;
  VariableValue _u_older, _u_older_bak;
  VariableGradient  _grad_u, _grad_u_bak;
  VariableGradient  _grad_u_old, _grad_u_old_bak;
  VariableGradient  _grad_u_older, _grad_u_older_bak;
  VariableSecond _second_u, _second_u_bak;
  VariableSecond _second_u_old, _second_u_old_bak;
  VariableSecond _second_u_older, _second_u_older_bak;

  VariableValue _u_neighbor;
  VariableValue _u_old_neighbor;
  VariableValue _u_older_neighbor;
  VariableGradient _grad_u_neighbor;
  VariableGradient _grad_u_old_neighbor;
  VariableGradient _grad_u_older_neighbor;
  VariableSecond _second_u_neighbor;
  VariableSecond _second_u_old_neighbor;
  VariableSecond _second_u_older_neighbor;

  // time derivatives

  /// u_dot (time derivative)
  VariableValue _u_dot, _u_dot_bak;
  /// derivative of u_dot wrt u
  VariableValue _du_dot_du, _du_dot_du_bak;

  // nodal stuff

  /// If the variable is defined at the node (used in compute nodal values)
  bool _is_defined;
  /// If true, the nodal value gets inserted on calling insert()
  bool _has_nodal_value;
  bool _has_nodal_value_neighbor;
  const Node * & _node;
  dof_id_type _nodal_dof_index;
  VariableValue _nodal_u;
  VariableValue _nodal_u_old;
  VariableValue _nodal_u_older;
  /// nodal values of u_dot
  VariableValue _nodal_u_dot;
  /// nodal values of derivative of u_dot wrt u
  VariableValue _nodal_du_dot_du;

  /// If the variable is defined at the neighbor node (used in compute nodal values)
  bool _is_defined_neighbor;
  const Node * & _node_neighbor;
  dof_id_type _nodal_dof_index_neighbor;
  VariableValue _nodal_u_neighbor;
  VariableValue _nodal_u_old_neighbor;
  VariableValue _nodal_u_older_neighbor;

  /// if variable is nodal
  bool _is_nodal;

  // damping
  VariableValue _increment;

  /// scaling factor for this variable
  Real _scaling_factor;

  friend class NodeFaceConstraint;
  friend class ValueThresholdMarker;
  friend class ValueRangeMarker;
};

#endif /* MOOSEVARIABLE_H */
