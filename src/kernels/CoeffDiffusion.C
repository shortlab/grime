#include "CoeffDiffusion.h"

// If we use a material pointer we need to include the
// material class
//#include "Material.h"

template<>
InputParameters validParams<CoeffDiffusion>()
{
  InputParameters params = validParams<Diffusion>();
  params.addRequiredParam<Real>("diffusivity","diffusivity of this species");
  return params;
}

CoeffDiffusion::CoeffDiffusion(const std::string & name, InputParameters parameters)
  :Diffusion(name,parameters),
   // We are grabbing the "diffusivity" from input
   _diffusivity(getParam<Real>("diffusivity"))
{
}

Real
CoeffDiffusion::computeQpResidual()
{
  // We're dereferencing the _diffusivity pointer to get to the
  // material properties vector... which gives us one property
  // value per quadrature point.

  // Also... we're reusing the Diffusion Kernel's residual
  // so that we don't have to recode that.
  //  if (_u[_qp]>=0.0)
    return _diffusivity *Diffusion::computeQpResidual();

}

Real
CoeffDiffusion::computeQpJacobian()
{
  // We're dereferencing the _diffusivity pointer to get to the
  // material properties vector... which gives us one property
  // value per quadrature point.

  // Also... we're reusing the Diffusion Kernel's residual
  // so that we don't have to recode that.
  return _diffusivity *Diffusion::computeQpJacobian();
}

Real CoeffDiffusion::computeQpOffDiagJacobian(unsigned int /*jvar*/)
{
  return 0.0;
}
