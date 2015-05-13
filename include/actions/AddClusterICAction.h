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

#ifndef ADDCLUSTERICACTION_H
#define ADDCLUSTERICACTION_H

#include "Action.h"

class AddClusterICAction;

template<>
InputParameters validParams<AddClusterICAction>();


class AddClusterICAction : public Action
{
public:
  AddClusterICAction(const std::string & name, InputParameters params);

  virtual void act();
};

#endif // AddClusterICAction_H
