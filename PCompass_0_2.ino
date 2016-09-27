const byte stepsPin=7;     //контакт для шага
const byte directionPin=8;//контакт для управления вращением
const byte enablePin=11; //контакт включения
const int  delayTime=20;//регулирование скорости двигателя
const float KSG=1.1111111111;//умножая на это градусы получаем шаги
float NewCord;//Новые координаты
float OldCord=0;//Старые)
float PortValue;//Значение,которое пришло из порта
float Steps;//шаги
void setup()
{
  pinMode (stepsPin,OUTPUT);
  pinMode (directionPin,OUTPUT);
  pinMode (enablePin,OUTPUT);
  Serial.begin(9600);
}
void rotate(byte dir, float stepsValue)//Функция для *ходьбы* вперед или назад
{
  digitalWrite(enablePin, HIGH);
  digitalWrite(directionPin,dir);//направление
  for(float i=0.0; i<abs(stepsValue); i++)
  {
    digitalWrite(stepsPin, HIGH);
    delay(delayTime);
    digitalWrite(stepsPin, LOW);
    delay(delayTime);
  }
}
void loop()
{
  while (Serial.available() > 0)
  {  

    PortValue=Serial.parseInt();
    Serial.println(PortValue);
  }
  NewCord=PortValue*KSG;
  Steps=(NewCord-OldCord);
  if (Steps>=0)
  {
    rotate(1, Steps);//вызов функции вращения вперед
  }
  else
  {
    Steps*=(-1);
    rotate(0, Steps);//вызов функции вращения назад
  }
  OldCord=NewCord;
}





