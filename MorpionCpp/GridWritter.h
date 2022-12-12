#include <iostream>
#include <string>
using namespace std;

char grid[] = { '*', '|', '*', '|', '*', '\n', '*', '|', '*', '|', '*' , '\n', '*', '|', '*', '|', '*' };
int totalTurn = 0;
char characters[] = { 'X', 'O' };
bool isDraw;

int winConditions[][3] = { {0, 1, 2}, {0, 3, 6}, {0, 4, 8}, {1, 4, 7}, {2, 4, 6}, {2, 5, 8}, {6, 7, 8}, {3, 4, 5} };

void ResetGrid()
{
	for (int i = 0; i < 9; i++)
	{
		grid[i * 2] = '*';
	}
	isDraw = false;
	totalTurn = 0;
}

void PrintMorpionHelp()
{
	char helpGrid[17];
	copy(begin(grid), end(grid), begin(helpGrid));

	for (int i = 0; i < 17; i++)
	{
		if (helpGrid[i] == '*')
			helpGrid[i] = (i/2) + '1';
		cout << helpGrid[i];	
	}
	cout << endl << endl;
}

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

		if (((characters[playerId] == gridElement[pos[0]]) && gridElement[pos[0]] == gridElement[pos[1]]) && gridElement[pos[1]] == gridElement[pos[2]]) //Compare si les 3 positions ont le même character
		{
			hasAWinner = true;
			//winnerId == playerId;
			break;
		}
	}

	return hasAWinner;
}

bool IsOver(int playerId)
{
	bool actualPlayerWon = HasSomeoneWon(playerId);

	bool hasMaxTurn = totalTurn == 9;
	if (hasMaxTurn && !actualPlayerWon) isDraw = true; //Egalité

	bool isOver = actualPlayerWon || hasMaxTurn;
	return isOver;
}

bool IsDraw()
{
	return isDraw;
}

int AICasePicker()
{
	char gridElement[9];				//Ne récupère que les éléments placés dans la grille
	for (int i = 0; i < 9; i++)
	{
		gridElement[i] = grid[i * 2];
	}

	//l'ai regarde si elle est en mesure de gagner
	for (int i = 0; i < 8; i++)
	{
		int pos[3];
		for (int j = 0; j < 3; j++)			//Récupère les combinaison gagnantes
		{
			pos[j] = winConditions[i][j];
		}

		// Si l'ai a 2/3 de la combi et que la case est vide, l'ai comblera
		if (((characters[1] == gridElement[pos[1]]) && gridElement[pos[1]] == gridElement[pos[2]]) && gridElement[pos[0]] == '*')
			return pos[0];

		if (((characters[1] == gridElement[pos[0]]) && gridElement[pos[0]] == gridElement[pos[2]]) && gridElement[pos[1]] == '*')
			return pos[1];

		if (((characters[1] == gridElement[pos[0]]) && gridElement[pos[0]] == gridElement[pos[1]]) && gridElement[pos[2]] == '*')
			return pos[2];
	}

	//l'ai regarde si elle peut empecher le joueur de gagner
	for (int i = 0; i < 8; i++)
	{
		int pos[3];
		for (int j = 0; j < 3; j++)			//Récupère les combinaison gagnantes
		{
			pos[j] = winConditions[i][j];
		}

		// Si le joueur a 2/3 de la combi et que la case est vide, l'ai comblera
		if (((characters[0] == gridElement[pos[1]]) && gridElement[pos[1]] == gridElement[pos[2]]) && gridElement[pos[0]] == '*')
			return pos[0];

		if (((characters[0] == gridElement[pos[0]]) && gridElement[pos[0]] == gridElement[pos[2]]) && gridElement[pos[1]] == '*')
			return pos[1];

		if (((characters[0] == gridElement[pos[0]]) && gridElement[pos[0]] == gridElement[pos[1]]) && gridElement[pos[2]] == '*')
			return pos[2];
	}

	//l'ai regarde si elle peut mettre 2 cases
	for (int i = 0; i < 8; i++)
	{
		int pos[3];
		for (int j = 0; j < 3; j++)			//Récupère les combinaison gagnantes
		{
			pos[j] = winConditions[i][j];
		}

		// Si l'ai a 1/3 de la combi et que la case est vide, l'ai comblera
		if ((characters[1] == gridElement[pos[1]] || (characters[1] == gridElement[pos[2]])) && gridElement[pos[1]] == '*' && gridElement[pos[2]] == '*')
			return pos[0];

		if ((characters[1] == gridElement[pos[0]] || (characters[1] == gridElement[pos[2]])) && gridElement[pos[0]] == '*' && gridElement[pos[2]] == '*')
			return pos[1];

		if ((characters[1] == gridElement[pos[0]] || (characters[1] == gridElement[pos[1]])) && gridElement[pos[0]] == '*' && gridElement[pos[1]] == '*')
			return pos[2];
	}

	//Sinon elle essaie peut etre d'avoir le 4
	int z = rand() % 2;
	if (gridElement[4] == '*' && z == 1) return 4;

	//Sinon au pif
	int x;
	do {
		x = rand() % 8;
	} while (gridElement[x] != '*');
	return x;
}
