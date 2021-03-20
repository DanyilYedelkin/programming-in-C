#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int mighty_method(char *number);

int main(){
    char *input = calloc(100000000, sizeof(char));
    scanf("%s", input);
    int output = mighty_method(input);

    printf("%d\n", output);

    free(input);
    return 0;
}

int mighty_method(char *number){
    unsigned long long sum = 0;
    char num = number[0];
    for(long long i = 0; i < strlen(number); i++){
        num = number[i];
        sum += num - '0';
        if(number[i + 1] == '\0') break;
    }
    if((sum > 0) && (sum < 10)) return sum;
    else{
        char *change = calloc(100000000, sizeof(char));
        char new_num = 'a';
        long a = 0;
        for(long i = 0; (i < 10) && (sum != 0); i++, sum /= 10, a++){
            new_num = (sum % 10) + '0';
            change[i] = new_num;
            if((i + 1) == 10) change[a+1] = '\0';
        }
        int new_sum = mighty_method(change);
        if(change != NULL) free(change);
        else return 0;
        return new_sum;
    }
}
