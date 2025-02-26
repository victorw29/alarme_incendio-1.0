#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"


// Definição dos pinos
#define button_a 5
#define button_b 6
#define led_red 13
#define buzzer 21

// Declaração das funções
void iniciar_led_red(void); // Função para inicializar o led vermelho
void desligar_led_red(void); // Função para desligar o led vermelho
void acionar_led_red(void);   // Função para acionar o led vermelho
void iniciar_buzzer(void);     // Função para inicializar o buzzer
void tocar_alarme_incendio(void); // Função para tocar o alarme de incêndio
void verificar_botao_A(void);     // Função de debouncing do botão A
void verificar_botao_B(void);     // Função de debouncing do botão B

// Sequência de notas da sirene
#define NOTE_C4 262
#define NOTE_D4 294
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_G4 392
#define NOTE_E5 659

int melody[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_E5};
int noteDuration = 300; // Duração de cada nota (ms)

// Variáveis para debouncing dos botões
volatile bool botao_pressionado_A = false;
volatile bool botao_pressionado_B = false;

// Funções para controle do led
void iniciar_led_red(void) {
  gpio_init(led_red);
  gpio_set_dir(led_red, GPIO_OUT);
  gpio_put(led_red, false); // Inicializa o led desligado
}

void acionar_led_red(void) {
  gpio_put(led_red, true); // Liga o led
}

void desligar_led_red(void) {
  gpio_put(led_red, false); // Desliga o led
}

// Funções para controle do Buzzer
void iniciar_buzzer(void) {
  gpio_init(buzzer);
  gpio_set_dir(buzzer, GPIO_OUT);
  gpio_put(buzzer, false); // Inicializa o buzzer desligado
}

void tocar_nota(int frequencia, int duracao_ms) {
  int tempo = 1000000 / frequencia; // Cálculo do tempo para cada ciclo
  for (int i = 0; i < (duracao_ms * 1000) / tempo; i++) {
    gpio_put(buzzer, 1);
    sleep_us(tempo / 2);
    gpio_put(buzzer, 0);
    sleep_us(tempo / 2);
  }
}

void tocar_alarme_incendio(void) {
  // Define a melodia da sirene e a duração de cada nota
  int melody[] = {440, 659, 440, 659, 440, 659, 440, 659}; // A4, E5, A4, E5, A4, E5, A4, E5  
  int noteDuration = 500; // Duração da nota em milissegundos

  for (int i = 0; i < 10; i++) {
    desligar_led_red();
    botao_pressionado_B = false; // Reseta o estado do botão B
    acionar_led_red(); // Aciona o led red (Sirene)

    // Toca a melodia da sirene
    for (int j = 0; j < sizeof(melody) / sizeof(melody[0]); j++) {
      // Toca sirene de emergência
      tocar_nota(melody[j], noteDuration); // Toca a nota com a duração definida
      sleep_ms(50); // Intervalo de 0,05 segundos entre as notas
    }

    sleep_ms(500); // Mantém o buzzer e o led ligados por 0,5 segundos
    gpio_put(buzzer, 0); // Desliga o buzzer
    // Não desligue o LED aqui, o LED deve permanecer ligado
    sleep_ms(500); // Intervalo de 0,5 segundos entre as execuções
  }
}

// Funções para debouncing dos botões
void verificar_botao_A(void) {
  static uint32_t ultima_leitura_A = 0;
  uint32_t leitura_atual_A = gpio_get(button_a);
  if (leitura_atual_A == 0 && (time_us_32() - ultima_leitura_A) > 100000) {
    botao_pressionado_A = true;
    ultima_leitura_A = time_us_32();
  }
}

void verificar_botao_B(void) {
  static uint32_t ultima_leitura_B = 0;
  uint32_t leitura_atual_B = gpio_get(button_b);
  if (leitura_atual_B == 0 && (time_us_32() - ultima_leitura_B) > 100000) {
    botao_pressionado_B = true;
    ultima_leitura_B = time_us_32();
  }
}

// Função de inicialização
void setup(void) {
  gpio_init(button_a);
  gpio_set_dir(button_a, GPIO_IN);
  gpio_pull_up(button_a);

  gpio_init(button_b);
  gpio_set_dir(button_b, GPIO_IN);
  gpio_pull_up(button_b);

  iniciar_led_red();  // Inicia o Led vermelho
  iniciar_buzzer();  // Inicia o Buzzer
  stdio_init_all(); // Inicia a interface serial para depuração

  printf("Setup completo, iniciando execução!\n");
}

// Função principal
void loop(void) {
  verificar_botao_A();
  verificar_botao_B();

  if (botao_pressionado_A) {
    printf("DETECÇÃO DE FUMAÇA!!\n");
    botao_pressionado_A = false;
  }

  if (botao_pressionado_B) {
    printf("ACIONANDO ALARME DE INCÊNDIO!!");
    tocar_alarme_incendio(); // Chama a função para tocar o alarme de incêndio
    botao_pressionado_B = false;
  }

  sleep_ms(1000);
}

int main(void) {
  setup();
  while(1) {
    loop();
  }
  return 0;
}
