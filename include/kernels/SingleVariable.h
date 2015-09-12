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

#ifndef SINGLEVARIABLE_H
#define SINGLEVARIABLE_H

#include "Kernel.h"

//Forward Declarations
class SingleVariable;


template<>
InputParameters validParams<SingleVariable>();

class SingleVariable : public Kernel
{
public:
  
  SingleVariable(const InputParameters & parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  Real  _coeff;
  std::vector<unsigned int> _vars;

  std::vector<VariableValue *> _v_vals;
};
#endif 
