#include <stdio.h>
#include "pico/stdlib.h"

// Definição do pino conectado ao buzzer
#define BUZZER_PIN 10

// Frequências das notas musicais (em Hertz)
#define NOTE_DO  262   // Nota Dó
#define NOTE_RE  294   // Nota Ré
#define NOTE_MI  330   // Nota Mi
#define NOTE_FA  349   // Nota Fá
#define NOTE_SOL 392   // Nota Sol
#define NOTE_LA  440   // Nota Lá
#define NOTE_SI  494   // Nota Si

// Mapeamento do teclado matricial para as notas musicais
int note_frequencies[4][4] = {
    {NOTE_DO, NOTE_RE, NOTE_MI, 0},    // Linha 1: Teclas 1, 2, 3, A
    {NOTE_FA, NOTE_SOL, NOTE_LA, 0},  // Linha 2: Teclas 4, 5, 6, B
    {NOTE_SI, 0,       0,       0},   // Linha 3: Teclas 7, 8, 9, C
    {0,       0,       0,       0}    // Linha 4: Teclas *, 0, #, D
};

// Configuração dos pinos do teclado matricial
const uint rows[] = {9, 8, 7, 6}; // Pinos das linhas: R1, R2, R3, R4
const uint cols[] = {5, 4, 3, 2}; // Pinos das colunas: C1, C2, C3, C4

// Função para gerar o som correspondente a uma frequência
void play_tone(uint frequency, uint duration_ms) {
    if (frequency == 0) return; // Não gera som se a tecla não for válida

    uint period = 1000000 / frequency; // Período do sinal (em microssegundos)
    uint half_period = period / 2;     // Meio período para alternar o estado do pino

    // Gera o sinal de áudio no buzzer pelo tempo especificado
    for (uint i = 0; i < (duration_ms * 1000) / period; i++) {
        gpio_put(BUZZER_PIN, 1);       // Liga o buzzer
        sleep_us(half_period);        // Aguarda metade do período
        gpio_put(BUZZER_PIN, 0);       // Desliga o buzzer
        sleep_us(half_period);        // Aguarda a outra metade do período
    }
}

int main() {

    // Inicializa o pino do buzzer
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT); // Define como saída

    // Configura os pinos das linhas do teclado como entradas com pull-up
    for (int i = 0; i < 4; i++) {
        gpio_init(rows[i]);
        gpio_set_dir(rows[i], GPIO_IN);  // Define como entrada
        gpio_pull_up(rows[i]);           // Habilita o pull-up interno
    }

    // Configura os pinos das colunas do teclado como saídas
    for (int i = 0; i < 4; i++) {
        gpio_init(cols[i]);
        gpio_set_dir(cols[i], GPIO_OUT); // Define como saída
        gpio_put(cols[i], 1);           // Inicializa como nível alto
    }

    // Loop infinito para detectar teclas pressionadas e tocar as notas
    while (1) {
        // Varre cada coluna do teclado
        for (int col = 0; col < 4; col++) {
            gpio_put(cols[col], 0); // Ativa a coluna atual (nível baixo)

            // Verifica se alguma tecla da coluna atual foi pressionada
            for (int row = 0; row < 4; row++) {
                if (!gpio_get(rows[row])) { // Se a linha estiver em nível baixo, tecla pressionada
                    uint frequency = note_frequencies[row][col]; // Obtém a frequência da tecla
                    play_tone(frequency, 500); // Toca a nota correspondente por 500ms

                    // Aguarda a liberação da tecla antes de continuar
                    while (!gpio_get(rows[row])) {
                        sleep_ms(10); // Pequena espera para evitar leitura contínua
                    }
                }
            }

            gpio_put(cols[col], 1); // Desativa a coluna atual (nível alto)
        }

        sleep_ms(50); // Pequena pausa para evitar leitura instável (debounce)
    }
}

