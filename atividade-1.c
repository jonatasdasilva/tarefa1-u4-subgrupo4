#include <stdio.h>
#include "pico/stdlib.h"

#define LED_PIN_RED 13 // LED vermelho no GPIO 13
#define LED_PIN_BLUE 12 // LED azul no GPIO 12
#define LED_PIN_GREEN 11 // LED verde no GPIO 11

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

void setup_keyboard()
{
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
}

void ponto()
{
          gpio_put(LED_RED,true);
          sleep_ms(200);
          gpio_put(LED_RED,false);
          sleep_ms(125);
}

void traco()
{
          gpio_put(LED_BLUE,true);
          sleep_ms(200);
          gpio_put(LED_BLUE,false);
          sleep_ms(125);
}
int main()
{

    stdio_init_all();
    // configuração do teclado
    setup_keyboard();

        // Configura o LED vermelho como saída
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    // Configura o LED azul como saída
    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    // Configura o LED verde como saída
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    while (1)
    {
        // leitura do teclado
        char key = scan_keypad();
        gpio_put(LED_PIN_RED, false);
        gpio_put(LED_PIN_BLUE, false);
        gpio_put(LED_PIN_GREEN, false);
        if (key != '\0')
        { // Se alguma tecla foi pressionada
            printf("tecla pressionada: %c\n", key);
            if (key == 'A')
            {
               // Liga o LED vermelho se o botão "A" for pressionado
            gpio_put(LED_PIN_RED, true);
            sleep_ms(300); // Mantém o LED ligado por 300 ms
            } else 
            if (key == 'B')
                {
                    // Liga o LED azul se o botão "B" for pressionado
                    gpio_put(LED_PIN_BLUE, true);
                    sleep_ms(300); // Mantém o LED ligado por 300 ms
                }else
                    if(key== 'C'){
                        // Liga o LED verde se o botão "C" for pressionado
                        gpio_put(LED_PIN_GREEN, true);
                        sleep_ms(300); // Mantém o LED ligado por 300 ms
                    }else
                        if(key == 'D'){
                            // Liga o LED branco se o botão "D" for pressionado
                            gpio_put(LED_PIN_RED, true);
                            gpio_put(LED_PIN_BLUE, true);
                            gpio_put(LED_PIN_GREEN, true);
                            sleep_ms(300); // Mantém o LED ligado por 300 ms
                        }else
                            {
                                // Desliga o LED
                                gpio_put(LED_PIN_RED, false);
                                gpio_put(LED_PIN_BLUE, false);
                                gpio_put(LED_PIN_GREEN, false);
                            }
        }
        sleep_ms(100);
    }

    return 0;
}
