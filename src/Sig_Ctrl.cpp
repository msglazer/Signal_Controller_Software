#include <Arduino.h>
#include <Button.h>
//--------------------------Button Pins-------------------------------
#define BTN1 1
#define BTN2 2
#define BTN3 3
#define BTN4 4 //change these values

//--------------------------Button Setup-------------------------------
#define PULLUP true
#define INVERT true
#define DEBOUNCE_MS 20

//--------------------------Relay Pins-------------------------------
#define RELAY_1 5
#define RELAY_2 6
#define RELAY_3 7
#define RELAY_4 8
#define RELAY_5 9
#define RELAY_6 10 //change these values

//--------------------------Bulb Status-------------------------------
#define SOLID  1
#define FLASH  2
#define OFF    3

int bulb1_state = SOLID;
int bulb2_state = SOLID;

//--------------------------Bulb Color-------------------------------
#define RED    1
#define YELLOW 2
#define GREEN  3

int bulb1_color = RED;
int bulb2_color = RED;


Button toggle1(BTN1, PULLUP, INVERT, DEBOUNCE_MS);
Button toggle2(BTN2, PULLUP, INVERT, DEBOUNCE_MS);
Button toggle3(BTN3, PULLUP, INVERT, DEBOUNCE_MS);
Button toggle4(BTN4, PULLUP, INVERT, DEBOUNCE_MS);

//--------------------------Functions-------------------------------
void change_flashing();
void change_color();
void primary_relay_ctrl(int state, int color);
void secondary_relay_ctrl(int state, int color);


void setup(void)
{
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);
  pinMode(RELAY_5, OUTPUT);
  pinMode(RELAY_6, OUTPUT);
}

void loop(void)
{
  toggle1.read();
  toggle2.read();
  toggle3.read();
  toggle4.read();

  change_flashing();
  change_color();
  primary_relay_ctrl(bulb1_state, bulb1_color);
  secondary_relay_ctrl(bulb2_state, bulb2_color);
}

void change_flashing()
{
  int b1 = 0;
  int b2 = 0;

  if (toggle1.wasReleased())
  {
    b1++;

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

    if (b2 == 1)
    {
      bulb2_state = SOLID;
    }
    else if (b2 == 2)
    {
      bulb2_state = FLASH;
    }
    else if (b1 == 3)
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
  int b1 = 0;
  int b2 = 0;

  if (toggle3.wasReleased())
  {
    b1++;

    if (b1 == 1)
    {
      bulb1_color = RED;
    }
    else if (b1 == 2)
    {
      bulb1_color = YELLOW;
    }
    else if (b1 == 3)
    {
      bulb1_color = GREEN;
    }
    else
    {
      b1 = 0;
    }
  }
  if (toggle4.wasReleased())
  {
    b2++;

    if (b2 == 1)
    {
      bulb2_color = RED;
    }
    else if (b2 == 2)
    {
      bulb2_color = YELLOW;
    }
    else if (b2 == 3)
    {
      bulb2_color = GREEN;
    }
    else
    {
      b2 = 0;
    }
  }
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
    analogWrite(RELAY_1,127);
  }

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
    analogWrite(RELAY_4,127);
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
