/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/
#ifndef GRAINFORCEANDTORQUESUM_H
#define GRAINFORCEANDTORQUESUM_H

#include "GrainForceAndTorqueInterface.h"
#include "GeneralUserObject.h"

//Forward Declarations
class GrainForceAndTorqueSum;

template<>
InputParameters validParams<GrainForceAndTorqueSum>();

/**
 * This class is here to get the force and torque acting on a grain
 * from different userobjects and sum them all
 */
class GrainForceAndTorqueSum :
    public GrainForceAndTorqueInterface,
    public GeneralUserObject
{
public:
  GrainForceAndTorqueSum(const InputParameters & parameters);

  virtual void initialize();
  virtual void execute(){};
  virtual void finalize(){};

  virtual const std::vector<RealGradient> & getForceValues() const;
  virtual const std::vector<RealGradient> & getTorqueValues() const;
  virtual const std::vector<RealGradient> & getForceDerivatives() const;
  virtual const std::vector<RealGradient> & getTorqueDerivatives() const;

protected:
  /// Vector of userobjects providing forces and torques acting on grains
  std::vector<UserObjectName> _sum_objects;
  /// Total no. of userobjects that provides forces and torques acting on grains
  unsigned int _num_forces;
  unsigned int _ncrys;

  std::vector<const GrainForceAndTorqueInterface *> _sum_forces;

  ///@{ providing sum of all grain forces, torques & their derivatives
  std::vector<RealGradient> _force_values;
  std::vector<RealGradient> _torque_values;
  std::vector<RealGradient> _force_derivatives;
  std::vector<RealGradient> _torque_derivatives;
  ///@}
};

#endif //GRAINFORCEANDTORQUESUM_H
