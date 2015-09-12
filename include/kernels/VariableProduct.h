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

#ifndef VARIABLEPRODUCT_H
#define VARIABLEPRODUCT_H

#include "Kernel.h"

//Forward Declarations
class VariableProduct;


template<>
InputParameters validParams<VariableProduct>();

class VariableProduct : public Kernel
{
public:
  
  VariableProduct(const InputParameters & parameters);
  
protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();

private:
  VariableValue & _secondVar;
  Real  _coeff;
  std::vector<unsigned int> _vars;
  /// Coupled primary species concentrations.
  std::vector<VariableValue *> _v_vals;
};
#endif 
