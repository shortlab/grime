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

#ifndef DEFECTSINK_H
#define DEFECTSINK_H

#include "Kernel.h"

//Forward Declarations
class DefectSink;

/**
 * validParams returns the parameters that this Kernel accepts / needs
 * The actual body of the function MUST be in the .C file.
 */
template<>
InputParameters validParams<DefectSink>();

class DefectSink : public Kernel
{
public:

  DefectSink(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
//  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  /**
   * This MooseArray will hold the reference we need to our
   * material property from the Material class
   */

  VariableValue & _sink_rate;
//  VariableValue & _sink_concentration;
  VariableValue & _defect_concentration_correction;
//  unsigned int _other_defect_var;

};
#endif //DEFECTSINK_H
