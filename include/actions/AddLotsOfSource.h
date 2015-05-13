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

#ifndef ADDLOTSOFSOURCE_H
#define ADDLOTSOFSOURCE_H

#include "AddVariableAction.h"

class AddLotsOfSource;

template<>
InputParameters validParams<AddLotsOfSource>();


class AddLotsOfSource : public AddVariableAction
{
public:
  AddLotsOfSource(const std::string & name, InputParameters params);

  virtual void act();
};

#endif // AddLotsOfSource_H
