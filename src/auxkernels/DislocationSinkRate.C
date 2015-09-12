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

#include "DislocationSinkRate.h"

template<>
InputParameters validParams<DislocationSinkRate>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredParam<std::string>("Diffusivity","The diffusivity to use in this calculation");
  params.addRequiredParam<std::string>("DislocationDensity","The location-dependent density of dislocations");
  params.addParam<Real>("DislocationCoreSize", 1e-8, "The core size of a dislocation, relative to this defect");
  return params;
}


DislocationSinkRate::DislocationSinkRate(const InputParameters & parameters)
  :AuxKernel(parameters),
   _prop_name_D(getParam<std::string>("Diffusivity")),
   _D_species(getMaterialProperty<Real>(_prop_name_D)),
   _prop_name_DD(getParam<std::string>("DislocationDensity")),
   _dislocation_density(getMaterialProperty<Real>(_prop_name_DD)),
   _dislocation_core_size(getParam<Real>("DislocationCoreSize"))

{}

Real
DislocationSinkRate::computeValue()
{
  Real Half_Dislocation_Distance = std::pow((1 / (3.14159 * _dislocation_density[_qp])), 0.5);

  Real K_dislocations = (2 * 3.14159 * _dislocation_density[_qp] * _D_species[_qp])
                         / std::log(Half_Dislocation_Distance / _dislocation_core_size);

  return K_dislocations;
}
