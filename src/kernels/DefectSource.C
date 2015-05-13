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

#include "DefectSource.h"

template<>
InputParameters validParams<DefectSource>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("PrimarySource", "The primary source of this defect");
  params.addCoupledVar("SecondarySource", 0, "The optional secondary source of this defect");
  return params;
}


DefectSource::DefectSource(const std::string & name,
                                   InputParameters parameters)
  :Kernel(name,parameters),
   _primary_source(coupledValue("PrimarySource")),
   _secondary_source(coupledValue("SecondarySource")),
   _intracascade_survival(getMaterialProperty<Real>("IntracascadeSurvivalMatProp"))
{}

Real
DefectSource::computeQpResidual()
{
  return -_test[_i][_qp]
           * ((_intracascade_survival[_qp] * _primary_source[_qp])
           + _secondary_source[_qp]); // Negative sign because positive source from weak form PDE
}

Real
DefectSource::computeQpJacobian()
{
  return 0;
}
