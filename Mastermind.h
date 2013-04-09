/*
=================
main.cpp
Main entry point for the Card application
=================
*/
#include "GameConstants.h"
#include "cPeg.h"
#include "cBoard.h"
#include "cCode.h"
#include "cPlayer.h"
#include "cHumanPlayer.h"
#include "cComputer.h"
#include "cGuess.h"
#include "cScore.h"

//using namespace std;

void main()
{
	// Variables
	cBoard ThisBoard;
	cCode ThisCode;
	string PlayerGuess;
	string ThisPlayerName;
	int tries = 0;
	char const ValidChar[] = "BYGR";

	cout << "\t\tMastermind - Crack the Code!!!!\n\n";
	
	// Get player name
	cout << "What is your name? \n";	
	cin >> ThisPlayerName;

	// Create Computer object
	cComputer ThisComputer;

	// Create player object
	cHumanPlayer ThisPlayer(ThisPlayerName);

	// Enter Guess upto 10 times and while the player hasn't won
	while (tries < 10)
	{
		// get a valid guess
		ThisComputer.getCode();

			// Get player guess
			cout << "Please guess a sequence of four colors, like this RGBY \n";
			cin >> PlayerGuess;

		// Store the players Guess on /in the board
			ThisPlayer.setPlayerGuess(PlayerGuess);

		// Check Guess against code
			if (PlayerGuess == ThisComputer.getCode())
			{
				cout << "Congratulations, you have won! \n";
				tries = 10;
			// if the same display player winning message
			}
			else 
			{
				
				ThisPlayer.setPlayerScore(ThisComputer.computeScore(PlayerGuess, ThisComputer.getCode()));
			// otherwise generate the score, store the score & display the game board
				cout << "Your score is ";
				ThisPlayer.showPlayerBoard(tries);
				cout << "\n";
			}

		// increment tries
			tries++;

		// clear the guess
			PlayerGuess = "";
	}
	// if the player hasn't won then the winner must be the computer

	if (PlayerGuess != ThisComputer.getCode())
	{
		cout << "Unfortunately you have lost the game. The correct code was ";
		ThisComputer.showCode();
		cout << "\n";
	}

	cout << "End\n";

	cin.get();
	cin.get();
}