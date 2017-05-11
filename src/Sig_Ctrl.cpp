#include <Arduino.h>
#include <Button.h>

#define BTN1 1
#define BTN2 2
#define BTN3 3
#define BTN4 4 //change these values

#define RELAY_1 5
#define RELAY_2 6
#define RELAY_3 7
#define RELAY_4 8
#define RELAY_5 9
#define RELAY_6 10 //change these values

#define PULLUP true
#define INVERT true
#define SOLID  1
#define FLASH  2
#define RED    1
#define YELLOW 2
#define GREEN  3

#define DEBOUNCE_MS 20

int bulb1_state = SOLID;
int bulb2_state = SOLID;

int bulb1_color = RED;
int bulb2_color = RED;

Button toggle1(BTN1, PULLUP, INVERT, DEBOUNCE_MS);
Button toggle2(BTN2, PULLUP, INVERT, DEBOUNCE_MS);
Button toggle3(BTN3, PULLUP, INVERT, DEBOUNCE_MS);
Button toggle4(BTN4, PULLUP, INVERT, DEBOUNCE_MS);

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
    if (b1 == 2)
    {
      bulb1_state = FLASH;
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
    if (b2 == 2)
    {
      bulb2_state = FLASH;
    }
    else
    {
      b2 = 0;
    }
  }
}

void change_color()
{

}

void primary_relay_ctrl()
{

}

void secondary_relay_ctrl()
{

}
