#include <iostream>
#include <cstdlib>
#include "GridWritter.h"
using namespace std;

#define Player 0
#define AI 1

void PrintEnd()
{
	
	string winString;
	switch (WinnerId())
	{
		case Player: winString = "Vous remportez la partie !"; break;
		case AI: winString = "L'AI remporte la partie !"; break;
		default: winString = "Match nul !";
	}
	cout << "\t" << winString << endl;
}

int caseStates[9]; //0 Empty, 1: O, 2: X
void PlayerTurn()
{
	int choice;
	do
	{
		cout << "> Selectionnez votre case (1-9) : ";
		cin >> choice;
		choice -= 1;
		if (choice < 9) if (caseStates[choice] != 0) cout << "Case Prise" << endl;
		else;																							//Reste & gérer les inputs n'étant pas entre 1 et 9
	} while (caseStates[choice] != 0);

	caseStates[choice] = 1;
	cout << "- Vous jouez : " << endl;
	WriteMorpionCase(choice, Player);
}
void AITurn()
{
	int x;
	do {															//Créer une fonction qui return une case empechant le joueur de gagner
		x = rand() % 8;
	} while (caseStates[x] != 0);

	caseStates[x] = 2;
	cout << "- L'AI joue : " << endl;
	WriteMorpionCase(x, AI);
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
		PrintEnd();
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

	PrintMorpionGrid();
	ChooseCase(Player);
}