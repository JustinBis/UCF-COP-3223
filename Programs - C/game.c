/* ****************** */
/* P9 - Education Game*/
/* Justin Bisignano   */
/* COP 3223 Section 4 */
/* 11/9/2012          */
/* ****************** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ADD 1
#define MULT 2

// Function Prototypes
int arithGame(int max, int op);
int guessGame();
int max(int a, int b);
int min(int a, int b);

// Main Function
int main(void){
    // Initilize Variables
    int selection, operation, max;
    int flag = 1;
    int score = 0;
    // Seed the random number generator just once
    srand(time(0));

    // Create outer main loop
    while (flag){
        // Print Main Options
        printf("Please make a selection from the following:\n");
        printf("1. Play Arithmetic Game.\n");
        printf("2. Play Guessing Game.\n");
        printf("3. Print Score.\n");
        printf("4. Quit.\n");

        // Scan in selection
        scanf("%d", &selection);

        // Check selection and execute respective functions
        if (selection==1){
            printf("Would you like, 1)Addition or 2)Multiplication?\n");
            scanf("%d", &operation);
            printf("What is the maximum number you would like?\n");
            scanf("%d", &max);
            score += arithGame(max, operation);

        }
        else if (selection==2){
            score += guessGame();
        }
        else if (selection==3){
            printf("Your score is %d.\n\n", score);
        }
        else if (selection==4){
            printf("Thank you for playing!\n");
            flag = 0;
        }

    }

    // Program Completed, so return 0.
    return 0;
}

// Artithmetic Game Function
int arithGame(int max, int op){
    int i, a, b, answer;
    int score = 0;
    // Run 10 times
    for (i = 0; i<10; i++){
        // Generate two random numbers
        a = rand()%max + 1;
        b = rand()%max + 1;

        // Check to see what operation we are supposed to do
        if (op==ADD){
            printf("What is %d+%d?\n", a, b);
            scanf("%d", &answer);
            if (answer==a+b){
                printf("Correct, great job!\n");
                score += 1;
            }
            else{
                printf("Sorry, that's incorrect, the answer is %d.\n", a+b);
            }
        }
        else if(op==MULT){
            printf("What is %dx%d?\n", a, b);
            scanf("%d", &answer);
            if (answer == a*b){
                printf("Correct, great job!\n");
                score += 1;
            }
            else{
                printf("Sorry, that's incorrect, the answer is %d.\n", a*b);
            }

        }
        else // If they selected an invalid operation, i.e. not 1 or 2
            return 0;
    }
    printf("Your score for the round is %d\n\n", score);
    return score;
}

// Guessing Game Function
int guessGame(){
    // Setup Variables
    int guess = 0; // Set guess to 0 to prevent the slight possiblilty of guess already equaling secret in uninitilized memory.
    int score = 0, numguesses = 0;
    int secret = rand()%100 + 1; // Returns a random number between 1 and 100 inclusive.


    // Loop until the guess is right
    while(guess != secret){
        printf("Enter your guess!\n");
        scanf("%d", &guess);

        if (max(guess, secret) == guess)
            printf("Your guess is too high, try again.\n");
        else if (min(guess, secret) == guess)
            printf("Your guess is too low, try again.\n");

        numguesses++;
    }

    // Now that the guess is correct, congratulate user and return the score
    printf("Great, you guessed the correct number %d in %d guesses.\n", secret, numguesses);
    score = 17 - numguesses;

    // Set score to be between 0 and 10 if outside of those bounds.
    if (score > 10)
        score = 10;
    else if (score < 0)
        score = 0;

    printf("Your score for the round is %d.\n\n", score);
    return score;
}

int max(int a, int b){
    if (a>b)
        return a;
    else if (b>a)
        return b;
    else
        return 0;
}

int min(int a, int b){
    if (a<b)
        return a;
    else if (b<a)
        return b;
    else
        return 0;
}
