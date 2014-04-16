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

#include "DefectRecombination.h"

template<>
InputParameters validParams<DefectRecombination>()
{
  InputParameters params = validParams<Kernel>();
  params.addRequiredCoupledVar("OtherDefect", "The other type of defect recombining with this defect");
  params.addRequiredCoupledVar("Recombination", "The recombination rate of both defects together");
  return params;
}


DefectRecombination::DefectRecombination(const std::string & name,
                                   InputParameters parameters)
  :Kernel(name,parameters),
   _other_defect(coupledValue("OtherDefect")),
   _other_defect_var(coupled("OtherDefect")),
   _recombination_rate(coupledValue("Recombination"))
{}

Real
DefectRecombination::computeQpResidual()
{
  return _test[_i][_qp] * _recombination_rate[_qp] * _other_defect[_qp] * _u[_qp]; // Positive sign because negative source from weak form PDE
}

Real
DefectRecombination::computeQpJacobian()
{
  return _test[_i][_qp] * _recombination_rate[_qp] * _other_defect[_qp] * _phi[_j][_qp]; // Positive sign because negative source from weak form PDE
}

Real
DefectRecombination::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _other_defect_var)
    return _test[_i][_qp] * _recombination_rate[_qp] * _phi[_j][_qp] * _u[_qp]; // Positive sign because negative source from weak form PDE

  return 0;
}
