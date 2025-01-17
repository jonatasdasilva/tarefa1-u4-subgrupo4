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

char scan_keypad()
{
    for (int row = 0; row < 4; row++)
    {
        gpio_put(ROW_PINS[row], 0); // Ativa a linha colocando em LOW
        for (int col = 0; col < 4; col++)
        {
            if (!gpio_get(COL_PINS[col]))
            {
                gpio_put(ROW_PINS[row], 1); // Restaura a linha para HIGH
                return KEYPAD[row][col];    // Retorna a tecla pressionada
            }
        }
        gpio_put(ROW_PINS[row], 1); // linha volta para HIGH após a varredura
    }
    return '\0'; // Nenhuma tecla pressionada
}

int main()
{

    stdio_init_all();

    // Configuração das linhas do teclado como saída
    for (int i = 0; i < 4; i++)
    {
        gpio_init(ROW_PINS[i]);
        gpio_set_dir(ROW_PINS[i], GPIO_OUT);
        gpio_put(ROW_PINS[i], 1); // nível alto por padrão
    }

    // Configuração das colunas do teclado
    for (int i = 0; i < 4; i++)
    {
        gpio_init(COL_PINS[i]);
        gpio_set_dir(COL_PINS[i], GPIO_IN);
        gpio_pull_up(COL_PINS[i]); // pull-up interno
    }
    while (1)
    {
        char key = scan_keypad();
        if (key != '\0')
        { // Se alguma tecla foi pressionada
            printf("tecla pressionada: %c\n", key);
            if (key == 'A')
            {
                // e aqui vem a lógica da tecla
            }
        }
        sleep_ms(100);
    }

    return 0;
}
