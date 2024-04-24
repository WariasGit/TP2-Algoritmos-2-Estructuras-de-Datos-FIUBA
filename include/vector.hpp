#ifndef VECTOR_H
#define VECTOR_H

#include <cstddef>
#include <exception>
#include <typeinfo>

class vector_exception : public std::exception {
    // Excepción especifica y exclusiva para errores dentro del vector.
    // Usar de la forma "throw vector_exception();" cuando una precondición no se cumpla.

    // Ejemplo:
    //     if (condición_de_error){
    //         throw vector_exception();
    //     }
};

template<typename T>
class vector {
private:
    T* datos;
    size_t cantidad_datos;  //tope
    // Tamaño del arreglo "datos".
    size_t tamanio_maximo;  //[MAX]
public:
    // Constructor.
    vector();

    // Pre: El índice debe ser menor o igual que la cantidad de datos.
    // Post: Agrega el dato antes del dato en la posición indicada, moviendo todos los elementos siguientes.
    void alta(T dato, size_t indice);

    // Pre: - El parametro dato debe ser del tipo de dato T.
    // Post: Agrega el dato al final del vector. Equivale a alta(dato, cantidad_datos).
    void alta(T dato);

    // Pre: El vector no puede estar vacío. El índice debe ser menor que la cantidad de datos.
    // Post: Elimina el dato en la posición indicada, moviendo todos los elementos siguientes, y lo devuelve.
    T baja(size_t indice);

    // Pre: El vector no puede estar vacío.
    // Post: Elimina el ultimo dato y lo devuelve. Equivale a baja(cantidad_datos - 1).
    T baja();

    // Pre: -
    // Post: Devuelve true si el vector está vacío (es decir, si no hay datos).
    bool vacio();

    // Pre: -
    // Post: Devuelve la cantidad de datos del vector.
    size_t tamanio();

    // Pre: El vector no puede estar vacío. El índice debe ser menor que la cantidad de datos.
    // Post: Devuelve una referencia al dato deseado.
    T& operator[](size_t indice);

    // Constructor de copia (ya implementado).
    vector(const vector<T>& vector);

    // Operador de asignación (ya implementado).
    vector<T>& operator=(const vector<T>& vector);

    // Destructor.
    ~vector();

private:
    /*
    * Pre: El parametro tamanio_nuevo debe ser un valor valido.
    * Post: Redimensiona el vector al tamanio pedido.
    */
    void redimensionar_vector(size_t tamanio_nuevo);

    /*
    * Pre:
    * Post: Evalua si el vector esta vacio, lleno o solo ocupa la mitad de su capacidadd y redimensiona segun sea necesario.
    */
    void se_redimensiona();
};

template<typename T>
vector<T>::vector() {
    datos = nullptr;
    cantidad_datos = 0;
    tamanio_maximo = 0;
}

template<typename T>
void vector<T>::alta(T dato, size_t indice) {
    if (indice>cantidad_datos || typeid(dato) != typeid(T)){
        throw vector_exception();
    }
    else{
        se_redimensiona();
        for (size_t i=cantidad_datos; i>indice; --i ){
                datos[i] = datos[i-1];
        }
        datos[indice] = dato;
        ++cantidad_datos;
    }
}

template<typename T>
void vector<T>::alta(T dato) {
    if (typeid(dato) != typeid(T)){
        throw vector_exception();
    }
    else{
        se_redimensiona();
        datos[cantidad_datos] = dato;
        ++cantidad_datos;
    }
}

template<typename T>
T vector<T>::baja(size_t indice) {
    if (indice>= cantidad_datos || cantidad_datos == 0){
        throw vector_exception();
    }
    else{
        T dato_eliminado = datos[indice];
        for (size_t i=indice; i<cantidad_datos -1; ++i){
            datos[i] = datos[i +1];
        }
        --cantidad_datos;
        se_redimensiona();
        return dato_eliminado;
    }
}

template<typename T>
T vector<T>::baja() {
    if (cantidad_datos == 0){
        throw vector_exception();
    }
    else{
        T dato_eliminado = datos[cantidad_datos -1];
        --cantidad_datos;
        se_redimensiona();
        return dato_eliminado;
    }
}

template<typename T>
bool vector<T>::vacio() {
    return cantidad_datos==0;
}

template<typename T>
size_t vector<T>::tamanio() {
    return cantidad_datos;
}

template<typename T>
T& vector<T>::operator[](size_t indice) {
    if (cantidad_datos == 0 || indice >= cantidad_datos){
        throw vector_exception();
    }
    else{
        return datos[indice];
    }
    
}

template<typename T>
vector<T>::~vector() {
    if (datos != nullptr){
        delete [] datos ;
    }
}

// Estos dos métodos ya están implementados. No hace falta modificarlos.
template<typename T>
vector<T>::vector(const vector& vector) {
    datos = nullptr;
    cantidad_datos = vector.cantidad_datos;
    tamanio_maximo = vector.tamanio_maximo;
    if (tamanio_maximo) {
        datos = new T[tamanio_maximo];
        for (size_t i = 0; i < cantidad_datos; i++) {
            datos[i] = vector.datos[i];
        }
    }
}

template<typename T>
vector<T>& vector<T>::operator=(const vector& vector) {
    if (this != &vector) {
        delete[] datos;
        datos = nullptr;
        cantidad_datos = vector.cantidad_datos;
        tamanio_maximo = vector.tamanio_maximo;
        if (tamanio_maximo) {
            datos = new T[tamanio_maximo];
            for (size_t i = 0; i < cantidad_datos; i++) {
                datos[i] = vector.datos[i];
            }
        }
    }
    return *this;
}

template<typename T>
void vector<T>::redimensionar_vector(size_t tamanio_nuevo){
    T* nuevo_puntero = new T[tamanio_nuevo];
    for (size_t i=0; i<cantidad_datos; ++i){
        nuevo_puntero[i] = datos[i];
    }
    if (datos != nullptr) {
        delete[] datos;
    }
    datos = nuevo_puntero;
    tamanio_maximo = tamanio_nuevo;
}

template<typename T>
void vector<T>::se_redimensiona(){
    if (cantidad_datos == tamanio_maximo){
            if (tamanio_maximo == 0){
                redimensionar_vector(10);
            }
            else{
                redimensionar_vector(tamanio_maximo*2);
            }
    }
    else if (cantidad_datos < tamanio_maximo/2){
        redimensionar_vector(tamanio_maximo/2);
    }
}

#endif