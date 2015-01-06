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

#ifndef MOOSE_H
#define MOOSE_H

// libMesh includes
#include "libmesh/perf_log.h"
#include "libmesh/parallel.h"
#include "libmesh/libmesh_common.h"
#include "XTermConstants.h"

#include <string>

using namespace libMesh;

class ActionFactory;
class Factory;

/**
 * Testing a condition on a local CPU that need to be propagated across all processes.
 *
 * If the condition 'cond' is satisfied, it gets propagated across all processes, so the parallel code take the same path (if that is requires).
 */
#define parallel_if (cond)                       \
    bool __local_bool__ = (cond);               \
    Parallel::max<bool>(__local_bool__);        \
    if (__local_bool__)

/**
 * Wrap all fortran function calls in this.
 */
#ifdef __bg__ // On Blue Gene Architectures there is no underscore
  #define FORTRAN_CALL(name) name
#else  // One underscore everywhere else
  #define FORTRAN_CALL(name) name ## _
#endif

// forward declarations
class Syntax;
class FEProblem;

/// Execution flags - when is the object executed/evaluated
// Note: If this enum is changed, make sure to modify:
//   (1) the local function populateExecTypes in Moose.C.
//   (2) the method SetupInterface::getExecuteOptions
//   (3) the function Output::getExecuteOptions
enum ExecFlagType {
  EXEC_NONE              = 0x00,
  /// Object is evaluated only once at the beginning of the simulation
  EXEC_INITIAL           = 0x01,
  /// Object is evaluated in every residual computation
  EXEC_LINEAR            = 0x02,
  /// Object is evaluated in every jacobian computation
  EXEC_NONLINEAR         = 0x04,
  /// Object is evaluated at the end of every time step
  EXEC_TIMESTEP_END      = 0x08,
  /// Object is evaluated at the beginning of every time step
  EXEC_TIMESTEP_BEGIN    = 0x10,
  /// Object is evaluated at the end of the simulations (output only)
  EXEC_FINAL             = 0x20,
  /// Forces execution to occur (output only)
  EXEC_FORCED            = 0x40,
  /// Forces execution on failed solve (output only)
  EXEC_FAILED            = 0x80,
  /// For use with custom executioners that want to fire objects at a specific time
  EXEC_CUSTOM            = 0x100,
  ///@{
  /// Deprecated
  EXEC_RESIDUAL          = 0x200, // EXEC_LINEAR
  EXEC_JACOBIAN          = 0x400, // EXEC_NONLINEAR
  EXEC_TIMESTEP          = 0x800, // EXEC_TIMESTEP_END
  OUTPUT_NONE            = 0x00,
  OUTPUT_INITIAL         = 0x01,
  OUTPUT_LINEAR          = 0x02,
  OUTPUT_NONLINEAR       = 0x04,
  OUTPUT_TIMESTEP_END    = 0x08,
  OUTPUT_TIMESTEP_BEGIN  = 0x10,
  OUTPUT_FINAL           = 0x20,
  OUTPUT_FORCED          = 0x40,
  OUTPUT_FAILED          = 0x80,
  OUTPUT_CUSTOM          = 0x100
  ///@}
};

// Support for deprecated output flags
typedef ExecFlagType OutputExecFlagType;

// Some define trickery to allow YAK to continue to operate, this will
// allow the update to MOOSE to occur w/o an integration branch
#define EXEC_RESIDUAL EXEC_LINEAR
#define EXEC_JACOBIAN EXEC_NONLINEAR
#define EXEC_TIMESTEP EXEC_TIMESTEP_END

namespace Moose
{

/**
 * Perflog to be used by applications.
 * If the application prints this in the end they will get performance info.
 */
extern PerfLog perf_log;

/**
 * PerfLog to be used during setup.  This log will get printed just before the first solve. */
extern PerfLog setup_perf_log;

/**
 * A static list of all the exec types.
 */
extern const std::vector<ExecFlagType> exec_types;

/**
 * Variable indicating whether we will enable FPE trapping for this run.
 */
extern bool _trap_fpe;

/**
 * Variable indicating whether Console coloring will be turned on (default: true).
 */
extern bool _color_console;

/**
 * Variable to toggle any warning into an error
 */
extern bool _warnings_are_errors;

/**
 * Variable to turn on exceptions during mooseError() and mooseWarning(), should
 * only be used with MOOSE unit.
 */
extern bool _throw_on_error;

/**
 * Macros for coloring any output stream (_console, std::ostringstream, etc.)
 */
#define COLOR_BLACK   (Moose::_color_console ? BLACK : "")
#define COLOR_RED     (Moose::_color_console ? RED : "")
#define COLOR_GREEN   (Moose::_color_console ? GREEN : "")
#define COLOR_YELLOW  (Moose::_color_console ? YELLOW : "")
#define COLOR_BLUE    (Moose::_color_console ? BLUE : "")
#define COLOR_MAGENTA (Moose::_color_console ? MAGENTA : "")
#define COLOR_CYAN    (Moose::_color_console ? CYAN : "")
#define COLOR_WHITE   (Moose::_color_console ? WHITE : "")
#define COLOR_DEFAULT (Moose::_color_console ? DEFAULT : "")

/**
 * Import libMesh::out, and libMesh::err for use in MOOSE.
 */
using libMesh::out;
using libMesh::err;

/**
 * Register objects that are in MOOSE
 */
void registerObjects(Factory & factory);
void addActionTypes(Syntax & syntax);
void registerActions(Syntax & syntax, ActionFactory & action_factory);

void setSolverDefaults(FEProblem & problem);

/**
 * Swap the libMesh MPI communicator out for ours.
 */
MPI_Comm swapLibMeshComm(MPI_Comm new_comm);

void enableFPE(bool on = true);

// MOOSE Requires PETSc to run, this CPP check will cause a compile error if PETSc is not found
#ifndef LIBMESH_HAVE_PETSC
  #error PETSc has not been detected, please ensure your environment is set up properly then rerun the libmesh build script and try to compile MOOSE again.
#endif

} // namespace Moose

#endif /* MOOSE_H */
