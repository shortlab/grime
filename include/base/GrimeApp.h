#ifndef GRIMEAPP_H
#define GRIMEAPP_H

#include "MooseApp.h"

class GrimeApp;

template<>
InputParameters validParams<GrimeApp>();

class GrimeApp : public MooseApp
{
public:
  GrimeApp(const std::string & name, InputParameters parameters);
  virtual ~GrimeApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* GRIMEAPP_H */
