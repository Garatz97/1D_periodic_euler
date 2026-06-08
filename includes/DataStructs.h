#ifndef _DATA_STRUCTS
#define _DATA_STRUCTS

#include <cstddef>

template<class T>
class DataStruct 
{
  private:
    int size;          // Número de puntos espaciales (N)
    int num_vars;      // Número de variables por punto (3 para Euler)
    T *data;
    bool initialized;

  public:

    // constructors & destructor
    inline DataStruct()
    {
      size = 0;
      num_vars = 3; // Inicializamos para Euler
      data = NULL;
      initialized = false;
    };

    inline DataStruct(int _size)
    {
      num_vars = 3;
      // ¡Multiplicamos la memoria reservada por 3!
      data = new T[_size * num_vars]; 
      size = _size;
      initialized = true;
    };

    inline ~DataStruct() 
    {
      if(initialized) delete[] data;
    };

    // accessors
    inline int getSize()
    {
      return size;
    }

    inline T* getData()
    {
      return data;
    }

    inline T getData(int i)
    {
      return data[i];
    }

    // --- NUEVOS MÉTODOS PARA EULER (Enfoque AoS) ---
    // Devuelven una referencia (T&) para poder leer y escribir en ellos fácilmente
    inline T& getRho(int i)  { return data[i * num_vars + 0]; }
    inline T& getRhoU(int i) { return data[i * num_vars + 1]; }
    inline T& getRhoE(int i) { return data[i * num_vars + 2]; }
    // -----------------------------------------------

    void setSize(int _size);

    inline DataStruct<T>& operator=(DataStruct<T> &rhs)
    {
      this->setSize(rhs.getSize());
      T *dataRHS = rhs.getData();

      // copy data (ahora copiamos size * num_vars elementos)
      for(int n = 0; n < size * num_vars; n++)
      {
        data[n] = dataRHS[n];
      }

      return *this;
    }

};

#endif // _DATA_STRUCTS