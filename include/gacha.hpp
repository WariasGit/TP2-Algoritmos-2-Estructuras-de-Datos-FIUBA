#ifndef AYED_TP2_1C2024_GACHA_HPP
#define AYED_TP2_1C2024_GACHA_HPP

#include "salto.hpp"
#include "vector.hpp"
#include "generador_salto.hpp"

class gacha {
private:
    int pity_contador_cinco_estrellas;
    int pity_contador_cuatro_estrellas;
    vector<salto> historial_saltos;

    /*
    * Pre: Minimo y maximo deben ser valores enteros validos. Minimo debe ser menor o igual que maximo.
    * Post: Devuelve un numero entero aleatorio en el rango [minimo, maximo]. 
    *       El numero aleatorio generado, sigue una distribucion uniforme dentro del rango.
    *       Cada llamada produce un resultado independiente del resto de llamadas.
    * */
    static int generar_numero_aleatorio(int minimo, int maximo);

    /*
    * Pre: Numero_aleatorio debe ser un valor entero valido.
    * Post:  Evalua el numero y genera un salto segun sus probabilidades. 5 estrellas(1%), 4 estrellas (10%) Y 3 estrellas (89%).
    * */
    salto hacer_un_salto(int numero_aleatorio);

    /*
    * Pre: Nuevo_salto_generado debe ser un salto valido.
    * Post: Evalua la rareza del salto. Si es un 3 estrellas, evalua el sistema pity con el metodo manejar_pity(salto).
    *       Si no, edita los contadores segun corresponda, agrega el salto al historial de saltos y retorna el salto. 
    * */
    salto aplicar_sistema_pity(salto nuevo_salto_generado);

    /*
    * Pre: Salto_tres_estrellas debe ser un salto valido.
    * Post: Evalua los contadores de saltos. 
    *       Si es necesario, genera un salto nuevo segun corresponda, edita los contadores, agrega el salto al historial de saltos y retorna el salto.
    *       Si no, edita los contadores segun corresponda, agrega el salto al historial de saltos y retorna el salto, de 3 estrellas.
    * */
    salto manejar_pity(salto salto_tres_estrellas);

    /*
    * Pre:
    * Post: Recorre el vector historial_saltos y elimina uno a uno sus elementos.
    * */
    void eliminar_historial_saltos();
public:
    /*
    * Constructor sin parametros
    */
    gacha();

    /*
    * Pre:
    * Post: Se genera un numero aleatorio del 1 al 100. Con ese numero se produce un salto segun la probabilidad que representa. 
    *       Finalmente, retorna un salto, luego de aplicar el sistema pity.
    * */
    salto generar_salto();

    /*
    * Pre:
    * Post: Genera 10 saltos y los devolvera dentro de un vector. Equivale a ejecutar generar_salto() 10 veces.
    * */
    vector<salto> generar_salto_multiple();

    /*
    * Pre:
    * Post: Genera "cantidad" saltos y los devolvera dentro de un vector. Equivale a ejecutar generar_salto() "cantidad" de veces.
    * */
    vector<salto> generar_salto_multiple(size_t cantidad);

    /*
    * Pre: El historial de saltos debe contener al menos un elemento, caso contrario, mostrara un mensaje de error.
    * Post: Este método guardará, a modo de registro, la información de todos los saltos generados en un archivo registro_saltos.csv.
    *       Accede al historial de saltos, y copia la informacion en el archivo. Luego elimina el historial y finalmente, muestra un mensaje de exito.
    * */
    void exportar_saltos();
};

#endif