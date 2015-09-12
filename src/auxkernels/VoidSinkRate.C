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

#include "VoidSinkRate.h"

template<>
InputParameters validParams<VoidSinkRate>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredParam<std::string>("Diffusivity","The diffusivity of the defect to use in this calculation");
  params.addRequiredCoupledVar("VoidDensity", "The density of voids in the material");
  params.addRequiredCoupledVar("AverageVoidRadius", "The average void radius at this location and time");
  return params;
}


VoidSinkRate::VoidSinkRate(const InputParameters & parameters)
  :AuxKernel(parameters),
   _prop_name_D(getParam<std::string>("Diffusivity")),
   _D_species(getMaterialProperty<Real>(_prop_name_D)),
   _void_density(coupledValue("VoidDensity")),
   _average_void_radius(coupledValue("AverageVoidRadius"))

{}

Real
VoidSinkRate::computeValue()
{
  Real K_Voids = 4 * 3.14159 * _void_density[_qp] * _D_species[_qp] * _average_void_radius[_qp];

  return K_Voids;
}
