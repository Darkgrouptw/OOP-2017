#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct ElementSet
{
	int		NumberElement = 0;								// ��Ʀr
	char	operationElement;								// �� Operation
	int		state = 0;										// 0 �N��S���ϥΡA1 �N��Ʀr�A2 �N��O Operation�A3 �N��O�t�ƫ᭱�n���@�� Operation
};

// ���J���rŪ�i�ӡA�M�� parse ���@�� ElementSet �s�_��
vector<ElementSet *> EvaluateString(string input)
{
	vector<ElementSet *> set;

	// ���A
	// 0 => Ū�Ʀr
	// 1 => Ū�r��
	int state = 0;

	// �[�J�Ĥ@�ӭ�
	ElementSet *tempE = new ElementSet();
	set.push_back(tempE);

	for (int i = 0; i < (int)input.length(); i++)
	{
		#pragma region ���L�ť�
		if (input[i] == ' ')
			continue;
		#pragma endregion
		
		// �O�Ʀr���ɭ�
		if ((set[set.size() - 1]->state == 0 || set[set.size() - 1]->state == 2) && input[i] == '-')
		{
			set[set.size() - 1]->state = 3;
			continue;
		}
		#pragma region  �Ʀr & �Ÿ��P�_
		switch (input[i])
		{
		case '+':
		case '-':
		case '*':
		case '/':
			// �P�_�O�_�J��Operation
			if (set[set.size() - 1]->state == 3)
			{
				set[set.size() - 1]->NumberElement *= -1;
				set[set.size() - 1]->state = 1;
			}

			// ��Ÿ��[�i�h
			tempE = new ElementSet();
			tempE->operationElement = input[i];
			tempE->state = 2;
			set.push_back(tempE);

			// ��Ū��[�i�h
			tempE = new ElementSet();
			set.push_back(tempE);
			break;

		default:
			tempE = set[set.size() - 1];
			tempE->NumberElement = tempE->NumberElement * 10 + input[i] - '0';
			if(tempE->state != 3)
				tempE->state = 1;
			break;
		}
		#pragma endregion
	}
	if (set[set.size() - 1]->state == 3)
	{
		set[set.size() - 1]->NumberElement *= -1;
		set[set.size() - 1]->state = 1;
	}

	return set;
}

// +-*/ ���u������ table
int PriorityTable(char operation)
{
	if (operation == '*' || operation == '/')
		return 2;
	return 1;
}

//��������
void InfixToPostfix(vector<ElementSet *> &forms)
{
	// �Ȧs������
	vector<ElementSet *> tempArray;							// �Ȧs���}�C

	vector<ElementSet *> operStack;							// �Ÿ����}�C

	#pragma region Copy �@������
	for (int i = 0; i < forms.size(); i++)
		tempArray.push_back(forms[i]);
	#pragma endregion
	#pragma region ����������
	// ����F��M�šA�̫�A��F��[�i�h
	forms.erase(forms.begin(), forms.end());

	for (int i = 0; i < tempArray.size(); i++)
		switch (tempArray[i]->state)
		{
		case 1:
			forms.push_back(tempArray[i]);
			break;
		case 2:
			int NowPriority = PriorityTable(tempArray[i]->operationElement);														// �{�b�Ÿ��� �u������
			int PrePriority = (operStack.size() == 0) ? -1 : PriorityTable(operStack[operStack.size() - 1]->operationElement);		// �e�@�ӲŸ��� �u������ (-1 �N��S��)

			if (PrePriority == -1 || NowPriority >= PrePriority)
				operStack.push_back(tempArray[i]);
			else if (NowPriority < PrePriority)
			{
				// �o��ݭn��Ҧ��p�� Operation ����X��
				while (NowPriority < PrePriority)
				{
					forms.push_back(operStack[operStack.size() - 1]);
					operStack.pop_back();
					PrePriority = (operStack.size() == 0) ? -1 : PriorityTable(operStack[operStack.size() - 1]->operationElement);
				}
				operStack.push_back(tempArray[i]);
			}
			break;
		}

	// �ݭn��Ѿl�� operStack ��X��
	for (int i = operStack.size() - 1; i >= 0; i--)
	{
		ElementSet *lastE = operStack[operStack.size() - 1];
		forms.push_back(lastE);
		operStack.pop_back();
	}
	#pragma endregion


}

// ���B���~~~
int PostifxOperation(vector<ElementSet *> forms)
{
	vector<double> numStack;								// �Ʀr���}�C
	for (int i = 0; i < forms.size(); i++)
		switch (forms[i]->state)
		{
		case 1:
			numStack.push_back((double)forms[i]->NumberElement);
			break;
		case 2:
			double FirstNumber = numStack[numStack.size() - 1];
			double SecondNumber = numStack[numStack.size() - 2];
			numStack.pop_back();

			// �Ÿ����P�_
			switch (forms[i]->operationElement)
			{
			case '+':
				numStack[numStack.size() - 1] = SecondNumber + FirstNumber;
				break;
			case '-':
				numStack[numStack.size() - 1] = SecondNumber - FirstNumber;
				break;
			case '*':
				numStack[numStack.size() - 1] = SecondNumber * FirstNumber;
				break;
			case '/':
				numStack[numStack.size() - 1] = SecondNumber / FirstNumber;
				break;
			}
			break;
		}
	return (int)numStack[0];
}

void main()
{
	// �`�@���X�����
	int num;
	cin >> num;
	getchar();														// �� enter
	
	string inputStr;
	for (int i = 0; i < num; i++)
	{
		// ��|�h�B�⪺���lŪ�i��
														
		getline(cin, inputStr);

		vector<ElementSet *> tempArray = EvaluateString(inputStr);
		InfixToPostfix(tempArray);
		cout << PostifxOperation(tempArray) << endl;
		// ���դ����O�_���T
		/*for (int j = 0; j < (int)tempArray.size(); j++)
		{
			ElementSet *tempE = tempArray[j];
			if(tempE->state == 1)
				cout << tempE->NumberElement << " ";
			else
				cout << tempE->operationElement << " ";
		}
		cout << endl;*/
	}
	system("PAUSE");
}