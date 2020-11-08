// Bibliotecas

#include <PushButton.h>
#include <Stepper.h>


//------------ Constantes --------------

#define e1 8
#define e2 9
#define e3 10 
#define e4 11

//----------- Botoes ----------------

#define bt1 7
#define bt2 6
#define bt3 5
#define bt4 4
#define bt5 3

const int passosPorGiro = 64; // Referente ao modelo


//-----------instanciacao de objetos-----------------

PushButton botao1(bt1);PushButton botao2(bt2);PushButton botao3(bt3);
PushButton botao4(bt4); PushButton botao5(bt5);

Stepper motorPasso(passosPorGiro,e1,e3,e2,e4);

// Variaveis uteis


short andar_atual = 1;


void setup() {
  Serial.begin(9600);
  motorPasso.setSpeed(500); // RPM 
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

// Monitorando leitura

  botao1.button_loop();  botao2.button_loop(); botao3.button_loop();  botao4.button_loop(); botao5.button_loop();
  
  

// Controla andares

  if(botao1.pressed()){
    int sobeDesece = (1 - andar_atual) >= 0 ? 1 : -1;
    operacoesComMotor(abs(1 - andar_atual),sobeDesece);
    andar_atual = 1;
    
  }else if(botao2.pressed()){
    int sobeDesece = (2 - andar_atual) >= 0 ? 1 : -1;
    operacoesComMotor(abs(2 - andar_atual),sobeDesece);
    andar_atual = 2;
    
  }else if(botao3.pressed()){
    int sobeDesece = (3 - andar_atual) >= 0 ? 1 : -1;
    operacoesComMotor(abs(3 - andar_atual),sobeDesece);
    andar_atual = 3;
    
  }else if(botao4.pressed()){
    int sobeDesece = (4 - andar_atual) >= 0 ? 1 : -1;
    operacoesComMotor(abs(4 - andar_atual),sobeDesece);
    andar_atual = 4;
    
  }else if(botao5.pressed()){
    int sobeDesece = (4 - andar_atual) >= 0 ? 1 : -1;
    operacoesComMotor(abs(4 - andar_atual),sobeDesece);
    andar_atual = 5;
  }
   

  Serial.println(andar_atual);
  
}

void operacoesComMotor(int voltas,int sentido){

  for(int i = 0; i < voltas*(passosPorGiro/2); i++){
    motorPasso.step(sentido*passosPorGiro);
    
  }
  
}
