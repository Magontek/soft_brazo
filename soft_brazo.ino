#include <Servo.h>

Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

float ang1=90,ang2=90,ang3=90,ang4=90,ang5=90;

bool verb=true;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.print("serial up \n");
  Serial.print("Controlador Brazo 3 ejes v=0.1 \n");
  delay(20);
  servo1.attach(3);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(9);
  servo5.attach(10);
  delay(20);
  servo1.write(90);
  servo2.write(90);
  servo3.write(90);
  servo4.write(90);
  servo5.write(90);
}

char err=0;
int count=0;
void serial_catcher(){
    if (Serial.available() > 0) {
      delay(2);
      Serial.flush();
      char modo=Serial.read();
      if (verb){
        Serial.print(" modo:");
        Serial.print(modo);
      }
      switch (modo){
        case 's':
          for (int i=0;i<5;i++){
            
          }
        break;
        case 'm':// 'm' es de manual
          Serial.flush();
          delay(2);
          char tipo=Serial.read();
          if (verb){
            Serial.print(" tipo:");
            Serial.print(tipo);
          }
          switch (tipo){
            case 'v':
              verb=!verb;
              Serial.print("Modo Verborragico ");
              Serial.println(verb);
            break;
            case 's':// 's' es servo, se selecciona entre los que estan conectados
              Serial.flush();
              delay(2);
              char servo=Serial.read();
              delay(2);
              float angulo=Serial.parseFloat();
              if (!verb){
                Serial.println(angulo);
              }
              switch (servo){//seleeciona el servo
                case 'a':
                  ang1=angulo;
                break;
                case 'b':
                  ang2=angulo;
                break;
                case 'c':
                  ang3=angulo;
                break;
                case 'd':
                  ang4=angulo;
                break;
                case 'e':
                  ang5=angulo;
                break;
                default:
                  Serial.println("Ese servo no existe");
                break;
              }
            break;
            default:
              Serial.println("Tipo incorrecto");
            break;
          }
        break;
        default:
          Serial.println("Modo incorrecto");
        break;
      }
      
      count++;
      if (verb){
        Serial.print(" conteo=");
        Serial.println(count);
      }
  }
  
}

long old_time;
void loop() {
  // put your main code here, to run repeatedly:
  serial_catcher();
  if(millis()-old_time>100){
    old_time=millis();
    servo1.write(ang1);
    delay(2);
    servo1.write(ang2);
    delay(2);
    servo1.write(ang3);
    delay(2);
    servo1.write(ang4);
    delay(2);
    servo1.write(ang5);
  }
  
}
