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

#ifndef VOIDSINKRATE_H
#define VOIDSINKRATE_H

#include "AuxKernel.h"

//Forward Declarations
class VoidSinkRate;

/**
 * validParams returns the parameters that this AuxKernel accepts / needs
 * The actual body of the function MUST be in the .C file.
 */
template<>
InputParameters validParams<VoidSinkRate>();

class VoidSinkRate : public AuxKernel
{
public:

  VoidSinkRate(const InputParameters & parameters);

protected:
  virtual Real computeValue();

  /**
   * This MooseArray will hold the reference we need to our
   * material property from the Material class
   */

  std::string _prop_name_D;
  const MaterialProperty<Real> & _D_species;
  VariableValue & _void_density;
  VariableValue & _average_void_radius;

};
#endif //VOIDSINKRATE_H
