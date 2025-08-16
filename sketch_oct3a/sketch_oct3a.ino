int pinEntrada1 = 4; //control signal
int pinEntrada2 = 5;  //
int pinEntrada3 = 12; //control signal
int pinEntrada4 = 13;  //

int pinEntrada5 = 14; //data signal
int pinEntrada6 = 2;  //data signal
int pinEntrada7 = 0; //careful
int pinEntrada8 = 15;  //careful
int pinEntrada9 = 16; //

uint32_t mascaraPin1;
uint32_t mascaraPin2;//control signal
uint32_t mascaraPin3;
uint32_t mascaraPin4;

uint32_t mascaraPin5;
uint32_t mascaraPin6;
uint32_t mascaraPin7;//data signal
uint32_t mascaraPin8;
uint32_t mascaraPin9;


bool estadoGPIO1 = false;
bool estadoGPIO2 = false;
bool estadoGPIO3 = false;
bool estadoGPIO4 = false;

bool estadoGPIO5 = false;
bool estadoGPIO6 = false;
bool estadoGPIO7 = false;
bool estadoGPIO8 = false;
bool estadoGPIO9 = false;



void setup() {
  // put your setup code here, to run once:
      Serial.begin(31250);
           // pinMode(sect2, INPUT);
      // pinMode(data1, INPUT);
      // pinMode(data2, INPUT);
      mascaraPin1 = (1 << pinEntrada1);
      pinMode(pinEntrada1, INPUT);
      mascaraPin2 = (1 << pinEntrada2);
      pinMode(pinEntrada2, INPUT);
      mascaraPin3 = (1 << pinEntrada3);
      pinMode(pinEntrada3, INPUT);
      mascaraPin4 = (1 << pinEntrada4);
      pinMode(pinEntrada4, INPUT);  
        
        
      mascaraPin5 = (1 << pinEntrada5);
      pinMode(pinEntrada5, INPUT);
      mascaraPin6 = (1 << pinEntrada6);
      pinMode(pinEntrada6, INPUT);    
      mascaraPin7 = (1 << pinEntrada7);
      pinMode(pinEntrada7, INPUT);
      mascaraPin8 = (1 << pinEntrada8);
      pinMode(pinEntrada8, INPUT);
      mascaraPin9 = (1 << pinEntrada9);
      pinMode(pinEntrada9, INPUT);
    
    }
void loop() {

  estadoGPIO1 = GPIO_REG_READ(GPIO_IN_ADDRESS) & mascaraPin1;
  estadoGPIO2 = GPIO_REG_READ(GPIO_IN_ADDRESS) & mascaraPin2;
  estadoGPIO3 = GPIO_REG_READ(GPIO_IN_ADDRESS) & mascaraPin3;
  estadoGPIO4 = GPIO_REG_READ(GPIO_IN_ADDRESS) & mascaraPin4;

  estadoGPIO5 = GPIO_REG_READ(GPIO_IN_ADDRESS) & mascaraPin5;
  estadoGPIO6 = GPIO_REG_READ(GPIO_IN_ADDRESS) & mascaraPin6;
  estadoGPIO7 = GPIO_REG_READ(GPIO_IN_ADDRESS) & mascaraPin7;
  estadoGPIO8 = GPIO_REG_READ(GPIO_IN_ADDRESS) & mascaraPin8;
  estadoGPIO9 = GPIO_REG_READ(GPIO_IN_ADDRESS) & mascaraPin9;
  




  if((estadoGPIO1 == false ) && (estadoGPIO5 == false )){
     Serial.println("key 1");
      
  }
  if((estadoGPIO1 == false ) && (estadoGPIO6 == false )){
     Serial.println("key 2");

  }
 
  if((estadoGPIO1 == false ) && (estadoGPIO7 == false )){
     Serial.println("key 3");
  }
  
  if((estadoGPIO1 == false ) && (estadoGPIO8 == false )){
     Serial.println("key 4");

  }
 
  if((estadoGPIO1 == false ) && (estadoGPIO9 == false )){
     Serial.println("key 5");

  }
 
 
  
  //Serial.print(",");
  //Serial.println(estadoGPIO2);
   //Serial.println(estadoGPIO2);
  // // Verificar si el pin está en HIGH o LOW y enviar al puerto serial
  // if ((!estadoGPIO1) && (!estadoGPIO2)) {
  //   Serial.println(1);
  // } else {
  //   Serial.println(0);
  // }


// if ((digitalRead(sect1)== HIGH) && (digitalRead(data1)== LOW ))
// {
// //key number one of section one has been pressed
// Serial.println("key1 section1 pressed!");
// }
// if ((digitalRead(sect2)== HIGH) && (digitalRead(data2)== LOW ))
// {
// //key number one of section one has been pressed
// Serial.println("key2 section2 pressed!");
// }
  // delay(20);
}
