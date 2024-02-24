const int TRIG=7;
const int ECHO=6;
const int LimitSettingPin=A0;
const int timeInput=A1;
int minDistance=0;
int maxDistance=1000;
int minTime=100;
int maxTime=2000;
long duration;
long distance;
int delay_time;
int flag = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,INPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
}

void loop()
{
  int distanceLimit;
  int currentDistance;
  boolean DistanceSensorEnabled = true;
  currentDistance = getDistance();
  distanceLimit = map(analogRead(LimitSettingPin), 0, 1023, minDistance,maxDistance);
  delay_time = map(analogRead(timeInput), 0, 1023, minTime,maxTime);
  Serial.println(distance);
  delay(10);
  
  if(flag == 0 && currentDistance < distanceLimit)
  {
    digitalWrite(13,HIGH);
    digitalWrite(12,HIGH);
    delay(delay_time);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
    flag = 1;
  }
  if(currentDistance > distanceLimit+100)
  {
    flag = 0;
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
    delay(10);
  }
}

long getDistance()
{
  digitalWrite(TRIG,LOW);
  delay(2);
  digitalWrite(TRIG,HIGH);
  delay(10);
  digitalWrite(TRIG,LOW);
  duration=pulseIn(ECHO,HIGH);
  distance=.343*(duration/2);
  return distance;
}
