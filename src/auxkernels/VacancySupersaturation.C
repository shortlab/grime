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

#include "VacancySupersaturation.h"

template<>
InputParameters validParams<VacancySupersaturation>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("Numerator", "The numerator of the supersaturation equation");
  params.addRequiredCoupledVar("EquilibriumVacancies", "The thermal vacancy concentration");
  return params;
}


VacancySupersaturation::VacancySupersaturation(const InputParameters & parameters)
  :AuxKernel(parameters),
   _numerator(coupledValue("Numerator")),
   _thermal_vacancies(coupledValue("EquilibriumVacancies")),
   _D_v(getMaterialProperty<Real>("VacancyDiffusivityMatProp"))
{}

Real
VacancySupersaturation::computeValue()
{
  Real _supersaturation =   (_numerator[_qp])
                          / (_D_v[_qp] * _thermal_vacancies[_qp]);

  if (_supersaturation < 0)
    _supersaturation = 0;

  return _supersaturation;
}
