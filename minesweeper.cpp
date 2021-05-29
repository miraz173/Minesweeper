/*g++ E:\CPP\Practice\minesweeper.cpp -o E:\CPP\Practice\minesweeper.exe
  E:\CPP\Practice\minesweeper.exe

  Taskkill /F /IM "minesweeper.exe" /T*/
#include <iostream>
#include <windows.h>
using namespace std;

int constantCellNum = 10;
char cell[10][10];
bool disceveredCell[10][10];
bool gameOver = false;

void getInput();
int showPuzzle();
void bomb();

int main() 	
{
	bomb();
	while(gameOver == false)
	{
		system("cls");
		showPuzzle();
		getInput();
	}
	system("pause");
	return 0;
}

/*void wall()
{
	for (int row = 0; row <= constantCellNum; ++row)
	{
		for (int col = 0; col <= constantCellNum; ++col)
		{
			if (row%2 == 0)
			{
				cout<<'-';
			}
			else if (col%2 == 0)
			{
				cout<<'|';
			}
			else cout<<'X';
		}
		cout<<'\n';
	}
}*/

void bomb() //function to create bomb and count bomb numbers.
{

	for (int i = 0; i < constantCellNum; ++i) //make bomb
	{
		for (int j = 0; j < constantCellNum; ++j)
		{
			if (rand()%3 == 0)
			{
				cell[i][j] = '*';
			}
		}
	}

	for (int i = 0; i < constantCellNum; ++i)
	{
		for (int j = 0; j < constantCellNum; ++j)
		{
			if (cell[i][j] != '*') //the cell not already filled with bomb, then we will put number of bomb around the cell
			{
				int bombCount = 0; //bomb num around cell cellI,cellJ
				for (int cellI = i-1; cellI <= i+1; ++cellI)
				{
					for (int cellJ = j-1; cellJ <= j+1; ++cellJ)
					{
						if (cell[cellI][cellJ] == '*' && cellJ >=0 && cellI>=0 && cellJ < constantCellNum && cellI< constantCellNum)
						{
							bombCount++;
						}
					}
				}
				cell[i][j] = bombCount+48; //cel[][] is a character array. so, we have to store 'num'(num + 48), not num.
			}
			//cout<<cell[i][j]<<' ';
		}
		//cout<<'\n';
	}
	int broken = 0;
	for (int i = 2; i < constantCellNum; ++i) //for the first discovered cell;
	{
		for (int j = 2; j < constantCellNum; ++j)
		{
			if (cell[i][j] == '1')
			{
				disceveredCell[i][j] = true;
				disceveredCell[i+1][j+1] = true;
				disceveredCell[i-1][j-1] = true;
				disceveredCell[i][j+1] = true;
				disceveredCell[i+1][j] = true;
				broken = 1;
				break;
			}
		}
		if (broken == 1)
		{
			break;
		}
	}
}

int showPuzzle()
{
	cout<<"   ";
	for (int j = 0; j < 10; ++j)
	{
		cout<<' ' << j+1;
	}
	cout<<'\n';//columm number will be shown
	cout<<"   _";
	for (int j = 0; j < 10; ++j)
	{
		cout<<"__";
	}
	cout<<'\n';

	for (int i = 0; i < 10; ++i)
	{
		/*------------------------------*/ //row number will be shown
		if (i==9)
		{
			cout<< i+1 <<"| ";
		}
		else cout<< i+1 <<" | ";
		/*------------------------------*/

		for (int j = 0; j < 10; ++j)
		{
			if (disceveredCell[i][j] == false)
			{
				cout <<"X "; //cell not discovered yet
			}
			else 
			{
				cout<< cell[i][j]<<' '; //cell discovered. show bomb number around it.
			}
		}
		cout<<endl;
	}
	return 0;
}

void getInput()
{
	int i,j;
	cin >>i >>j;
	i=i-1; j=j-1; //first cell is 0,0 for computer; 1,1 for human.
	if (cell[i][j] == '*') //stepped on the mine, you are shredded into pieces.
	{
		gameOver = true; //"gameOver == true" means the while loop in main() will break, thus ending the program.
		cout<<"GAME OVER.\nBETTER LUCK NEXT TIME.\n";
	}
	else
	{
		disceveredCell[i][j] = true; //if true, showPuzzle() will show the number of bomb around the cell[i][j]
	}
}