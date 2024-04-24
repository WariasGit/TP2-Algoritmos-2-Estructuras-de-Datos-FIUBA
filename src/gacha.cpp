#include "gacha.hpp"
#include "generador_salto.hpp"
#include <random>
#include <iostream>
#include <fstream>

void gacha::eliminar_historial_saltos() {
    size_t elementos = historial_saltos.tamanio();
    for (size_t i = 0; i < elementos; ++i){
        historial_saltos.baja();
    }
}


int gacha::generar_numero_aleatorio(int minimo, int maximo){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(minimo, maximo);
    return dis(gen);
}

salto gacha::hacer_un_salto(int numero){
    if (numero == 1){
        return generador_salto::generar_salto_5_estrellas();
    }
    else if (numero > 1 && numero <=11){
        return generador_salto::generar_salto_4_estrellas();
    }
    else {
        return generador_salto::generar_salto_3_estrellas();
    }
}

salto gacha::manejar_pity(salto salto_tres_estrellas){
    if (pity_contador_cinco_estrellas >= 89){
        salto salto_cinco_estrellas = generador_salto::generar_salto_5_estrellas();
        pity_contador_cinco_estrellas = 0;
        ++pity_contador_cuatro_estrellas;
        historial_saltos.alta(salto_cinco_estrellas);
        return salto_cinco_estrellas;
    }
    else if (pity_contador_cuatro_estrellas >= 9){
        salto salto_cuatro_estrellas = generador_salto::generar_salto_4_estrellas();
        pity_contador_cuatro_estrellas = 0;
        ++pity_contador_cinco_estrellas;
        historial_saltos.alta(salto_cuatro_estrellas);
        return salto_cuatro_estrellas;
    }
    else{
        ++pity_contador_cinco_estrellas;
        ++pity_contador_cuatro_estrellas;
        historial_saltos.alta(salto_tres_estrellas);
        return salto_tres_estrellas;
    }
}

salto gacha::aplicar_sistema_pity(salto nuevo_salto_generado){
    rareza rareza_obtenida = nuevo_salto_generado.obtener_rareza();
    switch (rareza_obtenida){
    case TRES_ESTRELLAS:
        return manejar_pity(nuevo_salto_generado);
    case CUATRO_ESTRELLAS:
        pity_contador_cuatro_estrellas = 0;
        ++pity_contador_cinco_estrellas;
        historial_saltos.alta(nuevo_salto_generado);
        return nuevo_salto_generado;
    case CINCO_ESTRELLAS:
        pity_contador_cinco_estrellas =0;
        ++pity_contador_cuatro_estrellas;
        historial_saltos.alta(nuevo_salto_generado);
        return nuevo_salto_generado;
    default:
        return nuevo_salto_generado;
    }
}





gacha::gacha() {
    pity_contador_cinco_estrellas = 0;
    pity_contador_cuatro_estrellas = 0;
}

salto gacha::generar_salto() {
    int numero_aleatorio = generar_numero_aleatorio(1,100);
    salto nuevo_salto_generado = hacer_un_salto(numero_aleatorio);
    return aplicar_sistema_pity(nuevo_salto_generado);
}

vector<salto> gacha::generar_salto_multiple() {
    vector<salto> saltos_generados;
    for (int i = 0; i < 10; ++i){
        salto nuevo_salto = generar_salto();
        saltos_generados.alta(nuevo_salto);
    }
    return saltos_generados;
}

vector<salto> gacha::generar_salto_multiple(size_t cantidad) {
    vector<salto> saltos_generados;
    for (size_t i = 0; i < cantidad; ++i){
        salto nuevo_salto = generar_salto();
        saltos_generados.alta(nuevo_salto);
    }
    return saltos_generados;
}

void gacha::exportar_saltos() {
    if (historial_saltos.vacio()){
        std::cout << "No hay saltos para exportar."<< std::endl;
        return;
    }
    else{
        std::ofstream archivo_historial ("registro_saltos.csv", std::ofstream::app);
        if (!archivo_historial.is_open()) {
            std::cerr << "Error al abrir el archivo registro_saltos." << std::endl;
            return;
        }
        for (size_t i = 0; i < historial_saltos.tamanio(); ++i ){
            archivo_historial << historial_saltos[i] << std::endl;
        }
        archivo_historial.close();
        eliminar_historial_saltos();
        std::cout << "Los saltos se han exportado correctamente y el historial de saltos se ha limpiado." << std::endl;
    }
}





