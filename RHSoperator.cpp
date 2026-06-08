#include "RHSoperator.h"

template<class T>
RHSOperator<T>::RHSOperator()
{

}

template<class T>
RHSOperator<T>::~RHSOperator()
{

}

template<class T>
Central1D<T>::Central1D(DataStruct<T> &_U, 
                     DataStruct<T> &_mesh, 
                     FluxFunction<T> &_F):
U(_U), mesh(_mesh), F(_F)
{
  RHS.setSize(_U.getSize());
}

template<class T>
Central1D<T>::~Central1D()
{

}

template<class T>
void Central1D<T>::evalRHS(DataStruct<T> &Uin)
{
  const T *dataMesh = mesh.getData();
  const int len = U.getSize();
  
  // 1. Calculamos todos los flujos del dominio a la vez
  // IMPORTANTE PARA HPC: Leer nota de abajo.
  DataStruct<T> flux(len);
  F.computeFlux(Uin, flux);
  
  // 2. Aplicamos diferencias centradas espaciales a las 3 variables
  for(int j = 0; j < len; j++)
  {
    T dx;
    if(j == 0) // Condición de contorno periódica (Izquierda)
    {
      dx = dataMesh[len-1] - dataMesh[len-2];
      dx += dataMesh[1] - dataMesh[0];
      
      RHS.getRho(0)  = -(flux.getRho(1)  - flux.getRho(len-2))  / dx;
      RHS.getRhoU(0) = -(flux.getRhoU(1) - flux.getRhoU(len-2)) / dx;
      RHS.getRhoE(0) = -(flux.getRhoE(1) - flux.getRhoE(len-2)) / dx;
    }
    else if (j == len - 1) // Condición de contorno periódica (Derecha)
    {
      RHS.getRho(len-1)  = RHS.getRho(0);
      RHS.getRhoU(len-1) = RHS.getRhoU(0);
      RHS.getRhoE(len-1) = RHS.getRhoE(0);
    }
    else // Nodos interiores
    {
      dx = dataMesh[j+1] - dataMesh[j-1];
      
      RHS.getRho(j)  = -(flux.getRho(j+1)  - flux.getRho(j-1))  / dx;
      RHS.getRhoU(j) = -(flux.getRhoU(j+1) - flux.getRhoU(j-1)) / dx;
      RHS.getRhoE(j) = -(flux.getRhoE(j+1) - flux.getRhoE(j-1)) / dx;
    }
  }
}

template<class T>
void Central1D<T>::eval()
{
  evalRHS(U);
}

template<class T>
void Central1D<T>::eval(DataStruct<T> &Uin)
{
  evalRHS(Uin);
}

template<class T>
DataStruct<T>& Central1D<T>::ref2RHS()
{
  return RHS;
}

template class RHSOperator<float>;
template class RHSOperator<double>;

template class Central1D<float>;
template class Central1D<double>;