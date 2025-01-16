#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define INITIAL_BALANCE 1024
#define INITIAL_BANKROLL 10240
#define MAX_BALANCE 2048
#define MIN_BET 1
#define ITERATIONS 100000000
#define WHEEL_MAX 1000
#define WIN_THRESHOLD 492

int main(int argc, char const *argv[]) {
    srand((unsigned int)time(NULL));
    
    long long totalWins = 0;
    long long totalLosses = 0;
    int balance = INITIAL_BALANCE;
    long long bankroll = INITIAL_BANKROLL;
    int bet = MIN_BET;
    
    // Tracking variables
    long long maxBankroll = bankroll;
    int currentLossStreak = 0;
    int maxLossStreak = 0;
    int finalLossStreak = 0;
    int bankruptcyIteration = 0;
    
    printf("Simulation started...\n");
    printf("Initial balance: %d\n", INITIAL_BALANCE);
    printf("Initial bankroll: %lld\n\n", bankroll);

    for (int i = 0; i < ITERATIONS; i++) {
        if (balance <= bet) {
            bankroll += balance;
            balance = INITIAL_BALANCE;
            bankroll -= balance;
            bet = MIN_BET;
            
            if (bankroll < 0) {
                bankruptcyIteration = i;
                finalLossStreak = currentLossStreak;
                break;
            }
        }
        else if (balance >= MAX_BALANCE) {
            bankroll += balance;
            balance = INITIAL_BALANCE;
            bankroll -= balance;
            bet = MIN_BET;
        }

        if (bankroll > maxBankroll) {
            maxBankroll = bankroll;
        }

        int wheel = rand() % WHEEL_MAX;
        
        if (wheel < WIN_THRESHOLD) {
            totalWins += bet;
            balance += bet;
            bet = MIN_BET;
            currentLossStreak = 0;
        } else {
            totalLosses += bet;
            balance -= bet;
            currentLossStreak++;
            
            if (currentLossStreak > maxLossStreak) {
                maxLossStreak = currentLossStreak;
            }
            
            if ((long long)bet * 2 > INT_MAX) {
                printf("Error: Bet overflow at iteration %d\n", i);
                bet = MIN_BET;
            } else {
                bet *= 2;
            }
        }

        if (i % 10000000 == 0 && i > 0) {
            printf("Progress: %d%%\n", i / (ITERATIONS / 100));
        }
    }

    printf("\nFinal Results:\n");
    printf("Iterations before bankruptcy: %d\n", bankruptcyIteration);
    printf("Maximum bankroll reached: %lld (profit of %lld)\n", 
           maxBankroll, maxBankroll - INITIAL_BANKROLL);
    printf("Final bankroll: %lld (profit/loss of %lld)\n", 
           bankroll, bankroll - INITIAL_BANKROLL);
    printf("Longest loss streak: %d\n", maxLossStreak);
    printf("Fatal streak length: %d\n", finalLossStreak);
    
    double winRate = (double)totalWins / (totalWins + totalLosses);
    printf("Win rate: %.4f%%\n", winRate * 100);
    printf("Loss rate: %.4f%%\n", (1 - winRate) * 100);

    return 0;
}
