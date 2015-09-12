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

#ifndef DEFECTRECOMBINATIONRATECONSTANT_H
#define DEFECTRECOMBINATIONRATECONSTANT_H

#include "AuxKernel.h"

//Forward Declarations
class DefectRecombinationRateConstant;

/**
 * validParams returns the parameters that this AuxKernel accepts / needs
 * The actual body of the function MUST be in the .C file.
 */
template<>
InputParameters validParams<DefectRecombinationRateConstant>();

class DefectRecombinationRateConstant : public AuxKernel
{
public:

  DefectRecombinationRateConstant(const InputParameters & parameters);

protected:
  virtual Real computeValue();

  /**
   * This MooseArray will hold the reference we need to our
   * material property from the Material class
   */

  const MaterialProperty<Real> & _D_v;
  const MaterialProperty<Real> & _D_i;
  const MaterialProperty<Real> & _lattice_parameter;
  const MaterialProperty<Real> & _atomic_volume;

};
#endif //DEFECTRECOMBINATIONRATECONSTANT_H
