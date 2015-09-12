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

#include "DefectSink.h"

template<>
InputParameters validParams<DefectSink>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("SinkRate", "The rate constant for this particular type of sink");
  //params.addCoupledVar("SinkConcentration", "The concentration of this particular type of sink");
  params.addCoupledVar("ConcentrationCorrection", 0, "The correction to subtract from this defect concentration, such as a thermal vacancy concentration");
  return params;
}


DefectSink::DefectSink(const InputParameters & parameters)
  :Kernel(parameters),
   _sink_rate(coupledValue("SinkRate")),
//   _sink_concentration(coupledValue("SinkConcentration")),
   _defect_concentration_correction(coupledValue("ConcentrationCorrection"))
{}

Real
DefectSink::computeQpResidual()
{
//  return _test[_i][_qp] * _sink_rate[_qp] * _sink_concentration[_qp] * (_u[_qp] - _sink_concentration_correction[_qp]); // Positive sign because negative source from weak form PDE
  return _test[_i][_qp] * _sink_rate[_qp] * (_u[_qp] - _defect_concentration_correction[_qp]); // Positive sign because negative source from weak form PDE
}

Real
DefectSink::computeQpJacobian()
{
//  return _test[_i][_qp] * _sink_rate[_qp] * _sink_concentration[_qp] * _phi[_j][_qp]; // Positive sign because negative source from weak form PDE
  return _test[_i][_qp] * _sink_rate[_qp] * _phi[_j][_qp]; // Positive sign because negative source from weak form PDE
}

/*
Real
DefectSink::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _other_defect_var)
    return _test[_i][_qp] * _recombination_rate[_qp] * _phi[_j][_qp] * _u[_qp]; // Positive sign because negative source from weak form PDE

  return 0;
}
*/
