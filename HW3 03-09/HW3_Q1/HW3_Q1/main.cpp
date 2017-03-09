#include <iostream>
#include <vector>

using namespace std;

// ��ӼƦr�@�� pair�A A >= B
struct numPair
{
	int numA = 0;
	int numB = 0;
};

// �j�J�Ϊ�����
vector<numPair>* EgyptianFraction(int num)
{
	vector<numPair> *numArray = new vector<numPair>();
	int tempNum = 0;
	for(long long int i = num * 2; i <= num * (num + 1); i++)
		if (i * num % (i - num) == 0)
		{
			numPair p;
			p.numA = (int)i;
			p.numB = (int)(i * num / (i - num));

			// �s�i�}�C��
			numArray->push_back(p);
		}
	return numArray;
}

void main()
{
	// �o�D�O���򰭪��j�J�Τ��ƪ��F�� ??????
	int num;											// �`�έn��J�X�����
	int tempNum;										// �n�] 1/x = 1/A + 1/B
	cin >> num;

	vector<vector<numPair> *>		outputArray;		// �Ψӿ�X���}�C


	// ���B��
	for (int i = 0; i < num; i++)
	{
		cin >> tempNum;
		outputArray.push_back(EgyptianFraction(tempNum));
	}

	// Output ��
	vector<numPair> *tempPair;
	for (int i = 0; i < num; i++)
	{
		tempPair = outputArray[i];
		cout << tempPair->size() << endl;
		for (int j = 0; j < (int)tempPair->size(); j++)
			cout << (*tempPair)[j].numA << " " << (*tempPair)[j].numB << endl;
		cout << endl;
	}
	outputArray.erase(outputArray.begin(), outputArray.end());
	system("PAUSE");
}