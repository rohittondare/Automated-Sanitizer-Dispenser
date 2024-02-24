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
  //digitalWrite(13,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH);
  delay(15);
  digitalWrite(13,LOW);
  delay(20);
  digitalWrite(13,HIGH);
  delay(15);
  digitalWrite(13,LOW);  
 }

void loop()
{
  int distanceLimit;
 int currentDistance;
 boolean DistanceSensorEnabled = true;
     
  currentDistance = getDistance();
  distanceLimit = map(analogRead(LimitSettingPin), 0, 1023, minDistance,maxDistance);
  delay_time = map(analogRead(timeInput), 0, 1023, minTime,maxTime);
  Serial.println(currentDistance);
  delay(10);
  
  if(flag == 4 && currentDistance < distanceLimit && currentDistance != 0)
  {
    digitalWrite(13,HIGH);
    digitalWrite(12,HIGH);
    Serial.println("in");
    delay(delay_time);
    digitalWrite(12,LOW);
    digitalWrite(13,LOW);
    flag = 0;
    delay(1000);
    Serial.print("end");
  }
  if(currentDistance > distanceLimit+100)
  {
    if(flag < 4)
    {
      flag++;
    }
    Serial.print("flag:");
    Serial.println(flag);
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
