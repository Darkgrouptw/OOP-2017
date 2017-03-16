#include <iostream>
#include <cmath>

using namespace std;

void CountNOrder(int *years, const int Count)
{
	double NOrder = log2(2);
	int CurrentOrder = 3;
	double CPU = 4;
	for (int i = 0; i < Count; i++)
	{
		while (NOrder <= CPU)
		{
			NOrder += log2(CurrentOrder++);
		}
		CPU *= 2;
		years[i] = CurrentOrder - 2;
	}
}

int main()
{
	int num;

	// 前處理
	const int YearCount = (220 - 190 + 1);
	int *years = new int[YearCount];
	CountNOrder(years, YearCount);

	while (cin >> num)
	{
		// 預計要次方的間隔
		int CountYear = num / 10 - 190;
		cout << years[CountYear] << endl;

	}
	return 0;
}