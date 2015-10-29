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

#ifndef USERFUNCTIONTEST_H
#define USERFUNCTIONTEST_H

//CPPUnit includes
#include "cppunit/extensions/HelperMacros.h"

// Forward declarations
class MooseMesh;
class FEProblem;
class Factory;
class MooseApp;

class MooseUtilsTest : public CppUnit::TestFixture
{

  CPPUNIT_TEST_SUITE( MooseUtilsTest );

  CPPUNIT_TEST( camelCaseToUnderscore );
  CPPUNIT_TEST( underscoreToCamelCase );

  CPPUNIT_TEST_SUITE_END();

public:
  void camelCaseToUnderscore();
  void underscoreToCamelCase();
};

#endif  // USERFUNCTIONTEST_H
