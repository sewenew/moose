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

#ifndef EIGENSYSTEM_H
#define EIGENSYSTEM_H

#include "NonlinearSystem.h"

class FEProblem;

class EigenSystem : public NonlinearSystem
{
public:
  EigenSystem(FEProblem & problem, const std::string & name);
  virtual ~EigenSystem();

  /**
   * Adds a kernel
   * @param kernel_name The type of the kernel.
   * @param name The name of the kernel.
   * @param parameters Kernel parameters.
   */
  virtual void addKernel(const std::string & kernel_name, const std::string & name, InputParameters parameters);

  /**
   * Mark a variable as a variable of the eigen system
   * @param var_name The name of the variable.
   */
  virtual void markEigenVariable(const VariableName & var_name);

  /**
   * System or kernel tags
   */
  enum SYSTEMTAG
  {
    ALL,
    EIGEN
  };

  /**
   * Scale the solution vector
   *
   * @param tag System tag.
   * @param factor The scaling factor.
   */
  void scaleSystemSolution(SYSTEMTAG tag, Real scaling_factor);

  /**
   * Linear combination of the solution vectors
   *
   * @param tag System tag.
   * @param coefficients Coefficients for current, old and older solutions.
   */
  void combineSystemSolution(SYSTEMTAG tag, const std::vector<Real> & coefficients);

  /**
   * Initialize the solution vector with a constant value
   *
   * @param tag System tag.
   * @param v The value.
   */
  void initSystemSolution(SYSTEMTAG tag, Real v);
  void initSystemSolutionOld(SYSTEMTAG tag, Real v);

  /**
   * Ask eigenkernels to operate on old or current solution vectors
   */
  void eigenKernelOnOld();
  void eigenKernelOnCurrent();

  /**
   * Build DoF indices for a system
   */
  void buildSystemDoFIndices(SYSTEMTAG tag = ALL);

  /**
   * Return if eigen kernels should be on old solution
   */
  bool activeOnOld();

  /**
   * Get variable names of the eigen system
   */
  const std::set<VariableName> & getEigenVariableNames() const { return _eigen_var_names; }

  /**
   * Save the old solutions
   */
  void saveOldSolutions();

  /**
   * Restore the old solutions
   */
  void restoreOldSolutions();

  /**
   * Weather or not the system contains eigen kernels
   */
  bool containsEigenKernel() const;

protected:

  std::set<VariableName> _eigen_var_names;
  bool _all_eigen_vars;
  std::set<dof_id_type> _eigen_var_indices;

  bool _active_on_old;

  // Used for saving old solutions so that they wont be accidentally changed
  // FIXME: can be removed in the future when STEP is available.
  NumericVector<Real> * _sys_sol_old;
  NumericVector<Real> * _sys_sol_older;
  NumericVector<Real> * _aux_sol_old;
  NumericVector<Real> * _aux_sol_older;
  /// counter of eigen kernels
  unsigned int _eigen_kernel_counter;
};

#endif /* EIGENSYSTEM_H */
