#include <iostream>
#include <string>

using namespace std;



//////////////////////////////////////////////////////////////////////////
//  �e�O
//////////////////////////////////////////////////////////////////////////
struct Panel
{
	// ��V
	enum Direction
	{
		LU = 0,																	// ���W
		LD = 1,																	// ���U
		RU = 2,																	// �k�W
		RD = 3																	// �k�U
	};

	string *map;
	bool IsValid = true;
	int w, h;

	void Init(int w, int h)													// ��l��
	{
		this->w = w;
		this->h = h;

		string line = "";
		for (int i = 0; i < w; i++)
			line += "*";

		// �зs�}�C
		map = new string[h];
		for (int i = 0; i < h; i++)
			map[i] = line;
	}										
	void Delete()															//�Ŷ�
	{
		delete[] map;
	}													

	bool CheckValid(int x, int y)											// �T�{�O�_�O���ıo
	{
		if (x < w && y < h && x >=0 && y >= 0)
			return true;
		IsValid = false;
		return false;
	}

	void DrawLine(int x1, int y1, int x2, int y2)							// �e�u
	{
		if (CheckValid(x1, y1) && CheckValid(x2, y2) && IsValid)
		{
			#pragma region �P�_��V
			int xdir, ydir;
			if (x1 > x2)
				xdir = -1;
			else if (x1 == x2)
				xdir = 0;
			else
				xdir = 1;

			if (y1 > y2)
				ydir = -1;
			else if (y1 == y2)
				ydir = 0;
			else
				ydir = 1;
			#pragma endregion
			#pragma region ����
			int startX = x1;
			int startY = y1;
			for (; startX != x2 || startY != y2; startX += xdir, startY += ydir)
				map[startY][startX] = 'X';
			map[y2][x2] = 'X';
			#pragma endregion
		}
	}
	void DrawSquare(int x, int y, int width)								// �e�����
	{
		// �k
		DrawLine(x + width - 1, y, x + width - 1, y + width - 1);

		// �U
		DrawLine(x, y + width - 1, x + width - 1, y + width - 1);

		// ��
		DrawLine(x, y, x, y + width - 1);

		// �W
		DrawLine(x, y, x + width - 1, y);

	}
	void DrawTriangle(int x, int y, int width, int dir)						// �e�T����
	{
		switch (dir)
		{
		case LU:
			DrawLine(x, y, x - width + 1, y);
			DrawLine(x, y, x, y - width + 1);
			DrawLine(x - width + 1, y, x, y - width + 1);
			break;
		case LD:
			DrawLine(x, y, x, y + width - 1);
			DrawLine(x, y, x - width + 1, y);
			DrawLine(x - width + 1, y, x , y + width - 1);
			break;
		case RU:
			DrawLine(x, y, x + width - 1, y);
			DrawLine(x, y, x, y - width + 1);
			DrawLine(x + width - 1, y, x, y - width + 1);
			break;
		case RD:
			DrawLine(x + width - 1, y, x, y + width - 1);
			DrawLine(x, y, x + width - 1, y);
			DrawLine(x, y, x, y + width - 1);
			break;
		}
	}

	void Print()
	{
		for (int i = 0; i < h; i++)
			cout << map[i] << endl;
	}
};
int main()
{
	int		a, b;																// �e�O�j�p
	string	commondStr;															// �R�O�r��
	Panel	p;																	// �e��

	// ��J�e���j�p
	cin >> a >> b;
	p.Init(b, a);
	do 
	{
		// ��J
		cin >> commondStr;
		
		if (commondStr == "S")
		{
			int tempW, tempX, tempY;
			cin >> tempW >> tempX >> tempY;
			p.DrawSquare(tempX, tempY, tempW);
		}
		else if (commondStr == "T")
		{
			int tempW, tempX, tempY, tempDirIndex;
			string tempDir;
			cin >> tempW >> tempX >> tempY >> tempDir;

			#pragma region ��V�B�z
			if (tempDir[0] == 'L')
				tempDirIndex = 0;
			else
				tempDirIndex = 1;
			tempDirIndex <<= 1;													// �k���@��

			if (tempDir[1] == 'D')
				tempDirIndex++;
			#pragma endregion
			p.DrawTriangle(tempX, tempY, tempW, tempDirIndex);
		}
		else if (commondStr == "L")
		{
			int tempX1, tempY1, tempX2, tempY2;
			cin >> tempX1 >> tempY1 >> tempX2 >> tempY2;
			p.DrawLine(tempX1, tempY1, tempX2, tempY2);
		}

		if (p.IsValid)
			p.Print();
		else
		{
			cout << "Out of range." << endl;
			p.IsValid = true;
		}
		cout << endl;
	} while (commondStr != "EXIT");
	return 0;
}