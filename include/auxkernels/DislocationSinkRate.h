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

#ifndef DISLOCATIONSINKRATE_H
#define DISLOCATIONSINKRATE_H

#include "AuxKernel.h"

//Forward Declarations
class DislocationSinkRate;

/**
 * validParams returns the parameters that this AuxKernel accepts / needs
 * The actual body of the function MUST be in the .C file.
 */
template<>
InputParameters validParams<DislocationSinkRate>();

class DislocationSinkRate : public AuxKernel
{
public:

  DislocationSinkRate(const InputParameters & parameters);

protected:
  virtual Real computeValue();

  /**
   * This MooseArray will hold the reference we need to our
   * material property from the Material class
   */

  std::string _prop_name_D;
  const MaterialProperty<Real> & _D_species;
  std::string _prop_name_DD;
  const MaterialProperty<Real> & _dislocation_density;
  Real _dislocation_core_size;

};
#endif //DISLOCATIONSINKRATE_H
