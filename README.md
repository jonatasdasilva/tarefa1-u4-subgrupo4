
---

## **🛠 Projeto: Leitura de Teclado Matricial com Raspberry Pi Pico**  

### 📌 **Descrição**  
Este projeto implementa a leitura de um **teclado matricial 4x4** utilizando o **Raspberry Pi Pico**. O código identifica a tecla pressionada e exibe a informação no **monitor serial**.  

---

### 📋 **Dependências**  
Antes de compilar e rodar o projeto, certifique-se de que possui:  

- **Raspberry Pi Pico SDK** configurado corretamente  
- **CMake** instalado  
- **Compilador ARM GCC** instalado  
- **Extensão Raspberry Pi Pico para VSCode** (opcional)  

---

### 🏗 **Esquema de Conexão**  

| **Linha (ROW)** | **Pino GPIO** | **Coluna (COL)** | **Pino GPIO** |
|----------------|-------------|----------------|-------------|
| R1            | GP2         | C1            | GP20        |
| R2            | GP3         | C2            | GP19        |
| R3            | GP8         | C3            | GP18        |
| R4            | GP9         | C4            | GP17        |

> **Obs.:** O teclado utiliza **pull-up interno** para as colunas.  

---

---

### 📜 **Código Principal**
O projeto possui três funções principais:

#### 🏗 **1. `setup_keyboard()`**  
Configura os **GPIOs** do teclado matricial:
- Define as **linhas (ROWS)** como **saídas**.
- Define as **colunas (COLS)** como **entradas com pull-up interno**.

#### 🔍 **2. `scan_keypad()`**  
Lê o teclado e **retorna a tecla pressionada**.  

#### 🔄 **3. `main()`**  
- Inicializa o **monitor serial**.  
- Configura o teclado com `setup_keyboard()`.  
- Entra em um **loop infinito** para detectar teclas pressionadas.  

---

### 🎯 **Exemplo de Saída no Monitor Serial**
Ao pressionar uma tecla no hardware ou no simulador Wokwi, o monitor serial exibirá:
```
tecla pressionada: 5
tecla pressionada: B
tecla pressionada: #
```

---


###Função liga_leds(key) 💡

A função liga_leds controla o estado de LEDs conectados à Raspberry Pi Pico com base na tecla pressionada no teclado matricial. Cada tecla específica (A, B, C, ou D) acende um LED correspondente ou combinações de LEDs.


---

Descrição 🗒

A função recebe como argumento a tecla pressionada (key) e executa as seguintes ações:

'A': Liga o LED vermelho. 🔴

'B': Liga o LED azul. 🔵

'C': Liga o LED verde. 🟢

'D': Liga todos os LEDs (cria luz branca combinando vermelho, azul e verde). ⚪️

Qualquer outra tecla desliga todos os LEDs.


Após acender o LED correspondente, o LED permanece ligado por 300 milissegundos antes de ser desligado.


---

Parâmetros 🎯

key (char): Caracter correspondente à tecla pressionada no teclado matricial. Deve ser uma das seguintes opções:

'A': Liga o LED vermelho.

'B': Liga o LED azul.

'C': Liga o LED verde.

'D': Liga todos os LEDs (luz branca).




---

Fluxo de Execução ⚒️

1. Verifica o valor do parâmetro key.


2. Liga o LED correspondente ao valor de key


3. Caso a tecla pressionada não corresponda a nenhuma das opções acima, todos os LEDs são desligados.


4. O LED permanece ligado por 300 milissegundos antes de ser desligado.



---

Exemplo de Uso 💻

char tecla = 'A'; // Simulação de tecla pressionada
liga_leds(tecla); // Liga o LED vermelho por 300 ms


---

Notas 📋

A função usa sleep_ms(300) para manter o LED aceso por 300 milissegundos.

Certifique-se de que os LEDs estão conectados corretamente aos GPIOs especificados:

LED vermelho: GPIO 13.

LED azul: GPIO 12.

LED verde: GPIO 11.


---

Dependências 👨‍💻

Esta função depende de:

Configuração inicial dos GPIOs, realizada antes de chamar a função. Certifique-se de que os GPIOs estão configurados como saída:

gpio_init(LED_PIN_RED);
gpio_set_dir(LED_PIN_RED, GPIO_OUT);
gpio_put(LED_PIN_RED, false);



---