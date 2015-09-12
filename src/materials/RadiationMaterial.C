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

#include "RadiationMaterial.h"

template<>
InputParameters validParams<RadiationMaterial>()
{
  InputParameters params = validParams<Material>();

  // These parameters are simple constants from the input file
  params.addParam<Real>("ConstantTemperature", 298, "The temperature for a constant-T simulation, in K");

  // These parameters are used in diffusivity calculations
  params.addParam<Real>("VacancyActivationEnergy", 0.33, "Activation energy for vacancy diffusion, in eV");
  params.addParam<Real>("InterstitialActivationEnergy", 0.66, "Activation energy for interstitial diffusion, in eV");
  params.addParam<Real>("VacancyD0", 1e8, "Diffusivity prefactor for vacancies, in nm^2/s");
  params.addParam<Real>("InterstitialD0", 1e8, "Diffusivity prefactor for interstitials, in nm^2/s");

  // These parameters relate to intracascade defect annihilation
  params.addParam<Real>("IntraCascadeSurvivalFraction", 0.1, "The fraction of Frenkel pairs that survive the initial damage cascade");

  // These parameters relate to defect sink and recombination reactions
  params.addParam<Real>("VacancySinkDensity", 1, "Density of vacancy sinks, in #/m^3");
  params.addParam<Real>("InterstitialSinkDensity", 1, "Density of interstitial sinks, in #/m^3");
  params.addParam<Real>("VacancySinkStrength", 1, "Strength factor for vacancy sinks, no units");
  params.addParam<Real>("InterstitialSinkStrength", 1, "Strength factor for interstitial sinks, no units");
  params.addParam<Real>("RecombinationEfficiency", 1, "Efficiency for vacancy-interstitial recombination, no units (fraction from 0-1)");

  // These parameters are crystallographic in nature
  params.addParam<Real>("LatticeParameter", 1e-1, "Lattice parameter of the pure element in question");
  params.addParam<Real>("DislocationDensityInitial", 1e-11, "Starting dislocation density in the material");
  params.addParam<Real>("AverageVoidRadiusInitial", 0.5, "Initial average void radius");

  // Many material properties scale with temperature (to be implemented later)
//  params.addRequiredCoupledVar("temperature", "Temperature of the CRUD for viscosity calculation (water temperature)");

  return params;
}

RadiationMaterial::RadiationMaterial(const InputParameters & parameters)
    :Material(parameters),

     // Get simple parameters from the input file
     _constant_temperature(getParam<Real>("ConstantTemperature")),

     // Get defect diffusivity parameters from the input file
     _vacancy_D0(getParam<Real>("VacancyD0")),
     _interstitial_D0(getParam<Real>("InterstitialD0")),
     _vacancy_activation_energy(getParam<Real>("VacancyActivationEnergy")),
     _interstitial_activation_energy(getParam<Real>("InterstitialActivationEnergy")),

     // Get defect diffusivity parameters from the input file
     _intracascade_survival(getParam<Real>("IntraCascadeSurvivalFraction")),

     // Get defect rate constant parameters from the input file
     _vacancy_sink_density(getParam<Real>("VacancySinkDensity")),
     _interstitial_sink_density(getParam<Real>("InterstitialSinkDensity")),
     _vacancy_sink_strength(getParam<Real>("VacancySinkStrength")),
     _interstitial_sink_strength(getParam<Real>("InterstitialSinkStrength")),
     _recombination_efficiency(getParam<Real>("RecombinationEfficiency")),

     // Get crystallographic parameters
     _lattice_parameter(getParam<Real>("LatticeParameter")),
     _dislocation_density_initial(getParam<Real>("DislocationDensityInitial")),
     _average_void_radius_initial(getParam<Real>("AverageVoidRadiusInitial")),

     // Declare material properties that kernels can use
     _vacancy_diffusivity_matprop(declareProperty<Real>("VacancyDiffusivityMatProp")),
     _interstitial_diffusivity_matprop(declareProperty<Real>("InterstitialDiffusivityMatProp")),

     // Declare intracascade-related properties for kernel use
     _intracascade_survival_matprop(declareProperty<Real>("IntracascadeSurvivalMatProp")),

     // Declare material properties that are just the rate constants,
     // so that they may be defined in the most logical place, within
     // within the context of a single material.
     _vacancy_sink_density_matprop(declareProperty<Real>("VacancySinkDensityMatProp")),
     _interstitial_sink_density_matprop(declareProperty<Real>("InterstitialSinkDensityMatProp")),
     _vacancy_sink_strength_matprop(declareProperty<Real>("VacancySinkStrengthMatProp")),
     _interstitial_sink_strength_matprop(declareProperty<Real>("InterstitialSinkStrengthMatProp")),
     _recombination_efficiency_matprop(declareProperty<Real>("RecombinationEfficiencyMatProp")),

     _lattice_parameter_matprop(declareProperty<Real>("LatticeParameterMatProp")),
     _atomic_volume_matprop(declareProperty<Real>("AtomicVolumeMatProp")),
     _number_density_matprop(declareProperty<Real>("NumberDensityMatProp")),
     _dislocation_density_matprop(declareProperty<Real>("DislocationDensityMatProp")),
     _thermal_vacancy_concentration_matprop(declareProperty<Real>("ThermalVacancyConcentrationMatProp")),
     _average_void_radius_matprop(declareProperty<Real>("AverageVoidRadiusMatProp"))

     // Bring in any coupled variables needed to calculate material properties
//     _T(coupledValue("temperature"))

{
}

void
RadiationMaterial::computeQpProperties()
{
  Real _T = _constant_temperature;  // Comment to allow variable temperatures

  Real _boltzmann_constant = 8.62e-5;  // In eV-K units

  Real _N_avogadro = 6.02e23;  // Number of atoms per mole

  Real _Fe_density = 7.85;  // in g/cc

  Real _Fe_molar_mass = 55.85;  // in g/mol

  _vacancy_diffusivity_matprop[_qp] = _vacancy_D0 *
    std::exp((-_vacancy_activation_energy)
     / (_boltzmann_constant * _T));

  _interstitial_diffusivity_matprop[_qp] = _interstitial_D0 *
    std::exp((-_interstitial_activation_energy)
     / (_boltzmann_constant * _T));

  _intracascade_survival_matprop[_qp] = _intracascade_survival;

  _vacancy_sink_density_matprop[_qp] = _vacancy_sink_density;
  _interstitial_sink_density_matprop[_qp] = _interstitial_sink_density;
  _vacancy_sink_strength_matprop[_qp] = _vacancy_sink_strength;
  _interstitial_sink_strength_matprop[_qp] = _interstitial_sink_strength;
  _recombination_efficiency_matprop[_qp] = _recombination_efficiency;

  _lattice_parameter_matprop[_qp] = _lattice_parameter;

  _atomic_volume_matprop[_qp] =   (1.93559e-10 * std::pow(_T, 2))
                                + (2.68634e-7 * _T)
                                +  0.0116954;

  _number_density_matprop[_qp] =   (_Fe_density / 1e21)  // Density in g/nm3
                                 / _Fe_molar_mass        // Gives mol/nm3
                                 * _N_avogadro;          // Gives atoms/nm3

  _dislocation_density_matprop[_qp] = _dislocation_density_initial;
  _average_void_radius_matprop[_qp] = _average_void_radius_initial;

  _thermal_vacancy_concentration_matprop[_qp] = (std::pow(10, (-44.5997 + 5.73698 * std::log(_T - 376.952)))) * _number_density_matprop[_qp];
}
