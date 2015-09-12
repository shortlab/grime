#include "GrimeApp.h"
#include "Moose.h"
#include "AppFactory.h"

// Include kernel header files
#include "DefectSink.h"
#include "DefectSource.h"
#include "DefectRecombination.h"
#include "MatPropDiffusion.h"
  //for cluster
#include "CoeffDiffusion.h"

// Include auxkernel header files
#include "DislocationSinkRate.h"
#include "DefectRecombinationRateConstant.h"
#include "ExcessInterstitialFractionAux.h"
#include "VacancySupersaturation.h"
#include "VacancySupersaturationNumerator.h"
#include "VoidNucleation.h"
#include "VoidSinkRate.h"

// Next come the materials
#include "RadiationMaterial.h"

template<>
InputParameters validParams<GrimeApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

GrimeApp::GrimeApp(const InputParameters & parameters) :
    MooseApp(parameters)
{
  srand(processor_id());

  Moose::registerObjects(_factory);
  GrimeApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  GrimeApp::associateSyntax(_syntax, _action_factory);
}

GrimeApp::~GrimeApp()
{
}

void
GrimeApp::registerApps()
{
  registerApp(GrimeApp);
}

void
GrimeApp::registerObjects(Factory & factory)
{
  // Register kernels
  registerKernel(DefectSink);
  registerKernel(DefectSource);
  registerKernel(DefectRecombination);
  registerKernel(MatPropDiffusion);
  registerKernel(CoeffDiffusion);

  // Register auxkernels
  registerAux(DislocationSinkRate);
  registerAux(DefectRecombinationRateConstant);
  registerAux(ExcessInterstitialFractionAux);
  registerAux(VacancySupersaturation);
  registerAux(VacancySupersaturationNumerator);
  registerAux(VoidNucleation);
  registerAux(VoidSinkRate);

  // Register materials classes
  registerMaterial(RadiationMaterial);
}

void
GrimeApp::associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
}
