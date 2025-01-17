
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