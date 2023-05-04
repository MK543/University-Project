#define czyRaport 1
#define lag 0
//Przyłacza Arduino
int Button1Pin = A1; //nazwa pinu dla "Przycisk żądanie 1-go poziomu"
int Button2Pin = A2; //nazwa pinu dla "Przycisk żądanie 2-go poziomu"
int Button3Pin = A3; //nazwa pinu dla "Przycisk żądanie 3-go poziomu"
int Sensor1Pin = A5; //nazwa pinu dla "Sensor obecności kabiny na 1-wszym poziomie"
int Sensor2Pin = 12; //nazwa pinu dla "Sensor obecności kabiny na 2-gim poziomie"
int Sensor3Pin = 13; //nazwa pinu dla "Sensor obecności kabiny na 3-cim poziomie"
int OutputQ2Pin = 4;//numer pinu dla Control Signal of Relay 4 / Output Signal Q2 / Start/Stop Signal
int OutputQ1Pin = 5;//numer pinu dla Control Signal of Relay 3 / Output Signal Q1 / Forward/Reverse Signal
//Zmienne globalne
boolean Q1 = 0;//Forward/Reverse Control Signal Relay 3
boolean Q2 = 0;//Start/Stop Control Signal Relay 4
boolean I2 = 0;//Odczyt z "Przycisk żądanie 1-go poziomu"
boolean I3 = 0;//Odczyt z "Przycisk żądanie 2-go poziomu"
boolean I4 = 0;//Odczyt z "Przycisk żądanie 3-go poziomu"
boolean I6 = 0;//Odczyt z "Sensor obecności kabiny na 1. poziomie"
boolean I7 = 0;//Odczyt z "Sensor obecności kabiny na 2. poziomie"
boolean I8 = 0;//Odczyt z "Sensor obecności kabiny na 3. poziomie"
//Flagi stanow
boolean M1 = 0;
boolean M2 = 0;
boolean M3 = 0;
boolean M4 = 0;
boolean M5 = 0;
boolean M6 = 0;
boolean M7 = 0;
boolean M1p = 0;
boolean M2p = 0;
boolean M3p = 0;
boolean M4p = 0;
boolean M5p = 0;
boolean M6p = 0;
boolean M7p = 0;
void raport()
{
 Serial.println("Odczyt przyciskow ");
 Serial.print(I2);
 Serial.print(I3);
 Serial.print(I4);
 Serial.println();
 Serial.println("Odczyt sensorow ");
 Serial.print(I6);
 Serial.print(I7);
 Serial.print(I8);
 Serial.println();
 Serial.println("Flagi ");
 Serial.print(M1);
 Serial.print(M2);
 Serial.print(M3);
 Serial.print(M4);
 Serial.print(M5);
 Serial.print(M6);
 Serial.print(M7);
 Serial.println();
 Serial.println("Wyjscia ");
 Serial.print(Q1);
 Serial.print(Q2);
 Serial.println();
}
void odczytWejsc()
{
 I2 = digitalRead(Button1Pin);
 I3 = digitalRead(Button2Pin);
 I4 = digitalRead(Button3Pin);
 I6 = digitalRead(Sensor1Pin);
 I7 = digitalRead(Sensor2Pin);
 I8 = digitalRead(Sensor3Pin);
}
void funkcjaPrzejscia()
{
 //Obliczenie wartości funkcji przejśc stanów (flag)
 M1p = !M1&!M2&!M3&!M4&!M5&!M6&!M7&I6&!I7&!I8 | M1&!I3&!I4 | M5&I6 | M1&I3&I4; 
 M2p = M1&I3&!I4 | M2&!I7;
 M3p = M1&!I3&I4 | M3&!I8 | M4&!I2&I4;
 M4p = M2&I7 | M4&!I2&I4 | M7&I7 | M4&I2&I4;
 M5p = !M1&!M2&!M3&!M4&!M5&!M6&!M7&!I6&(I7&!I8 | !I7&I8) | M4&I2&!I4 | M5&!I6 | M6&I2&!I3&!I4;
 M6p = M3&I8 | M6&!I2&!I3 | M6&I2&I3;
 M7p = M6&!I2&I3 | M7&!I7;
 //Przepisanie "nowych" wartości do "starych"
 M1 = M1p;
 M2 = M2p;
 M3 = M3p;
 M4 = M4p;
 M5 = M5p;
 M6 = M6p;
 M7 = M7p;
}
void funkcjaWyjscia()
{
 Q1 = M5 | M7;
 Q2 = M1 | M4 | M6;
}
void zapisWyjscia()
{
 digitalWrite(OutputQ1Pin, Q1);
 digitalWrite(OutputQ2Pin, Q2);
}
void setup()
{
 pinMode(Button1Pin, INPUT);
 pinMode(Button2Pin, INPUT);
 pinMode(Button3Pin, INPUT);
 pinMode(Sensor1Pin, INPUT);
 pinMode(Sensor2Pin, INPUT);
 pinMode(Sensor3Pin, INPUT);
 pinMode(OutputQ1Pin, OUTPUT);
 pinMode(OutputQ2Pin, OUTPUT);
 Serial.begin(9600);
 Serial.println("Koniec wykonywania Setup");
}
void loop()
{
 odczytWejsc();
 funkcjaPrzejscia();
 funkcjaWyjscia();
 zapisWyjscia();
 raport();
}

