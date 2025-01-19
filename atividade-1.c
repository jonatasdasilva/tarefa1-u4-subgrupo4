#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/gpio.h"

#define ROWS 4
#define COLS 4

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

// Mapeamento dos caracteres para Código Morse.
const char *morse_code[ROWS][COLS] = {
    {".----", "..---", "...--", ".-"},    // 1, 2, 3, A
    {"....-", ".....", "-....", "-..."},  // 4, 5, 6, B
    {"--...", "---..", "----.", "-.-."},  // 7, 8, 9, C
    {NULL, "-----", NULL, "-.--"}         // *, 0, #, D
};

// GPIO pins for buzzers
#define BUZZER_DOT 10
#define BUZZER_DASH 22

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
    {NOTE_FA, NOTE_SOL, NOTE_LA, 0},   // Linha 2: Teclas 4, 5, 6, B
    {NOTE_SI, 0,       0,       0},    // Linha 3: Teclas 7, 8, 9, C
    {0,       0,       0,       0}     // Linha 4: Teclas *, 0, #, D
};

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

// Função para gerar o som correspondente a uma frequência
void play_tone(uint frequency, uint duration_ms) {
    if (frequency == 0) return; // Não gera som se a tecla não for válida

    uint period = 1000000 / frequency; // Período do sinal (em microssegundos)
    uint half_period = period / 2;     // Meio período para alternar o estado do pino

    // Gera o sinal de áudio no buzzer pelo tempo especificado
    for (uint i = 0; i < (duration_ms * 1000) / period; i++) {
        gpio_put(BUZZER_DOT, 1);       // Liga o buzzer
        sleep_us(half_period);        // Aguarda metade do período
        gpio_put(BUZZER_DOT, 0);       // Desliga o buzzer
        sleep_us(half_period);        // Aguarda a outra metade do período
    }
}

// Função que implementa o teclado musical com retorno ao menu
void music_keyboard() {
    // Configura os pinos do teclado musical
    for (int i = 0; i < 4; i++) {
        gpio_init(ROW_PINS[i]);
        gpio_set_dir(ROW_PINS[i], GPIO_IN);  // Define como entrada
        gpio_pull_up(ROW_PINS[i]);           // Habilita o pull-up interno
    }

    for (int i = 0; i < 4; i++) {
        gpio_init(COL_PINS[i]);
        gpio_set_dir(COL_PINS[i], GPIO_OUT); // Define como saída
        gpio_put(COL_PINS[i], 1);           // Inicializa como nível alto
    }

    // Loop infinito para detectar teclas pressionadas e tocar as notas
    while (1) {
        for (int col = 0; col < 4; col++) {
            gpio_put(COL_PINS[col], 0); // Ativa a coluna atual (nível baixo)

            for (int row = 0; row < 4; row++) {
                if (!gpio_get(ROW_PINS[row])) { // Se a linha estiver em nível baixo, tecla pressionada
                    char key = KEYPAD[row][col]; // Determina a tecla pressionada

                    if (key == '#') { // Verifica se é o comando para sair
                        printf("Saindo do teclado musical...\n");
                        return; // Sai da função para voltar ao menu
                    }

                    if (key >= '1' && key <= '7') { // Apenas teclas válidas para notas
                        uint frequency = note_frequencies[row][col]; // Obtém a frequência da tecla
                        play_tone(frequency, 500); // Toca a nota correspondente por 500ms
                    } else {
                        printf("Tecla %c não corresponde a uma nota.\n", key);
                    }

                    while (!gpio_get(ROW_PINS[row])) {
                        sleep_ms(10); // Pequena espera para evitar leitura contínua
                    }
                }
            }

            gpio_put(COL_PINS[col], 1); // Desativa a coluna atual (nível alto)
        }

        sleep_ms(50); // Pequena pausa para evitar leitura instável (debounce)
    }
}
// Emiti o sinal luminoso para o código Morse reerente ao ponto.
void ponto()
{
    gpio_put(LED_PIN_RED,true);
    sleep_ms(200);
    gpio_put(LED_PIN_RED,false);
}

// Emiti o sinal luminoso para o código Morse reerente ao traço.
void traco()
{
     gpio_put(LED_PIN_BLUE,true);
     sleep_ms(200);
     gpio_put(LED_PIN_BLUE,false);
}

// Inicializa os buzzers a serem utilizados.
void initialization_buzzers() {
    // Inicializa o pino GPIO para uso geral
    gpio_init(BUZZER_DOT);
    // Configura o pino como saída digital
    gpio_set_dir(BUZZER_DOT, GPIO_OUT);
    // Desliga p pino GPIO configurado como saída digital
    gpio_put(BUZZER_DOT, 0);

    // Refaz o mesmos passos para a outra porta definida para o outro Buzzer
    gpio_init(BUZZER_DASH);
    gpio_set_dir(BUZZER_DASH, GPIO_OUT);
    gpio_put(BUZZER_DASH, 0);
}

// Configuração e PWM para os buzzers
void buzzer_pwm(uint gpio, uint16_t frequency, uint16_t duration_ms) {
    // Configura a pino da gpio pasado como saída de modulação por largura de pulso (PWM).
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    // Mapeia um pino GPIO para uma fatia de PWM.
    uint slice = pwm_gpio_to_slice_num(gpio);

    // Define o período de um sinal PWM em uma determinada fatia (slice).
    pwm_set_wrap(slice, 125000000 / frequency);
    // Configura a modulação por largura de pulso (PWM) em um dos canais de um slice.
    pwm_set_chan_level(slice, PWM_CHAN_A, (125000000 / frequency) / 2);
    // Habilita a geração de um sinal PWM em um determinado slice do controlador.
    pwm_set_enabled(slice, true);

    sleep_ms(duration_ms);

    pwm_set_enabled(slice, false);
    gpio_set_function(gpio, GPIO_FUNC_SIO);
    // Seta a direçao da GPIO como saída
    gpio_set_dir(gpio, GPIO_OUT);
    // Define o estado do pino gpio como baixo (0 V)
    gpio_put(gpio, 0);
}

// Emite a sequência de som em código Morse.
void play_morse_code(const char *morse) {
    // Recebe a strig correspondente ao código morse a ser transformado em som.
    for (size_t i = 0; i < strlen(morse); i++) {
        if (morse[i] == '.') {
            buzzer_pwm(BUZZER_DOT, 5280, 100); // Os pontos: 100ms, increased frequency
        } else if (morse[i] == '-') {
            buzzer_pwm(BUZZER_DASH, 5280, 300); // Traços: 300ms, increased frequency
        }
        sleep_ms(100); // intervalos entre pontos e traços
    }
    sleep_ms(300); // intervalos entre letras
}

//Função para ligar leds de acordo com a tecla pressionada
void liga_leds() {
  while (true) {
    gpio_put(LED_PIN_RED, false);
    gpio_put(LED_PIN_BLUE, false);
    gpio_put(LED_PIN_GREEN, false);
    char value = scan_keypad(); // Ler novo caracter
    if (value == '#'){
        // Se for pressionado o caracter # sai da opção celecionada.
      printf("Saindo...\n");
      break;
    }
    if (value == 'A') {
      printf("tecla pressionada: %c\n", value);
        // Liga o LED vermelho se o botão "A" for pressionado
        gpio_put(LED_PIN_RED, true);
        sleep_ms(300); // Mantém o LED ligado por 300 ms
    } 
    else if (value == 'B') {
        // Liga o LED azul se o botão "B" for pressionado
        printf("tecla pressionada: %c\n", value);
        gpio_put(LED_PIN_BLUE, true);
        sleep_ms(300); // Mantém o LED ligado por 300 ms
    } 
    else if (value == 'C') {
        // Liga o LED verde se o botão "C" for pressionado
        printf("tecla pressionada: %c\n", value);
        gpio_put(LED_PIN_GREEN, true);
        sleep_ms(300); // Mantém o LED ligado por 300 ms
    } 
    else if (value == 'D') {
        // Liga o LED branco se o botão "D" for pressionado
        printf("tecla pressionada: %c\n", value);
        gpio_put(LED_PIN_RED, true);
        gpio_put(LED_PIN_BLUE, true);
        gpio_put(LED_PIN_GREEN, true);
        sleep_ms(300); // Mantém o LED ligado por 300 ms
    } 
    else {
        // Desliga todos os LEDs se nenhuma tecla relevante for pressionada
        gpio_put(LED_PIN_RED, false);
        gpio_put(LED_PIN_BLUE, false);
        gpio_put(LED_PIN_GREEN, false);
    }
    sleep_ms(50); // Delay Debounce
  }
}

// Realiza a leitura do caracter do teclado e conversão em código morse.
void execute_morse_in_buzzers() {
  while (true) {
    char pressed = scan_keypad(); // Ler novo caracter
    if (pressed == '#'){
        // Se for pressionado o caracter # sai da opção celecionada.
      printf("Saindo...\n");
      break;
    }
    if (pressed) {
      if (pressed == '*')
        printf("Key pressed: %c | Não existe código morse para o caracter. \n", pressed);
      else
        printf("Key pressed: %c | ", pressed);

        // detecta qual o código morse para o caracter clicado.
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (KEYPAD[i][j] == pressed && morse_code[i][j] != NULL) {
                    printf("Morse: %s\n", morse_code[i][j]);
                    play_morse_code(morse_code[i][j]);
                }
            }
        }
    }
    sleep_ms(50); // Delay Debounce
  }
}

// Função de emissão de luz para código Morse.
void init_morse_led(const char *morse) {
  // Recebe a strig correspondente ao código morse a ser transformado em som.
  for (size_t i = 0; i < strlen(morse); i++) {
    if (morse[i] == '.') {
        ponto(); // led vermelho
    } else if (morse[i] == '-') {
        traco();// led azul
    }
    sleep_ms(125); 
  }
  sleep_ms(250);
}

// Realiza a leitura do caracter do teclado e conversão em código morse.
void execute_morse_in_leds() {
  while (true) {
    char pressed = scan_keypad(); // Ler novo caracter
    if (pressed == '#'){
        // Se for pressionado o caracter # sai da opção celecionada.
      printf("Saindo...\n");
      break;
    }
    if (pressed) {
      if (pressed == '*')
        printf("Key pressed: %c | Não existe código morse para o caracter. \n", pressed);
      else
        printf("Key pressed: %c | ", pressed);

        // detecta qual o código morse para o caracter clicado.
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (KEYPAD[i][j] == pressed && morse_code[i][j] != NULL) {
                    printf("Morse: %s\n", morse_code[i][j]);
                    init_morse_led(morse_code[i][j]);
                }
            }
        }
    }
    sleep_ms(50); // Delay Debounce
  }
}

// Inicializa os led
void inicializa_leds() {
  // Configura o LED vermelho como saída
  gpio_init(LED_PIN_RED);
  gpio_set_dir(LED_PIN_RED, GPIO_OUT);
  // Configura o LED azul como saída
  gpio_init(LED_PIN_BLUE);
  gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
  // Configura o LED verde como saída
  gpio_init(LED_PIN_GREEN);
  gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
}

// menu principal
void menu () {
    printf("Bem vindo ao Teclado Matricial com Raspberry Pi Pico W\n");
    printf("Escolha uma das opções:\n");
    printf("1. Liga Leds\n");
    printf("2. Notas Musicais em Keyboard\n");
    printf("3. Código Morse luminoso\n");
    printf("4. Código Morse Sonoro\n");
    //printf("3. \n");
    printf("#. Para sair\n");
}

// Menu para acener os leds
void menu_leds () {
    printf("Escolha uma das opções:\n");
    printf("A. Liga Led Vermelho\n");
    printf("B. Liga Led Azul\n");
    printf("C. Liga Led Verde\n");
    printf("D. Liga Led Branco\n");
    printf("#. Para Sair\n");

}

int main()
{

  stdio_init_all();
  // configuração do teclado
  setup_keyboard();
  inicializa_leds();
  initialization_buzzers();
  printf("Digite  *  para entrar no Menu de Aplicações\n");

  while (1)
  {
    // leitura do teclado
    char key = scan_keypad();
    if (key != '\0')
    { // Se alguma tecla foi pressionada
      printf("tecla pressionada: %c\n", key);

      if (key == '*'){
        menu();
        sleep_ms(50);
        while(key != '#') {
          char key = scan_keypad();
          
          if (key == '1') {
            menu_leds ();
            sleep_ms(50);
            liga_leds();
            sleep_ms(50);
            menu();
          }

          if (key == '2') {
            printf("\n");
            sleep_ms(50);
            music_keyboard(); // Chamando a funcionalidade do teclado musical
            sleep_ms(50);
            menu();
          }

          if (key == '3') {
            printf("\n");
            sleep_ms(50);
            execute_morse_in_leds();
            sleep_ms(50);
            menu();
          }

          if (key == '4') {
            printf("\n");
            sleep_ms(50);
            execute_morse_in_buzzers();
            sleep_ms(50);
            menu();
          }

          if (key == '#') {
            printf("saindo...\n");
            break;
          }
          sleep_ms(50);
        }
      }

      if (key != '#'){
        printf("Pressione a tecla * para menu de aplicações.\n");
        sleep_ms(50);
      }
      //printf("tecla pressionada: %c\n", key);
      if (key == '#')
      {
        // Saído do programa
        printf("saindo...\n");
        return 1;
      }
    }
    sleep_ms(50);
  }
  return 0;
}
