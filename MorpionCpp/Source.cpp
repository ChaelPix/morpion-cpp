#include <iostream>
#include <cstdlib>
#include "GridWritter.h"
using namespace std;

#define Player 0
#define AI 1

int caseStates[9]; //0 Empty, 1: O, 2: X
int totalGames = 0;

void ResetGame()
{
	for (int i = 0; i < 9; i++)
	{
		caseStates[i] = false;
	}
	ResetGrid();
}

bool AskReplay()
{
	char replay;
	cout << "Rejouer ? (O/N) - ";
	cin >> replay;
	cin.ignore();

	if (replay == 'O' || replay == 'o')
	{
		ResetGame();
		return true;
	}
	else
		return false;
}

int scorePlayer = 0, scoreAi = 0;
bool PrintEnd(int playerId)
{
	string winString;
	int winner = playerId;
	if (IsDraw()) winner = 2;

	switch (winner)
	{
		case Player: winString = "Vous remportez la partie !"; scorePlayer++;  break;
		case AI: winString = "L'ordinateur remporte la partie !"; scoreAi++; break;
		case 2: winString = "Match nul !";
	}

	totalGames++;
	cout << "\t" << winString << endl
		<< "\t Score - Joueur : " << scorePlayer << " - Ordinateur : " << scoreAi << endl
		<< "\t Partie(s) : " << totalGames << endl << endl;
	
	return AskReplay();
}


bool CheckCaseState(int caseChoice)
{
	if (caseChoice < 9 && caseChoice >= 0)
	{
		if (caseStates[caseChoice] != 0)
		{
			cout << "Case Prise" << endl
				<< "> Aide : " << endl;
			PrintMorpionHelp();
		}
		else 
			return true;
	}
	else
	{
		cout << "- Case Inexistante !" << endl
			<< "> Aide : " << endl;
		PrintMorpionHelp();
	}
	return false;
}

void PlayerTurn()
{
	int choice;
	bool isCaseChoosen = false;
	do
	{
		cout << "> Selectionnez votre case (1-9) : ";
		cin >> choice;
		cin.ignore();
		choice -= 1;
		isCaseChoosen = CheckCaseState(choice);
	} while (!isCaseChoosen);

	caseStates[choice] = 1;
	cout << "- Vous jouez : " << endl;
	WriteMorpionCase(choice, Player);
}

void AITurn()
{
	int x = AICasePicker();
	caseStates[x] = 2;
	cout << "- L'ordinateur joue : " << endl;
	WriteMorpionCase(x, AI);
}

void StartGame()
{
	cout << "\tPartie #" << totalGames + 1 << endl << endl;
	srand(time(NULL));
	cout << "- Grille : " << endl;
	PrintMorpionHelp();
}

void ChooseCase(int playerId)
{
	switch (playerId)
	{
		case 0: PlayerTurn(); break;
		case 1: AITurn(); break;
	}

	if (IsOver(playerId))
	{
		if (PrintEnd(playerId))
		{
			StartGame();
			ChooseCase(Player);
		} else
			return;
	}

	switch (playerId)
	{
		case 0: ChooseCase(AI); break;
		case 1: ChooseCase(Player); break;
	}
}

int main()
{
	cout << "\t MXRPION !" << endl << "---------------------------" << endl << endl;
	StartGame();
	ChooseCase(Player);
}