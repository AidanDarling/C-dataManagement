// stackproblem.c – Lab 02 – Aidan, Darling

#include <stdio.h>


// Globals used for code
int top = -1;
char stack [80];

// Pushes value to the top of stack
int push (char x){
    // Checks to see if the array has hit its limit
    if (top == 80){
        return 0;
    }
    // If it has not, then increases top of stack by 1 and puts value to new top of stack
    else{
        top++;
        stack[top] = x;
        return 1;
    }
}

// Pops top value out of the stack
int pop(char *popVar){
    // Checks to see if a valid item exits to be popped
    if (top == -1){
        return 0;
    }
    // If it has not, pops value from top of stack and then decreases top of stack by 1
    else{
        *popVar = stack[top];
        top--;
        return 1;
    }
}

int main(){
    // Variables used to run main code
    char reVar;
    char userVar;
    char userChoice;
    char *tosCheck;
    int exit = 1;
    // Loops through the scan function until it reaches the newline value
    while(exit == 1){
        // Scans current value in the given line of charecters
        scanf("%c", &userVar);
        if (userVar == '\n'){
            // When newline is found, exits the loop
            exit = 0;
        }
        else{
            // Scans the current value and saves it in the stack
            push(userVar);
        }  
    }
    printf("%c", stack[top]);

    // Prints out every charecter given in reverse order
    while(pop(&reVar) == 1){
        printf("%c", reVar);
    }


}