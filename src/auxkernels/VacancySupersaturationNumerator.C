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

#include "VacancySupersaturationNumerator.h"

template<>
InputParameters validParams<VacancySupersaturationNumerator>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("Vacancies", "The defect concentration, such as a vacancy concentration");
  params.addRequiredCoupledVar("Interstitials", "The concentration of interstitials");
  params.addRequiredCoupledVar("EquilibriumVacancies", "The thermal vacancy concentration");
  return params;
}


VacancySupersaturationNumerator::VacancySupersaturationNumerator(const InputParameters & parameters)
  :AuxKernel(parameters),
   _vacancies(coupledValue("Vacancies")),
   _interstitials(coupledValue("Interstitials")),
   _thermal_vacancies(coupledValue("EquilibriumVacancies")),
   _D_v(getMaterialProperty<Real>("VacancyDiffusivityMatProp")),
   _D_i(getMaterialProperty<Real>("InterstitialDiffusivityMatProp"))
{}

Real
VacancySupersaturationNumerator::computeValue()
{
  Real _numerator =   ((_D_v[_qp] * _vacancies[_qp]) - 0.7*(_D_i[_qp] * _interstitials[_qp]));

  return _numerator;
}
