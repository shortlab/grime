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

#ifndef EXCESSINTERSTITIALFRACTIONAUX_H
#define EXCESSINTERSTITIALFRACTIONAUX_H

#include "AuxKernel.h"


//Forward Declarations
class ExcessInterstitialFractionAux;

template<>
InputParameters validParams<ExcessInterstitialFractionAux>();

/**
 * Coupled auxiliary value
 */
class ExcessInterstitialFractionAux : public AuxKernel
{
public:

  /**
   * Factory constructor, takes parameters so that all derived classes can be built using the same
   * constructor.
   */
  ExcessInterstitialFractionAux(const std::string & name, InputParameters parameters);

protected:
  virtual Real computeValue();

  VariableValue & _vacancy_creation;
  VariableValue & _interstitial_creation;

};

#endif //EXCESSINTERSTITIALFRACTIONAUX_H
