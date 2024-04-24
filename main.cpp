#include <iostream>
#include "gacha.hpp"

int main() {
    gacha sistema_gacha;
    sistema_gacha.generar_salto();
    sistema_gacha.generar_salto_multiple();
    sistema_gacha.generar_salto_multiple(30);
    sistema_gacha.exportar_saltos();
    return 0;
}