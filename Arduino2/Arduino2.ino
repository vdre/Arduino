#include <Servo.h>

//Victor Rivera
/*
     1 arriba
     2 abajo
     3 izquierda
     4 derecha
     5 para
     6 automatico
 */
int clockPin = 8;        //Pin SH_CP pin 11 del 74hc595
int latchPin = 12;        //Pin ST_CP pin 12 del 74hc595
int dataPin = 13;
int izqA = 10; 
int izqB = 11; 
int derA = 5; 
int derB = 6;
int pinServo = 9;
int vel = 255; // Velocidad de los motores (0-255)
int estado=0;
int pulsoMin = 750;   
int pulsoMax = 2550;
int cont=0;

#define pinTrig 2
#define pinEcho 3
int duracion=0;
int distancia=0;
int aux;

Servo miServo;

void setup()  { 
  miServo.attach(pinServo, pulsoMin, pulsoMax);
  Serial.begin(9600);
  pinMode(derA, OUTPUT);
  pinMode(derB, OUTPUT);
  pinMode(izqA, OUTPUT);
  pinMode(izqB, OUTPUT);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  digitalWrite(latchPin, LOW) ;
   shiftOut(dataPin, clockPin, MSBFIRST, 0);
   digitalWrite(latchPin, HIGH) ; 
 } 
 
void loop()  { 

if(estado==0){
  estado='5';}
aux=estado;
  if(Serial.available()>0){

estado = Serial.read();

}
if(estado=='1'){
  // Frente 2 segundos  
    analogWrite(derB, 0);
    analogWrite(izqB, 0); 
    analogWrite(derA, vel);  
    analogWrite(izqA, vel);
}
if(estado=='3'){
  // Reversa 2 segundos
    analogWrite(derA, 0);    
    analogWrite(izqA, 0);
    analogWrite(derB, vel);  
    analogWrite(izqB, vel);
}
    if(estado=='4'){
  // Izquierda 0,5 segundos 
    analogWrite(derB, 0);
    analogWrite(izqB, 0);
    analogWrite(derA, 50);
    analogWrite(izqA, vel);
    digitalWrite(latchPin, LOW) ;
   shiftOut(dataPin, clockPin, MSBFIRST, B00010000);
   digitalWrite(latchPin, HIGH) ; 
   delay(300);
     digitalWrite(latchPin, LOW) ;
    shiftOut(dataPin, clockPin, MSBFIRST, B00000000);
    digitalWrite(latchPin, HIGH) ; 
    delay(300);
   
    } 
    if(estado=='2'){
  // Derecha 0,5 segundos
    analogWrite(derB, 0);
    analogWrite(izqB, 0);
    analogWrite(derA, vel);  
    analogWrite(izqA, 50);
    digitalWrite(latchPin, LOW) ;
   shiftOut(dataPin, clockPin, MSBFIRST, B01000000);
   digitalWrite(latchPin, HIGH) ;
   delay(300);
    digitalWrite(latchPin, LOW) ;
    shiftOut(dataPin, clockPin, MSBFIRST, B00000000);
    digitalWrite(latchPin, HIGH) ; 
    delay(300);
   }

    if(estado=='5'){
  // Detiene los Motores   
    analogWrite(derB, 0);
    analogWrite(izqB, 0);
    analogWrite(derA, 0);    
    analogWrite(izqA, 0);
    }

if(estado=='l'){
  digitalWrite(latchPin, LOW) ;
   shiftOut(dataPin, clockPin, MSBFIRST, B10000000);
   digitalWrite(latchPin, HIGH) ; 
}

if(estado=='m'){
  digitalWrite(latchPin, HIGH) ; 
   shiftOut(dataPin, clockPin, MSBFIRST, B00000000);
   digitalWrite(latchPin, LOW);
}

if(estado=='r'){
  // Reversa 2 segundos
    analogWrite(derA, 0);    
    analogWrite(izqA, 0);
    analogWrite(derB, 135);  
    analogWrite(izqB, 135);
    digitalWrite(latchPin, LOW) ;
    shiftOut(dataPin, clockPin, MSBFIRST, B00100001);
    digitalWrite(latchPin, HIGH) ;
    delay(300);
     digitalWrite(latchPin, LOW) ;
    shiftOut(dataPin, clockPin, MSBFIRST, B00000000);
    digitalWrite(latchPin, HIGH) ; 
    delay(300);
}

if(estado=='a'){
    
    digitalWrite(latchPin, LOW) ;
    shiftOut(dataPin, clockPin, MSBFIRST, B00000001);
    digitalWrite(latchPin, HIGH) ;
    delay(300);
    digitalWrite(latchPin, LOW) ;
    shiftOut(dataPin, clockPin, MSBFIRST,0);
    digitalWrite(latchPin, HIGH) ;
    delay(300);
     digitalWrite(latchPin, LOW) ;
    shiftOut(dataPin, clockPin, MSBFIRST, B00000001);
    digitalWrite(latchPin, HIGH) ;
    delay(300);
    estado=aux;
}

if(estado=='s'){
    
    digitalWrite(latchPin, LOW) ;
    shiftOut(dataPin, clockPin, MSBFIRST, B00000001);
    digitalWrite(latchPin, HIGH) ;
    delay(50);
    digitalWrite(latchPin, LOW) ;
    shiftOut(dataPin, clockPin, MSBFIRST,0);
    digitalWrite(latchPin, HIGH) ;
    delay(100);
     digitalWrite(latchPin, LOW) ;
    shiftOut(dataPin, clockPin, MSBFIRST, B00000001);
    digitalWrite(latchPin, HIGH) ;
    delay(50);
    estado=aux;
    
}



if(estado=='6'){
digitalWrite(pinTrig, LOW);
delayMicroseconds(2);
digitalWrite(pinTrig, HIGH);
delayMicroseconds(10);
digitalWrite(pinTrig, LOW);
duracion = pulseIn(pinEcho, HIGH);
distancia = (duracion/2) / 29;

if (distancia <= 20 && distancia >3){

Serial.print(distancia);
Serial.println("cm");
Serial.println("Alarma.......");
//digitalWrite(pinZum, HIGH);
  
        analogWrite(derB, 0);                  // Parar los motores por 200 mili segundos
        analogWrite(izqB, 0); 
        analogWrite(derA, 0);    
        analogWrite(izqA, 0); 
        
        miServo.write(0);
        delay(1000);  
        
        digitalWrite(pinTrig, LOW);
        delayMicroseconds(2);
        digitalWrite(pinTrig, HIGH);
        delayMicroseconds(10);
        digitalWrite(pinTrig, LOW);
        duracion = pulseIn(pinEcho, HIGH);
        distancia = (duracion/2) / 29;

        // sets the servo position according to the scaled value 
             
               if (distancia <= 40  && distancia >3){
                  
                 miServo.write(154);
                 delay(1000);
    
                  digitalWrite(pinTrig, LOW);
                  delayMicroseconds(2);
                  digitalWrite(pinTrig, HIGH);
                  delayMicroseconds(10);
                  digitalWrite(pinTrig, LOW);
                  duracion = pulseIn(pinEcho, HIGH);
                  distancia = (duracion/2) / 29;
                  
                         
                         if (distancia <= 45  && distancia >3){
                          
                          digitalWrite(derB, 0);     
                          digitalWrite(izqB, 100); 
                          digitalWrite(derA, 0);  
                          digitalWrite(izqA, 0); 
                          delay(1500);
                          
                         digitalWrite(derB, 0);     
                         digitalWrite(izqB, 0); 
                         digitalWrite(derA, 70);  
                         digitalWrite(izqA, 70); 
        
                         miServo.write(78);
                         delay(800);
                        }
                        else if (distancia >2 ){
                            
                         digitalWrite(derB, 0);
                         digitalWrite(izqB, 0);
                         digitalWrite(derA, 0);  
                         analogWrite(izqA, 70);
                         delay(1200);
                          
                         digitalWrite(derB, 0);     
                         digitalWrite(izqB, 0); 
                         digitalWrite(derA, 70);  
                         digitalWrite(izqA, 70); 
        
                         miServo.write(78);
                         delay(800);
                
                        }
                delay(100);
                }
           
               else if (distancia >2 ){
                  
                 digitalWrite(derB, 0);
                  digitalWrite(izqB, 0);
                  analogWrite(derA, 100);
                  digitalWrite(izqA, 0);
                  delay(1200);
                   
                 digitalWrite(derB, 0);     
                 digitalWrite(izqB, 0); 
                 digitalWrite(derA, 70);  
                 digitalWrite(izqA, 70); 

                 miServo.write(77);
                 delay(800);
                
                }

          delay(100);
        
}

else if (distancia >2){

    Serial.print(distancia);
    Serial.println("cm");
    
             digitalWrite(derB, 0);     
             digitalWrite(izqB, 0); 
             digitalWrite(derA, 70);  
             digitalWrite(izqA, 70); 
    
    }


   delay(100);

}

miServo.write(77);
                 
}
