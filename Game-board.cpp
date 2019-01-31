#include<iostream>
#include<iomanip>
#include <string>
#include <stdio.h>     
#include <stdlib.h>
#include <vector>
#include <ctype.h>
#include <math.h>
#include <fstream>
#include <time.h>
using namespace std;
int arraytest[256][4] = {};
//int arrayprint[256][4] = {};

void swap(int firstcell, int secondcell)
{
	int temp1 = 0;
	int temp2 = 0;
	int temp3 = 0;
	int temp4 = 0;
	temp1 = arraytest[firstcell][0];
	temp2 = arraytest[firstcell][1];
	temp3 = arraytest[firstcell][2];
	temp4 = arraytest[firstcell][3];

	arraytest[firstcell][0] = arraytest[secondcell][0];
	arraytest[firstcell][1] = arraytest[secondcell][1];
	arraytest[firstcell][2] = arraytest[secondcell][2];
	arraytest[firstcell][3] = arraytest[secondcell][3];

	arraytest[secondcell][0] = temp1;
	arraytest[secondcell][1] = temp2;
	arraytest[secondcell][2] = temp3;
	arraytest[secondcell][3] = temp4;
}
int check()
{//this is designed to check the score of a board checks matched edges
	int score = 0;
/*#pragma region "Outside"
	for (int i = 0; i < 16; i++)
	{//top row
		if (arraytest[i][0] == 0)
		{
			score++;
		}
	}
	for (int i = 0; i < 256; i = i + 16)
	{//ends rows
		if (arraytest[i][3] == 0)
		{
			score++;
		}
		if (arraytest[i+15][1] == 0)
		{
			score++;
		}
	}
	for (int i = 240; i < 256; i++)
	{//bottom row
		if (arraytest[i][2] == 0)
		{
			score++;
		}
	}
#pragma endregion*/
	//Outside if correct
#pragma region "Between cell matching"
	int z = 1;
	float x = 0;
	int b = 15;
	for (int i = 0; i < 256; i++)
	{
		if(i == b)
		{
			continue;
		}
		//printf("%i\n",i);
		//printf("%i == %i\n",arraytest[i][2], arraytest[i+16][0]);
		if(arraytest[i][1] == arraytest[i+1][3] && arraytest[i][1] != 0)
		{
			//arraytest[i][1] = 256;
			//arraytest[i+1][3] = 256;
			score++;
		}
		x = z/16;
		int u = floor(x);
		//printf("cell %i => %i using %i\n",i,u, 15*u+(16+(u-1)));
		b = 15*u+(16+(u-1));
		z++;
	}
	for (int i = 0; i < 240; i++)
	{
		if(arraytest[i][2] == arraytest[i+16][0] && arraytest[i][2] != 0)
		{
			//arraytest[i][2] = 256;
			//arraytest[i+16][0] = 256;
			score++;
		}
	}
#pragma endregion

	return score;
}
void rotate(int cell, int amount)
{
	int temp1 = 0;
	int temp2 = 0;
	int temp3 = 0;
	int temp4 = 0;
	if (amount > 0)
	{

		for (int i = 0; i < amount; i++)
		{
			temp1 = arraytest[cell][0];
			temp2 = arraytest[cell][1];
			temp3 = arraytest[cell][2];
			temp4 = arraytest[cell][3];

			arraytest[cell][0] = temp4;
			arraytest[cell][1] = temp1;
			arraytest[cell][2] = temp2;
			arraytest[cell][3] = temp3;
		}//4 per -1
	}else if (amount < 0)
	{
		for (int i = 0; i < abs(amount); i++)
		{
			temp1 = arraytest[cell][0];
			temp2 = arraytest[cell][1];
			temp3 = arraytest[cell][2];
			temp4 = arraytest[cell][3];

			arraytest[cell][0] = temp2;
			arraytest[cell][1] = temp3;
			arraytest[cell][2] = temp4;
			arraytest[cell][3] = temp1;
		}//4 per -1
	}
}
void returnresult()
{
	ofstream outfile ("Result.txt");
	
	for (int i = 0; i < 16; i++)
	{
		for(int y = 0; y < 16; y++)
		{
			for(int z = 0; z < 4; z++)
			{
				outfile << " " << arraytest[i * 16 + y][z];
			}
			outfile << "\t";
		}
		outfile << endl;
	}
	outfile.close();

}
void randomswap()
{
	int x = 0;
	int r2 = 1;
	srand(time(NULL)); 
	int r = 10;
	int checkscore = 0;
	float percentage = 0.0;
	float p2 = 0.0;
	while (x < 1000000)
	{
		  // Initialization, should only be called once.
		r = rand() % 255 + 1;
		if(r % 2 == 0)
		{
			rotate(r,1);
		}else
		{
			rotate(r,-1);
		}
		//printf("%i",r);
		swap(r,r2);
		r2 = r;
		checkscore = check();
		percentage = (float)checkscore/480*100;//544 real total
		if(p2 >= percentage)
		{
			//nothing
		}else
		{
			p2 = percentage;
			returnresult();
			printf("Percentage = %f and raw = %i\n",p2,checkscore);
		}
		x++;
	}
}
int importdata()
{
	FILE *file;
	file = fopen("Data.txt","r");
	if(!file)
	{
		printf("Cannot open file\n");
		return 0;
	}
	char ch = fgetc(file);
	int fourposition = 0;
	int overall = 1;
	char * temp;
	temp = (char *) malloc(sizeof(char));
	int tracker = 0;
	bool number = false;

	while(ch != EOF)
	{
		ch = fgetc(file);
		if(isspace(ch))
		{
			number = false;
			continue;
		}
		else 
		{
			if(number == false)
			{
				//printf("\n");
				number = true;
				fourposition++;
				if (fourposition > 4)
				{
					fourposition = 1;
					overall++;
				}
			}
			if(number == true)
			{
				if (arraytest[overall-1][fourposition - 1] != 0)
				{
					int tempvar = (arraytest[overall - 1][fourposition - 1] * 10) + ( ch - '0');
					//printf("[%i], %i == %i",tempvar,fourposition , overall);
					arraytest[overall-1][fourposition - 1] = tempvar;
				}else
				{
					arraytest[overall-1][fourposition - 1] = ch - '0';
				}
				//printf("current pos = %i and %i, %i ",overall,fourposition,arraytest[overall-1][fourposition - 1]);
			}
		}

	}
	fclose(file);
	printf("\n");
	return 1;
}
int selection()
{//tells which command to excecute
	string input = "";
	printf("Commands Swap(1,2)[Swaps two peices 1-16], rotate(1,x)[rotates a peice by x*90],\n ");
	printf("Enter a command:  ");
	getline(cin,input);
	if(input.empty() || !isalpha(input[0]))
	{
		return 0;
	}else if(input[0] == 'o')
	{
		returnresult();
	}
	else
	{
		char *num1;
		char *num2;
		int numberpointer = 1;
		num1 = (char *) malloc(sizeof(char));
		num2 = (char *) malloc(sizeof(char));
		int charactercounter = 0;
		char currentchar = input[charactercounter];
		while (currentchar != '(')
		{
			//printf("%c",input[charactercounter]);
			charactercounter++;
			currentchar = input[charactercounter];
		}
		charactercounter++;
		//printf("\n");
		currentchar = input[charactercounter];
		while (currentchar != ',')
		{
			if (isspace(currentchar))
			{
				charactercounter++;
				currentchar = input[charactercounter];
				continue;
			}
			num1[numberpointer - 1] = input[charactercounter];
			numberpointer++;
			num1 = (char *) realloc(num1, numberpointer * sizeof(char));
			//printf("%c",num1[numberpointer - 2]);
			charactercounter++;
			currentchar = input[charactercounter];
		}
		charactercounter++;
		//printf("\n");
		currentchar = input[charactercounter];
		numberpointer = 1;
		while (currentchar != ')')
		{
			if (isspace(currentchar))
			{
				charactercounter++;
				currentchar = input[charactercounter];
				continue;
			}
			num2[numberpointer - 1] = input[charactercounter];
			numberpointer++;
			num2 = (char *) realloc(num2, numberpointer * sizeof(char));
			//printf("%c",num2[numberpointer - 2]);
			charactercounter++;
			currentchar = input[charactercounter];
		}
		printf("\n");
		if (input[0] == 's')
		{
			if(atoi(num1) > 16 || atoi(num2) > 16)
			{
				printf("Error check range\n");
				return 0;
			}
			//swap(atoi(num1)-1,atoi(num2)-1);
			randomswap();
		}else if(input[0] == 'r')
		{
			if(atoi(num1) > 256 || atoi(num2) > 3 || atoi(num2) < -3)
			{
				printf("Error check range\n");
				return 0;
			}
			rotate(atoi(num1)-1,atoi(num2));
		}
	}
}
void display()
{
	int i,j;  
	cout<<"       "<<0;//5 space chars

	for(i = 1;i <= 15;++i)
	{
		if (i > 9)
		{
			cout<<"      "<<i;//5 space chars
		}else
		{
			cout<<"       "<<i;//6 space chars
		}
	}
	cout<<'\n';
	cout<<"   +-------+";

	for(i = 2;i <= 16;++i)
	{
		cout<<"-------+";
	}
	cout<<'\n';
	int x = 0;
	int y = 0;
	for(i = 0;i <= 15;++i)
	{
		for (int z = 0; z < 3; z++)
		{
			if(z%2==1)
			{
				cout<<setw(3)<<i<<"|";//Line after number, the first line of the series
			}else
			{
				cout<<setw(4)<<"|";
			}
			if (z == 1)
			{
				x = x - 16;
				for(j = 1;j <= 16;++j)
				{
					cout<<setw(3)<<arraytest[x][3];
					cout <<setw(4)<<arraytest[x][1]<<setw(1)<<"|";
					x++;
					y = 1;
				}
			}else if (z == 0)
			{
				for(j = 1;j <= 16;++j)
				{
					cout<<setw(5)<<arraytest[x][0]<<setw(3)<<"|";
					x++;
				}
			}
			else
			{
				x = x - 16;
				for(j = 1;j <= 16;++j)
				{
					cout<<setw(5)<<arraytest[x][2]<<setw(3)<<"|";
					x++;
				}
			}
			cout<<'\n';
		}
		cout<<" --+-------";
		for(j = 2;j <= 15;++j)
		{
			cout<<"+-------";
		}
		cout<<"+-------+";
		cout<<'\n';

	}
}
bool safety = false;
int main()
{ 
	if (!safety)
	{
		if( importdata() == 0)
		{
			return 0;
		}
	}
	if (safety)
	{
		int checkscore = check();
		float percentage = (float)checkscore/480*100;//544 real total
		printf("The current score is: %i/480 = %f% \n",checkscore,percentage);
		display();

		if (selection() == 0)
		{
			return 0;//if selection returns an error exit program
		}

		return main();
	}
	//return 0;
}