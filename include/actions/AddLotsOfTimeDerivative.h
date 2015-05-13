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

#ifndef ADDLOTSOFTIMEDERIVATIVE_H
#define ADDLOTSOFTIMEDERIVATIVE_H

#include "AddVariableAction.h"

class AddLotsOfTimeDerivative;

template<>
InputParameters validParams<AddLotsOfTimeDerivative>();


class AddLotsOfTimeDerivative : public AddVariableAction
{
public:
  AddLotsOfTimeDerivative(const std::string & name, InputParameters params);

  virtual void act();
};

#endif // AddLotsOfTimeDerivative_H
