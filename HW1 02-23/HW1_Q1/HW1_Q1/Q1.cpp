#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//////////////////////////////////////////////////////////////////////////
// ���u���
//////////////////////////////////////////////////////////////////////////
struct InfoClass {
	string Name;
	string Salary;
	string Bonus;
};

//////////////////////////////////////////////////////////////////////////
// Print �ť�
//////////////////////////////////////////////////////////////////////////
void PrintBlank(int n)
{
	for (int i = 0; i < n; i++)
		cout << " ";
}

void main()
{
	int num;						// ����
	InfoClass *infoArray;			// �}�C���
	int MaxWords[] = {0 ,0, 0};		// �̤j�r�ƭ���

	while (cin >> num)
	{
		// ��l��
		infoArray = new InfoClass[num];
		for (int i = 0; i < 3; i++)
			MaxWords[i] = 0;

		// ��J���
		for (int i = 0; i < num; i++)
		{
			cin >> infoArray[i].Name >> infoArray[i].Salary >> infoArray[i].Bonus;

			// �P�_�r�Ƥj�p
			MaxWords[0] = max(MaxWords[0], (int)infoArray[i].Name.length());
			MaxWords[1] = max(MaxWords[0], (int)infoArray[i].Salary.length());
			MaxWords[2] = max(MaxWords[0], (int)infoArray[i].Bonus.length());
		}

		// ��X
		for (int i = 0; i < num; i++)
		{
			// �ť�
			PrintBlank(MaxWords[0] - (int)infoArray[i].Name.length());
			cout << infoArray[i].Name << "|  ";

			PrintBlank(MaxWords[1] - (int)infoArray[i].Salary.length());
			cout << infoArray[i].Salary << "|  ";

			PrintBlank(MaxWords[2] - (int)infoArray[i].Bonus.length());
			cout << infoArray[i].Bonus << endl;
		}
		delete[] infoArray;
	}
}
