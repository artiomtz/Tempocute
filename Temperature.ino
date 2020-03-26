float FloatTemperature = 10; // celsius temp float
int cTemperature = 28; // celsius temp int
int fTemperature = 0; // fahrenheit temp int
int TSet = 0; // temperature calibration

float PowerVoltage = 5.0; // ADJUST TEMPERATURE CALCULATION
float SensorValue = 0; // temperature read

int DSet = 0; // speed calibration
int lightDelay = 3; // ADJUST DISPLAY SPEED
int loadDelay = 80; // power up animation speed
long DisplayTime = 100; // ADJUST DISPLAY TIME

int NoiseValue = 0;
int NoiseJump = 15; // ADJUST NOISE VOLUME / SENSITIVITY
int LastNoise = 0;

bool day = true; // day / night
bool celsius = true; // celsius / fahrenheit

long ClockWait = 15000; // ADJUST CLAP TIME
long ClockCnt = 0;

char SpeedAdjust = 900; // adjust speed
char TempAdjust = 900; // calibrate temperature


////////// PINOUT:


char TempInput = A0; // temperature sensor
char NoiseInput = A2; // noise sensor
char SpeedInput = A4; // display speed
char TempSet = A5; // calibrate temperature
int digitalLight = 22; // digital LDR read

int Pin1 = 30; // diplay pin 30
int Pin2 = 31; // diplay pin 31
int Pin3 = 32; // diplay pin 32
int Pin4 = 33; // diplay pin 33
int Pin5 = 34; // diplay pin 34
int Pin6 = 35; // diplay pin 35
int Pin7 = 36; // diplay pin 36
int Pin8 = 37; // diplay pin 37
int Pin9 = 38; // diplay pin 38
int Pin10 = 39; // diplay pin 39
int Pin11 = 40; // diplay pin 40
int Pin12 = 41; // diplay pin 41
int Pin13 = 42; // diplay pin 42
int Pin14 = 43; // diplay pin 43
int Pin15 = 44; // diplay pin 44
int Pin16 = 45; // diplay pin 45
int Pin17 = 46; // diplay pin 46
int Pin18 = 47; // diplay pin 47
int Pin19 = 48; // diplay pin 48
int Pin20 = 49; // diplay pin 49
int Pin21 = 50; // diplay pin 50
int Pin22 = 51; // diplay pin 51
int Pin23 = 52; // diplay pin 52
int Pin24 = 53; // diplay pin 53


void setup()
{
  Serial.begin(9600);
  pinMode(Pin1,OUTPUT);
  pinMode(Pin2,OUTPUT);
  pinMode(Pin3,OUTPUT);
  pinMode(Pin4,OUTPUT);
  pinMode(Pin5,OUTPUT);
  pinMode(Pin6,OUTPUT);
  pinMode(Pin7,OUTPUT);
  pinMode(Pin8,OUTPUT);
  pinMode(Pin9,OUTPUT);
  pinMode(Pin10,OUTPUT);
  pinMode(Pin11,OUTPUT);
  pinMode(Pin12,OUTPUT);
  pinMode(Pin13,OUTPUT);
  pinMode(Pin14,OUTPUT);
  pinMode(Pin15,OUTPUT);
  pinMode(Pin16,OUTPUT);
  pinMode(Pin17,OUTPUT);
  pinMode(Pin18,OUTPUT);
  pinMode(Pin19,OUTPUT);
  pinMode(Pin20,OUTPUT);
  pinMode(Pin21,OUTPUT);
  pinMode(Pin22,OUTPUT);
  pinMode(Pin23,OUTPUT);
  pinMode(Pin24,OUTPUT);
  pinMode(Pin1,OUTPUT);
  pinMode(Pin1,OUTPUT);

  Serial.println("");
  Serial.println("       Digital sound-sensitive temperature display       ");
  Serial.println("                 (C) Artiom Tsimkin       ");
  Serial.println("");
  load();
}


void loop() // main
{
   if (ReadNoise()) // wait for 2 claps
   {
      delay(100);
      CalibrateTemp();
      ReadTemp(); // read temperature
      Display(1); // display C temp
      Display(2); // display C
      celsius = false;
      Display(1); // display F temp
      Display(3); // display F
      celsius = true;        
      Serial.println("");
      delay(100);
  }
}


void Display(int option)
{
  for(int i=0 ; i < DisplayTime ; i++) // display C temperature
  {
    CalibrateSpeed(); // read temp adjust
    ReadLight(); // read light
    
    switch (option)
    {
      case 1:   ShowTemp(); // display temp
                break;
                
      case 2:   if (day == true)
                {
                  LightCGreen(); // display C
                }
                else
                {
                  LightCRed(); // display C
                }
                break;
                
      case 3:   if (day == true)
                {
                  LightFGreen(); // display F
                }
                else
                {
                  LightFRed(); // display F
                }
                break;
                
      default:  LightError();
                break;
    }
  }  
}


void ReadTemp()
{
  SensorValue=0;
  for(int i=0 ; i<100 ; i++) // measure 100 times fast for accuracy
  {
    SensorValue += analogRead(TempInput);
  }
  SensorValue /= 100;
  FloatTemperature = (SensorValue / 1023) * PowerVoltage * 100;
  cTemperature = (int)FloatTemperature;
  fTemperature = ConvertTemp(cTemperature);
  Serial.print("The temperature is: ");
  Serial.print(cTemperature);
  Serial.print("C / ");
  Serial.print(fTemperature);
  Serial.println("F.");
}


void ReadLight()
{
  int LightValue = digitalRead(digitalLight);
  
  if (LightValue == HIGH) // dark
  {
    day = false;
    //Serial.println("(It's dark)");
  }
  else // not dark
  {
    day = true;
    //Serial.println("(It's not dark)");
  }
}


bool ReadNoise()
{
  bool clapclap = false;

  while (clapclap == false) // waiting for 2 claps
  {
    Serial.println("Waiting for clap 1.");
    while(!Clap()) {} // waiting for clap 1
    delay(200);
    Serial.println("Waiting for clap 2.");
    if (Clap()) // if clap 2
    {
      clapclap = true;
      Serial.println("Second clap detected!");
    }
    else
    {
      Serial.println("No second clap detected.");
      Serial.println("");
    }
  }
  delay(300);
  return true;
}


bool Clap()
{
  LastNoise = analogRead(NoiseInput);
  ClockCnt = 0;

  while(ClockCnt < ClockWait) // waiting for a clap for 1 sec
  {
    NoiseValue = analogRead(NoiseInput);
    if ((NoiseValue - LastNoise) > NoiseJump) // clap
    {
      return true;
    }
    LastNoise = NoiseValue;
    ClockCnt++;
  }
  ClockCnt = 0;
  return false;
}


int ConvertTemp(int cTemp)
{
  switch (cTemp)
  {
    case 10:  return 50;
              break;
    case 11:  return 51;
              break;
    case 12:  return 53;
              break;
    case 13:  return 55;
              break;
    case 14:  return 57;
              break;
    case 15:  return 59;
              break;
    case 16:  return 60;
              break;
    case 17:  return 62;
              break;
    case 18:  return 64;
              break;
    case 19:  return 66;
              break;
    case 20:  return 68;
              break;
    case 21:  return 69;
              break;
    case 22:  return 71;
              break;
    case 23:  return 73;
              break;
    case 24:  return 75;
              break;
    case 25:  return 77;
              break;
    case 26:  return 78;
              break;
    case 27:  return 80;
              break;
    case 28:  return 82;
              break;
    case 29:  return 84;
              break;
    case 30:  return 86;
              break;
    case 31:  return 87;
              break;
    case 32:  return 89;
              break;
    case 33:  return 91;
              break;
    case 34:  return 93;
              break;
    case 35:  return 95;
              break;
    case 36:  return 96;
              break;
    case 37:  return 98;
              break;
    default:  return 0;
  }
}


void CalibrateTemp()
{
  TSet = analogRead(TempSet);
  //Serial.print("Temperature calibration: ");
  //Serial.println(TSet);
  if (TSet >= 0 && TSet < 34) { PowerVoltage = 3.6; }
  else if (TSet >= 34 && TSet < 68) { PowerVoltage = 3.8; }
  else if (TSet >= 68 && TSet < 102) { PowerVoltage = 4.0; }
  else if (TSet >= 102 && TSet < 136) { PowerVoltage = 4.2; }
  else if (TSet >= 136 && TSet < 170) { PowerVoltage = 4.4; }
  else if (TSet >= 170 && TSet < 204) { PowerVoltage = 4.6; }
  else if (TSet >= 204 && TSet < 238) { PowerVoltage = 4.8; }
  else if (TSet >= 238 && TSet < 268) { PowerVoltage = 5.0; }
  else if (TSet >= 268 && TSet < 302) { PowerVoltage = 5.2; }
  else if (TSet >= 302 && TSet < 336) { PowerVoltage = 5.4; }
  else if (TSet >= 336 && TSet < 370) { PowerVoltage = 5.6; }
  else if (TSet >= 370 && TSet < 404) { PowerVoltage = 5.8; }
  else if (TSet >= 404 && TSet < 438) { PowerVoltage = 6.0; }
  else if (TSet >= 438 && TSet < 472) { PowerVoltage = 6.2; }
  else if (TSet >= 472 && TSet < 506) { PowerVoltage = 6.4; }
  else if (TSet >= 506 && TSet < 540) { PowerVoltage = 6.6; }
  else if (TSet >= 540 && TSet < 574) { PowerVoltage = 6.8; }
  else if (TSet >= 574 && TSet < 608) { PowerVoltage = 7.0; }
  else if (TSet >= 608 && TSet < 642) { PowerVoltage = 7.2; }
  else if (TSet >= 642 && TSet < 676) { PowerVoltage = 7.4; }
  else if (TSet >= 676 && TSet < 710) { PowerVoltage = 7.6; }
  else if (TSet >= 710 && TSet < 744) { PowerVoltage = 7.8; }
  else if (TSet >= 744 && TSet < 778) { PowerVoltage = 8.0; }
  else if (TSet >= 778 && TSet < 812) { PowerVoltage = 8.2; }
  else if (TSet >= 812 && TSet < 846) { PowerVoltage = 8.4; }
  else if (TSet >= 846 && TSet < 880) { PowerVoltage = 8.6; }
  else if (TSet >= 880 && TSet < 914) { PowerVoltage = 8.8; }
  else if (TSet >= 914 && TSet < 948) { PowerVoltage = 9.0; }
  else if (TSet >= 948 && TSet < 982) { PowerVoltage = 9.2; }
  else { PowerVoltage = 9.4; }
}


void CalibrateSpeed()
{
  DSet = analogRead(SpeedInput);
  if (DSet >= 0 && DSet < 102) { lightDelay = 1; }
  else if (DSet >= 102 && DSet < 204) { lightDelay = 2; }
  else if (DSet >= 204 && DSet < 302) { lightDelay = 3; }
  else if (DSet >= 302 && DSet < 404) { lightDelay = 4; }
  else if (DSet >= 404 && DSet < 472) { lightDelay = 5; }
  else if (DSet >= 472 && DSet < 540) { lightDelay = 6; }
  else if (DSet >= 540 && DSet < 608) { lightDelay = 8; }
  else if (DSet >= 608 && DSet < 676) { lightDelay = 10; }
  else if (DSet >= 676 && DSet < 710) { lightDelay = 15; }
  else if (DSet >= 710 && DSet < 744) { lightDelay = 20; }
  else if (DSet >= 744 && DSet < 778) { lightDelay = 25; }
  else if (DSet >= 778 && DSet < 812) { lightDelay = 30; }
  else if (DSet >= 812 && DSet < 846) { lightDelay = 35; }
  else if (DSet >= 846 && DSet < 880) { lightDelay = 45; }
  else if (DSet >= 880 && DSet < 914) { lightDelay = 55; }
  else if (DSet >= 914 && DSet < 948) { lightDelay = 65; }
  else if (DSet >= 948 && DSet < 982) { lightDelay = 75; }
  else { lightDelay = 85; }
}


void ShowTemp()
{
  if (day == false) ////////////////// RED
  {
    if (celsius == true) //////////// RED celsius
    {
      switch (cTemperature)
      {
        case 10:
          LightLeftRed1();
          LightRightRed0();
          break;
        case 11:
          LightLeftRed1();
          LightRightRed1();
          break;
        case 12:
          LightLeftRed1();
          LightRightRed2();
          break;
        case 13:
          LightLeftRed1();
          LightRightRed3();
          break;
        case 14:
          LightLeftRed1();
          LightRightRed4();
          break;
        case 15:
          LightLeftRed1();
          LightRightRed5();
          break;
        case 16:
          LightLeftRed1();
          LightRightRed6();
          break;
        case 17:
          LightLeftRed1();
          LightRightRed7();
          break;
        case 18:
          LightLeftRed1();
          LightRightRed8();
          break;
        case 19:
          LightLeftRed1();
          LightRightRed9();
          break;
        case 20:
          LightLeftRed2();
          LightRightRed0();
          break;
        case 21:
          LightLeftRed2();
          LightRightRed1();
          break;
        case 22:
          LightLeftRed2();
          LightRightRed2();
          break;
        case 23:
          LightLeftRed2();
          LightRightRed3();
          break;
        case 24:
          LightLeftRed2();
          LightRightRed4();
          break;
        case 25:
          LightLeftRed2();
          LightRightRed5();
          break;
        case 26:
          LightLeftRed2();
          LightRightRed6();
          break;
        case 27:
          LightLeftRed2();
          LightRightRed7();
          break;
        case 28:
          LightLeftRed2();
          LightRightRed8();
          break;
        case 29:
          LightLeftRed2();
          LightRightRed9();
          break;
        case 30:
          LightLeftRed3();
          LightRightRed0();
          break;
        case 31:
          LightLeftRed3();
          LightRightRed1();
          break;
        case 32:
          LightLeftRed3();
          LightRightRed2();
          break;
        case 33:
          LightLeftRed3();
          LightRightRed3();
          break;
        case 34:
          LightLeftRed3();
          LightRightRed4();
          break;
        case 35:
          LightLeftRed3();
          LightRightRed5();
          break;
        case 36:
          LightLeftRed3();
          LightRightRed6();
          break;
        case 37:
          LightLeftRed3();
          LightRightRed7();
          break;
        default:
          LightError();
          break;
      }
    }

    else ////////// RED fahrenheit
    {
      switch (fTemperature)
      {
        case 50:
          LightLeftRed5();
          LightRightRed0();
          break;
        case 51:
          LightLeftRed5();
          LightRightRed1();
          break;
        case 53:
          LightLeftRed5();
          LightRightRed3();
          break;
        case 55:
          LightLeftRed5();
          LightRightRed5();
          break;
        case 57:
          LightLeftRed5();
          LightRightRed7();
          break;
        case 59:
          LightLeftRed5();
          LightRightRed9();
          break;
        case 60:
          LightLeftRed6();
          LightRightRed0();
          break;
        case 62:
          LightLeftRed6();
          LightRightRed2();
          break;
        case 64:
          LightLeftRed6();
          LightRightRed4();
          break;
        case 66:
          LightLeftRed6();
          LightRightRed6();
          break;
        case 68:
          LightLeftRed6();
          LightRightRed8();
          break;
        case 69:
          LightLeftRed6();
          LightRightRed9();
          break;
        case 71:
          LightLeftRed7();
          LightRightRed1();
          break;
        case 73:
          LightLeftRed7();
          LightRightRed3();
          break;
        case 75:
          LightLeftRed7();
          LightRightRed5();
          break;
        case 77:
          LightLeftRed7();
          LightRightRed7();
          break;
        case 78:
          LightLeftRed7();
          LightRightRed8();
          break;
        case 80:
          LightLeftRed8();
          LightRightRed0();
          break;
        case 82:
          LightLeftRed8();
          LightRightRed2();
          break;
        case 84:
          LightLeftRed8();
          LightRightRed4();
          break;
        case 86:
          LightLeftRed8();
          LightRightRed6();
          break;
        case 87:
          LightLeftRed8();
          LightRightRed7();
          break;
        case 89:
          LightLeftRed8();
          LightRightRed9();
          break;
        case 91:
          LightLeftRed9();
          LightRightRed1();
          break;
        case 93:
          LightLeftRed9();
          LightRightRed3();
          break;
        case 95:
          LightLeftRed9();
          LightRightRed5();
          break;
        case 96:
          LightLeftRed9();
          LightRightRed6();
          break;
        case 98:
          LightLeftRed9();
          LightRightRed8();
          break;
        default:
          LightError();
          break;
      }
    }
  }
  
  else ////////////// GREEN / day
  {
    if (celsius == true) //////////// GREEN celsius
    {
      switch (cTemperature)
      {
        case 10:
          LightLeftGreen1();
          LightRightGreen0();
          break;
        case 11:
          LightLeftGreen1();
          LightRightGreen1();
          break;
        case 12:
          LightLeftGreen1();
          LightRightGreen2();
          break;
        case 13:
          LightLeftGreen1();
          LightRightGreen3();
          break;
        case 14:
          LightLeftGreen1();
          LightRightGreen4();
          break;
        case 15:
          LightLeftGreen1();
          LightRightGreen5();
          break;
        case 16:
          LightLeftGreen1();
          LightRightGreen6();
          break;
        case 17:
          LightLeftGreen1();
          LightRightGreen7();
          break;
        case 18:
          LightLeftGreen1();
          LightRightGreen8();
          break;
        case 19:
          LightLeftGreen1();
          LightRightGreen9();
          break;
        case 20:
          LightLeftGreen2();
          LightRightGreen0();
          break;
        case 21:
          LightLeftGreen2();
          LightRightGreen1();
          break;
        case 22:
          LightLeftGreen2();
          LightRightGreen2();
          break;
        case 23:
          LightLeftGreen2();
          LightRightGreen3();
          break;
        case 24:
          LightLeftGreen2();
          LightRightGreen4();
          break;
        case 25:
          LightLeftGreen2();
          LightRightGreen5();
          break;
        case 26:
          LightLeftGreen2();
          LightRightGreen6();
          break;
        case 27:
          LightLeftGreen2();
          LightRightGreen7();
          break;
        case 28:
          LightLeftGreen2();
          LightRightGreen8();
          break;
        case 29:
          LightLeftGreen2();
          LightRightGreen9();
          break;
        case 30:
          LightLeftGreen3();
          LightRightGreen0();
          break;
        case 31:
          LightLeftGreen3();
          LightRightGreen1();
          break;
        case 32:
          LightLeftGreen3();
          LightRightGreen2();
          break;
        case 33:
          LightLeftGreen3();
          LightRightGreen3();
          break;
        case 34:
          LightLeftGreen3();
          LightRightGreen4();
          break;
        case 35:
          LightLeftGreen3();
          LightRightGreen5();
          break;
        case 36:
          LightLeftGreen3();
          LightRightGreen6();
          break;
        case 37:
          LightLeftGreen3();
          LightRightGreen7();
          break;
        default:
          LightError();
          break;
      }
    }

    else ////////// GREEN fahrenheit
    {
      switch (fTemperature)
      {
        case 50:
          LightLeftGreen5();
          LightRightGreen0();
          break;
        case 51:
          LightLeftGreen5();
          LightRightGreen1();
          break;
        case 53:
          LightLeftGreen5();
          LightRightGreen3();
          break;
        case 55:
          LightLeftGreen5();
          LightRightGreen5();
          break;
        case 57:
          LightLeftGreen5();
          LightRightGreen7();
          break;
        case 59:
          LightLeftGreen5();
          LightRightGreen9();
          break;
        case 60:
          LightLeftGreen6();
          LightRightGreen0();
          break;
        case 62:
          LightLeftGreen6();
          LightRightGreen2();
          break;
        case 64:
          LightLeftGreen6();
          LightRightGreen4();
          break;
        case 66:
          LightLeftGreen6();
          LightRightGreen6();
          break;
        case 68:
          LightLeftGreen6();
          LightRightGreen8();
          break;
        case 69:
          LightLeftGreen6();
          LightRightGreen9();
          break;
        case 71:
          LightLeftGreen7();
          LightRightGreen1();
          break;
        case 73:
          LightLeftGreen7();
          LightRightGreen3();
          break;
        case 75:
          LightLeftGreen7();
          LightRightGreen5();
          break;
        case 77:
          LightLeftGreen7();
          LightRightGreen7();
          break;
        case 78:
          LightLeftGreen7();
          LightRightGreen8();
          break;
        case 80:
          LightLeftGreen8();
          LightRightGreen0();
          break;
        case 82:
          LightLeftGreen8();
          LightRightGreen2();
          break;
        case 84:
          LightLeftGreen8();
          LightRightGreen4();
          break;
        case 86:
          LightLeftGreen8();
          LightRightGreen6();
          break;
        case 87:
          LightLeftGreen8();
          LightRightGreen7();
          break;
        case 89:
          LightLeftGreen8();
          LightRightGreen9();
          break;
        case 91:
          LightLeftGreen9();
          LightRightGreen1();
          break;
        case 93:
          LightLeftGreen9();
          LightRightGreen3();
          break;
        case 95:
          LightLeftGreen9();
          LightRightGreen5();
          break;
        case 96:
          LightLeftGreen9();
          LightRightGreen6();
          break;
        case 98:
          LightLeftGreen9();
          LightRightGreen8();
          break;
        default:
          LightError();
          break;
      }
    }
  }
}


void TurnOff()
{
    digitalWrite(Pin1,HIGH);
    digitalWrite(Pin2,HIGH);
    digitalWrite(Pin3,HIGH);
    digitalWrite(Pin4,HIGH);
    digitalWrite(Pin21,HIGH);
    digitalWrite(Pin22,HIGH);
    digitalWrite(Pin23,HIGH);
    digitalWrite(Pin24,HIGH);
    //delay(1);
}


void load()
{
    digitalWrite(Pin1,LOW);
    digitalWrite(Pin2,LOW);
    digitalWrite(Pin3,LOW);
    digitalWrite(Pin4,LOW);
    digitalWrite(Pin21,LOW);
    digitalWrite(Pin22,LOW);
    digitalWrite(Pin23,LOW);
    digitalWrite(Pin24,LOW);
    digitalWrite(Pin5,LOW);
    digitalWrite(Pin6,LOW);
    digitalWrite(Pin7,LOW);
    digitalWrite(Pin8,LOW);
    digitalWrite(Pin9,LOW);
    digitalWrite(Pin10,LOW);
    digitalWrite(Pin11,LOW);
    digitalWrite(Pin12,HIGH);
    digitalWrite(Pin13,LOW);
    digitalWrite(Pin14,LOW);
    digitalWrite(Pin15,LOW);
    digitalWrite(Pin16,LOW);
    digitalWrite(Pin17,LOW);
    digitalWrite(Pin18,LOW);
    digitalWrite(Pin19,LOW);
    digitalWrite(Pin20,LOW);
    delay(loadDelay);
    digitalWrite(Pin1,LOW);
    digitalWrite(Pin2,LOW);
    digitalWrite(Pin3,LOW);
    digitalWrite(Pin4,LOW);
    digitalWrite(Pin21,LOW);
    digitalWrite(Pin22,LOW);
    digitalWrite(Pin23,LOW);
    digitalWrite(Pin24,LOW);
    digitalWrite(Pin5,LOW);
    digitalWrite(Pin6,LOW);
    digitalWrite(Pin7,LOW);
    digitalWrite(Pin8,LOW);
    digitalWrite(Pin9,LOW);
    digitalWrite(Pin10,LOW);
    digitalWrite(Pin11,HIGH);
    digitalWrite(Pin12,LOW);
    digitalWrite(Pin13,HIGH);
    digitalWrite(Pin14,LOW);
    digitalWrite(Pin15,LOW);
    digitalWrite(Pin16,LOW);
    digitalWrite(Pin17,LOW);
    digitalWrite(Pin18,LOW);
    digitalWrite(Pin19,LOW);
    digitalWrite(Pin20,LOW);
    delay(loadDelay);
    digitalWrite(Pin1,LOW);
    digitalWrite(Pin2,LOW);
    digitalWrite(Pin3,LOW);
    digitalWrite(Pin4,LOW);
    digitalWrite(Pin21,LOW);
    digitalWrite(Pin22,LOW);
    digitalWrite(Pin23,LOW);
    digitalWrite(Pin24,LOW);
    digitalWrite(Pin5,LOW);
    digitalWrite(Pin6,LOW);
    digitalWrite(Pin7,LOW);
    digitalWrite(Pin8,LOW);
    digitalWrite(Pin9,LOW);
    digitalWrite(Pin10,HIGH);
    digitalWrite(Pin11,LOW);
    digitalWrite(Pin12,LOW);
    digitalWrite(Pin13,LOW);
    digitalWrite(Pin14,HIGH);
    digitalWrite(Pin15,LOW);
    digitalWrite(Pin16,LOW);
    digitalWrite(Pin17,LOW);
    digitalWrite(Pin18,LOW);
    digitalWrite(Pin19,LOW);
    digitalWrite(Pin20,LOW);
    delay(loadDelay);
    digitalWrite(Pin1,LOW);
    digitalWrite(Pin2,LOW);
    digitalWrite(Pin3,LOW);
    digitalWrite(Pin4,LOW);
    digitalWrite(Pin21,LOW);
    digitalWrite(Pin22,LOW);
    digitalWrite(Pin23,LOW);
    digitalWrite(Pin24,LOW);
    digitalWrite(Pin5,LOW);
    digitalWrite(Pin6,LOW);
    digitalWrite(Pin7,LOW);
    digitalWrite(Pin8,LOW);
    digitalWrite(Pin9,HIGH);
    digitalWrite(Pin10,LOW);
    digitalWrite(Pin11,LOW);
    digitalWrite(Pin12,LOW);
    digitalWrite(Pin13,LOW);
    digitalWrite(Pin14,LOW);
    digitalWrite(Pin15,HIGH);
    digitalWrite(Pin16,LOW);
    digitalWrite(Pin17,LOW);
    digitalWrite(Pin18,LOW);
    digitalWrite(Pin19,LOW);
    digitalWrite(Pin20,LOW);
    delay(loadDelay);
    digitalWrite(Pin1,LOW);
    digitalWrite(Pin2,LOW);
    digitalWrite(Pin3,LOW);
    digitalWrite(Pin4,LOW);
    digitalWrite(Pin21,LOW);
    digitalWrite(Pin22,LOW);
    digitalWrite(Pin23,LOW);
    digitalWrite(Pin24,LOW);
    digitalWrite(Pin5,LOW);
    digitalWrite(Pin6,LOW);
    digitalWrite(Pin7,LOW);
    digitalWrite(Pin8,HIGH);
    digitalWrite(Pin9,LOW);
    digitalWrite(Pin10,LOW);
    digitalWrite(Pin11,LOW);
    digitalWrite(Pin12,LOW);
    digitalWrite(Pin13,LOW);
    digitalWrite(Pin14,LOW);
    digitalWrite(Pin15,LOW);
    digitalWrite(Pin16,HIGH);
    digitalWrite(Pin17,LOW);
    digitalWrite(Pin18,LOW);
    digitalWrite(Pin19,LOW);
    digitalWrite(Pin20,LOW);
    delay(loadDelay);
    digitalWrite(Pin1,LOW);
    digitalWrite(Pin2,LOW);
    digitalWrite(Pin3,LOW);
    digitalWrite(Pin4,LOW);
    digitalWrite(Pin21,LOW);
    digitalWrite(Pin22,LOW);
    digitalWrite(Pin23,LOW);
    digitalWrite(Pin24,LOW);
    digitalWrite(Pin5,LOW);
    digitalWrite(Pin6,LOW);
    digitalWrite(Pin7,HIGH);
    digitalWrite(Pin8,LOW);
    digitalWrite(Pin9,LOW);
    digitalWrite(Pin10,LOW);
    digitalWrite(Pin11,LOW);
    digitalWrite(Pin12,LOW);
    digitalWrite(Pin13,LOW);
    digitalWrite(Pin14,LOW);
    digitalWrite(Pin15,LOW);
    digitalWrite(Pin16,LOW);
    digitalWrite(Pin17,HIGH);
    digitalWrite(Pin18,LOW);
    digitalWrite(Pin19,LOW);
    digitalWrite(Pin20,LOW);
    delay(loadDelay);
    digitalWrite(Pin1,LOW);
    digitalWrite(Pin2,LOW);
    digitalWrite(Pin3,LOW);
    digitalWrite(Pin4,LOW);
    digitalWrite(Pin21,LOW);
    digitalWrite(Pin22,LOW);
    digitalWrite(Pin23,LOW);
    digitalWrite(Pin24,LOW);
    digitalWrite(Pin5,LOW);
    digitalWrite(Pin6,HIGH);
    digitalWrite(Pin7,LOW);
    digitalWrite(Pin8,LOW);
    digitalWrite(Pin9,LOW);
    digitalWrite(Pin10,LOW);
    digitalWrite(Pin11,LOW);
    digitalWrite(Pin12,LOW);
    digitalWrite(Pin13,LOW);
    digitalWrite(Pin14,LOW);
    digitalWrite(Pin15,LOW);
    digitalWrite(Pin16,LOW);
    digitalWrite(Pin17,LOW);
    digitalWrite(Pin18,HIGH);
    digitalWrite(Pin19,LOW);
    digitalWrite(Pin20,LOW);
    delay(loadDelay);
    digitalWrite(Pin1,LOW);
    digitalWrite(Pin2,LOW);
    digitalWrite(Pin3,LOW);
    digitalWrite(Pin4,LOW);
    digitalWrite(Pin21,LOW);
    digitalWrite(Pin22,LOW);
    digitalWrite(Pin23,LOW);
    digitalWrite(Pin24,LOW);
    digitalWrite(Pin5,HIGH);
    digitalWrite(Pin6,LOW);
    digitalWrite(Pin7,LOW);
    digitalWrite(Pin8,LOW);
    digitalWrite(Pin9,LOW);
    digitalWrite(Pin10,LOW);
    digitalWrite(Pin11,LOW);
    digitalWrite(Pin12,LOW);
    digitalWrite(Pin13,LOW);
    digitalWrite(Pin14,LOW);
    digitalWrite(Pin15,LOW);
    digitalWrite(Pin16,LOW);
    digitalWrite(Pin17,LOW);
    digitalWrite(Pin18,LOW);
    digitalWrite(Pin19,HIGH);
    digitalWrite(Pin20,LOW);
    delay(loadDelay);    
    digitalWrite(Pin1,LOW);
    digitalWrite(Pin2,LOW);
    digitalWrite(Pin3,LOW);
    digitalWrite(Pin4,LOW);
    digitalWrite(Pin21,LOW);
    digitalWrite(Pin22,LOW);
    digitalWrite(Pin23,LOW);
    digitalWrite(Pin24,LOW);
    digitalWrite(Pin5,LOW);
    digitalWrite(Pin6,LOW);
    digitalWrite(Pin7,LOW);
    digitalWrite(Pin8,LOW);
    digitalWrite(Pin9,LOW);
    digitalWrite(Pin10,LOW);
    digitalWrite(Pin11,LOW);
    digitalWrite(Pin12,LOW);
    digitalWrite(Pin13,LOW);
    digitalWrite(Pin14,LOW);
    digitalWrite(Pin15,LOW);
    digitalWrite(Pin16,LOW);
    digitalWrite(Pin17,LOW);
    digitalWrite(Pin18,LOW);
    digitalWrite(Pin19,LOW);
    digitalWrite(Pin20,HIGH);
    delay(loadDelay);
    digitalWrite(Pin1,LOW);
    digitalWrite(Pin2,LOW);
    digitalWrite(Pin3,LOW);
    digitalWrite(Pin4,LOW);
    digitalWrite(Pin21,LOW);
    digitalWrite(Pin22,LOW);
    digitalWrite(Pin23,LOW);
    digitalWrite(Pin24,LOW);
    digitalWrite(Pin5,LOW);
    digitalWrite(Pin6,LOW);
    digitalWrite(Pin7,LOW);
    digitalWrite(Pin8,LOW);
    digitalWrite(Pin9,LOW);
    digitalWrite(Pin10,LOW);
    digitalWrite(Pin11,LOW);
    digitalWrite(Pin12,LOW);
    digitalWrite(Pin13,LOW);
    digitalWrite(Pin14,LOW);
    digitalWrite(Pin15,LOW);
    digitalWrite(Pin16,LOW);
    digitalWrite(Pin17,LOW);
    digitalWrite(Pin18,LOW);
    digitalWrite(Pin19,LOW);
    digitalWrite(Pin20,LOW);
    delay(4*loadDelay);
}

////////////////////////////////////////////////////////////

void LightError()
{
    digitalWrite(Pin1,LOW);
    digitalWrite(Pin2,HIGH);
    digitalWrite(Pin3,LOW);
    digitalWrite(Pin4,HIGH);
    digitalWrite(Pin21,LOW);
    digitalWrite(Pin22,HIGH);
    digitalWrite(Pin23,LOW);
    digitalWrite(Pin24,HIGH);
    digitalWrite(Pin5,HIGH);
    digitalWrite(Pin6,LOW);
    digitalWrite(Pin7,HIGH);
    digitalWrite(Pin8,LOW);
    digitalWrite(Pin9,HIGH);
    digitalWrite(Pin10,LOW);
    digitalWrite(Pin11,HIGH);
    digitalWrite(Pin12,LOW);
    digitalWrite(Pin13,LOW);
    digitalWrite(Pin14,LOW);
    digitalWrite(Pin15,LOW);
    digitalWrite(Pin16,LOW);
    digitalWrite(Pin17,LOW);
    digitalWrite(Pin18,LOW);
    digitalWrite(Pin19,LOW);
    digitalWrite(Pin20,LOW);
    delay(lightDelay);
    TurnOff();
}


void LightCGreen()
{
  for(int i=0 ; i<2 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,HIGH);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,HIGH);
      digitalWrite(Pin10,HIGH);
      digitalWrite(Pin11,HIGH);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,HIGH);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightCRed()
{
  for(int i=0 ; i<2 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,HIGH);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,HIGH);
      digitalWrite(Pin15,HIGH);
      digitalWrite(Pin16,HIGH);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,HIGH);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}



void LightFGreen()
{
  for(int i=0 ; i<2 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,HIGH);
      digitalWrite(Pin10,HIGH);
      digitalWrite(Pin11,HIGH);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,HIGH);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightFRed()
{
  for(int i=0 ; i<2 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,HIGH);
      digitalWrite(Pin15,HIGH);
      digitalWrite(Pin16,HIGH);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,HIGH);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightRightGreen0()
{
  for(int i=0 ; i<2 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,HIGH);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,HIGH);
      digitalWrite(Pin10,HIGH);
      digitalWrite(Pin11,HIGH);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,HIGH);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,HIGH);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightLeftGreen1()
{
  for(int i=0 ; i<2 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,HIGH);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,HIGH);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,HIGH);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,HIGH);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}

void LightRightGreen1()
{
  for(int i=0 ; i<2 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,HIGH);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,HIGH);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,HIGH);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,HIGH);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightLeftGreen2()
{
  for(int i=0 ; i<3 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,HIGH);
      digitalWrite(Pin6,HIGH);
      digitalWrite(Pin7,HIGH);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else if(i==1)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,HIGH);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,HIGH);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,HIGH);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightRightGreen2()
{
  for(int i=0 ; i<3 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,HIGH);
      digitalWrite(Pin10,HIGH);
      digitalWrite(Pin11,HIGH);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else if(i==1)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,HIGH);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,HIGH);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,HIGH);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightLeftGreen3()
{
  for(int i=0 ; i<2 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,HIGH);
      digitalWrite(Pin6,HIGH);
      digitalWrite(Pin7,HIGH);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,HIGH);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightRightGreen3()
{
  for(int i=0 ; i<2 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,HIGH);
      digitalWrite(Pin10,HIGH);
      digitalWrite(Pin11,HIGH);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,HIGH);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightLeftGreen4()
{
  for(int i=0 ; i<3 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,HIGH);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else if(i==1)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,HIGH);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,HIGH);
      digitalWrite(Pin6,HIGH);
      digitalWrite(Pin7,HIGH);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,HIGH);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightRightGreen4()
{
  for(int i=0 ; i<3 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,HIGH);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else if(i==1)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,HIGH);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,HIGH);
      digitalWrite(Pin10,HIGH);
      digitalWrite(Pin11,HIGH);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,HIGH);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightLeftGreen5()
{
  for(int i=0 ; i<3 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,HIGH);
      digitalWrite(Pin6,HIGH);
      digitalWrite(Pin7,HIGH);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else if(i==1)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,HIGH);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,HIGH);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,HIGH);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightRightGreen5()
{
  for(int i=0 ; i<3 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,HIGH);
      digitalWrite(Pin10,HIGH);
      digitalWrite(Pin11,HIGH);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else if(i==1)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,HIGH);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,HIGH);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,HIGH);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightLeftGreen6()
{
  for(int i=0 ; i<3 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,HIGH);
      digitalWrite(Pin6,HIGH);
      digitalWrite(Pin7,HIGH);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else if(i==1)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,HIGH);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,HIGH);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,HIGH);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightRightGreen6()
{
  for(int i=0 ; i<3 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,HIGH);
      digitalWrite(Pin10,HIGH);
      digitalWrite(Pin11,HIGH);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else if(i==1)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,HIGH);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,HIGH);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,HIGH);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightLeftGreen7()
{
  for(int i=0 ; i<2 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,HIGH);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,HIGH);
      digitalWrite(Pin6,HIGH);
      digitalWrite(Pin7,HIGH);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,HIGH);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightRightGreen7()
{
  for(int i=0 ; i<2 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,HIGH);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,HIGH);
      digitalWrite(Pin10,HIGH);
      digitalWrite(Pin11,HIGH);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,HIGH);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightLeftGreen8()
{
  for(int i=0 ; i<2 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,HIGH);
      digitalWrite(Pin6,HIGH);
      digitalWrite(Pin7,HIGH);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,HIGH);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,HIGH);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightRightGreen8()
{
  for(int i=0 ; i<2 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,HIGH);
      digitalWrite(Pin10,HIGH);
      digitalWrite(Pin11,HIGH);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,HIGH);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,HIGH);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightLeftGreen9()
{
  for(int i=0 ; i<3 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,HIGH);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else if(i==1)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,HIGH);
      digitalWrite(Pin6,HIGH);
      digitalWrite(Pin7,HIGH);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,HIGH);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}

void LightRightGreen9()
{
  for(int i=0 ; i<3 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,HIGH);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else if(i==1)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,HIGH);
      digitalWrite(Pin10,HIGH);
      digitalWrite(Pin11,HIGH);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,HIGH);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}

///////////////////////////////////////////////////////////////

void LightRightRed0()
{
  for(int i=0 ; i<2 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,HIGH);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,HIGH);
      digitalWrite(Pin15,HIGH);
      digitalWrite(Pin16,HIGH);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,HIGH);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,HIGH);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightLeftRed1()
{
  for(int i=0 ; i<2 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,HIGH);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,HIGH);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,HIGH);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,HIGH);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}

void LightRightRed1()
{
  for(int i=0 ; i<2 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,HIGH);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,HIGH);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,HIGH);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,HIGH);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightLeftRed2()
{
  for(int i=0 ; i<3 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,HIGH);
      digitalWrite(Pin19,HIGH);
      digitalWrite(Pin20,HIGH);
      delay(lightDelay);
      TurnOff();
    }
    else if(i==1)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,HIGH);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,HIGH);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,HIGH);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightRightRed2()
{
  for(int i=0 ; i<3 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,HIGH);
      digitalWrite(Pin15,HIGH);
      digitalWrite(Pin16,HIGH);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else if(i==1)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,HIGH);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,HIGH);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,HIGH);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightLeftRed3()
{
  for(int i=0 ; i<2 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,HIGH);
      digitalWrite(Pin19,HIGH);
      digitalWrite(Pin20,HIGH);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,HIGH);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightRightRed3()
{
  for(int i=0 ; i<2 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,HIGH);
      digitalWrite(Pin15,HIGH);
      digitalWrite(Pin16,HIGH);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,HIGH);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightLeftRed4()
{
  for(int i=0 ; i<3 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,HIGH);
      delay(lightDelay);
      TurnOff();
    }
    else if(i==1)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,HIGH);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,HIGH);
      digitalWrite(Pin19,HIGH);
      digitalWrite(Pin20,HIGH);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,HIGH);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightRightRed4()
{
  for(int i=0 ; i<3 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,HIGH);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else if(i==1)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,HIGH);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,HIGH);
      digitalWrite(Pin15,HIGH);
      digitalWrite(Pin16,HIGH);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,HIGH);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightLeftRed5()
{
  for(int i=0 ; i<3 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,HIGH);
      digitalWrite(Pin19,HIGH);
      digitalWrite(Pin20,HIGH);
      delay(lightDelay);
      TurnOff();
    }
    else if(i==1)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,HIGH);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,HIGH);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,HIGH);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightRightRed5()
{
  for(int i=0 ; i<3 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,HIGH);
      digitalWrite(Pin15,HIGH);
      digitalWrite(Pin16,HIGH);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else if(i==1)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,HIGH);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,HIGH);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,HIGH);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightLeftRed6()
{
  for(int i=0 ; i<3 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,HIGH);
      digitalWrite(Pin19,HIGH);
      digitalWrite(Pin20,HIGH);
      delay(lightDelay);
      TurnOff();
    }
    else if(i==1)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,HIGH);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,HIGH);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,HIGH);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightRightRed6()
{
  for(int i=0 ; i<3 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,HIGH);
      digitalWrite(Pin15,HIGH);
      digitalWrite(Pin16,HIGH);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else if(i==1)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,HIGH);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,HIGH);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,HIGH);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightLeftRed7()
{
  for(int i=0 ; i<2 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,HIGH);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,HIGH);
      digitalWrite(Pin19,HIGH);
      digitalWrite(Pin20,HIGH);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,HIGH);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightRightRed7()
{
  for(int i=0 ; i<2 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,HIGH);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,HIGH);
      digitalWrite(Pin15,HIGH);
      digitalWrite(Pin16,HIGH);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,HIGH);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightLeftRed8()
{
  for(int i=0 ; i<2 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,HIGH);
      digitalWrite(Pin19,HIGH);
      digitalWrite(Pin20,HIGH);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,HIGH);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,HIGH);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightRightRed8()
{
  for(int i=0 ; i<2 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,HIGH);
      digitalWrite(Pin15,HIGH);
      digitalWrite(Pin16,HIGH);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,HIGH);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,HIGH);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}


void LightLeftRed9()
{
  for(int i=0 ; i<3 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,HIGH);
      delay(lightDelay);
      TurnOff();
    }
    else if(i==1)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,HIGH);
      digitalWrite(Pin19,HIGH);
      digitalWrite(Pin20,HIGH);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,HIGH);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}

void LightRightRed9()
{
  for(int i=0 ; i<3 ; i++)
  {
    if(i==0)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,LOW);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,HIGH);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else if(i==1)
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,HIGH);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,HIGH);
      digitalWrite(Pin23,HIGH);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,HIGH);
      digitalWrite(Pin15,HIGH);
      digitalWrite(Pin16,HIGH);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
    else
    {
      digitalWrite(Pin1,HIGH);
      digitalWrite(Pin2,HIGH);
      digitalWrite(Pin3,LOW);
      digitalWrite(Pin4,LOW);
      digitalWrite(Pin21,LOW);
      digitalWrite(Pin22,LOW);
      digitalWrite(Pin23,LOW);
      digitalWrite(Pin24,HIGH);
      digitalWrite(Pin5,LOW);
      digitalWrite(Pin6,LOW);
      digitalWrite(Pin7,LOW);
      digitalWrite(Pin8,LOW);
      digitalWrite(Pin9,LOW);
      digitalWrite(Pin10,LOW);
      digitalWrite(Pin11,LOW);
      digitalWrite(Pin12,LOW);
      digitalWrite(Pin13,LOW);
      digitalWrite(Pin14,HIGH);
      digitalWrite(Pin15,LOW);
      digitalWrite(Pin16,LOW);
      digitalWrite(Pin17,LOW);
      digitalWrite(Pin18,LOW);
      digitalWrite(Pin19,LOW);
      digitalWrite(Pin20,LOW);
      delay(lightDelay);
      TurnOff();
    }
  }
}
