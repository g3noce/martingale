#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//[RAPPEL DE COMPILATION](pour Mingw en C) : gcc main.c -o main.exe

int main(int argc, char const *argv[]){
    srand((unsigned int)time(NULL));
    int balance = 1024;// a small wallet to limit bets
    int bankroll = 10240;//global money usable by the wallet
    int wheel = 0;//
    int bet = 1;// minimum bet
    int k = 0;//win percentage
    int j = 0;//loss percentage
    for (int i = 0; i < 1000; i++)// loop for the long term math
    {
    while (balance <= 2048){//limit of the small wallet when it doubles
        if (balance - bet <= 0){//if the next loss the small wallet is negative then we stop betting
            bet = 1;
            break;
        }
        
        wheel = rand() % 1000;//simulation wheel
        if (wheel > 0 && wheel < 492)// I put 492 / 1000 instead of 495 because I noticed that in the long term there's a 3 / 1000 percentage shift.
        {
            k += 1*bet;//I multiply by the number of bets to see the short-term variance.
            balance += bet;
            //printf("win %d balance %d\n", bet,balance);
            bet = 1;
        } else// if it's a loos
        {
            j += 1*bet;//I multiply by the number of bets to see the short-term variance.
            balance -= bet;
            //printf("loss %d balance %d\n", bet,balance);
            bet = bet*2;
        }
    }
    if (balance >= 2048){//if it's a double up
        bankroll += balance;
        balance = 1024;
        bankroll -= balance;
    }
    else{// if it's a loss down
        bankroll += balance;
        balance = 1024;
        bankroll -= balance;
    }
    }
    printf("bankroll : %d\ncashout : %d\n", bankroll, bankroll - 10240);
    printf("p(win)%f , p(loss)%f\n",(float)k/(k+j), (float)j/(k+j));// percentage of wins and losses (with variance view option)
}
