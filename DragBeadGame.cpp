#include<iostream>
#include<iomanip>
#include<windows.h>
#include<time.h>

using namespace std;
void Initialize(int b[5][6]);
void DrawScene(int b[5][6], int p_x, int p_y);
void OutputMessage();
void HandleUserInput(int choice, int b[5][6], int &p_x, int &p_y, int &last_p_x, int &last_p_y);
void BeadSwap(int b[5][6], int p_x, int p_y, int last_p_x, int last_p_y);
bool ClearBead(int b[5][6]);
void DropBead(int b[5][6]);
void GenerateBead(int b[5][6]);
int main(void)
{
	srand((unsigned int)time(NULL));
	int player_x = 0;
	int player_y = 0;
	int last_player_x = 0;
	int last_player_y = 0;
	int bead[5][6];
	int choice = 0;
	Initialize(bead);
	while (true)
	{
		DrawScene(bead, player_x, player_y);
		OutputMessage();
		cin >> choice;
		HandleUserInput(choice, bead, player_x, player_y, last_player_x, last_player_y);
		system("CLS");
	}
	cin.get();
}
void Initialize(int b[5][6])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			b[i][j] = rand() % 6;
		}
	}
}
void DrawScene(int b[5][6], int p_x, int p_y)
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			switch (b[i][j])
			{
			case 0:
				cout << "◆";
				break;
			case 1:
				cout << "◇";
				break;
			case 2:
				cout << "■";
				break;
			case 3:
				cout << "□";
				break;
			case 4:
				cout << "◉";
				break;
			case 5:
				cout << "◎";
				break;
			case 6:
				cout << "G ";
				break;
			default:
				cout << "  ";
				break;
			}
			if (j == p_x && i == p_y)
				cout << "-";
			else
				cout << " ";
		}
		cout << endl;
	}
}
void OutputMessage()
{
	cout << "\n4. Go left.\n";
	cout << "6. Go right.\n";
	cout << "8. Go up.\n";
	cout << "2. Go down.\n";
	cout << "5. Finish dragging.\n";
}
void HandleUserInput(int choice, int b[5][6], int &p_x, int &p_y, int &last_p_x, int &last_p_y)
{
	last_p_x = p_x;
	last_p_y = p_y;
	switch (choice)
	{
	case 4:
		if (p_x > 0)
		{
			p_x--;
			BeadSwap(b, p_x, p_y, last_p_x, last_p_y);
		}
		break;
	case 6:
		if (p_x < 5)
		{
			p_x++;
			BeadSwap(b, p_x, p_y, last_p_x, last_p_y);
		}
		break;
	case 8:
		if (p_y > 0)
		{
			p_y--;
			BeadSwap(b, p_x, p_y, last_p_x, last_p_y);
		}
		break;
	case 2:
		if (p_y < 4)
		{
			p_y++;
			BeadSwap(b, p_x, p_y, last_p_x, last_p_y);
		}
		break;
	case 5:
		while (ClearBead(b))
		{
			system("CLS");
			DrawScene(b, p_x, p_y);
			Sleep(1000);

			DropBead(b);

			system("CLS");
			DrawScene(b, p_x, p_y);
			Sleep(1000);

			GenerateBead(b);

			system("CLS");
			DrawScene(b, p_x, p_y);
			Sleep(1000);
		}
		break;
	default:
		break;
	}
}
void BeadSwap(int b[5][6], int p_x, int p_y, int last_p_x, int last_p_y)
{
	int temp[1][1];
	temp[1][1] = b[p_y][p_x];
	b[p_y][p_x] = b[last_p_y][last_p_x];
	b[last_p_y][last_p_x] = temp[1][1];
}
bool ClearBead(int b[5][6])
{
	int temp_b[5][6];
	int count = 1;
	int type = 1;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			temp_b[i][j] = b[i][j];
		}
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			count = 0;
			type = b[i][j];
			for (int r = j; b[i][r] == type && r < 6; r++)
			{
				count++;
				if (count > 2)
					for (int u = j; u <= r; u++)
						temp_b[i][u] = 99;
			}
			count = 0;
			for (int r = i; b[r][j] == type && r < 5; r++)
			{
				count++;
				if (count > 2)
					for (int u = i; u <= r; u++)
						temp_b[u][j] = 99;
			}
		}
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			b[i][j] = temp_b[i][j];
		}
	}
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (b[i][j] == 99)
				return true;
		}
	}
	cout << "\nNo bead can be eliminated!";
	Sleep(1000);
	return false;
}
void DropBead(int b[5][6])
{
	int count = 0;
	for (int j = 0; j < 6; j++)
	{
		for (int i = 0; i < 5; i++)
		{
			if (b[i][j] == 99)
			{
				count++;
				for (int r = i; r > 0; r--)
					b[r][j] = b[r - 1][j];
			}
		}
		for (count; count > 0; count--)
			b[count - 1][j] = 6;
	}
}
void GenerateBead(int b[5][6])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			if (b[i][j] == 6)
				b[i][j] = rand() % 6;
		}
	}
}
