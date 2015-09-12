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

#include "MatPropDiffusion.h"

template<>
InputParameters validParams<MatPropDiffusion>()
{
  InputParameters params = validParams<Diffusion>();
  params.addRequiredParam<std::string>("diffusivity","The real material property (here is it a diffusivity) to use in this kernel");
  return params;
}


MatPropDiffusion::MatPropDiffusion(const InputParameters & parameters)
  :Diffusion(parameters),
   _prop_name(getParam<std::string>("diffusivity")),
   _D_species(getMaterialProperty<Real>(_prop_name))
{}

Real
MatPropDiffusion::computeQpResidual()
{
  return _D_species[_qp] * Diffusion::computeQpResidual();
}

Real
MatPropDiffusion::computeQpJacobian()
{
  return _D_species[_qp] * Diffusion::computeQpJacobian();
}
