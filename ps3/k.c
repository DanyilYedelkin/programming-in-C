#include <stdlib.h>
#include <stdio.h>
#include "k.h"

void add_random_tile(struct game *game){
    int row, col;
    // find random, but empty tile
    do{
        row = rand() % SIZE;
        col = rand() % SIZE;
    }while(game->board[row][col] != ' ');

    // place to the random position 'A' or 'B' tile
    if(rand() % 2 == 0){
        game->board[row][col] = 'A';
    }else{
        game->board[row][col] = 'B';
    }
}

bool is_game_won(const struct game game){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(game.board[i][j] == 'K') return true;
        }
    }
    return false;
}
bool is_move_possible(const struct game game){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(game.board[i][j] == ' ' || game.board[i][j] == game.board[i+1][j] || game.board[i][j] == game.board[i][j+1]) return true;
        }
    }
    return false;
}
bool update(struct game *game, int dy, int dx){
    if((dx == 0 && dy == 0) || (dx != 0 && dy != 0)) return false;
    int check = 0;

    if(dx == 1){
        for(int i = 0; i < SIZE; i++){
            for(int j = (SIZE - 1); j >= 0; j--){
                if(game->board[i][j] == ' '){
                    if(game->board[i][j-1] == ' ' && (j - 1) >= 0){
                        if(game->board[i][j-2] == ' ' && (j - 2) >= 0){
                            if(game->board[i][j-3] != ' ' && (j - 3) >= 0){
                                game->board[i][j] = game->board[i][j-3];
                                game->board[i][j-3] = ' ';
                            }
                        } else if((j - 2) >= 0){
                            game->board[i][j] = game->board[i][j-2];
                            game->board[i][j-2] = ' ';
                        }
                    } else if((j - 1) >= 0){
                        game->board[i][j] = game->board[i][j-1];
                        game->board[i][j-1] = ' ';
                    }
                }
            }
            for(int j = (SIZE - 1); j >= 0; j--){
                if((game->board[i][j] == game->board[i][j-1]) && game->board[i][j] != ' ' && game->board[i][j-1] != ' '){
                    //letter: A B C D E F G H I J K
                    //score: 2 4 8 16 32 64 128 256 512 1024 2048
                    char letter = game->board[i][j];
                    int new_letter = (int)letter + 1;
                    letter = (char)new_letter;
                    //letter "A" can't be, so we don't use it
                    if(letter == 'B') game->score = game->score + 4;
                    if(letter == 'C') game->score = game->score + 8;
                    if(letter == 'D') game->score = game->score + 16;
                    if(letter == 'E') game->score = game->score + 32;
                    if(letter == 'F') game->score = game->score + 64;
                    if(letter == 'G') game->score = game->score + 128;
                    if(letter == 'H') game->score = game->score + 256;
                    if(letter == 'I') game->score = game->score + 512;
                    if(letter == 'J') game->score = game->score + 1024;
                    if(letter == 'K') game->score = game->score + 2048;
                    game->board[i][j] = letter;
                    game->board[i][j-1] = ' ';
                    check += 1;
                }
            }
            // flip all letters in one direction so that there is no space (" ") between them 
            for(int j = (SIZE - 1); j >= 0; j--){
                if(game->board[i][j] == ' '){
                    if(game->board[i][j-1] == ' ' && (j - 1) >= 0){
                        if(game->board[i][j-2] == ' ' && (j - 2) >= 0){
                            if(game->board[i][j-3] != ' ' && (j - 3) >= 0){
                                game->board[i][j] = game->board[i][j-3];
                                game->board[i][j-3] = ' ';
                            }
                        } else if((j - 2) >= 0){
                            game->board[i][j] = game->board[i][j-2];
                            game->board[i][j-2] = ' ';
                        }
                    } else if((j - 1) >= 0){
                        game->board[i][j] = game->board[i][j-1];
                        game->board[i][j-1] = ' ';
                    }
                }
            }
        }
    } else if(dx == -1){
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                if(game->board[i][j] == ' '){
                    if(game->board[i][j+1] == ' ' && (j + 1) < SIZE){
                        if(game->board[i][j+2] == ' ' && (j + 2) < SIZE){
                            if(game->board[i][j+3] != ' ' && (j + 3) < SIZE){
                                game->board[i][j] = game->board[i][j+3];
                                game->board[i][j+3] = ' ';
                            }
                        } else if((j + 2) < SIZE){
                            game->board[i][j] = game->board[i][j+2];
                            game->board[i][j+2] = ' ';
                        }
                    } else if((j + 1) < SIZE){
                        game->board[i][j] = game->board[i][j+1];
                        game->board[i][j+1] = ' ';
                    }
                }
            }
            for(int j = 0; j < SIZE; j++){
                if((game->board[i][j] == game->board[i][j+1]) && game->board[i][j] != ' ' && game->board[i][j+1] != ' '){
                    //letter: A B C D E F G H I J K
                    //score: 2 4 8 16 32 64 128 256 512 1024 2048
                    char letter = game->board[i][j];
                    int new_letter = (int)letter + 1;
                    letter = (char)new_letter;
                    //letter "A" can't be, so we don't use it
                    if(letter == 'B') game->score = game->score + 4;
                    if(letter == 'C') game->score = game->score + 8;
                    if(letter == 'D') game->score = game->score + 16;
                    if(letter == 'E') game->score = game->score + 32;
                    if(letter == 'F') game->score = game->score + 64;
                    if(letter == 'G') game->score = game->score + 128;
                    if(letter == 'H') game->score = game->score + 256;
                    if(letter == 'I') game->score = game->score + 512;
                    if(letter == 'J') game->score = game->score + 1024;
                    if(letter == 'K') game->score = game->score + 2048;
                    game->board[i][j] = letter;
                    game->board[i][j+1] = ' ';
                    check += 1;
                }
            }
            // flip all letters in one direction so that there is no space (" ") between them 
            for(int j = 0; j < SIZE; j++){
                if(game->board[i][j] == ' '){
                    if(game->board[i][j+1] == ' ' && (j + 1) < SIZE){
                        if(game->board[i][j+2] == ' ' && (j + 2) < SIZE){
                            if(game->board[i][j+3] != ' ' && (j + 3) < SIZE){
                                game->board[i][j] = game->board[i][j+3];
                                game->board[i][j+3] = ' ';
                            }
                        } else if((j + 2) < SIZE){
                            game->board[i][j] = game->board[i][j+2];
                            game->board[i][j+2] = ' ';
                        }
                    } else if((j + 1) < SIZE){
                        game->board[i][j] = game->board[i][j+1];
                        game->board[i][j+1] = ' ';
                    }
                }
            }
        }
    } else if(dy == 1){
        for(int i = (SIZE - 1); i >= 0; i--){
            for(int j = 0; j < SIZE; j++){
                if(game->board[i][j] == ' '){
                    if(game->board[i-1][j] == ' ' && (i - 1) >= 0){
                        if(game->board[i-2][j] == ' ' && (i - 2) >= 0){
                            if(game->board[i-3][j] != ' ' && (i - 3) >= 0){
                                game->board[i][j] = game->board[i-3][j];
                                game->board[i-3][j] = ' ';
                            }
                        } else if((i - 2) >= 0){
                            game->board[i][j] = game->board[i-2][j];
                            game->board[i-2][j] = ' ';
                        }
                    } else if((i - 1) >= 0){
                        game->board[i][j] = game->board[i-1][j];
                        game->board[i-1][j] = ' ';
                    }
                }
            }
            for(int j = 0; j < SIZE; j++){
                if((game->board[i][j] == game->board[i-1][j]) && game->board[i][j] != ' ' && game->board[i-1][j] != ' '){
                    //letter: A B C D E F G H I J K
                    //score: 2 4 8 16 32 64 128 256 512 1024 2048
                    char letter = game->board[i][j];
                    int new_letter = (int)letter + 1;
                    letter = (char)new_letter;
                    //letter "A" can't be, so we don't use it
                    if(letter == 'B') game->score = game->score + 4;
                    if(letter == 'C') game->score = game->score + 8;
                    if(letter == 'D') game->score = game->score + 16;
                    if(letter == 'E') game->score = game->score + 32;
                    if(letter == 'F') game->score = game->score + 64;
                    if(letter == 'G') game->score = game->score + 128;
                    if(letter == 'H') game->score = game->score + 256;
                    if(letter == 'I') game->score = game->score + 512;
                    if(letter == 'J') game->score = game->score + 1024;
                    if(letter == 'K') game->score = game->score + 2048;
                    game->board[i][j] = letter;
                    game->board[i-1][j] = ' ';
                    check += 1;
                }
            }
            // flip all letters in one direction so that there is no space (" ") between them 
            for(int j = 0; j < SIZE; j++){
                if(game->board[i][j] == ' '){
                    if(game->board[i-1][j] == ' ' && (i - 1) >= 0){
                        if(game->board[i-2][j] == ' ' && (i - 2) >= 0){
                            if(game->board[i-3][j] != ' ' && (i - 3) >= 0){
                                game->board[i][j] = game->board[i-3][j];
                                game->board[i-3][j] = ' ';
                            }
                        } else if((i - 2) >= 0){
                            game->board[i][j] = game->board[i-2][j];
                            game->board[i-2][j] = ' ';
                        }
                    } else if((i - 1) >= 0){
                        game->board[i][j] = game->board[i-1][j];
                        game->board[i-1][j] = ' ';
                    }
                }
            }
        }
    } else if(dy == -1){
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j < SIZE; j++){
                if(game->board[i][j] == ' '){
                    if(game->board[i+1][j] == ' ' && (i + 1) < SIZE){
                        if(game->board[i+2][j] == ' ' && (i + 2) < SIZE){
                            if(game->board[i+3][j] != ' ' && (i + 3) < SIZE){
                                game->board[i][j] = game->board[i+3][j];
                                game->board[i+3][j] = ' ';
                            }
                        } else if((i + 2) < SIZE){
                            game->board[i][j] = game->board[i+2][j];
                            game->board[i+2][j] = ' ';
                        }
                    } else if((i + 1) < SIZE){
                        game->board[i][j] = game->board[i+1][j];
                        game->board[i+1][j] = ' ';
                    }
                }
            }
            for(int j = 0; j < SIZE; j++){
                if((game->board[i][j] == game->board[i+1][j]) && game->board[i][j] != ' ' && game->board[i+1][j] != ' '){
                    //letter: A B C D E F G H I J K
                    //score: 2 4 8 16 32 64 128 256 512 1024 2048
                    char letter = game->board[i][j];
                    int new_letter = (int)letter + 1;
                    letter = (char)new_letter;
                    //letter "A" can't be, so we don't use it
                    if(letter == 'B') game->score = game->score + 4;
                    if(letter == 'C') game->score = game->score + 8;
                    if(letter == 'D') game->score = game->score + 16;
                    if(letter == 'E') game->score = game->score + 32;
                    if(letter == 'F') game->score = game->score + 64;
                    if(letter == 'G') game->score = game->score + 128;
                    if(letter == 'H') game->score = game->score + 256;
                    if(letter == 'I') game->score = game->score + 512;
                    if(letter == 'J') game->score = game->score + 1024;
                    if(letter == 'K') game->score = game->score + 2048;
                    game->board[i][j] = letter;
                    game->board[i+1][j] = ' ';
                    check += 1;
                }
            }
            // flip all letters in one direction so that there is no space (" ") between them 
            for(int j = 0; j < SIZE; j++){
                if(game->board[i][j] == ' '){
                    if(game->board[i+1][j] == ' ' && (i + 1) < SIZE){
                        if(game->board[i+2][j] == ' ' && (i + 2) < SIZE){
                            if(game->board[i+3][j] != ' ' && (i + 3) < SIZE){
                                game->board[i][j] = game->board[i+3][j];
                                game->board[i+3][j] = ' ';
                            }
                        } else if((i + 2) < SIZE){
                            game->board[i][j] = game->board[i+2][j];
                            game->board[i+2][j] = ' ';
                        }
                    } else if((i + 1) < SIZE){
                        game->board[i][j] = game->board[i+1][j];
                        game->board[i+1][j] = ' ';
                    }
                }
            }
        }
    }

    if(check != 0) return true;
    else return false;
}


/*int main(){
    struct game game = {
        .board = {
            {'A', 'A', 'A', 'A'},
            {'B', 'B', 'B', 'B'},
            {'C', 'C', 'C', 'C'},
            {'D', 'D', 'D', 'D'}
        },
        .score = 1024
    };

    bool result = update(&game, -1, 0);

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            printf("%c ", game.board[i][j]);
        }
        printf("\n");
    }
    printf("\n%d\n", game.score);

    printf("%d\n", result);

    return 0;
}*/
