#include "pico/stdlib.h"

// Definição dos pinos para o teclado
const uint ROW_PINS[4] = {8, 7, 6, 5};     // Linhas: R1, R2, R3, R4
const uint COL_PINS[4] = {4, 3, 2, 28};    // Colunas: C1, C2, C3, C4

// Definição dos pinos para o LED e buzzer
#define LED_PIN1 13 // LED 1 conectado ao pino 13
#define LED_PIN2 12 // LED 2 conectado ao pino 12
#define LED_PIN3 11 // LED 3 conectado ao pino 11
#define BUZZER_PIN 21 // Buzzer conectado ao pino 21

// Mapeamento do display de 7 segmentos para os pinos
const uint SEGMENT_PINS[7] = {1, 0, 9, 10, 14, 15, 16}; // A, B, C, D, E, F, G

// Mapeamento dos números para os segmentos do display de 7 segmentos
const uint8_t DIGIT_PATTERNS[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

const char KEYPAD[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};

// Função para varrer o teclado e identificar a tecla pressionada
char scan_keypad()
{
    for (int row = 0; row < 4; row++)
    {
        gpio_put(ROW_PINS[row], 0); // Ativa a linha colocando em LOW
        for (int col = 0; col < 4; col++)
        {
            if (!gpio_get(COL_PINS[col])) // Se a tecla for pressionada
            {
                gpio_put(ROW_PINS[row], 1); // Restaura a linha para HIGH
                return KEYPAD[row][col];    // Retorna a tecla pressionada
            }
        }
        gpio_put(ROW_PINS[row], 1); // Linha volta para HIGH após a varredura
    }
    return '\0'; // Nenhuma tecla pressionada
}

// Função para configurar o teclado
void setup_keyboard()
{
    for (int i = 0; i < 4; i++)
    {
        gpio_init(ROW_PINS[i]);
        gpio_set_dir(ROW_PINS[i], GPIO_OUT);
        gpio_put(ROW_PINS[i], 1); // Nível alto por padrão
    }

    for (int i = 0; i < 4; i++)
    {
        gpio_init(COL_PINS[i]);
        gpio_set_dir(COL_PINS[i], GPIO_IN);
        gpio_pull_up(COL_PINS[i]); // Pull-up interno
    }
}

// Função para configurar o buzzer
void setup_buzzer()
{
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
}

// Função para configurar os pinos do display de 7 segmentos
void setup_display()
{
    for (int i = 0; i < 7; i++)
    {
        gpio_init(SEGMENT_PINS[i]);
        gpio_set_dir(SEGMENT_PINS[i], GPIO_OUT);
        gpio_put(SEGMENT_PINS[i], 0); // Desliga os segmentos por padrão
    }
}

// Função para mostrar um número no display de 7 segmentos
void display_digit(uint8_t digit)
{
    uint8_t pattern = DIGIT_PATTERNS[digit];
    for (int i = 0; i < 7; i++)
    {
        gpio_put(SEGMENT_PINS[i], (pattern >> i) & 1); // Aciona o segmento
    }
}

int main()
{
    setup_keyboard();
    setup_buzzer();
    setup_display();

    // Configuração dos LEDs
    gpio_init(LED_PIN1);
    gpio_set_dir(LED_PIN1, GPIO_OUT);
    gpio_init(LED_PIN2);
    gpio_set_dir(LED_PIN2, GPIO_OUT);
    gpio_init(LED_PIN3);
    gpio_set_dir(LED_PIN3, GPIO_OUT);
    gpio_put(LED_PIN1, false);
    gpio_put(LED_PIN2, false);
    gpio_put(LED_PIN3, false);

    while (1)
    {
        char key = scan_keypad();
        if (key != '\0') // Se alguma tecla foi pressionada
        {
            printf("Tecla pressionada: %c\n", key);

            // Verifica se a tecla pressionada é um número e exibe no display de 7 segmentos
            if (key >= '0' && key <= '9')
            {
                uint8_t digit = key - '0'; // Converte o caractere para o número correspondente
                display_digit(digit); // Exibe o número no display
            }
            else
            {
                gpio_put(LED_PIN1, false);
                gpio_put(LED_PIN2, false);
                gpio_put(LED_PIN3, false);
            }
        }
        sleep_ms(100); // Espera 100ms
    }

    return 0;
}
