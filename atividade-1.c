#include <stdio.h>
#include "pico/stdlib.h"

const uint ROW_PINS[4] = {2, 3, 8, 9};     // Linhas: R1, R2, R3, R4
const uint COL_PINS[4] = {20, 19, 18, 17}; // Colunas: C1, C2, C3, C4

// Mapeamento das teclas
const char KEYPAD[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

int main()
{

    while (1)
    {
        printf("ola mundo!");
        sleep_ms(100);
    }

    return 0;
}
