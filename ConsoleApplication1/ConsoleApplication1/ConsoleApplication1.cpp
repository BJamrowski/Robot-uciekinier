// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

// komentarz na test branch
using namespace std;
enum direction{UP, RIGHT, DOWN, LEFT};


// TODO zamieniæ main na osobne funkcje dla czytelnoœci
void findMe(){		// NIEU¯YWANA
	// method to find robot in the beginning
	int myPosition[2];
	int enemy[2];
	int position[4];

	for (int i = 0; i < 2; i++)
	{
		position[i] = rand() %10;
		position[i+2] = rand() %10;
		
		if(position[i] == position[i+2]){
			position[i] = rand() %10;
		}
	}
}

// sprawdza czy przed nami nie ma przeciwnika 
// TODO dodac reakcje na znalezienie przeciwnika
void changeSurroundings(direction zwrot, int position[], int localization[][10]) {
	int safe = 5;
	switch (zwrot)
	{
		case UP:
			for (int i = position[0] - 1; safe > 0; i--)
			{
				if (i == 0) return;
				localization[i - 1][position[1] - 1] = safe;
				safe--;
			}
			break;
		case RIGHT:
			for (int i = position[1] + 1; safe > 0; i++)
			{
				if (i == 0) return;
				localization[position[0] - 1][i - 1] = safe;
				safe--;
			}
			break;
		case DOWN:
			for (int i = position[0] + 1; safe > 0; i++)
			{
				if (i == 0) return;
				localization[i - 1][position[1] - 1] = safe;
				safe--;
			}
			break;
			break;
		case LEFT:
			for (int i = position[1] - 1; safe > 0; i--)
			{
				if (i == 0) return;
				localization[position[0] - 1][i - 1] = safe;
				safe--;
			}
			break;
		default:
			return;
			break;
	}
}

void moveToSafeArea(direction zwrot, int position[], int localization[][10]) {
	switch (zwrot)
	{
		case UP:
			for (int i = 5; i > 0; i--)
			{
				if (localization[position[0] - 4][position[1] - 1] == 1 || localization[position[0] - 2][position[1] - 1] == 5) {
					localization[position[0] - 2][position[1] - 1] = 9;
					localization[position[0] - 1][position[1] - 1] = -1;
					position[0] = position[0] - 1;
					changeSurroundings(zwrot, position, localization);
				}
				return;
			}
			break;
		case RIGHT:
			for (int i = 5; i > 0; i--)
			{
				if (localization[position[0] - 1][position[1] + 4] == 1) {
					localization[position[0] - 1][position[1]] = 9;
					localization[position[0] - 1][position[1] - 1] = -1;
					position[1] = position[1] + 1;
					changeSurroundings(zwrot, position, localization);
				}
				return;
			}
			break;
		case DOWN:
			for (int i = 5; i > 0; i--)
			{
				if (localization[position[0] + 4][position[1] - 1] == 1 || localization[position[0]][position[1] - 1] == 5) {
					localization[position[0]][position[1] - 1] = 9;
					localization[position[0] - 1][position[1] - 1] = -1;
					position[0] = position[0] + 1;
					changeSurroundings(zwrot, position, localization);
				}
				return;
			}
			break;
		case LEFT: // work in progress
			for (int i = 5; i > 0; i--)
			{
				if (localization[position[0] - 1][position[1] - 6] == 1 || localization[position[0] - 1][position[1] - 2] == 5) {
					localization[position[0] - 1][position[1] - 2] = 9;
					localization[position[0] - 1][position[1] - 1] = -1;
					position[1] = position[1] - 1;
					changeSurroundings(zwrot, position, localization);
				}
				return;
			}
			break;
			break;
		default:
			break;
		}
}

int _tmain(int argc, _TCHAR* argv[])
{
	direction zwrot = LEFT;
	int localization[10][10];
		//inicjalizacja tablicy mapy
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			localization[i][j] = -1;
		}
	}
	// tablica z po³o¿eniem robota i przeciwnika
	int position[4];
	
	// losowanie po³o¿enie
	// pozniej zmienic na lokalizacje w terenie
	/*
	for (int i = 0; i < 2; i++)
	{
		position[i] = (rand() % 10) + 1;
		position[i + 2] = (rand() %10) + 1;
		
		if(position[i] == position[i+2]){
			position[i] = rand() %10;
		}
	}
	*/

	position[0] = 9;	//x
	position[1] = 8;	//y
	position[2] = 1;
	position[3] = 1;

	// naniesienie robota i przeciwnika na mape
	localization[position[0]-1][position[1]-1] = 9;
	localization[position[2]-1][position[3]-1] = 0;
	//swap(localization[position[0]-1][position[1]-1],localization[0][0]);

	changeSurroundings(zwrot, position, localization);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout<<"["<< localization[i][j] <<"] ";
		}
		cout<<endl<<endl;
	}

	// wyswietlenie wspó³rzêdnych 
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			cout<<"My position Y: "<<position[i]<<endl;
			break;
		case 1:
			cout<<"My position X: "<<position[i]<<endl;
			break;
		case 2:
			cout<<"Enemy position Y: "<<position[i]<<endl;
			break;
		case 3:
			cout<<"Enemy position X: "<<position[i]<<endl;
			break;
		default:
			break;
		}
	}



	moveToSafeArea(zwrot, position, localization);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << "[" << localization[i][j] << "] ";
		}
		cout << endl << endl;
	}

	// wyswietlenie wspó³rzêdnych 
	for (int i = 0; i < 4; i++)
	{
		switch (i)
		{
		case 0:
			cout << "My position Y: " << position[i] << endl;
			break;
		case 1:
			cout << "My position X: " << position[i] << endl;
			break;
		case 2:
			cout << "Enemy position Y: " << position[i] << endl;
			break;
		case 3:
			cout << "Enemy position X: " << position[i] << endl;
			break;
		default:
			break;
		}
	}
		return 0;
}
