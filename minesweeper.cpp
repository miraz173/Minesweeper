/*g++ E:\CPP\Practice\minesweeper.cpp -o E:\CPP\Practice\minesweeper.exe
  E:\CPP\Practice\minesweeper.exe

  Taskkill /F /IM "minesweeper.exe" /T*/
#include <iostream>
#include <windows.h>
using namespace std;

int constantCellNum = 10;
char cell[10][10];
bool discoveredCell[10][10];
bool gameOver = false;
int totalBombNumber = 0, totalDiscoveredCellNum = 5;

void getInput();
void showPuzzle();
void bomb();
void gameSucces();

int main() 	
{
	bomb();
	while(gameOver == false)
	{
		system("cls"); //clears the output screen
		showPuzzle();
		getInput();
		gameSucces();
	}
	system("pause");
	return 0;
}

void bomb() //function to create bomb and count bomb numbers.
{

/*----------------- will create bomb and bombs around cells will be counted and stored-----------------*/

	for (int i = 0; i < constantCellNum; ++i) //makes bomb
	{
		for (int j = 0; j < constantCellNum; ++j)
		{
			if (rand()%3 == 0) //randomly generating bomb, marking with '*'.
			{
				cell[i][j] = '*';
				totalBombNumber++;
			}
		}
	}

	for (int i = 0; i < constantCellNum; ++i) //codes inside loop counts bombNum around cells
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
		}
	}

/*-----------------bomb created and bombs around cells are counted and stored-------------------------*/



/*------------------------making default discovered cells-------------------------------------------*/

	bool broken = 0; //temporary variable to indicate the loop to be broken. 
	for (int i = 1; i < constantCellNum-1; ++i) //for the first/default discovered cells;
	{
		for (int j = 1; j < constantCellNum-1; ++j)
		{
			if (cell[i][j] == '1')
			{
				discoveredCell[i][j] = true;
				discoveredCell[i+1][j+1] = true;
				discoveredCell[i-1][j-1] = true;
				discoveredCell[i][j+1] = true;
				discoveredCell[i+1][j] = true;
				broken = 1;
				break;
			}
		}
		if (broken == 1)
		{
			break;
		}
	}

/*------------------------ made default discovered cells------------------------------------------*/

}


void showPuzzle()
{
	/*-----------------------------columm number will be shown---------------------------------*/
	cout<<"   ";
	for (int j = 0; j < 10; ++j)
	{
		cout<<' ' << j+1;
	}
	cout<<"\n   _";
	for (int j = 0; j < 10; ++j)
	{
		cout<<"__";
	}
	cout<<'\n';
	/*-----------------------------columm number will be shown---------------------------------*/

	for (int i = 0; i < 10; ++i)
	{
	/*---------------row number will be shown---------------*/
		if (i==9)
		{
			cout<< i+1 <<"| ";
		}
		else cout<< i+1 <<" | ";
	/*---------------row number will be shown---------------*/ 


	/*---------------------------print the maze/house-------------------------*/
		for (int j = 0; j < 10; ++j)
		{
			if (discoveredCell[i][j] == false)
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
	/*---------------------------print the maze/house-------------------------*/
}

void getInput() //takes co-ordinate number as input. if cell is empty/noBomb, then cell is discovered. if co-ordinates are negative, then flag the cell.
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
		discoveredCell[i][j] = true; //if true, showPuzzle() will show the number of bomb around the cell[i][j]
		totalDiscoveredCellNum++;
	}
}

void gameSucces() //if player discovered all the cells, then mission completes. 
{
	int numOfCellWithoutBomb = (constantCellNum*constantCellNum) - totalBombNumber;

	if (totalDiscoveredCellNum == numOfCellWithoutBomb)
	{
		cout<<"\n\tCONGRATS! \nYou Did it Somehow! Mission Accomplished.\n";
		gameOver = true;
	}
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
