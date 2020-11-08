// Bibliotecas

#include <PushButton.h> //Biblioteca para utilizar os push buttons sem o bounce 
#include <Stepper.h> // bilioteca para utilizacao do motor de passo
#include <LiquidCrystal_I2C.h> //biblioteca para utilizar o lcd com o modulo I2C

//------------ Constantes --------------
               
#define e1 8
#define e2 9  //entradas do motor de passo
#define e3 10 
#define e4 11

//----------- Botoes ----------------

#define bt1 7
#define bt2 6  //entradas correspondentes para os push buttons 
#define bt3 5
#define bt4 4
#define bt5 3

// DEFINIÇÕES
#define endereco  0x27 // Endereços comuns: 0x27, 0x3F
#define colunas   16 
#define linhas    2

const int passosPorGiro = 64; // Referente ao modelo

//-----------definicao das entradas do lcd-----------
  
LiquidCrystal_I2C lcd(endereco, colunas, linhas);
//-----------instanciacao de objetos-----------------

PushButton botao1(bt1); PushButton botao2(bt2); PushButton botao3(bt3); PushButton botao4(bt4); PushButton botao5(bt5);

Stepper motorPasso(passosPorGiro,e1,e3,e2,e4);

// Variaveis uteis


short andar_atual = 1, andar_anterior = andar_atual;


void setup() {
  Serial.begin(9600);
  motorPasso.setSpeed(500); // RPM 
  pinMode(LED_BUILTIN, OUTPUT);
  
  lcd.init(); // INICIA A COMUNICAÇÃO COM O DISPLAY
  lcd.backlight(); // LIGA A ILUMINAÇÃO DO DISPLAY
  lcd.clear(); // LIMPA O DISPLAY
  lcd.print("primeiro andar");
  
}

void loop() {

// Monitorando leitura

  botao1.button_loop();  botao2.button_loop(); botao3.button_loop();  botao4.button_loop(); botao5.button_loop();

  lcd.setCursor(0,0);
  
//----------Acionando andares----------

  if(botao1.pressed()){
    lcd.clear(); // LIMPA O DISPLAY
    andar_atual = 1;
    if(andar_atual != andar_anterior){
      int sobeDesce = (andar_atual - andar_anterior) >= 0 ? 1 : -1;
        operacoesComMotor(abs(andar_atual - andar_anterior),sobeDesce);
        andar_anterior = andar_atual;
        lcd.clear(); // LIMPA O DISPLAY
        lcd.setCursor(0, 0);
        lcd.print("primeiro andar");
    }
  }
  
  if(botao2.pressed()){
    lcd.clear(); // LIMPA O DISPLAY
    andar_atual = 2;
    if(andar_atual != andar_anterior){
      int sobeDesce = (andar_atual - andar_anterior) >= 0 ? 1 : -1;
      
      operacoesComMotor(abs(andar_atual - andar_anterior),sobeDesce);
      andar_anterior = andar_atual;
      lcd.clear(); // LIMPA O DISPLAY
      lcd.setCursor(0, 0);
      lcd.print("segundo andar");
      }
  }
  
  if(botao3.pressed()){
    lcd.clear(); // LIMPA O DISPLAY
    andar_atual = 3;
    if(andar_atual != andar_anterior){
      int sobeDesce = (andar_atual - andar_anterior) >= 0 ? 1 : -1;
      operacoesComMotor(abs(andar_atual - andar_anterior),sobeDesce);
      andar_anterior = andar_atual;
      lcd.clear(); // LIMPA O DISPLAY
      lcd.setCursor(0, 0);
      lcd.print("terceiro andar");
    }
  }
  
  if(botao4.pressed()){
    lcd.clear(); // LIMPA O DISPLAY
    andar_atual = 4;
    if(andar_atual != andar_anterior){
      int sobeDesce = (andar_atual - andar_anterior) >= 0 ? 1 : -1;
      if(sobeDesce > 0){
        lcd.setCursor(7, 0);
        lcd.write(0);

      }
      if(sobeDesce < 0){
        lcd.setCursor(7, 0);
        lcd.write(1);
      }
      operacoesComMotor(abs(andar_atual - andar_anterior),sobeDesce);
      andar_anterior = andar_atual;
      lcd.clear(); // LIMPA O DISPLAY
      lcd.setCursor(0, 0);
      lcd.print("quarto andar");
      }
  }
  
  if(botao5.pressed()){
    lcd.clear(); // LIMPA O DISPLAY
    andar_atual = 5;
    if(andar_atual != andar_anterior){
      int sobeDesce = (andar_atual - andar_anterior) >= 0 ? 1 : -1;
      operacoesComMotor(abs(andar_atual - andar_anterior),sobeDesce);
      andar_anterior = andar_atual;
      lcd.clear(); // LIMPA O DISPLAY
      lcd.setCursor(0, 0);
      lcd.print("quinto andar");
      }
  }


}


void operacoesComMotor(int voltas,int sentido){ // Funcao para girar o motor para direita ou esquerda baseado no andar que es encontra
  if(voltas != 0){ 
    for(int i = 0; i < voltas*(passosPorGiro/2); i++){
      motorPasso.step(sentido*passosPorGiro);
    }
  }
}
