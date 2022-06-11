#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <windows.h>
using namespace std;


char grid[15][15], search_words[53][15];
int overlap[15][15];
char word[15], newword[15] = { '\0' };
int len = 0;

void gotoxy(int ypos, int xpos, int col, char ch)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
	HANDLE  screen = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(screen, col);
	DWORD useless;
	WriteConsole(screen, &ch, 1, (LPDWORD)&useless, NULL);
	SetConsoleTextAttribute(screen, 15);
	SMALL_RECT windowSize = { 0, 0, 100, 100 };
	SetConsoleWindowInfo(screen, TRUE, &windowSize);
}

void print_2D(char grid[][15]) 
{
	for (int i = 0; i < 15; i++)  
	{
		for (int j = 0; j < 15; j++)
		{
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (int i = 0; search_words[i][0] != '\0'; i++)  
	{
		for (int j = 0; search_words[i][j] != '\0'; j++)
		{
			cout << search_words[i][j];
		}
		cout << " ";
	}
	cout << endl;
}

void initiallise(char grid[][15], char word[15])
{
	for (int i = 0; i < 15; i++)  //initiallise grid
	{
		for (int j = 0; j < 15; j++)
		{
			grid[i][j] = '\0';
		}
	}
	for (int j = 0; j < 15; j++)  //initiallise word
	{
		word[j] = '\0';
	}
	for (int i = 0; i < 53; i++)  //initiallise search_words
	{
		for (int j = 0; j < 15; j++)
		{
			search_words[i][i] = '\0';
		}
	}
	for (int i = 0; i < 15; i++)  //initiallise overlap
	{
		for (int j = 0; j < 15; j++)
		{
			overlap[i][j] = 0;
		}
	}
}

void file_input(char grid[][15])
{
	ifstream fin("teleword_2.txt");  //popullating array from file
	while (fin.eof() == false) {
		for (int i = 0; i < 15; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				fin >> grid[i][j];
			}
		}
		for (int j = 0; j < 53; j++)
		{
			fin >> search_words[j];
		}
	}
	fin.close();
	for (int i = 0; i < 53; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (search_words[i][j] >= 'A' && search_words[i][j] <= 'Z' || search_words[i][j] >= 'a' && search_words[i][j] <= 'z') 
			{
				if (search_words[i][j] >= 'a' && search_words[i][j] <= 'z')
				{
					search_words[i][j] = search_words[i][j] - 32;
				}
				else
					search_words[i][j] = search_words[i][j];
			}
			else 
			{
				search_words[i][j] = '\0'; //since comma or fullstop comming at the end
			}
		}
	}


	
}

void data_entry(char search[])
{
	len = strlen(search);
	strcpy(word, search);
}

void left_to_right(char grid[][15], char word[15])
{
	int k = 0, l = 0, pos = 0;
	bool found = false;
	int counter = 0;
	for (int i = 0; i < 15; i++)   //finding substring
	{
		for (int j = 0; j < 15; j++)
		{
			if (grid[i][j] == word[0])   //comparing grid letters with first letter of the word
			{
				found = false;
				k = i;
				l = j;
				pos = j;
				for (int x = 1; l < 15 && x < len; x++)
				{
					l++;
					if (word[x] != '\0' && grid[k][l] == word[x]) //comparing next letters
					{
						if (l == 15)  //incase if within the loop l becomes 15(outside range)
						{
							found = false;//bcz row ends but word isnt yet completely found
						}
						else
							found = true;
					}
					else
					{
						found = false;
						break;
					}
				}
				if (found == true)
				{
					while (counter < 1)
					{
						cout << "From Left to Right" << endl;
						counter++;
					}
					cout << "Row Number " << k + 1 << endl;
					cout << "Position " << pos + 1 << endl;
					for (int i = 0; i < len; i++) 
					{
						overlap[k][pos]++;
						pos++;     //since left to right col increment
					}
				}
			}
		}
	}
}

void right_to_left(char grid[][15], char word[15])
{
	int k = 0, l = 0, pos = 0;
	bool found = false;
	int counter = 0;
	for (int i = 0; i < 15; i++)   //finding substring
	{
		for (int j = 14; j >= 0; j--)
		{
			if (grid[i][j] == word[0])   //comparing grid letters with first letter of the word
			{
				found = false;
				k = i;
				l = j;
				pos = j;
				for (int x = 1; l >= 0 && x < len; x++)
				{
					l--;   //col decrement
					if (word[x] != '\0' && grid[k][l] == word[x]) //comparing next letters
					{
						if (l == -1)  //incase if within the loop l becomes -1(outside range)
						{
							found = false;
						}
						else
							found = true;
					}
					else
					{
						found = false;
						break;
					}
				}
				if (found == true)
				{
					while (counter < 1)
					{
						cout << "From Right to Left" << endl;
						counter++;
					}
					cout << "Row Number " << k + 1 << endl;
					cout << "Position " << pos + 1 << endl;
					for (int i = 0; i < len; i++)
					{
						overlap[k][pos]++;   
						pos--;     
					}
				}
			}
		}
	}
}

void top_to_bottom(char grid[][15], char word[15])
{
	int k = 0, l = 0, pos = 0, poss = 0;
	bool found = false;
	int counter = 0;
	for (int i = 0; i < 15; i++)   //finding substring
	{
		for (int j = 0; j < 15; j++)
		{
			if (grid[i][j] == word[0])   //comparing grid letters with first letter of the word
			{
				found = false;
				k = i;
				poss = k;
				l = j;
				pos = j;
				for (int x = 1; k < 15 && x < len; x++)
				{
					k++; //row increment
					if (word[x] != '\0' && grid[k][l] == word[x]) //comparing next letters
					{
						if (k == 15)  //incase if within the loop k becomes 15(outside range)
						{
							found = false;
						}
						else
							found = true;
					}
					else
					{
						found = false;
						break;
					}
				}
				if (found == true)
				{
					while (counter < 1)
					{
						cout << "From Top to Bottom" << endl;
						counter++;
					}
					cout << "Row Number " << poss + 1 << endl;
					cout << "Position " << pos + 1 << endl;
					for (int i = 0; i < len; i++)
					{
						overlap[poss][pos]++;
						poss++;  
					}
				}
			}
		}
	}
}

void bottom_to_top(char grid[][15], char word[15])
{
	int k = 0, l = 0, pos = 0, poss = 0;
	bool found = false;
	int counter = 0;
	for (int i = 14; i >= 0; i--)   //finding substring
	{
		for (int j = 0; j < 15; j++)
		{
			if (grid[i][j] == word[0])   //comparing grid letters with first letter of the word
			{
				found = false;
				k = i;
				poss = k;
				l = j;
				pos = j;
				for (int x = 1; k >= 0 && x < len; x++)
				{
					k--; //row decrement
					if (word[x] != '\0' && grid[k][l] == word[x]) //comparing next letters
					{
						if (k == -1)  //incase if within the loop k becomes -1(outside range)
						{
							found = false;
						}
						else
							found = true;
					}
					else
					{
						found = false;
						break;
					}
				}
				if (found == true)
				{
					while (counter < 1)
					{
						cout << "From Bottom to top" << endl;
						counter++;
					}
					cout << "Row Number " << poss + 1 << endl;
					cout << "Position " << pos + 1 << endl;
					for (int i = 0; i < len; i++)
					{
						overlap[poss][pos]++;
						poss--;    
					}
				}
			}
		}
	}
}   //

void bottom_right_diagonally(char grid[][15], char word[15])
{
	int k = 0, l = 0, pos = 0, poss = 0;
	bool found = false;
	int counter = 0;
	for (int i = 0; i < 15; i++)   //finding substring
	{
		for (int j = 0; j < 15; j++)
		{
			if (grid[i][j] == word[0])   //comparing grid letters with first letter of the word
			{
				found = false;
				k = i;
				poss = k;
				l = j;
				pos = j;
				for (int x = 1; k < 15 && l < 15 && x < len; x++)
				{
					k++; //row increment
					l++; //col increment
					if (word[x] != '\0' && grid[k][l] == word[x]) //comparing next letters
					{
						if (k == 15 || l == 15)  //incase if within the loop k or l becomes 15(outside range)
						{
							found = false;
						}
						else
							found = true;
					}
					else
					{
						found = false;
						break;
					}
				}
				if (found == true)
				{
					while (counter < 1)
					{
						cout << "Towards Bottom Right Diagonally" << endl;
						counter++;
					}
					cout << "Row Number " << poss + 1 << endl;
					cout << "Position " << pos + 1 << endl;

					for (int i = 0; i < len; i++)
					{
						overlap[poss][pos]++;
						poss++;
						pos++;
					}
				}
			}
		}
	}
}

void bottom_left_diagonally(char grid[][15], char word[15])
{
	int k = 0, l = 0, pos = 0, poss = 0;
	bool found = false;
	int counter = 0;
	for (int i = 0; i < 15; i++)   //finding substring
	{
		for (int j = 14; j >= 0; j--)
		{
			if (grid[i][j] == word[0])   //comparing grid letters with first letter of the word
			{
				found = false;
				k = i;
				poss = k;
				l = j;
				pos = j;
				for (int x = 1; k < 15 && l < 15 && x < len; x++)
				{
					k++; //row increment
					l--; //col decrement
					if (word[x] != '\0' && grid[k][l] == word[x]) //comparing next letters
					{
						if (k == 15 || l == -1)  //incase if within the loop k becomes 15 or l becomes -1 (outside range)
						{
							found = false;
						}
						else
							found = true;
					}
					else
					{
						found = false;
						break;
					}
				}
				if (found == true)
				{
					while (counter < 1)
					{
						cout << "Towards Bottom Left Diagonally" << endl;
						counter++;
					}
					cout << "Row Number " << poss + 1 << endl;
					cout << "Position " << pos + 1 << endl;
					for (int i = 0; i < len; i++)
					{
						overlap[poss][pos]++;
						poss++;
						pos--;
					}
				}
			}
		}
	}
}

void top_right_diagonally(char grid[][15], char word[15])
{
	int k = 0, l = 0, pos = 0, poss = 0;
	bool found = false;
	int counter = 0;
	for (int i = 14; i >= 0; i--)   //finding substring
	{
		for (int j = 0; j < 15; j++)
		{
			if (grid[i][j] == word[0])   //comparing grid letters with first letter of the word
			{
				found = false;
				k = i;
				poss = k;
				l = j;
				pos = j;
				for (int x = 1; k >= 0 && l < 15 && x < len; x++)
				{
					k--; //row increment
					l++; //col increment
					if (word[x] != '\0' && grid[k][l] == word[x]) //comparing next letters
					{
						if (k == -1 || l == 15)  //incase if within the loop k becomes -1 OR l becomes 15(outside range)
						{
							found = false;
						}
						else
							found = true;
					}
					else
					{
						found = false;
						break;
					}
				}
				if (found == true)
				{
					while (counter < 1)
					{
						cout << "Towards Top Right Diagonally" << endl;
						counter++;
					}
					cout << "Row Number " << poss + 1 << endl;
					cout << "Position " << pos + 1 << endl;
					for (int i = 0; i < len; i++)
					{
						overlap[poss][pos]++;
						poss--;
						pos++;
					}
				}
			}
		}
	}
}

void top_left_diagonally(char grid[][15], char word[15])
{
	int k = 0, l = 0, pos = 0, poss = 0;
	bool found = false;
	int counter = 0;
	for (int i = 14; i >= 0; i--)   //finding substring
	{
		for (int j = 14; j >= 0; j--)
		{
			if (grid[i][j] == word[0])   //comparing grid letters with first letter of the word
			{
				found = false;
				k = i;
				poss = k;
				l = j;
				pos = j;
				for (int x = 1; k < 15 && l < 15 && x < len; x++)
				{
					k--; //row decrement
					l--; //col decrement
					if (word[x] != '\0' && grid[k][l] == word[x]) //comparing next letters
					{
						if (k == -1 || l == -1)  //incase if within the loop k or l becomes -1 (outside range)
						{
							found = false;
						}
						else
							found = true;
					}
					else
					{
						found = false;
						break;
					}
				}
				if (found == true)
				{
					while (counter < 1)
					{
						cout << "Towards Top Left Diagonally" << endl;
						counter++;
					}
					cout << "Row Number " << poss + 1 << endl;
					cout << "Position " << pos + 1 << endl;
					for (int i = 0; i < len; i++)
					{
						overlap[poss][pos]++;
						poss--;
						pos--;
					}
				}
			}
		}
	}
}

void print_overlap() 
{
	int i = 0, index = 0;
	for (int k = 0; k < 29 && i < 15; k++)
	{
		int j = 0;
		for (int l = 0; l < 29 && j < 15; l = l + 2)
		{
			if (overlap[i][j] == 0)
			{
				newword[index] = grid[i][j];
				index++;
				gotoxy(k, l, 15, grid[i][j]);   //unused words: white
			}
			else if (overlap[i][j] == 1)
			{
				gotoxy(k, l, 30, grid[i][j]);  //once : blue//30/55
			}
			else if (overlap[i][j] == 2)
			{
				gotoxy(k, l, 75, grid[i][j]);  //twice : magentta
			}
			else if (overlap[i][j] == 3)
			{
				gotoxy(k, l, 96, grid[i][j]);   //thrice : yellow//96
			}
			j++;
		}
		i++;
	}
}

int main()
{
	initiallise(grid, word);
	file_input(grid);
	print_2D(grid);
	for (int i = 0; i < 53; i++)
	{
		data_entry(search_words[i]);
		cout << endl << "Word: " << search_words[i] << endl;
		left_to_right(grid, word);
		right_to_left(grid, word);
		top_to_bottom(grid, word);
		bottom_to_top(grid, word);
		top_left_diagonally(grid, word);
		top_right_diagonally(grid, word);
		bottom_left_diagonally(grid, word);
		bottom_right_diagonally(grid, word);
	}
	print_overlap();
	gotoxy(285, 0, 0, '\0');
	cout << "----------------------";
	cout << endl << "Spare Word : " << newword << endl;
	system("pause");
	return 0;
}
