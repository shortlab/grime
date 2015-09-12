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

#ifndef ARCMATERIAL_H
#define ARCMATERIAL_H

#include "Material.h"

//Forward Declarations
class ArcMaterial;

template<>
InputParameters validParams<ArcMaterial>();

class ArcMaterial : public Material
{
public:
  ArcMaterial(const InputParameters & parameters);

protected:
//  virtual void initQpStatefulProperties();
  virtual void computeQpProperties();

private:

  /**
   * These variables will hold key values from the
   * input file for material property calculation.
   */

  // Simple parameters to be used all over
  Real _constant_temperature;

  // Parameters related to defect diffusivity
  Real _Cr_D0;
  Real _Cr_activation_energy;

  /**
   * This is the member reference that will hold the
   * computed values from this material class.
   */

  // Diffusivities of radiation defects
  MaterialProperty<Real> & _chromium_diffusivity_matprop;
  MaterialProperty<Real> & _thermal_conductivity_matprop;

  // Coupled variables used in calculation (TBD)
//  VariableValue & _T;

};

#endif //ARCMATERIAL_H
