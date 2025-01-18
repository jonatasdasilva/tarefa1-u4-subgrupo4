# 🛠 Projeto: Teclado Matricial 4x4 para Notas Musicais com Raspberry Pi Pico

## 📌 Descrição  
Este projeto implementa a leitura de um **teclado matricial 4x4** utilizando o **Raspberry Pi Pico** e reproduz sons de notas musicais em um **buzzer** conforme a tecla pressionada. Cada tecla está mapeada para uma frequência específica, correspondente a uma nota musical.  

---

## 📋 Dependências  
Antes de compilar e rodar o projeto, certifique-se de que possui:  

- **Raspberry Pi Pico SDK** configurado corretamente  
- **CMake** instalado  
- **Compilador ARM GCC** instalado  
- **Extensão Raspberry Pi Pico para VSCode** (opcional)  

---

## 🏗 Esquema de Conexão  

| **Linha (ROW)** | **Pino GPIO** | **Coluna (COL)** | **Pino GPIO** |
|----------------|-------------|----------------|-------------|
| R1            | GP9         | C1            | GP5         |
| R2            | GP8         | C2            | GP4         |
| R3            | GP7         | C3            | GP3         |
| R4            | GP6         | C4            | GP2         |
| **Buzzer**    | **GP10**    |                |             |

> **Obs.:** O teclado utiliza **pull-up interno** para as linhas.  

---

## 📜 Código Principal  

O projeto possui as seguintes seções principais:

### 🏗 1. Configuração do teclado matricial  
- Define os **GPIOs das linhas (ROWS)** como **entradas com pull-up interno**.  
- Define os **GPIOs das colunas (COLS)** como **saídas** inicialmente em nível alto.

### 🎵 2. Função `play_tone()`  
Gera o som correspondente a uma frequência no buzzer:  
- Converte a frequência da nota em um período (em microsegundos).  
- Alterna o estado do pino do buzzer entre **alto** e **baixo** para criar um sinal sonoro (PWM).  
- A duração do som pode ser configurada em milissegundos.

### 🔄 3. Loop Principal (`main()`)  
- Ativa uma coluna do teclado por vez.  
- Verifica as linhas ativas para identificar a tecla pressionada.  
- Toca a nota correspondente à tecla por meio do buzzer.  
- Aguarda a liberação da tecla antes de continuar (evita múltiplas leituras para a mesma tecla).

---

## 🎯 Exemplo de Funcionamento  

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

