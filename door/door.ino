#define open_pin 11
#define close_pin 12
#define PIR_pin 2
#define PIR2_pin 4
#define hall_open_pin 5//returns zero if closed, one if open
#define hall_closed_pin 6//returns zero if closed, one if open
unsigned long time = millis();
void setup() {
  Serial.begin(9600);
  pinMode(open_pin, OUTPUT);
  pinMode(close_pin, OUTPUT);
  pinMode(PIR_pin, INPUT);
  pinMode(PIR2_pin, INPUT);
  pinMode(hall_open_pin, INPUT);
  pinMode(hall_closed_pin, INPUT);
  digitalWrite(open_pin, 0);//leave at fullpeed
  digitalWrite(close_pin, 0);//turn off motor

  //zeroes the iris at boot to whatever end it isn't near
    make_open();
    make_closed();

}

void loop() {
  if(millis() - time > 2000)//if timed out
  {
   // Serial.println("timed out");
      make_closed();
  }
  
 // if(digitalRead(PIR_pin)|digitalRead(PIR2_pin))//if movement
  if(digitalRead(PIR_pin)|digitalRead(PIR2_pin))//if movement
  {  
   // Serial.println("people!");
      make_open();
    time = millis();//reset timeout (from stop time)
  }
}

boolean iris_closed() {
  if(digitalRead(hall_closed_pin) == 0)
  {
    //Serial.println("iris closed");
    return 1;
  }
  else
  {
    //Serial.println("iris not closed");
    return 0;
  }
}

boolean iris_open() {
  if(digitalRead(hall_open_pin) == 0)
  {
    //Serial.println("iris open");
    return 1;
  }
  else
  {
    //Serial.println("iris not open");
    return 0;
  }
}

void make_open() {
  if (iris_open())
  {
    //Serial.println("iris already open");
    return;
  }
  else
  {
    //Serial.print("opening");
      digitalWrite(close_pin, 0);
      digitalWrite(open_pin, 1);//move
      while(!iris_open())//wait for open
      {
    //Serial.print(".");
      }
  //  Serial.println();
  //  Serial.println("iris finised opening");
      digitalWrite(open_pin, 0);//stop
  }
}

void make_closed() {
  if (iris_closed())
  {
   // Serial.println("iris already closed");
    return;
  }
  //  Serial.print("closing");
      digitalWrite(open_pin, 0);
      digitalWrite(close_pin, 1);//move
      while(!iris_closed())//wait for closed
      {
   // Serial.print(".");
      }
      //delayMicroseconds(1000);
  //  Serial.println();
   // Serial.println("iris finised closing");
      digitalWrite(close_pin, 0);//stop
}
