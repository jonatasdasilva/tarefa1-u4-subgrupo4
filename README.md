
---

## **🛠 Projeto: Leitura de Teclado Matricial com Raspberry Pi Pico**  

### 📌 **Descrição**  
Este projeto implementa a leitura de um **teclado matricial 4x4** utilizando o **Raspberry Pi Pico W**. O código implementa uma variedade de aplicações, que conecta o periférico principal (teclado matricial) à funcionalidades específicas para cada uma das aplicações. A função principal do teclado é identificar a tecla pressionada, executar uma ação desejada e exibe a informação no **monitor serial**.Juntamente com o código, foi produzido um vídeo demonstrando o processo e o resultado da aplicação.

Link para o vídeo: [[Click aqui](https://youtu.be/bNFVArIUhn0)].  

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

A função liga_leds() é responsável por controlar LEDs em um sistema baseado em GPIO (General Purpose Input/Output), reagindo a diferentes entradas de um teclado matricial. Ela liga e desliga LEDs específicos ou executa uma sequência de transições de cores conforme os botões pressionados.

---

##### 🔄 Comportamento Principal

A função fica em um loop contínuo, aguardando a entrada de uma tecla através da função scan_keypad(). Dependendo da tecla pressionada, ela ativa LEDs específicos e/ou realiza transições de cores.

##### ⚙ Funcionamento:

LEDs Desligados Inicialmente: Todos os LEDs (vermelho, azul e verde) são desligados no início do loop.

Entrada de Teclado: A função aguarda o pressionamento de teclas, executando ações específicas para cada tecla pressionada.

##### 🎯 Comandos de Teclas:

- Tecla #: Sai da função e encerra o loop. `Exemplo: Saindo... 👋`
- Tecla A: Liga o LED vermelho por 300 ms. 🔴
- Tecla B: Liga o LED azul por 300 ms. 🔵
- Tecla C: Liga o LED verde por 300 ms. 🟢
- Tecla D: Liga todos os LEDs (vermelho, azul e verde) por 300 ms. ⚪
- Tecla 1: Liga o LED ciano (azul + verde) por 300 ms. 💠
- Tecla 2: Liga o LED magenta (vermelho + azul) por 300 ms. 🟣
- Tecla 3:  Liga o LED amarelo (vermelho + verde) por 300 ms. 🟡
- Tecla 0: Executa uma sequência de transições de cores entre vermelho, amarelo, - verde, ciano, azul e magenta, criando um efeito visual por 100 ms para cada cor. 🌈
- Qualquer outra tecla: Desliga todos os LEDs. ❌

---

##### ⏱ Delays:

Após cada ação, há um pequeno atraso de 50 ms para evitar o "debounce" do teclado, garantindo que os botões sejam lidos de forma precisa.

##### 🖥 Função Dependente:

A função utiliza gpio_put() para controlar o estado dos LEDs.
A função scan_keypad() é usada para ler a entrada do teclado matricial.


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

---

#### 2. 🚨 Conversor de Código Morse em sinal luminoso 


#### 3. 🔉 Conversor de Código Morse em som

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

#### 4. 🎹 Transforma o teclado em um Piano de Dó a Si

##### 📌 Descrição  
Este projeto implementa a leitura de um **teclado matricial 4x4** utilizando o **Raspberry Pi Pico** e reproduz sons de notas musicais em um **buzzer** conforme a tecla pressionada. Cada tecla está mapeada para uma frequência específica, correspondente a uma nota musical.  

---

##### 🏗 Esquema de Conexão  

| **Linha (ROW)** | **Pino GPIO** | **Coluna (COL)** | **Pino GPIO** |
|----------------|-------------|----------------|-------------|
| R1            | GP9         | C1            | GP5         |
| R2            | GP8         | C2            | GP4         |
| R3            | GP7         | C3            | GP3         |
| R4            | GP6         | C4            | GP2         |
| **Buzzer**    | **GP10**    |                |             |

> **Obs.:** O teclado utiliza **pull-up interno** para as linhas.  

---

##### 📜 Código Principal  

O projeto possui as seguintes seções principais:

###### 🏗 1. Configuração do teclado matricial  
- Define os **GPIOs das linhas (ROWS)** como **entradas com pull-up interno**.  
- Define os **GPIOs das colunas (COLS)** como **saídas** inicialmente em nível alto.

###### 🎵 2. Função `play_tone()`  
Gera o som correspondente a uma frequência no buzzer:  
- Converte a frequência da nota em um período (em microsegundos).  
- Alterna o estado do pino do buzzer entre **alto** e **baixo** para criar um sinal sonoro (PWM).  
- A duração do som pode ser configurada em milissegundos.

###### 🔄 3. Loop Principal (`main()`)  
- Ativa uma coluna do teclado por vez.  
- Verifica as linhas ativas para identificar a tecla pressionada.  
- Toca a nota correspondente à tecla por meio do buzzer.  
- Aguarda a liberação da tecla antes de continuar (evita múltiplas leituras para a mesma tecla).

---

##### 🎯 Exemplo de Funcionamento  

Ao pressionar uma tecla no teclado:
1. O buzzer reproduz o som correspondente à nota musical.
2. Cada tecla do teclado está mapeada para as notas musicais:
   - **1 → Dó**
   - **2 → Ré**
   - **3 → Mi**
   - **4 → Fá**
   - **5 → Sol**
   - **6 → Lá**
   - **7 → Si**
---

#### 5. 🎶 Melodia Game of Thrones com Raspberry Pi Pico

##### 📌 **Descrição**  
Este projeto implementa a reprodução de uma melodia baseada na música de **Game of Thrones** utilizando o **Raspberry Pi Pico** e dois **buzzers**. Quando executado, o código alterna entre os buzzers para tocar as notas musicais da melodia. Cada nota é reproduzida por um buzzer diferente, e o tempo de duração de cada nota é controlado, criando a sequência musical característica da música de Game of Thrones.

---

##### 🏗 **Esquema de Conexão**  

| **Buzzer**  | **Pino GPIO** |
|-------------|---------------|
| Buzzer 1    | GP10          |
| Buzzer 2    | GP22          |

> **Obs.:** O projeto utiliza **dois buzzers** conectados aos pinos **GP10** e **GP22** para alternar entre os sons.

---

##### 📜 **Código Principal**  
O projeto possui a função principal `play_song()`, que alterna entre dois buzzers para reproduzir as notas da melodia de Game of Thrones. O código está estruturado da seguinte forma:

###### 🔊 **1. Função `tocar_buzzer_frequencia()`**  
Essa função é responsável por gerar uma frequência sonora em um buzzer específico. Ela calcula o tempo de ciclo necessário para produzir a frequência e ativa/desativa o buzzer alternadamente para produzir o som desejado.

###### 🎶 **2. Função `tocar_melodia()`**  
Essa função percorre uma sequência de notas e suas respectivas durações, alternando entre os dois buzzers (definidos pelos pinos `pin1` e `pin2`). Cada nota é tocada por um período específico, e após a execução de cada nota, há uma pausa de 50 ms para evitar sobreposição de sons.

###### 🎧 **3. Função `play_song()`**  
Esta é a função principal que chama a função `tocar_melodia()` com os parâmetros apropriados (pins dos buzzers, sequência de notas e durações) e aguarda um pequeno intervalo entre as execuções.

---

##### 🎯 **Exemplo de Funcionamento**  
Ao rodar o código, a melodia de Game of Thrones será tocada alternando entre os dois buzzers. As notas são reproduzidas de acordo com a sequência e a duração definidas no código.

---

##### ⚙ **Funcionamento**:

   - **Alternância de Buzzers**: A melodia é tocada alternando entre os dois buzzers conectados aos pinos **GP10** e **GP22**.
   - **Notas e Durações**: As notas são definidas pela frequência e duração em arrays, e cada nota é tocada com base nesses parâmetros.
   - **Pausa entre Notas**: Após cada nota, há uma pausa de 50 ms, garantindo que os sons não se sobreponham.

---

##### 🖥 **Função Dependente**:
A função `gpio_put()` é utilizada para ativar e desativar os buzzers, e `sleep_ms()` é usada para adicionar pausas entre as notas.

---

##### 🎯 Exemplo de Funcionamento  

Menu de Música:
   Escolha uma das opções:
   1. Dó
   2. Ré
   3. Mi
   4. Fá
   5. Sol
   6. Lá
   7. Sí
   **0. Tocar música**
