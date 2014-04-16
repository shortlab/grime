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

#ifndef RADIATIONMATERIAL_H
#define RADIATIONMATERIAL_H

#include "Material.h"

//Forward Declarations
class RadiationMaterial;

template<>
InputParameters validParams<RadiationMaterial>();

class RadiationMaterial : public Material
{
public:
  RadiationMaterial(const std::string & name,
                  InputParameters parameters);

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
  Real _vacancy_D0;
  Real _interstitial_D0;
  Real _vacancy_activation_energy;
  Real _interstitial_activation_energy;

  // Intracascade properties
  Real _intracascade_survival;

  // Rate constants for defect sink and recombination reactions
  Real _vacancy_sink_density;
  Real _interstitial_sink_density;
  Real _vacancy_sink_strength;
  Real _interstitial_sink_strength;
  Real _recombination_efficiency;

  // Crystallographic properties
  Real _lattice_parameter;
  Real _dislocation_density_initial;
  Real _average_void_radius_initial;

  /**
   * This is the member reference that will hold the
   * computed values from this material class.
   */

  // Diffusivities of radiation defects
  MaterialProperty<Real> & _vacancy_diffusivity_matprop;
  MaterialProperty<Real> & _interstitial_diffusivity_matprop;

  // Intracascade specific properties
  MaterialProperty<Real> & _intracascade_survival_matprop;

  // Material-specific rate constant properties (here for convenience)
  MaterialProperty<Real> & _vacancy_sink_density_matprop;
  MaterialProperty<Real> & _interstitial_sink_density_matprop;
  MaterialProperty<Real> & _vacancy_sink_strength_matprop;
  MaterialProperty<Real> & _interstitial_sink_strength_matprop;
  MaterialProperty<Real> & _recombination_efficiency_matprop;

  // Other crystallographic material properties
  MaterialProperty<Real> & _lattice_parameter_matprop;
  MaterialProperty<Real> & _atomic_volume_matprop;
  MaterialProperty<Real> & _number_density_matprop;
  MaterialProperty<Real> & _dislocation_density_matprop;
  MaterialProperty<Real> & _thermal_vacancy_concentration_matprop;
  MaterialProperty<Real> & _average_void_radius_matprop;

  // Coupled variables used in calculation (TBD)
//  VariableValue & _T;

};

#endif //RADIATIONMATERIAL_H
