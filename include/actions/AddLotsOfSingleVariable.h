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

#ifndef ADDLOTSOFSINGLEVARIABLE_H
#define ADDLOTSOFSINGLEVARIABLE_H

#include "AddVariableAction.h"

class AddLotsOfSingleVariable;

template<>
InputParameters validParams<AddLotsOfSingleVariable>();


class AddLotsOfSingleVariable : public AddVariableAction
{
public:
  AddLotsOfSingleVariable(const std::string & name, InputParameters params);

  virtual void act();
};

#endif // AddLotsOfSingleVariable_H
