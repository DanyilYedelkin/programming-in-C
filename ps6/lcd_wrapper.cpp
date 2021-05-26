#include <Arduino.h>
#include "lcd_wrapper.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

void lcd_init(){
  lcd.init();
  lcd.backlight();
  lcd_set_cursor(0,0);
}

void lcd_clear(){
  lcd.clear();
}


void lcd_set_cursor(int y, int x){
  lcd.setCursor(x,y);
}


void lcd_print(char* text){
  //Serial.println(text);
    lcd.print(text);
}


void lcd_print_at(int y, int x, char* text){
    lcd_set_cursor(y, x);
    lcd_print(text);
}

//for checking numbers   ==========================================
void lcd_print_numbers(int number){
  //Serial.println(text);
   lcd.print(number);
}


void lcd_print_at_numbers(int y, int x, int number){
    lcd_set_cursor(y, x);
    lcd_print_numbers(number);
}
