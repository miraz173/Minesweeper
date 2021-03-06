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
int difficultyLevel;
/*---------------------Variable declaration----------------*/

/*---------------------Function declaration----------------*/
void asksThings();
void bomb();
void showPuzzle();
void getInput();
void gameSucces();
/*---------------------Function declaration----------------*/

int main() 	
{
	asksThings();
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

/*------------------bomb created and bombs around cells are counted and stored-------------------------*/



/*------------------------making default discovered cells-------------------------------------------*/

	bool broken = 0; //temporary variable to indicate the loop to be broken. 
	for (int i = 0; i < constantCellNum-1; ++i) //for the first/default discovered cells;
	{
		for (int j = 1; j < constantCellNum-1; ++j)
		{
			if (cell[i][j] == '1')
			{
				discoveredCell[i][j] = 1;
				discoveredCell[i][j-1] = 1;
				discoveredCell[i][j+1] = 1;
				discoveredCell[i+1][j] = 1;
				discoveredCell[i+1][j+1] = 1;
				broken = 1;
				break;
			}
		}
		if (broken == 1)
		{
			break;
		}
	}

/*------------------------ made default discovered cells--------------------------------------------*/

}

void asksThings()
{
	cout<< "Enter difficuluty Level(1-5): ";
	cin>> difficultyLevel;
	/*-----------check input validation----------------*/
	while (!cin) 
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout<<"Invalid Input Type.\nEnter difficuluty Level(1-5) again: ";
		cin >>difficultyLevel;
	}
	/*-----------checked input validation-------------*/

	if (difficultyLevel<1 || difficultyLevel>5)//invalid difficulity level will be assigned 'difficulityLevel=4'.
	{
		difficultyLevel = 4;
	}
	else 
	{
		difficultyLevel = 8 - difficultyLevel; //actual difficulty level(under the hood) ranges 3 - 7.
	}

	cout<< "Enter number of grid along X or Y axis(5-10): ";
	cin>> constantCellNum;
	/*-----------check input validation----------------*/
	while (!cin) 
	{
		cin.clear();
		cin.ignore(100, '\n');
		cout<< "Invalid input type.\nEnter number of grid along X or Y axis(5-10): ";
		cin >>constantCellNum;
	}
	/*-----------checked input validation-------------*/

	if (constantCellNum<5 || constantCellNum>10)//invalid constantCellNum level will be assigned 'constantCellNum=10'.
	{
		constantCellNum = 10;
	}
	cout<<"\n\tEnter Negative coordinate of the cell if you want to flag the cell.\n\tEnter X and then Y coordinate to discover the cell.\n\n\t";
	system("pause");
}

void showPuzzle()
{
	/*-----------------------------columm number will be shown---------------------------------*/
	cout<<"\n\t   ";
	for (int j = 0; j < constantCellNum; ++j)
	{
		cout<<' ' << j+1;
	}
	cout<<"\n\t   _";
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
			cout<<'\t'<< i+1 <<"| ";
		}
		else cout<< '\t'<< i+1 <<" | ";
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
	cout<<"\t   -";
	for (int j = 0; j < constantCellNum; ++j)
	{
		cout<<"--";
	}
	cout<<"\n\t   ";
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
	if(cin >>i >>j) //if inputs are in expexted format(int), 'cin' returns 'true'
	{
		if (i > constantCellNum || j > constantCellNum || i < -1*constantCellNum || j < -1*constantCellNum )
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
	else //inputs(i or j or both) are not in expected format(int). so clear cin-s internal buffer and the input buffer
	{
		cout<< "Invalid input type.\nEnter integer coordinate number again: ";//dont need to take input now as main() will execute getInput() again.
		cin.clear(); //clears cin-s internal buffer
		cin.ignore(100, '\n'); //100 --> asks cin to discard 100 characters from the input stream.
		Sleep(950); //wait 950 millisec cause need time to read.
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
/*always check the validation of input by using if(cin >> var){do stuff as input format is ok}  else{ cin.clear(); cin.ignore(100, '\n')*/