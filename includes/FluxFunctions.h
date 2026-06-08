#ifndef _FLUX_FUNCTIONS
#define _FLUX_FUNCTIONS

#include "DataStructs.h"

// base class for flux functions
template<class T>
class FluxFunction
{
  public:
    FluxFunction();

    // in U; out F (Procesará toda la memoria de golpe)
    virtual void computeFlux(DataStruct<T> &U, DataStruct<T> &F) = 0;
};

// Nueva clase para las ecuaciones de Euler 1D
template<class T>
class EulerFlux : public FluxFunction<T>
{
  private:
    T gamma; // Índice adiabático para el cálculo de la presión

  public:
    EulerFlux();

    // in U; out F
    virtual void computeFlux(DataStruct<T> &U, DataStruct<T> &F);
};

#endif // _FLUX_FUNCTIONS