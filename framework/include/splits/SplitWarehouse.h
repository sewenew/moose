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

#ifndef SPLITWAREHOUSE_H
#define SPLITWAREHOUSE_H

// C++ includes
#include <map>

// MOOSE includes
#include "Warehouse.h"
#include "MooseTypes.h"

// Forward declarations
class Split;

/**
 * Holds splits and provides some services
 */
class SplitWarehouse : public Warehouse<Split>
{
public:
  SplitWarehouse();
  virtual ~SplitWarehouse();

  /**
   * Add a split
   * @param name - name the split being added should have
   * @param split Split being added
   */
  void   addSplit(const std::string& name, MooseSharedPointer<Split> & split);
  Split *getSplit(const std::string& name);

protected:
  /// all splits
  std::map<std::string, MooseSharedPointer<Split> > _all_splits_by_name;
};

#endif // SPLITWAREHOUSE_H
