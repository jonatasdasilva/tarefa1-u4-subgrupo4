
---

## **🛠 Projeto: Leitura de Teclado Matricial com Raspberry Pi Pico**  

### 📌 **Descrição**  
Este projeto implementa a leitura de um **teclado matricial 4x4** utilizando o **Raspberry Pi Pico W**. O código implementa uma variedade de aplicações, que conecta o periférico principal (teclado matricial) à funcionalidades específicas para cada uma das aplicações. A função principal do teclado é identificar a tecla pressionada, executar uma ação desejada e exibe a informação no **monitor serial**.  

---

### 📋 **Dependências**  
Antes de compilar e rodar o projeto, certifique-se de que possui:  

- 🔧 **Raspberry Pi Pico SDK** `configurado corretamente`  
- ✔️ **CMake**  `instalado`
- ✔️ **Compilador ARM GCC**  `instalado`
- ✔️ **Extensão Wokwi Simulator**  `instalado`
- ➕ **Extensão Raspberry Pi Pico para VSCode** `(opcional)`

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

### 📂 Aplicações

#### 1. 💡 Função liga_leds(key)

A função liga_leds controla o estado de LEDs conectados à Raspberry Pi Pico com base na tecla pressionada no teclado matricial. Cada tecla específica (A, B, C, ou D) acende um LED correspondente ou combinações de LEDs.

---

##### 🗒 Descrição

A função recebe como argumento a tecla pressionada (key) e executa as seguintes ações:

'A': Liga o LED vermelho. 🔴

'B': Liga o LED azul. 🔵

'C': Liga o LED verde. 🟢

'D': Liga todos os LEDs (cria luz branca combinando vermelho, azul e verde). ⚪️

Qualquer outra tecla desliga todos os LEDs.

Após acender o LED correspondente, o LED permanece ligado por 300 milissegundos antes de ser desligado.

---

##### 🎯 Parâmetros

key (char): Caracter correspondente à tecla pressionada no teclado matricial. Deve ser uma das seguintes opções:

'A': Liga o LED vermelho.

'B': Liga o LED azul.

'C': Liga o LED verde.

'D': Liga todos os LEDs (luz branca).

---

##### ⚒️ Fluxo de Execução

1. Verifica o valor do parâmetro key.


2. Liga o LED correspondente ao valor de key


3. Caso a tecla pressionada não corresponda a nenhuma das opções acima, todos os LEDs são desligados.


4. O LED permanece ligado por 300 milissegundos antes de ser desligado.

---

##### 💻 Exemplo de Uso

char tecla = 'A'; // Simulação de tecla pressionada
liga_leds(tecla); // Liga o LED vermelho por 300 ms

---

##### 📋 Notas

A função usa sleep_ms(300) para manter o LED aceso por 300 milissegundos.

Certifique-se de que os LEDs estão conectados corretamente aos GPIOs especificados:

LED vermelho: GPIO 13.

LED azul: GPIO 12.

LED verde: GPIO 11.

---

##### 👨‍💻 Dependências

Esta função depende de:

Configuração inicial dos GPIOs, realizada antes de chamar a função. Certifique-se de que os GPIOs estão configurados como saída:

gpio_init(LED_PIN_RED);
gpio_set_dir(LED_PIN_RED, GPIO_OUT);
gpio_put(LED_PIN_RED, false);


#### 2. 

#### 3. 

#### 4. 🚨 Conversor de Código Morse em sinal luminoso 

#### 5. 🔉 Conversor de Código Morse em som

##### 🎯 Objetivo

A aplicação **converte** as teclas pressionadas em um teclado 4x4 em seus respectivos **códigos Morse**. Ao detectar uma tecla, a aplicação emite um som correspondente aos sinais longos (traços) e curtos (pontos) do código Morse daquela letra ou número. A frequência e a duração dos sinais sonoros são configurados pelo seu padrão para simular a transmissão tradicional de código Morse.

##### ⚡ Conexão no Raspberry Pi Pico W

Para esta aplicação foi utilizado: 2 Buzzers e 1 Keypad. Além do Keypad já mencionado anteriormente, os buzzers são configurados da forma abaixo.

| **Bazzer**  | **Pino GPIO** |
|-------------|---------------|
| bz1:1       | GP10          |
| bz1:2       | GND4          |
| bz2:1       | GP22          |
| bz2:2       | GND6          |

##### 📄 Funcionamento

A aplicação funciona da seguinte forma: o microcontrolador lê a matriz de teclas do teclado 4x4 e identifica a tecla pressionada. Em seguida, a aplicação consulta uma tabela de correspondência para encontrar o código Morse associado àquela tecla. Por fim, um sinal sonoro é gerado, com pulsos de curta e longa duração representando os pontos e traços do código Morse, respectivamente.

Para reproduzir os sons do código Morse, foram configurados pulsos sonoros de diferentes durações:

- Ponto: Um pulso curto com duração de 100ms.
- Traço: Um pulso longo com duração de 300ms.
  
Esses pulsos são gerados por um buzzer, que é acionado com uma frequência de 5280Hz. A combinação de pontos e traços, com as respectivas pausas de 100ms entre eles, forma os caracteres do código Morse.

###### 📑 Detalhamento

A aplicação inicia-se configurando os buzzers através da função `initialization_buzzers()`.

Após a configuração, o método `execute_morse_in_buzzers()` entra em um loop, aguardando a entrada do usuário. Ao detectar uma tecla pressionada, a função consulta uma **tabela de correspondência** (`morse_code`) para encontrar o **código Morse** associado à tecla.

Em seguida, o código Morse é exibido na tela e a função `play_morse_code()` é chamada para gerar os sinais sonoros correspondentes aos pontos e traços do código. 

A função `play_morse_code()` utiliza a função `buzzer_pwm()` para controlar a *frequência** e a **duração** dos pulsos sonoros emitidos pelos **buzzers**, reproduzindo assim o **som do código Morse**.

##### 📖 Exemplos

Ao ser pressionado as teclas: 1, 2, 3 e A. A saída abaixo é gerada na tela e o respectivo pulso sonoro emitido.

```
Morse Code Keyboard Ready

Key pressed: 1 | Morse: .----
Key pressed: 2 | Morse: ..---
Key pressed: 3 | Morse: ...--
Key pressed: A | Morse: .-
```

##### 📌 Conclusão

A aplicação implementa um conversor de teclado para código Morse. Onde ao detectar uma tecla pressionada no **Keypad** e gera **pulsos sonoros** correspondentes aos pontos e traços em **Código Morse**.  Esses sinais são então amplificados por um buzzer para produzir o som característico do código Morse.

Assim, mesmo de forma limitada, é possível enviar uma mensagem códificada, a qual pode ser interpretada pelo receptor.

---