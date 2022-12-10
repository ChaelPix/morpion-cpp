#include <iostream>
#include <cstdlib>
#include "GridWritter.h"
using namespace std;

#define Player 0
#define AI 1

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
		else PrintMorpionHelp();
	} while (caseStates[choice] != 0);

	caseStates[choice] = 1;
	cout << "- Vous jouez : " << endl;
	WriteMorpionCase(choice, Player);
}
void AITurn()
{
	int x;
	do {
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
		case 0: PlayerTurn(); ChooseCase(AI); break;
		case 1: AITurn(); ChooseCase(Player); break;
	}
}


int main()
{
	cout << "\t MXRPION !" << endl << "---------------------------" << endl << endl;

	PrintMorpionGrid();
	ChooseCase(Player);
}