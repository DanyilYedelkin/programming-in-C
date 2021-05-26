#include "mastermind.h"
#include "lcd_wrapper.h"
#include <Arduino.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

/*
         _nnnn_                      
        dGGGGMMb     ,"""""""""""""".
       @p~qp~~qMb    | Linux Rules! |
       M|@||@) M|   _;..............'
       @,----.JM| -'
      JS^\__/  qKL
     dZP        qKRb
    dZP          qKKb
   fZP            SMMb
   HZM            MMMM
   FqM            MMMM
 __| ".        |\dS"qML
 |    `.       | `' \Zq
_)      \.___.,|     .'
\____   )MMMMMM|   .'
     `-'       `--' hjm

*/


char* generate_code(bool repeat, int length){
  if((length > 10 && repeat == 0) || length < 1) return NULL;

  char* number = (char*)calloc(length + 1, sizeof(char));
  randomSeed(analogRead(A2));

  if(repeat == true){
    for(int num = 0; num < length; num++){
      number[num] = (int)random(0, 10) + '0';
    }
  } else if(repeat == false){
    for(int num = 0; num < length; num++){
      number[num] = (int)random(0, 10) + '0';

      //function for checking repeat number in the code
      for(int i = 0; i < num; i++){
        if(number[i] == number[num]){
          number[num] = (int)random(0, 10) + '0';
          //return check number to first locating for new checking repeat number
          i = -1;
        }
      }
    }
  }

  //end-of-line initialization (initialization the end of the code number)
  number[length] = '\0';

  return number;
}

void get_score(const char* secret, const char* guess, int* peg_a, int* peg_b){
  if((secret == NULL) || (guess == NULL)) return;

  //clearing the garbage in the memory of two variables
  (*peg_a) = 0;
  (*peg_b) = 0;

  //creating arrays to test for numbers that have already been found 
  bool used_digids_guess[strlen(guess)];
  for(int i = 0; i < strlen(guess); i++) used_digids_guess[i] = false;
  bool used_digids_secret[strlen(guess)];
  for(int i = 0; i < strlen(guess); i++) used_digids_secret[i] = false;

  //checking digits that are repeated in two numbers at the same places  
  for(int i = 0; i < strlen(guess); i++){
    if(secret[i] == guess[i]){
      (*peg_a)++;
      used_digids_guess[i] = true;
      used_digids_secret[i] = true;
    }
  }

  //checking for digits that are assigned in two arrays, but in different places 
  for(int i = 0; i < strlen(guess); i++){
    //checking if a digit has already been used in guess
    if(used_digids_guess[i] == true) continue;

    for(int j = 0; j < strlen(secret); j++){
      //checking if a digit has already been used in secret
      if(used_digids_secret[j] == true) continue;

      if(secret[j] == guess[i]){
        (*peg_b)++;
        used_digids_guess[i] = true;
        used_digids_secret[j] = true;
        if(j < strlen(guess)) break;
      }
    }
  }

  //checking values of two numbers
  //lcd_print_at_numbers(0, 1, *peg_a);
  //lcd_print_at_numbers(1, 1, *peg_b);
}

void turn_off_leds(){
  //turn off all red leds
  digitalWrite(LED_RED_1, LOW);
  digitalWrite(LED_RED_2, LOW);
  digitalWrite(LED_RED_3, LOW);
  digitalWrite(LED_RED_4, LOW);

  //turn off all blue leds
  digitalWrite(LED_BLUE_1, LOW);
  digitalWrite(LED_BLUE_2, LOW);
  digitalWrite(LED_BLUE_3, LOW);
  digitalWrite(LED_BLUE_4, LOW);
}

void render_leds(const int peg_a, const int peg_b){
  turn_off_leds();
  
  //creating variables for peg_a and peg_b
  int red = peg_a;
  int blue = peg_b;

  //LED backlight test
  for(int i = LED_RED_1, j = LED_BLUE_1; i <= LED_RED_4, j <= LED_RED_4; i+=2, j+=2){
    if(red > 0){
      digitalWrite(i, HIGH);
      red--;
    } else if((blue > 0) && (red <= 0)){
      digitalWrite(j, HIGH);
      blue--;
    }
  }
}

void render_history(char* secret, char** history, const int entry_nr){
  if(secret == NULL) return;

  //creating an array and filling it with a number of the location of a given number from history 
  char hist_num[4] = {'0', '0', ':', '\0'};
  if(entry_nr < 10) hist_num[1] = entry_nr + '0';
  else{
    hist_num[0] = '1';
    hist_num[1] = '0';
  }

  //output the serial number of the desired number from history and the number itself 
  lcd_print_at(0,0, hist_num);
  lcd_print_at(0, 4, history[entry_nr]);

  //creating variables for function get_score
  int peg_a = 0, peg_b = 0;

  get_score(secret, history[entry_nr], &peg_a, &peg_b);
  render_leds(peg_a, peg_b);
}

void begin(){
  lcd_init();
  lcd_clear();
  char* welcome = "Welcome to";
  lcd_print_at(0, 1, welcome);
  delay(1000);
  char* welcome2 = "Mastermind :D";
  lcd_print_at(1, 3, welcome2);
  for(int i = 0; i < 5; i++){
    digitalWrite(LED_RED_1, HIGH);
    digitalWrite(LED_RED_3, HIGH);
    digitalWrite(LED_BLUE_2, HIGH);
    digitalWrite(LED_BLUE_4, HIGH);
    delay(300);
    digitalWrite(LED_RED_2, HIGH);
    digitalWrite(LED_RED_4, HIGH);
    digitalWrite(LED_RED_1, LOW);
    digitalWrite(LED_RED_3, LOW);
    digitalWrite(LED_BLUE_2, LOW);
    digitalWrite(LED_BLUE_4, LOW);
    delay(300);
    digitalWrite(LED_RED_2, LOW);
    digitalWrite(LED_RED_4, LOW);
    digitalWrite(LED_BLUE_1, LOW);
    digitalWrite(LED_BLUE_3, LOW);
  }

  lcd_clear();
  
  lcd_print_at(0, 2, "Time to play");
  int repeat = 0;
  
  while(digitalRead(BTN_ENTER_PIN) != HIGH){
    if (repeat == 0){
      lcd_print_at(1, 0, "Press ENTER...");
      repeat = 1;
    } else{
      lcd_print_at(1, 0, "              ");
      repeat = 0;
    }
    
    digitalWrite(LED_RED_1, HIGH);
    delay(150);
    digitalWrite(LED_RED_1, LOW);
    delay(50);
    digitalWrite(LED_RED_2, HIGH);
    delay(150);
    digitalWrite(LED_RED_2, LOW);
    delay(50);
    digitalWrite(LED_RED_3, HIGH);
    delay(150);
    digitalWrite(LED_RED_3, LOW);
    delay(50);
    digitalWrite(LED_RED_4, HIGH);
    delay(150);
    digitalWrite(LED_RED_4, LOW);
    delay(50);

    if (repeat == 0){
      lcd_print_at(1, 0, "Press ENTER...");
      repeat = 1;
    } else{
      lcd_print_at(1, 0, "              ");
      repeat = 0;
    }

    if(digitalRead(BTN_ENTER_PIN) == HIGH) break;
    
    digitalWrite(LED_BLUE_4, HIGH);
    delay(150);
    digitalWrite(LED_BLUE_4, LOW);
    delay(50);
    digitalWrite(LED_BLUE_3, HIGH);
    delay(150);
    digitalWrite(LED_BLUE_3, LOW);
    delay(50);
    digitalWrite(LED_BLUE_2, HIGH);
    delay(150);
    digitalWrite(LED_BLUE_2, LOW);
    delay(50);
    digitalWrite(LED_BLUE_1, HIGH);
    delay(150);
    digitalWrite(LED_BLUE_1, LOW);
    delay(50);
    
    if(digitalRead(BTN_ENTER_PIN) == HIGH) break;

    delay(300);
  }
  
  lcd_clear();
  turn_off_leds();
  delay(1000);
}

//create functions
void first_button(int input_array[], char array[]);
void second_button(int input_array[], char array[]);
void third_button(int input_array[], char array[]);
void fourth_button(int input_array[], char array[]);
void final_scene(char* secret, int win);
void last_printf();

void yellow_grown(){
    digitalWrite(LED_YELLOW_1, HIGH);
    delay(150);
    digitalWrite(LED_YELLOW_1, LOW);
    delay(50);
    digitalWrite(LED_YELLOW_1, HIGH);
    delay(150);
    digitalWrite(LED_YELLOW_1, LOW);
    delay(50);
    digitalWrite(LED_YELLOW_1, HIGH);
    delay(150);
    digitalWrite(LED_YELLOW_1, LOW);
    delay(50);
    digitalWrite(LED_YELLOW_1, HIGH);
    delay(150);
    digitalWrite(LED_YELLOW_1, LOW);
    delay(50);
}

void printf_array(char array[]){
  //lcd_clear();
  lcd_print_at(1, 0, "Your guess:");
  lcd_print_at(1, 12, array);
}

void play_game(char* secret){
  //if(secret == NULL) return;

  secret = generate_code(false, 4);

  digitalWrite(LED_YELLOW_1, HIGH);
  begin();

  int array_number[4] = {0,0,0,0};
  int win = 0;
  char* array = (char*)calloc(strlen(secret) + 1, sizeof(char));
  for(int i = 0; i < strlen(secret); i++){
    array[i] = '0';
  }
  int peg_a = 0, peg_b = 0, guess_count = 0, history_list = 0;
  bool check_enter = false;

  char** history = (char**)calloc(10, sizeof(char*));
  char* guess_num_history = (char*)calloc(4, sizeof(char));
  guess_num_history[0] = '0';
  guess_num_history[2] = ':';
  
  for (int i = 0; i < 10; i++) {
    history[i] = (char*)calloc(strlen(secret)+1, sizeof(char));
  }
  
  while(guess_count < 10){
    
    turn_off_leds();
    printf_array(array);
    while(digitalRead(BTN_ENTER_PIN) != HIGH){
      if(digitalRead(BTN_1_PIN) == HIGH){
        int added = 0;
         //first_button(array_number, array);
         //printf_array(array);
         while(digitalRead(BTN_1_PIN) == HIGH){
            if((digitalRead(BTN_2_PIN) == HIGH) && (digitalRead(BTN_3_PIN) != HIGH)){
                if(history_list > 0){
                    history_list--;
                    render_history(secret, history, history_list);
                }
                added = 0;
            } else if((digitalRead(BTN_2_PIN) != HIGH) && (digitalRead(BTN_3_PIN) == HIGH)){
                if(history_list < 10 && guess_count > 1 && (history_list + 1) < guess_count){
                    history_list++;
                    render_history(secret, history, history_list);
                }
                added = 0;
            } else added = 1;
            delay(160);
         } 
         if(added == 1){
            first_button(array_number, array);
            printf_array(array);
         }
         //first_button(array_number, array);
         //printf_array(array);
      }
      if(digitalRead(BTN_2_PIN ) == HIGH){
         second_button(array_number, array);
         printf_array(array);
      }
      if(digitalRead(BTN_3_PIN) == HIGH){
         third_button(array_number, array);
         printf_array(array);
      }
      if(digitalRead(BTN_4_PIN) == HIGH){
         fourth_button(array_number, array);
         printf_array(array);  
      }
      delay(50);
      check_enter = true;
   }
   
   if(check_enter = true){
      history_list = guess_count;
      strncpy(history[guess_count], array, strlen(secret));
      
     get_score(secret, array, &peg_a,&peg_b);
     //lcd_clear();
     
     render_leds(peg_a, peg_b);
      if(guess_count < 10){
        guess_num_history[1] = guess_count + '0';
      } else{
        guess_num_history[0] = '1';
        guess_num_history[1] = '0';
      }
      lcd_print_at(0,0, guess_num_history);
      lcd_print_at(0, 4, array);
      char pokus[3] = {'0', '0', '\0'};
      if(guess_count < 9){
        pokus[1] = (guess_count + 1) + '0';
      } else{
        pokus[0] = '1';
        pokus[1] = '0';
      }
      pokus[2] = '\0';
      lcd_print_at(0, 14, pokus);
      for(int i = 0; i < 5; i++){
          array[i] = '0';
      }
      array[4] = '\0';
      
      for(int i = 0; i < 5; i++){
          array_number[i] = 0;
      }
      array_number[4] = '\0';
      //lcd_print_at(0, 4, array);
      
     /*char number[1];
     number[0] = (10 - guess_count) + '0';
     number[1] = '\0';*/
     if(peg_a == 4){
       win = 1;
       break;  
     }
     /*lcd_print(secret);
     lcd_set_cursor(1,0);
     lcd_print_at(1,5,number);*/
     
     guess_count++;
     delay(1200);
    }
  }

  delay(2000);

  for(int i = 0; i < 10; i++) {
    free(history[i]);
    history[i] = NULL;
  }
  free(history);
  free(guess_num_history);
  free(array);
  
  digitalWrite(LED_YELLOW_1, LOW);
  turn_off_leds();
  final_scene(secret, win);

  yellow_grown();
  lcd_clear();
}

void final_scene(char* secret, int win){
  lcd_clear();
  if(win == 1){
    lcd_print_at(0, 0, "Congratulations");
    delay(1000);
    lcd_print_at(1, 3, "You WIN :D");
  } else{
    lcd_clear();
    lcd_print_at(0, 1, "secret was:");
    delay(700);
    lcd_print_at(1, 11, secret);
    delay(2000);
    lcd_clear();
    lcd_print_at(0, 4, "Game Over");
    delay(1000);
    lcd_print_at(1, 5, "Nevermind");
  }

  for(int i = 0; i < 5; i++){
    digitalWrite(LED_RED_1, HIGH);
    digitalWrite(LED_RED_3, HIGH);
    digitalWrite(LED_BLUE_2, HIGH);
    digitalWrite(LED_BLUE_4, HIGH);
    delay(300);
    digitalWrite(LED_RED_2, HIGH);
    digitalWrite(LED_RED_4, HIGH);
    digitalWrite(LED_RED_1, LOW);
    digitalWrite(LED_RED_3, LOW);
    digitalWrite(LED_BLUE_2, LOW);
    digitalWrite(LED_BLUE_4, LOW);
    delay(300);
    digitalWrite(LED_RED_2, LOW);
    digitalWrite(LED_RED_4, LOW);
    digitalWrite(LED_BLUE_1, LOW);
    digitalWrite(LED_BLUE_3, LOW);
  }

  lcd_clear();
  
  //lcd_print_at(0, 1, "To try again:");
  int repeat = 0;
  int repeat2 = 0;
  int ENTER = 0;
  int QUIT = 0;
  
  while(1){
    lcd_clear();
    delay(100);
    if (repeat == 0){
      lcd_print_at(0, 1, "ENTER to P.A.");
      repeat = 1;
    } else{
      lcd_print_at(0, 1, "             ");
      repeat = 0;
    }
    if (repeat2 == 0){
      lcd_print_at(1, 3, "B_1 to QUIT");
      repeat2 = 1;
    } else{
      lcd_print_at(1, 3, "           ");
      repeat2 = 0;
    }
    
    if(digitalRead(BTN_ENTER_PIN) == HIGH){
      ENTER = 1;
      break;
    };
    if(digitalRead(BTN_1_PIN) == HIGH){
      QUIT = 1;
      break;
    };
    
    digitalWrite(LED_RED_1, HIGH);
    delay(150);
    digitalWrite(LED_RED_1, LOW);
    delay(50);
    digitalWrite(LED_RED_2, HIGH);
    delay(150);
    digitalWrite(LED_RED_2, LOW);
    delay(50);
    digitalWrite(LED_RED_3, HIGH);
    delay(150);
    digitalWrite(LED_RED_3, LOW);
    delay(50);
    digitalWrite(LED_RED_4, HIGH);
    delay(150);
    digitalWrite(LED_RED_4, LOW);
    delay(50);

    if (repeat == 0){
      lcd_print_at(1, 0, "ENTER to P.A.");
      repeat = 1;
    } else{
      lcd_print_at(1, 0, "              ");
      repeat = 0;
    }
    if (repeat2 == 0){
      lcd_print_at(1, 3, "B_1 to QUIT");
      repeat2 = 1;
    } else{
      lcd_print_at(1, 3, "           ");
      repeat2 = 0;
    }

    if(digitalRead(BTN_ENTER_PIN) == HIGH){
      ENTER = 1;
      break;
    };
    if(digitalRead(BTN_1_PIN) == HIGH){
      QUIT = 1;
      break;
    };
    
    digitalWrite(LED_BLUE_4, HIGH);
    delay(150);
    digitalWrite(LED_BLUE_4, LOW);
    delay(50);
    digitalWrite(LED_BLUE_3, HIGH);
    delay(150);
    digitalWrite(LED_BLUE_3, LOW);
    delay(50);
    digitalWrite(LED_BLUE_2, HIGH);
    delay(150);
    digitalWrite(LED_BLUE_2, LOW);
    delay(50);
    digitalWrite(LED_BLUE_1, HIGH);
    delay(150);
    digitalWrite(LED_BLUE_1, LOW);
    delay(50);
    
    if(digitalRead(BTN_ENTER_PIN) == HIGH){
      ENTER = 1;
      break;
    };
    if(digitalRead(BTN_1_PIN) == HIGH){
      QUIT = 1;
      break;
    };

    delay(300);
  }
  
  lcd_clear();
  turn_off_leds();
  delay(1000);

  free(secret);

  if(QUIT == 1){
    lcd_print_at(0, 3, "Goodbye :D");
    delay(1000);
    last_printf();

    delay(1000);
    return;
  } else if(ENTER == 1){
    char* code;
    play_game(code);
  }
}

void last_printf(){
  for(int i = 0; i < 5; i++){
    digitalWrite(LED_RED_1, HIGH);
    digitalWrite(LED_RED_3, HIGH);
    digitalWrite(LED_BLUE_2, HIGH);
    digitalWrite(LED_BLUE_4, HIGH);
    delay(300);
    digitalWrite(LED_RED_2, HIGH);
    digitalWrite(LED_RED_4, HIGH);
    digitalWrite(LED_RED_1, LOW);
    digitalWrite(LED_RED_3, LOW);
    digitalWrite(LED_BLUE_2, LOW);
    digitalWrite(LED_BLUE_4, LOW);
    delay(300);
    digitalWrite(LED_RED_2, LOW);
    digitalWrite(LED_RED_4, LOW);
    digitalWrite(LED_BLUE_1, LOW);
    digitalWrite(LED_BLUE_3, LOW);
  }  
}

void first_button(int input_array[], char array[]){
  input_array[0] = input_array[0] + 1;
  if(input_array[0] > 9) input_array[0] = 0;
  array[0] = input_array[0] + '0';
  delay(150);
  array[4] = '\0';
}

void second_button(int input_array[], char array[]){
  input_array[1] = input_array[1] + 1;
  if(input_array[1] > 9) input_array[1] = 0;
  array[1] = input_array[1] + '0';
  delay(150);
  array[4] = '\0';
}

void third_button(int input_array[], char array[]){
  input_array[2] = input_array[2] + 1;
  if(input_array[2] > 9) input_array[2] = 0;
  array[2] = input_array[2] + '0';
  delay(150);
  array[4] = '\0';
}

void fourth_button(int input_array[], char array[]){
  input_array[3] = input_array[3] + 1;
  if(input_array[3] > 9) input_array[3] = 0;
  array[3] = input_array[3] + '0';
  delay(150);
  array[4] = '\0';
}
