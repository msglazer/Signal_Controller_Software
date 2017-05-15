#include <Arduino.h>
#include <Button.h>
//--------------------------Button Pins-------------------------------
#define BTN1 3                      // xx
#define BTN2 2                      // xx
#define BTN3 0                      // xx
#define BTN4 1 //pin values for rev1a  xx  for 1b

//--------------------------Button Setup-------------------------------
#define PULLUP true
#define INVERT true
#define DEBOUNCE_MS 20

//--------------------------Relay Pins-------------------------------
#define RELAY_1 4                     //  xx
#define RELAY_2 29                    //  xx
#define RELAY_3 25                    //  xx
#define RELAY_4 8                     //  xx
#define RELAY_5 9                     //  xx
#define RELAY_6 10 //pin values for rev1a xx for 1b

//--------------------------Bulb Status-------------------------------
#define SOLID  1
#define FLASH  2
#define OFF    3

int bulb1_state = SOLID;
int bulb2_state = SOLID;

int b1 = 0;
int b2 = 0;
int b3 = 0;
int b4 = 0;

//--------------------------Bulb Color-------------------------------
#define RED    1
#define YELLOW 2
#define GREEN  3

int bulb1_color = RED;
int bulb2_color = RED;

//--------------------------Time Stuff-------------------------------
#define FLASH_DURATION 750

byte RELAY_1_STATE = LOW;
byte RELAY_4_STATE = LOW;

unsigned long currentMillis = 0;
unsigned long previous_R1_millis = 0;
unsigned long previous_R4_millis = 0;



Button toggle1(BTN1, PULLUP, INVERT, DEBOUNCE_MS);
Button toggle2(BTN2, PULLUP, INVERT, DEBOUNCE_MS);
Button toggle3(BTN3, PULLUP, INVERT, DEBOUNCE_MS);
Button toggle4(BTN4, PULLUP, INVERT, DEBOUNCE_MS);

//--------------------------Functions-------------------------------
void change_flashing();
void change_color();
void primary_relay_ctrl(int state, int color);
void secondary_relay_ctrl(int state, int color);
void relay_flash();


void setup(void)
{
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);
  pinMode(RELAY_5, OUTPUT);
  pinMode(RELAY_6, OUTPUT);

  Serial.begin(9600);
}

void loop(void)
{
  currentMillis = millis();

  toggle1.read(); // primary   flash
  toggle2.read(); // secondary flash
  toggle3.read(); // primary   color
  toggle4.read(); // secondary color

  change_flashing();
  change_color();
  primary_relay_ctrl(bulb1_state, bulb1_color);
  secondary_relay_ctrl(bulb2_state, bulb2_color);

  /*Serial.print("1st bulb state"); Serial.println(bulb1_state);
  Serial.print("2nd bulb state"); Serial.println(bulb2_state);
  Serial.print("1st bulb color"); Serial.println(bulb1_color);
  Serial.print("2nd bulb color"); Serial.println(bulb2_color);*/
}

void change_flashing()
{
  if (toggle1.wasReleased())
  {
    b1++;
    Serial.print("button 1 pressed"); Serial.println(b1);
    if (b1 == 1)
    {
      bulb1_state = SOLID;
    }
    else if (b1 == 2)
    {
      bulb1_state = FLASH;
    }
    else if (b1 == 3)
    {
      bulb1_state = OFF;
    }
    else
    {
      b1 = 0;
    }
  }
  if (toggle2.wasReleased())
  {
    b2++;
    Serial.print("button 2 pressed"); Serial.println(b2);
    if (b2 == 1)
    {
      bulb2_state = SOLID;
    }
    else if (b2 == 2)
    {
      bulb2_state = FLASH;
    }
    else if (b2 == 3)
    {
      bulb2_state = OFF;
    }
    else
    {
      b2 = 0;
    }
  }
}

void change_color()
{
  if (toggle3.wasReleased())
  {
    b3++;
    Serial.print("button 3 pressed"); Serial.println(b3);
    if (b3 == 1)
    {
      bulb1_color = RED;
    }
    else if (b3 == 2)
    {
      bulb1_color = YELLOW;
    }
    else if (b3 == 3)
    {
      bulb1_color = GREEN;
    }
    else
    {
      b3 = 0;
    }
  }
  if (toggle4.wasReleased())
  {
    b4++;
    Serial.print("button 4 pressed"); Serial.println(b4);
    if (b4 == 1)
    {
      bulb2_color = RED;
    }
    else if (b4 == 2)
    {
      bulb2_color = YELLOW;
    }
    else if (b4 == 3)
    {
      bulb2_color = GREEN;
    }
    else
    {
      b4 = 0;
    }
  }
}

void relay_1_flash()//better name?
{
  if (RELAY_1_STATE == LOW)
  {
    if (currentMillis - previous_R1_millis >= FLASH_DURATION)
    {
      RELAY_1_STATE = HIGH;
      previous_R1_millis = currentMillis;
    }
  }
  //make things blink using millis()
}

void relay_4_flash()//better name?
{
  if (RELAY_4_STATE == LOW)
  {
    if (currentMillis - previous_R4_millis >= FLASH_DURATION)
    {
      RELAY_4_STATE = HIGH;
      previous_R4_millis = currentMillis;
    }
  }
  //make things blink using millis()
}

void primary_relay_ctrl(int state, int color)
{
  if(state == OFF)
  {
    digitalWrite(RELAY_1, LOW);
  }
  else if(state == SOLID)
  {
    digitalWrite(RELAY_1, HIGH);
  }
  else if(state == FLASH)
  {
    relay_1_flash();
  }
  Serial.print("primary state"); Serial.println(state);

  if(color == RED)
  {
    digitalWrite(RELAY_2, LOW);
    digitalWrite(RELAY_3, LOW);
  }
  else if(color == YELLOW)
  {
    digitalWrite(RELAY_2, HIGH);
    digitalWrite(RELAY_3, LOW);
  }
  else if(color == GREEN)
  {
    digitalWrite(RELAY_2, LOW);
    digitalWrite(RELAY_3, HIGH);
  }
  //Serial.print("primary color"); Serial.println(color);
}

void secondary_relay_ctrl(int state, int color)
{
  if(state == OFF)
  {
    digitalWrite(RELAY_4, LOW);
  }
  else if(state == SOLID)
  {
    digitalWrite(RELAY_4, HIGH);
  }
  else if(state == FLASH)
  {
    relay_4_flash();
  }

  if(color == RED)
  {
    digitalWrite(RELAY_5, LOW);
    digitalWrite(RELAY_6, LOW);
  }
  else if(color == YELLOW)
  {
    digitalWrite(RELAY_5, HIGH);
    digitalWrite(RELAY_6, LOW);
  }
  else if(color == GREEN)
  {
    digitalWrite(RELAY_5, LOW);
    digitalWrite(RELAY_6, HIGH);
  }
}
