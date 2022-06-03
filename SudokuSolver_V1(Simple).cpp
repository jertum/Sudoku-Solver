// Written by Jeremy Tu June 3rd 2022

#include <iostream>
#include <stdio.h>
#include <vector>
#include <iterator>
#include <algorithm>
#include <string>

using namespace std;

#define N 9 // define grid dimension, 9 by 9

// First, create sudoku board (fixed board for now...)

int sudokuboard[N][N] =
{
	{9, 0, 0, 0, 4, 3, 1, 0, 0},
	{0, 0, 0, 0, 0, 2, 0, 0, 0},
	{0, 0, 8, 0, 0, 0, 0, 9, 0},
	{8, 0, 0, 0, 1, 9, 3, 0, 0},
	{0, 5, 0, 0, 0, 0, 0, 0, 7},
	{0, 0, 0, 6, 0, 0, 0, 0, 0},
	{0, 0, 0, 8, 0, 0, 6, 0, 0},
	{0, 0, 7, 0, 6, 4, 0, 0, 3},
	{4, 0, 0, 2, 0, 0, 0, 0, 0}
};

// Column Check
bool ColCheck(int column, int value) 
{
	vector<int> VolVector{};

	for (int i = 0; i < N; i++)
	{
		VolVector.push_back(sudokuboard[i][column]);
	}


	auto result = find(VolVector.begin(), VolVector.end(), value);

	if (result == VolVector.end())
	{
		return true; // Value is NOT found in the column
	}
	else if (result != VolVector.end())
	{
		return false; // Value IS found in the column
	}

}

// Row Check
bool RowCheck(int row, int value)
{
	vector<int> VolVector{};

	for (int i = 0; i < N; i++)
	{
		VolVector.push_back(sudokuboard[row][i]);
	}


	auto result = find(VolVector.begin(), VolVector.end(), value);

	if (result == VolVector.end())
	{
		return true; // Value is NOT found in the row
	}
	else if (result != VolVector.end())
	{
		return false; // Value IS found in the row
	}

}

// Box Check
// 
// Definition of Box Numbers is as follows:
// 1 2 3
// 4 5 6
// 7 8 9
bool BoxCheck(int boxnumber, int value)
{
	vector<int> VolVector{};

	for (int i = ((boxnumber-1)%3)*3; i < (((boxnumber - 1) % 3)*3)+3; i++) // Looking at Columns
	{
		for (int j = boxnumber-(((boxnumber-1)%3)+1); j < (boxnumber - (((boxnumber - 1) % 3) + 1)) + 3; j++) // Looking at Rows
		{
			VolVector.push_back(sudokuboard[j][i]);
		}
	}

	auto result = find(VolVector.begin(), VolVector.end(), value);

	if (result == VolVector.end())
	{
		return true; // Value is NOT found in the box
	}
	else if (result != VolVector.end())
	{
		return false; // Value IS found in the box
	}
}

// Get Box Number (Most likely can optomise later)
int BoxNumber(int i, int j)
{
	int boxnumber;
	if (i < 3 && j < 3)
	{
		boxnumber = 1;
	}
	else if (i < 3 && j < 6)
	{
		boxnumber = 2;
	}
	else if (i < 3 && j < 9)
	{
		boxnumber = 3;
	}
	else if (i < 6 && j < 3)
	{
		boxnumber = 4;
	}
	else if (i < 6 && j < 6)
	{
		boxnumber = 5;
	}
	else if (i < 6 && j < 9)
	{
		boxnumber = 6;
	}
	else if (i < 9 && j < 3)
	{
		boxnumber = 7;
	}
	else if (i < 9 && j < 6)
	{
		boxnumber = 8;
	}
	else if (i < 9 && j < 9)
	{
		boxnumber = 9;
	}
	return boxnumber;
}

void DisplayGame(int board[N][N] = sudokuboard) // Default is original Board
{
	for (int i = 0; i < N; i++) // Print Row
	{
		if (i==0)
		{
			cout << "\t|-------+-------+-------|\n";
		}
		for (int j = 0; j < N; j++) // Print Column
		{
			if (j == 0)
			{
				cout << "\t| ";
			}
			cout << board[i][j] << " ";

			if (((j + 1) % 3 == 0))
			{
				cout << "| ";
			}
		}
		cout << "\n";
		if ((i + 1) % 3 == 0)
		{
			cout << "\t|-------+-------+-------|\n";
		}

	}
}

bool ZeroCheck()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (sudokuboard[i][j] == 0)
			{
				return false; // There is a zero still present
			}
		}
	}

	return true; // There isn't a zero present
}

void SudokuSolve()
{
	// Initiate Array for number of hits
	int Hits[N][N]{0};
	int boxnumber = 0;
	int SavedValue = 0;

	bool IsZero = false;

	//while (!IsZero)
	//{
		for (int i = 0; i < N; i++) // Row
		{
			for (int j = 0; j < N; j++) // Column
			{

				int Possibilities = 0;
				boxnumber = BoxNumber(i, j);

				for (int value = 1; value < 10; value++)
				{
					if (sudokuboard[i][j] == 0)
					{
						bool IsColumn = ColCheck(j, value);
						bool IsRow = RowCheck(i, value);
						bool IsBox = BoxCheck(boxnumber, value);

						if (IsColumn && IsRow && IsBox)
						{
							//sudokuboard[i][j] = value;
							//ExitFlag = 1;
							Possibilities++;
							SavedValue = value;
						}
					}
				}
				Hits[i][j] = Possibilities;
				if (Possibilities == 1)
				{
					sudokuboard[i][j] = SavedValue;
				}
			}
		}
		IsZero = ZeroCheck();
	//}
	
	cout << "\n" << "\t      Solved Sudoku\n" << "\t=========================\n";
	DisplayGame(sudokuboard);

	cout << "\n" << "\t      TEST Sudoku\n" << "\t=========================\n";
	DisplayGame(Hits);

}

int main()
{
	cout << "\t     Original Sudoku\n" << "\t=========================\n";
	DisplayGame();
	SudokuSolve();
}