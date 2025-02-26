# Alarme de Incêndio com Raspberry Pi Pico

## 📌 Descrição do Projeto
Este projeto implementa um **sistema de alarme de incêndio** utilizando a **Raspberry Pi Pico**, um **buzzer**, um **LED vermelho** e dois **botões físicos** para simular a detecção de fumaça e o acionamento manual do alarme. Quando a detecção de fumaça é simulada, o sistema emite uma mensagem via **serial** e, caso o botão de alarme seja pressionado, o sistema **aciona um alerta sonoro e visual**.

## 🛠️ Componentes Utilizados
- **Microcontrolador:** Raspberry Pi Pico
- **LED vermelho:** Indica o estado do alarme
- **Buzzer:** Emite um alerta sonoro ao detectar um incêndio
- **Botão A:** Simula a detecção de fumaça
- **Botão B:** Aciona manualmente o alarme
- **Fios jumper** para conexões
- **Protoboard** para montagem

## ⚙️ Funcionamento
O código principal funciona da seguinte forma:
1. **Inicialização dos componentes**: O LED, o buzzer e os botões são configurados.
2. **Monitoramento dos botões**:
   - Se o **botão A** for pressionado, é exibida uma mensagem informando a detecção de fumaça.
   - Se o **botão B** for pressionado, o **alarme é acionado**.
3. **Alarme de Incêndio**:
   - O **LED vermelho** pisca continuamente.
   - O **buzzer toca uma sirene** com diferentes frequências para alertar sobre o incêndio.
   - O alerta continua por **10 ciclos**, podendo ser interrompido ao resetar a placa.

## 🔌 Ligações
| Componente    | Pino GPIO |
|--------------|----------|
| Botão A      | GPIO 5   |
| Botão B      | GPIO 6   |
| LED Vermelho | GPIO 13  |
| Buzzer       | GPIO 21  |

## 📜 Código Fonte
O código principal está estruturado da seguinte maneira:
- **Funções principais:**
  - `setup()`: Inicializa os componentes.
  - `loop()`: Monitora os botões e aciona os alarmes conforme necessário.
- **Funções auxiliares:**
  - `iniciar_led_red()`, `acionar_led_red()`, `desligar_led_red()` – Controle do LED vermelho.
  - `iniciar_buzzer()`, `tocar_nota()`, `tocar_alarme_incendio()` – Controle do buzzer e sirene.
  - `verificar_botao_A()`, `verificar_botao_B()` – Implementação de **debouncing** para evitar leituras erradas dos botões.

## 📦 Como Executar o Projeto
1. **Montar o circuito** conforme as ligações mencionadas.
2. **Compilar e carregar o código** na Raspberry Pi Pico.
3. **Monitorar a saída serial** para verificar mensagens de alerta.
4. **Pressionar os botões** para testar a detecção de fumaça e o acionamento do alarme.

## 🔧 Melhorias Futuras
- Adicionar um sensor real de fumaça (MQ-2, MQ-135, etc.).
- Implementar conexão Wi-Fi para enviar alertas remotos via Telegram ou e-mail.
- Incluir um display OLED para exibir mensagens de status.

## Utilizando o Wokwi Simulator

### No Site do Wokwi

1. Acesse [Wokwi Simulator](https://wokwi.com/).
2. Crie um novo projeto e selecione a placa **Raspberry Pi Pico**.
3. Importe o código para a área de edição.
4. Adicione os componentes ao circuito e conecte-os aos pinos correspondentes.
5. Inicie a simulação para verificar o funcionamento.

### No VSCode

1. Instale a extensão **Wokwi Simulator**.
2. Abra o repositório no VSCode.
3. Configure os arquivos `diagram.json` e `wokwi.toml` para o projeto.
4. Execute a simulação diretamente no editor.

---

## Configurações para Compilação

### Alterando o Caminho do `pico-sdk`

1. Localize o diretório onde o `pico-sdk` está instalado.
2. No arquivo `CMakeLists.txt`, altere o caminho do `pico-sdk`:

```cmake
set(PICO_SDK_PATH "/caminho/para/o/seu/pico-sdk" CACHE STRING "Pico SDK directory")
```
3. Salve e execute o CMake para compilar o projeto.

---

## Como Contribuir

1. Clone o repositório:

```bash
git clone https://github.com/victorw29/alarmeincendio
```

2. Faça suas alterações e envie um **pull request**.
3. Siga as boas práticas de desenvolvimento e documentação.

---

## Links Úteis

- [Projeto no Wokwi] https://wokwi.com/projects/423437352174661633

- [Vídeo no YouTube] 

---

✉️ **Autor:** Victor Weverthon (Desenvolvedor do projeto)
