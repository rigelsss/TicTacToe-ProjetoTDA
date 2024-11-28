#include <stdio.h>
#include <locale.h>
#include "load-game.h"

int main() {
    setlocale(LC_ALL, "pt_BR.UTF-8");
    mostrarLogo();
    menuInicial();
}