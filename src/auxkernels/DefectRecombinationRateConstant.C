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

#include "DefectRecombinationRateConstant.h"

template<>
InputParameters validParams<DefectRecombinationRateConstant>()
{
  InputParameters params = validParams<AuxKernel>();
  return params;
}


DefectRecombinationRateConstant::DefectRecombinationRateConstant(const InputParameters & parameters)
  :AuxKernel(parameters),
   _D_v(getMaterialProperty<Real>("VacancyDiffusivityMatProp")),
   _D_i(getMaterialProperty<Real>("InterstitialDiffusivityMatProp")),
   _lattice_parameter(getMaterialProperty<Real>("LatticeParameterMatProp")),
   _atomic_volume(getMaterialProperty<Real>("AtomicVolumeMatProp"))
{}

Real
DefectRecombinationRateConstant::computeValue()
{

  Real K_iv = (4 * 3.14159 * _atomic_volume[_qp] * (_D_v[_qp] + _D_i[_qp])) / (_lattice_parameter[_qp] * _lattice_parameter[_qp]);
  return K_iv;
}
