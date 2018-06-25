/* PROGRAMA PARA CONTROLE DE MOTOR E SHIELD L293D VIA SERIAL
* AUTOR: FELIPE ROQUE DE ALBUQUERQUE NETO
* CO-AUTOR: RAPHAEL DE MEDEIROS SOUTO MAIOR BALTAR
* CREDITOS: SIMON MONK & WAGNER RAMBO
*/

// --- Mapeamento de Hardware -- SHIFT REGISTER ---
#define   dir_clk      4     //clock do registrador no digital  4
#define   dir_ser      8     //dados do registrador no digital  8
#define   dir_latch   12     //latch do registrador no digital 12
#define   dir_en       7     //enable do registrador no digital 7
#define   pwm2a       11     //pwm motor 1


// --- Protótipo das Funções Auxiliares ---
void sendCommand(unsigned char value);   //Função para enviar o byte para saída do registrador


// --- Configurações Iniciais ---
void setup() 
{
  pinMode(dir_clk, OUTPUT);    //saída para clock
  pinMode(dir_ser, OUTPUT);    //saída para dados
  pinMode(dir_latch, OUTPUT);    //saída para latch
  pinMode(dir_en, OUTPUT);    //saída para enable
  pinMode(pwm2a, OUTPUT);    //saída para pwm motor1
  Serial.begin(9600);
  
 // digitalWrite(dir_en, LOW); /* Seria no caso de eu não quiser fazer o controle do pwm utilizando a serial*/
 // analogWrite(pwm2a, 0xFF);
 // analogWrite(pwm2b, 0xFF);
 // analogWrite(pwm0a, 0xFF);
 // analogWrite(pwm0b, 0xFF);
}

void loop() 
{
if(Serial.available())
  {
    int ciclo = Serial.parseInt(); // ciclo sera manipulado pela comunicação serial
    if(ciclo < 0)
    {
          sendCommand(0b10101100);
          ciclo = ciclo*(-1);
    }
    else
    {
        sendCommand(0b01010011);
    }
    analogWrite(pwm2a, ciclo);
  }
} 

// --- Desenvolvimento das Funções Auxiliares ---
void sendCommand(unsigned char value)
{
  
    boolean verify;                  //bit de controle

    digitalWrite(dir_latch, LOW);    //desliga latch
    digitalWrite(dir_clk,   LOW);    //desabilita o clock
    
    for(unsigned char i=0x0; i<0x08; i++)    //loop finito para enviar os 8 bits
    {
       digitalWrite(dir_clk, LOW);   //clock em low
       
       if(value & (1<<i)) verify = HIGH;
       else verify = LOW;
       
       digitalWrite(dir_ser, verify); //Habilita saída de dados conforme condição acima
       digitalWrite(dir_clk, HIGH);
    
    } //end for
    
    
    digitalWrite(dir_clk, LOW);
    
    digitalWrite(dir_latch, HIGH);
} 
