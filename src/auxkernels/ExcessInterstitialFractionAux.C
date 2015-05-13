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

// This file outputs the fluid velocity inside the CRUD fluid
// ***IN THE X-DIRECTION***
//
// It is used to get the maximum fluid speed heading towards the
// boiling chimney.
//
// A later version will output the scalar value of the fluid velocity
// at all locations, and could be used to relax the Darcy flow assumption.
// It is certainly possible that the tiny pores in the CRUD could restrict
// fluid velocity, leading to degraded heat transfer, an increase in
// temperature, and reduced boiling heat flux.
//
// In this case, a higher temperature (and gradient) must be established
// in order to transfer the remaining heat out the top of the CRUD.
//
// ***NOTE***: This idea has NOT been addressed by ANY models yet, and
// could comprise a large 'missing link' between physical understanding
// and fuel performance.

#include "ExcessInterstitialFractionAux.h"

template<>
InputParameters validParams<ExcessInterstitialFractionAux>()
{
  InputParameters params = validParams<AuxKernel>();
  params.addRequiredCoupledVar("vacancy_creation", "The variable describing vacancy creation");
  params.addRequiredCoupledVar("interstitial_creation", "The variable describing interstitial creation");
  return params;
}

ExcessInterstitialFractionAux::ExcessInterstitialFractionAux(const std::string & name, InputParameters parameters)
  :AuxKernel(name, parameters),
  _vacancy_creation(coupledValue("vacancy_creation")),
  _interstitial_creation(coupledValue("interstitial_creation"))

{}

Real
ExcessInterstitialFractionAux::computeValue()
{
  return ((_vacancy_creation[_qp] + _interstitial_creation[_qp]) / _vacancy_creation[_qp]) - 1;
}
