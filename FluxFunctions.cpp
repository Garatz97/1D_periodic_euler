#include "FluxFunctions.h"

template<class T>
FluxFunction<T>::FluxFunction()
{
  
};

// Constructor de Euler: Definimos la constante del gas
template<class T>
EulerFlux<T>::EulerFlux()
{
  gamma = 1.4; 
};

// Cálculo del vector de flujo de Euler para todo el dominio
template<class T>
void EulerFlux<T>::computeFlux(DataStruct<T> &U, DataStruct<T> &F)
{
  for(int i = 0; i < U.getSize(); i++)
  {
    // 1. Extraemos nuestras 3 variables de memoria usando los métodos que creamos
    T rho  = U.getRho(i);
    T rhou = U.getRhoU(i);
    T rhoE = U.getRhoE(i);

    // 2. Calculamos la velocidad (u = momento / masa)
    T u = rhou / rho;

    // 3. Calculamos la presión usando la ecuación de estado 
    T p = (gamma - 1.0) * (rhoE - 0.5 * rho * u * u); 

    // 4. Construimos el vector de flujo f y lo guardamos en F 
    F.getRho(i)  = rhou;
    F.getRhoU(i) = rhou * u + p;
    F.getRhoE(i) = u * (rhoE + p);
  }
};

// Declaración de las plantillas (necesario en C++)
template class FluxFunction<float>;
template class FluxFunction<double>;

template class EulerFlux<float>;
template class EulerFlux<double>;