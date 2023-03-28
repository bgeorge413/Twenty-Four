#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> 
#include <math.h>

int division(int operand1, int operand2){
    int result = (operand1 / operand2);
    return result;
}

int multiply(int operand1, int operand2){
    int result = (operand1 * operand2);
    return result;
}

int subtract(int operand1, int operand2){
    int result = (operand1 - operand2);
    return result;
}

int addition(int operand1, int operand2){
    int result = (operand1 + operand2);
    return result;
}

double operations(double operand1, double operand2, char operator){
    double result;

    if(operator == '+'){
        result = operand1 + operand2;
        return result;
    }

    if(operator == '-'){
        result = operand1 - operand2;
        return result;
    }

    if(operator == '*'){
        result = operand1 * operand2;
        return result;
    }

    else{
        result = operand1 / operand2;
        return result;
    }
}

void debugMode(int storeSolutions[3188][4], int debugValue){
    int solNum = 0;
    char opArray[4] = {'+', '-', '*', '/'};
    for (double a = 1.0; a < 10; a++){
        for (double b = 1.0; b < 10; b++){
            for (double c = 1.0; c < 10; c++){
                for (double d = 1.0; d < 10; d++){
                    for(int op1 = 0; op1 < 4; op1++){
                        for(int op2 = 0; op2 < 4; op2++){
                            for(int op3 = 0; op3 < 4; op3++){
                                double result = 0.0;

                                result = operations(a, b, opArray[op1]);
                                result = operations(result, c, opArray[op2]);
                                result = operations(result, d, opArray[op3]);
                                
                                if (fabs(result - 24.00) < 0.01){
                                    storeSolutions[solNum][0] = (int)a;
                                    storeSolutions[solNum][1] = (int)b;
                                    storeSolutions[solNum][2] = (int)c;
                                    storeSolutions[solNum][3] = (int)d;
                                    solNum++;
                                    if(debugValue == 1){
                                        printf("%d. %d%c%d%c%d%c%d\n", solNum, (int)a, opArray[op1], (int)b, opArray[op2], (int)c, opArray[op3], (int)d);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void getArguments(int argc, char *argv[], int *debugging, int *diffMode){
    if (argc > 1){
            while((argc = argc - 2) > 0){
                if(argv[1][1] == 'd'){
                    *debugging = atoi(argv[2]);
                }

                if(argv[1][1] == 'e'){
                    *diffMode = atoi(argv[2]);
                }

                argv = argv + 2;
            }
        }
}

int main(int argc, char *argv[]){
    int debugOn = 0;
    int easyOn = 1;
    char playAgain = ' ';
    int hardModePuzzles[3188][4];
    bool loopGood = true;

    int easyModePuzzles[10][4] = {{3, 9, 4, 1}, {8, 5, 8, 1}, {6, 1, 5, 1}, {2, 8, 7, 8}, {5, 2, 9, 2}, {2, 6, 8, 4}, {5, 5, 4, 3}, {6, 6, 2, 6}, {8, 4, 2, 6}, {6, 2, 8, 1}};

    srand(1);

    getArguments(argc, argv, &debugOn, &easyOn);

    printf("Welcome to the game of TwentyFour.\n");
    printf("Use each of the four numbers shown below exactly once,\ncombining them somehow with the basic mathematical operators (+,-,*,/)\nto yield the value twenty-four.\n");

    if(easyOn == 0 || debugOn == 1){
        debugMode(hardModePuzzles, debugOn);
    }

    while (loopGood){
        int result;
        int ranNum;
        int ranNumHard;
        int numberArray[4];
        
        bool tooManyOperators = false;
        bool tooFewOperators = false;
        bool invalidOperators = false;

        if(easyOn == 1){
            ranNum = (rand() % 10);
            for(int assign = 0; assign < 4; assign++){
                numberArray[assign] = easyModePuzzles[ranNum][assign];
            }
        }

        else if(easyOn == 0){
            ranNumHard = (rand() % 3188);
            for(int copyOver = 0; copyOver < 4; copyOver++){
                numberArray[copyOver] = hardModePuzzles[ranNumHard][copyOver];
            }
        }

        printf("The numbers to use are: %d, %d, %d, %d.\n", numberArray[0], numberArray[1], numberArray[2], numberArray[3]);

        printf("Enter the three operators to be used, in order (+,-,*, or /): ");

        int j = 0;
        char oneByOne = ' '; 
        char eatExtras;
        char userInput[3] = {' ', ' ', ' '};

        scanf(" %c", &oneByOne);

        while(oneByOne != '\n'){
            if (j < 3){
                userInput[j] = oneByOne;
                j++;
            }

            else if(j == 3){
                eatExtras = oneByOne;
                tooManyOperators = true;
            }
            scanf("%c", &oneByOne);
        }

        for(int check = 0; check < 3; check++){
            if(userInput[check] == ' '){
                tooFewOperators = true;
            }
        }

        if(tooManyOperators || tooFewOperators){
            printf("Error! The number of operators is incorrect. Please try again. \n");
            continue;
        }

        for (int count = 0; count < 3; count++){
            if(userInput[count] != '+'){
                if(userInput[count] != '-'){
                    if(userInput[count] != '*'){
                        if(userInput[count] != '/'){
                            invalidOperators = true;
                            continue;
                        }
                    }
                }
            }
        }
        
        if(invalidOperators){
                printf("Error! Invalid operator entered. Please try again. \n");
                continue;
            }
        
        result = numberArray[0];
        int numIndex = 0;
        char operator = ' ';
        int operandOne = 0;
        int operandTwo = 0;

        for(numIndex = 0; numIndex < 4; numIndex++){
            operandOne = result;

            if(numIndex + 1 < 4){
                operandTwo = numberArray[numIndex + 1];
            }

            if(numIndex < 3){
                operator = userInput[numIndex];
            }

            else if(numIndex == 3){
                continue;
            }

            if(operator == '/'){
                result = division(operandOne, operandTwo);
                printf("%d %c %d = %d.\n", operandOne, operator, operandTwo, result);
            }

            else if(operator == '*'){
                result = multiply(operandOne, operandTwo);
                printf("%d %c %d = %d.\n", operandOne, operator, operandTwo, result);
            }

            else if(operator == '-'){
                result = subtract(operandOne, operandTwo);
                printf("%d %c %d = %d.\n", operandOne, operator, operandTwo, result);
            }

            else if(operator == '+'){
                result = addition(operandOne, operandTwo);
                printf("%d %c %d = %d.\n", operandOne, operator, operandTwo, result);
            }

        }

        if (result != 24){
            printf("Sorry. Your solution did not evaluate to 24. \n\n");
        }

        if(result == 24){
            printf("Well done! You are a math genius. \n\n");
        }

        printf("Would you like to play again? Enter N for no and any other character for yes. ");
        scanf("%c", &playAgain);
        printf("\n");

        if(playAgain == 'N'){
            printf("Thanks for playing!\n");
            break;
        }

        else{
            continue;
        }

    }

    return 0;

}
