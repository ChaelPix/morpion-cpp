#include <iostream>
using namespace std;

char grid[] = { '*', '|', '*', '|', '*', '\n', '*', '|', '*', '|', '*' , '\n', '*', '|', '*', '|', '*' };
int totalTurn = 0;
char characters[] = { 'X', 'O' };
int winnerId = 0;

int winConditions[][3] = { {0, 1, 2}, {0, 3, 6}, {0, 4, 8}, {1, 4, 7}, {2, 4, 6}, {2, 5, 8}, {6, 7, 8}, {3, 4, 5} };

void PrintMorpionGrid()
{
	for (int i = 0; i < 17; i++)
	{
		cout << grid[i];
	}
	cout << endl << endl;
}

void WriteMorpionCase(int choice, int playerId)
{
	int caseId = choice * 2;
	grid[caseId] = characters[playerId];
	totalTurn++;
	PrintMorpionGrid();
}

bool HasSomeoneWon(int playerId)
{
	char gridElement[9];				//Ne récupère que les éléments placés dans la grille
	for (int i = 0; i < 9; i++)
	{
		gridElement[i] = grid[i*2];
	}

	bool hasAWinner = false;
	for (int i = 0; i < 8; i++)
	{
		int pos[3];
		for (int j = 0; j < 3; j++)			//Récupère la combinaison gagnante
		{
			pos[j] = winConditions[i][j];
		}

		if (((characters[playerId] == gridElement[pos[0]]) && gridElement[pos[0]] == gridElement[pos[1]]) && gridElement[pos[1]] == +gridElement[pos[2]]) //Compare si les 3 positions ont le même character
		{
			hasAWinner = true;
			winnerId == playerId;
			break;
		}

	}

	return hasAWinner;
}

bool IsOver(int playerId)
{
	bool actualPlayerWon = HasSomeoneWon(playerId);

	bool hasMaxTurn = totalTurn == 9;
	if (hasMaxTurn && !actualPlayerWon) winnerId = -1; //Egalité

	bool isOver = actualPlayerWon || hasMaxTurn;
	return isOver;
}

int WinnerId()
{
	return winnerId;
}

