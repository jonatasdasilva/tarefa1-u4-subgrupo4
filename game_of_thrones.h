
#ifndef GAME_OF_THRONES_H
#define GAME_OF_THRONES_H

#include "pico/stdlib.h"

// Definições dos pinos dos buzzers (podem ser configurados no programa principal)
#ifndef BUZZER_PIN_1
#define BUZZER_PIN_1 10
#endif

#ifndef BUZZER_PIN_2
#define BUZZER_PIN_2 22
#endif

// Notas da melodia de Game of Thrones
static const float note_sequence[] = {
    392.0, 261.63, 311.13, 349.23, 392.0, 261.63, 311.13, 349.23, 392.0, 261.63, 311.13, 349.23, 392.0, 261.63, 329.63, 349.23,
    392.0, 261.63, 329.63, 349.23, 392.0, 261.63, 311.13, 349.23, 392.0, 261.63, 311.13, 349.23, 392.0, 261.63, 311.13, 349.23,
    392.0, 392.0, 261.63, 261.63, 311.13, 349.23, 392.0, 261.63, 311.13, 349.23,
    294.33, 196.0, 233.08, 261.63, 294.33, 196.0, 233.08, 261.63, 294.33, 196.0, 233.08, 261.63, 294.33, 196.0, 233.08, 261.63,
    349.23, 349.23, 233.08, 233.08, 311.13, 294.33, 349.23, 233.08, 311.13, 294.33,
    261.63, 196.0, 220.0, 233.08, 261.63, 196.0, 220.0, 233.08, 261.63, 196.0, 220.0, 233.08, 261.63, 196.0, 220.0, 233.08,
    392.0, 392.0, 261.63, 261.63, 311.13, 349.23, 392.0, 261.63, 311.13, 349.23,
    294.33, 196.0, 233.08, 261.63, 294.33, 196.0, 233.08, 261.63, 294.33, 196.0, 233.08, 261.63, 294.33, 196.0, 233.08, 261.63,
    349.23, 349.23, 233.08, 233.08, 311.13, 294.33, 349.23, 233.08, 311.13, 294.33,
    261.63, 196.0, 220.0, 233.08, 261.63, 196.0, 220.0, 233.08, 261.63, 392.0, 415.30, 466.16, 523.25, 392.0, 415.30, 466.16,
    784.0, 784.0, 523.25, 523.25, 622.25, 698.46, 784.0, 523.25, 622.25, 698.46,
    587.33, 392.0, 466.16, 523.25, 587.33, 392.0, 466.16, 523.25, 587.33, 392.0, 466.16, 523.25, 587.33, 392.0, 466.16, 523.25,
    698.46, 698.46, 466.16, 466.16, 587.33, 587.33, 622.25, 622.25, 587.33, 587.33, 466.16, 466.16,
    523.25, 392.0, 415.30, 466.16
}; 

// Tempos das notas em milissegundos
static const int note_durations[] = {
    250, 250, 125, 125, 250, 250, 125, 125, 250, 250, 125, 125, 250, 250, 125, 125,
    250, 250, 125, 125, 250, 250, 125, 125, 250, 250, 125, 125, 250, 250, 125, 125,
    500, 250, 500, 250, 125, 125, 500, 500, 125, 125,
    250, 250, 125, 125, 250, 250, 125, 125, 250, 250, 125, 125, 250, 250, 125, 125,
    500, 250, 500, 250, 125, 125, 500, 500, 125, 125,
    250, 250, 125, 125, 250, 250, 125, 125, 250, 250, 125, 125, 250, 250, 125, 125,
    500, 250, 500, 250, 125, 125, 500, 500, 125, 125,
    250, 250, 125, 125, 250, 250, 125, 125, 250, 250, 125, 125, 250, 250, 125, 125,
    500, 250, 500, 250, 125, 125, 500, 500, 125, 125,
    250, 250, 125, 125, 250, 250, 125, 125, 250, 250, 125, 125, 250, 250, 125, 125,
    500, 250, 500, 250, 125, 125, 500, 500, 125, 125,
    250, 250, 125, 125, 250, 250, 125, 125, 250, 250, 125, 125, 250, 250, 125, 125,
    250, 125, 250, 125, 250, 125, 250, 125, 250, 125, 250, 125, 250, 125, 250, 125
};

// Função para tocar uma frequência no buzzer
static inline void tocar_buzzer_frequencia(int pin, float frequencia, int duracao_ms) {
    double tempo_ciclo = 1000000.0 / frequencia;
    int duracao_us = duracao_ms * 1000;
    int num_ciclos = duracao_us / tempo_ciclo;

    for (int i = 0; i < num_ciclos; i++) {
        gpio_put(pin, true);
        sleep_us(tempo_ciclo / 2);
        gpio_put(pin, false);
        sleep_us(tempo_ciclo / 2);
    }
    gpio_put(pin, false);
}

// Função para tocar uma melodia alternando entre dois buzzers
static inline void tocar_melodia(int pin1, int pin2, const float *notas, const int *tempos, int num_notas) {
    for (int i = 0; i < num_notas; i++) {
        if (i % 2 == 0) {
            tocar_buzzer_frequencia(pin1, notas[i], tempos[i]);
        } else {
            tocar_buzzer_frequencia(pin2, notas[i], tempos[i]);
        }
        sleep_ms(50); // Pausa entre as notas
    }
}

static inline void play_song() {
    int num_notas = sizeof(note_sequence) / sizeof(note_sequence[0]);
    tocar_melodia(BUZZER_PIN_1, BUZZER_PIN_2, note_sequence, note_durations, num_notas);
    sleep_ms(1000);
}

#endif // GAME_OF_THRONES_H
