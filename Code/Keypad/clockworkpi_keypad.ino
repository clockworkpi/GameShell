// CLOCKWORK Keypad Arduino driver
// For more information please visit https://forum.clockworkpi.com
// HAPPY HACKING

#include "UsbKeyboard.h"

#define KEY_ENTER           0x28    // Keyboard Return (ENTER)
#define KEY_ESCAPE          0x29    // Keyboard Escape
#define KEY_BACKSPACE       0x2A    // Keyboard Backspace
#define KEY_SPACE           0x2C    // Keyboard Space
#define KEY_DASH            0x2D    // Keyboard - and _
#define KEY_EQUAL           0x2E    // Keyboard = and +
#define KEY_HOME            0x4A    // Keyboard Home
#define KEY_PAGE_UP         0x4B    // Keyboard Page Up
#define KEY_END             0x4D    // Keyboard End
#define KEY_PAGE_DOWN       0x4E    // Keyboard Page Down
#define KEY_RIGHT_ARROW     0x4F    // Keyboard Right Arrow
#define KEY_LEFT_ARROW      0x50    // Keyboard Left Arrow
#define KEY_DOWN_ARROW      0x51    // Keyboard Down Arrow
#define KEY_UP_ARROW        0x52    // Keyboard Up Arrow
#define KEY_NUM_DASH        0x56    // Keyboard Num Pad -
#define KEY_NUM_PLUS        0x57    // Keyboard Num Pad +

#define KEY_OFF           1
#define KEY_ON            0
#define ADC_BOUNDARY      500
#define DIGITAL_KEY_NUM   9
#define ANALOG_KEY_NUM    6
#define KEY_NUM           (DIGITAL_KEY_NUM + ANALOG_KEY_NUM)
#define SHIFT_KEY_NUM     2
#define KEY_NULL          0xff

#define KEYPAD_UP     KEY_UP_ARROW
#define KEYPAD_LEFT   KEY_LEFT_ARROW
#define KEYPAD_DOWN   KEY_DOWN_ARROW
#define KEYPAD_RIGHT  KEY_RIGHT_ARROW
#define KEYPAD_Y      KEY_I
#define KEYPAD_X      KEY_U
#define KEYPAD_A      KEY_J
#define KEYPAD_B      KEY_K
#define KEYPAD_MENU   KEY_ESCAPE
#define KEYPAD_SELECT KEY_SPACE
#define KEYPAD_START  KEY_ENTER
#define KEYPAD_LIGHT1 KEY_L
#define KEYPAD_LIGHT2 KEY_O
#define KEYPAD_LIGHT4 KEY_Y
#define KEYPAD_LIGHT5 KEY_H

#define KEYPAD_UP_SHIFT     KEY_UP_ARROW
#define KEYPAD_LEFT_SHIFT   KEY_LEFT_ARROW
#define KEYPAD_DOWN_SHIFT   KEY_DOWN_ARROW
#define KEYPAD_RIGHT_SHIFT  KEY_RIGHT_ARROW
#define KEYPAD_Y_SHIFT      KEY_O
#define KEYPAD_X_SHIFT      KEY_Y
#define KEYPAD_A_SHIFT      KEY_H
#define KEYPAD_B_SHIFT      KEY_L
#define KEYPAD_MENU_SHIFT   KEY_BACKSPACE
#define KEYPAD_SELECT_SHIFT KEY_NUM_DASH
#define KEYPAD_START_SHIFT  KEY_NUM_PLUS
#define KEYPAD_LIGHT1_SHIFT KEY_END
#define KEYPAD_LIGHT2_SHIFT KEY_PAGE_DOWN
#define KEYPAD_LIGHT4_SHIFT KEY_PAGE_UP
#define KEYPAD_LIGHT5_SHIFT KEY_HOME

const int pins[KEY_NUM] = {3, 6, 7, 8, 9, 10, 11, 12, 13, 0, 2, 3, 4, 6, 7};
const int shift_pins[SHIFT_KEY_NUM] = {1, 5};

const int keys[KEY_NUM] = 
{
  KEYPAD_UP, KEYPAD_LEFT, KEYPAD_DOWN, KEYPAD_RIGHT, KEYPAD_Y, KEYPAD_X, KEYPAD_A, KEYPAD_B, KEYPAD_START, 
  KEYPAD_MENU, KEYPAD_SELECT, KEYPAD_LIGHT1, KEYPAD_LIGHT2, KEYPAD_LIGHT4, KEYPAD_LIGHT5
};
const int shift_keys[KEY_NUM] = 
{
  KEYPAD_UP_SHIFT, KEYPAD_LEFT_SHIFT, KEYPAD_DOWN_SHIFT, KEYPAD_RIGHT_SHIFT, KEYPAD_Y_SHIFT, KEYPAD_X_SHIFT, KEYPAD_A_SHIFT, KEYPAD_B_SHIFT, KEYPAD_START_SHIFT, 
  KEYPAD_MENU_SHIFT, KEYPAD_SELECT_SHIFT, KEYPAD_LIGHT1_SHIFT, KEYPAD_LIGHT2_SHIFT, KEYPAD_LIGHT4_SHIFT, KEYPAD_LIGHT5_SHIFT
};

int old_keys[KEY_NUM];

bool shift_key_pressed()
{
  for(int i = 0; i < SHIFT_KEY_NUM; i++)
  {
    if(analogRead(shift_pins[i]) /ADC_BOUNDARY == KEY_ON)
      return true;
  }
  return false;
}

void setup()
{
  TIMSK0 &= !(1 << TOIE0);

  for(int i = 0; i < KEY_NUM; i++)
  {
    if(i < DIGITAL_KEY_NUM)
    {
      pinMode(pins[i], INPUT);
    }
    old_keys[i] = KEY_NULL;
  }
  Serial.begin(115200);
}

void loop()
{
  int on_off, key;

  UsbKeyboard.update();
  delay(1000);

  for(int i = 0; i < KEY_NUM; i++)
  {
    if( i < DIGITAL_KEY_NUM)
    {
      on_off = digitalRead(pins[i]);
    }
    else
    {
      on_off = analogRead(pins[i])/ADC_BOUNDARY;
    }

    if(on_off == KEY_OFF)
    {
      if(old_keys[i] != KEY_NULL)
      {
        UsbKeyboard.release(old_keys[i]);
        old_keys[i] = KEY_NULL;
      }
    }
    else
    {
      if(shift_key_pressed())
      {
        key = shift_keys[i];
      }
      else
      {
        key = keys[i];
      }

      if(key != old_keys[i])
      {
        if(old_keys[i] != KEY_NULL)
        {
          UsbKeyboard.release(old_keys[i]);
        }
        UsbKeyboard.press(key);
        old_keys[i] = key;
      }
    }
  }
}
