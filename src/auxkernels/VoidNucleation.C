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

#include "VoidNucleation.h"

template<>
InputParameters validParams<VoidNucleation>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("Supersaturation", "The vacancy supersaturation in the material");
  return params;
}


VoidNucleation::VoidNucleation(const std::string & name,
                                   InputParameters parameters)
  :AuxKernel(name,parameters),
   _supersaturation(coupledValue("Supersaturation"))
{}

Real
VoidNucleation::computeValue()
{
  Real _void_nucleation_rate = (std::pow(10, (5.41547 * std::log10(_supersaturation[_qp])) - 14.6586));  // Line Eq: log(Y) = 5.41547 log(x) - 14.6586
  if (_void_nucleation_rate < 0)
    _void_nucleation_rate = 0;

  return _void_nucleation_rate; // Positive sign because negative source from weak form PDE
}
