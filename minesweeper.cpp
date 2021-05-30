/*g++ E:\CPP\Practice\minesweeper.cpp -o E:\CPP\Practice\minesweeper.exe
  E:\CPP\Practice\minesweeper.exe

  Taskkill /F /IM "minesweeper.exe" /T*/
#include <iostream>
#include <windows.h>
using namespace std;

/*---------------------Variable declaration----------------*/
int constantCellNum = 10;
char cell[10][10];
int discoveredCell[10][10] = {0};
bool gameOver = false;
int totalBombNumber = 0, totalDiscoveredCellNum = 5;
int difficultyLevel= 4;
/*---------------------Variable declaration----------------*/

/*---------------------Function declaration----------------*/
void aksThings();
void bomb();
void showPuzzle();
void getInput();
void gameSucces();
/*---------------------Function declaration----------------*/

int main() 	
{
	aksThings();
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
			if (rand()%difficultyLevel == 0) //randomly generating bomb, marking with '*'.
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
				discoveredCell[i][j] = 1;
				discoveredCell[i+1][j+1] = 1;
				discoveredCell[i-1][j-1] = 1;
				discoveredCell[i][j+1] = 1;
				discoveredCell[i+1][j] = 1;
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

void aksThings()
{
	cout<< "Enter difficuluty Level(1-5): ";
	cin>> difficultyLevel;
	if (difficultyLevel<1 || difficultyLevel>5)
	{
		difficultyLevel = 4;
	}
	else 
	{
		difficultyLevel = 8- difficultyLevel;
	}

	cout<< "Enter number of grid along X or Y axis(5-10): ";
	cin>> constantCellNum;
	if (constantCellNum<5 || constantCellNum>10)
	{
		constantCellNum = 10;
	}
	cout<<"Enter Negative coordinate of the cell if you want to flag the cell.\nEnter X and then Y coordinate to discover the cell.\n\n";
	system("pause");
}

void showPuzzle()
{
	/*-----------------------------columm number will be shown---------------------------------*/
	cout<<"   ";
	for (int j = 0; j < constantCellNum; ++j)
	{
		cout<<' ' << j+1;
	}
	cout<<"\n   _";
	for (int j = 0; j < constantCellNum; ++j)
	{
		cout<<"__";
	}
	cout<<'\n';
	/*-----------------------------columm number will be shown---------------------------------*/


	for (int i = 0; i < constantCellNum; ++i)
	{
	/*---------------row number will be shown---------------*/
		if (i>=9)
		{
			cout<< i+1 <<"| ";
		}
		else cout<< i+1 <<" | ";
	/*---------------row number will be shown---------------*/ 


/*---------------------------print the maze/house-------------------------*/
		for (int j = 0; j < constantCellNum; ++j)
		{
			if (discoveredCell[i][j] == 0)
			{
				cout <<"X "; //cell not discovered yet
			}
			else if(discoveredCell[i][j] == 1)
			{
				cout<< cell[i][j]<<' '; //cell discovered. show bomb number around it.
			}
			else /*if(discoveredCell[i][j] == 2)*/
			{
				cout<< "F "; //cell flagged.
			}
		}

	/*---------------row number will be shown at end---------------*/
		if (i>=9)
		{
			cout<<"|"<< i+1 <<'\n';
		}
		else cout<<"| "<< i+1 <<'\n';
	/*---------------row number will be shown at end---------------*/ 

	}
/*---------------------------print the maze/house-------------------------*/

	/*-----------------------------columm number will be shown at end row---------------------------------*/
	cout<<"   -";
	for (int j = 0; j < constantCellNum; ++j)
	{
		cout<<"--";
	}
	cout<<'\n';
	cout<<"   ";
	for (int j = 0; j < constantCellNum; ++j)
	{
		cout<<' ' << j+1;
	}
	/*-----------------------------columm number will be shown at end row---------------------------------*/

	cout<<endl;
}

void getInput() //takes co-ordinate number as input. if cell is empty/noBomb, then cell is discovered. if co-ordinates are negative, then flag the cell.
{
	int i,j;
	cin >>i >>j;

	if (i > constantCellNum || j > constantCellNum || i < -1*constantCellNum || j < -1*constantCellNum)
	{
		cout<<"\tInvalid Input.\nEnter X and then Y coordinate again.\n";
	}
	else if (i<0 && j<0) //flag the cell
	{
		i=i+1; j=j+1; //first cell is 0,0 for computer; 1,1 for human.
		discoveredCell[-1*i][-1*j] = 2; //if 2, showPuzzle() will show F/flag on the cell.
	}

	else if(i>0 && j>0)
	{
		i=i-1; j=j-1; //first cell is 0,0 for computer; 1,1 for human.
		if (cell[i][j] == '*') //stepped on the mine, you are shredded into pieces.
		{
			gameOver = true; //"gameOver == true" means the while loop in main() will break, thus ending the program.
			cout<<"GAME OVER.\nBETTER LUCK NEXT TIME.\n";
		}
		else
		{
			discoveredCell[i][j] = 1; //if 1/true, showPuzzle() will show the number of bomb around the cell[i][j]
			totalDiscoveredCellNum++;
		}
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
