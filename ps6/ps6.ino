#include "mastermind.h"
#include "lcd_wrapper.h"
#include "wiring_private.h"
#include <time.h>
#include <stdbool.h>

bool get = false;

void setup() {
    Serial.begin(9600);

    pinMode(BTN_1_PIN,INPUT);
    pinMode(BTN_2_PIN,INPUT);
    pinMode(BTN_3_PIN,INPUT);
    pinMode(BTN_4_PIN,INPUT);
    pinMode(BTN_ENTER_PIN,INPUT);

    pinMode(LED_RED_1, OUTPUT);
    pinMode(LED_RED_2, OUTPUT);
    pinMode(LED_RED_3, OUTPUT);
    pinMode(LED_RED_4, OUTPUT);
    
    pinMode(LED_BLUE_1, OUTPUT);
    pinMode(LED_BLUE_2, OUTPUT);
    pinMode(LED_BLUE_3, OUTPUT);
    pinMode(LED_BLUE_4, OUTPUT);
    
    pinMode(LED_YELLOW_1, OUTPUT);
    
    lcd_init();
    turn_off_leds();

    char* code;
    play_game(code);
    //free(code);   
}

void loop(){
    srand(time(NULL));
    /*if(get == false){
        lcd_clear();
        char* code = generate_code(false, 4);
        play_game(code);
        free(code);
    }
    get = true;*/
}
