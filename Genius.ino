// Código de Funcionamento Genius
// Traduzido e adaptado por Usinainfo
// www.usinainfo.com.br

//Definindo as notas de cada som
#define NOTE_D4  294
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_A5  880
 
int tons[3] = { NOTE_A5, NOTE_A4, NOTE_G4};    // Sortea os sons utilizados
int sequencia[100] = {};                                 // Inicia sequencial de até 100 variáveis
int rodada_atual = 0;                                    // Indica a rodada do jogo
int passo_atual_na_sequencia = 0;                        // Indica a situação atual da sequecia
 
int pinoAudio = 5;                       // Define o pino de áudio
int pinosLeds[3] = { 9, 10, 11 };         // Define os pinos dos LEDs
int pinosBotoes[3] = { 2, 3, 4 };     // Define os pinos dos buttons
 
int botao_pressionado = 0;  // Inicializa botão em 0
int perdeu_o_jogo = false;  // Variável fim de jogo
 
void setup() {
  for (int i = 0; i <= 3; i++) {
    pinMode(pinosLeds[i], OUTPUT);   // Define o pino dos LEDs como saída
  }
 
  for (int i = 0; i <= 3; i++) {
    pinMode(pinosBotoes[i], INPUT);  // Define o pino dos botões como entrada
  }
 
  pinMode(pinoAudio, OUTPUT);        // Define o pino de áudio como saída
  randomSeed(analogRead(0));         // Gera um valor entre 0 e 1023
}
 
void loop() {
    if (perdeu_o_jogo) {            // Se acabar o jogo reinicia todas as variáveis
    int sequencia[100] = {};
    rodada_atual = 0;
    passo_atual_na_sequencia = 0;
    perdeu_o_jogo = false;
  }
 
  if (rodada_atual == 0) {  // Som para inicialização da rodada
    tocarSomDeInicio();
    delay(500);
  }
  
  proximaRodada();        // Inicia a próxima rodada
  reproduzirSequencia();  // Reproduz a sequencia atual
  aguardarJogador();      // Aguarda jogadas
  delay(1000);            // 1 segundo de uma jogada a outra
}
 
void proximaRodada() {  // Sorteia o novo item da rodada
  int numero_sorteado = random(0, 3);
  sequencia[rodada_atual++] = numero_sorteado;
}
 
void reproduzirSequencia() {   //Reproduz a sequencia selecionada
  for (int i = 0; i < rodada_atual; i++) {
    tone(pinoAudio, tons[sequencia[i]]);
    digitalWrite(pinosLeds[sequencia[i]], HIGH);
    delay(500);
    noTone(pinoAudio);
    digitalWrite(pinosLeds[sequencia[i]], LOW);
    delay(100);
  }
  noTone(pinoAudio);
}
 
void aguardarJogador() {  // Aguarda o inicio do jogo
  for (int i = 0; i < rodada_atual; i++) {
    aguardarJogada();
    verificarJogada();
 
    if (perdeu_o_jogo) {
      break;
    }
 
    passo_atual_na_sequencia++;
  }
 
  passo_atual_na_sequencia = 0;  // Redefine a variável
}
 
void aguardarJogada() {
  boolean jogada_efetuada = false;
  while (!jogada_efetuada) {
    for (int i = 0; i <= 3; i++) {
      if (digitalRead(pinosBotoes[i]) == HIGH) {
        botao_pressionado = i; // Indica o botão pressionado
        tone(pinoAudio, tons[i]);
        digitalWrite(pinosLeds[i], HIGH);
        delay(300);
        digitalWrite(pinosLeds[i], LOW);
        noTone(pinoAudio);
 
        jogada_efetuada = true;
      }
    }
    delay(10);
  }
}
 
void verificarJogada() {
  if (sequencia[passo_atual_na_sequencia] != botao_pressionado) {
    for (int i = 0; i <= 3; i++) {  // Fim de jogo
      tone(pinoAudio, tons[i]);
      digitalWrite(pinosLeds[i], HIGH);
      delay(200);
      digitalWrite(pinosLeds[i], LOW);
      noTone(pinoAudio);
    }
 
    tone(pinoAudio, tons[3]);
    for (int i = 0; i <= 3; i++) {
      digitalWrite(pinosLeds[0], HIGH);
      digitalWrite(pinosLeds[1], HIGH);
      digitalWrite(pinosLeds[2], HIGH);
      digitalWrite(pinosLeds[3], HIGH);
      delay(100);
      digitalWrite(pinosLeds[0], LOW);
      digitalWrite(pinosLeds[1], LOW);
      digitalWrite(pinosLeds[2], LOW);
      digitalWrite(pinosLeds[3], LOW);
      delay(100);
    }
    noTone(pinoAudio);
 
    perdeu_o_jogo = true;
  }
}
 
void tocarSomDeInicio() {
  tone(pinoAudio, tons[0]);
  digitalWrite(pinosLeds[0], HIGH);
  digitalWrite(pinosLeds[1], HIGH);
  digitalWrite(pinosLeds[2], HIGH);
  digitalWrite(pinosLeds[3], HIGH);
  delay(500);
  digitalWrite(pinosLeds[0], LOW);
  digitalWrite(pinosLeds[1], LOW);
  digitalWrite(pinosLeds[2], LOW);
  digitalWrite(pinosLeds[3], LOW);
  delay(500);
  noTone(pinoAudio);
}
