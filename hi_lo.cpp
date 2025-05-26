// Implement a game of Hi-Lo. First, your program should pick a random integer between 1 and 100. The user is given 7 tries to guess the number.

// If the user does not guess the correct number, the program should tell them whether they guessed too high or too low. If the user guesses the right number, the program should tell them they won. If they run out of guesses, the program should tell them they lost, and what the correct number is. At the end of the game, the user should be asked if they want to play again. If the user doesn’t enter ‘y’ or ‘n’, ask them again.

#include <string>
#include <iostream>
#include <limits>
#include "Random.h"

int generateRandNum() 
{
    return Random::get(1, 100);
}

std::string checkHighOrLow(int userInput, int target)
{
    std::string returnValue {};
    if (userInput == target)
        return (returnValue = "Congrats! You win!");
    if (userInput < target)
        return (returnValue = "Your guess is too low");
    return (returnValue = "Your guess is too high");
}

int getGuessFromUser(int numGuess, int min, int max)
{
    while (true)
    {
        std::cout << "Guess #" << numGuess << ":";
        int userGuess {0};
        std::cin >> userGuess;

        // Will evalute to false if input anything other than an integer
        bool success { std::cin };
        std::cin.clear(); // put us back in 'normal' operation mode (if needed)
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // remove any extra input

        // If we didn't extract anything or the extracted guess is out of bounds, try again
        if (!success || userGuess < min || userGuess > max)
            continue;

        return userGuess;
    }
}

int main(int argc, char const *argv[])
{
    bool playAgain {true};
    while (playAgain) 
    {
        std::cout << "Let's play a game. I'm thinking of a number between 1 and 100. You have 7 tries to guess what it is." << '\n';
        int targetInt = generateRandNum();
        for (int i=1; i <= 7; i++) 
        {
            std::string gameResponse {checkHighOrLow(getGuessFromUser(i, 1, 100), targetInt)};

            std::cout <<  gameResponse << '\n';
            if (gameResponse == "Congrats! You win!")
                break;
            if (i==7) 
            {
                std::cout << "Sorry, you lost. The correct number was " << targetInt << '\n';
            }
        }

        while (true)
        {
            std::cout << "Would you like to play again (y/n)?";
            char playerAnswer {};
            std::cin >> playerAnswer;
            // clear out any extraneous input
		    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (playerAnswer == 'n')
            {
                playAgain = false;
                break;
            }
            if (playerAnswer == 'y')
            {
                break;
            }
        }   
    }
    return 0;
}
