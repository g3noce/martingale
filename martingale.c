#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//[RAPPEL DE COMPILATION](pour Mingw en C) : gcc main.c -o main.exe

int main(int argc, char const *argv[]){
    srand((unsigned int)time(NULL));
    int balance = 1024;
    int bankroll = 10240;
    int wheel = 0;
    int bet = 1;
    int k = 0;
    int j = 0;
    for (int i = 0; i < 1000; i++)
    {
    while (balance <= 2048){
        if (balance - bet <= 0){
            bet = 1;
            break;
        }
        wheel = rand() % 1000;
        if (wheel > 0 && wheel < 492)
        {
            k += 1*bet;
            if (bet != 0)
            {
                balance += bet;
                //printf("win %d balance %d\n", bet,balance);
                bet = 1;
            }
        } else
        {
            j += 1*bet;
            if (bet != 0)
            {
                balance -= bet;
                //printf("loss %d balance %d\n", bet,balance);
                bet = bet*2;
            }
        }
    }
    if (balance >= 2048){
        bankroll += balance;
        balance = 1024;
        bankroll -= balance;
    }
    else{
        bankroll += balance;
        balance = 1024;
        bankroll -= balance;
    }
    }
    printf("bankroll : %d\ncashout : %d\n", bankroll, bankroll - 10240);
    printf("p(win)%f , p(loss)%f\n",(float)k/(k+j), (float)j/(k+j));
}
