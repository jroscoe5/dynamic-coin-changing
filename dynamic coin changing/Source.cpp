// Jonnie Roscoe
// dynamic programming coin change

#include <iostream>
using namespace std;

const int inf = 100000;

void printArr(int arr[], int size)
{
	cout << "minimum array updated = {";
	for (int i = 0; i < size - 1; i++)
	{
		(arr[i] == inf) ? cout << "inf" : cout << arr[i];
		cout << ", ";
	}
	(arr[size - 1] == inf) ? cout << "inf" : cout << arr[size - 1];
	cout << "}" << endl;
}

void makeChange(int coinTypes[], int num_diff_coins, int targetValue)
{
	int* sequence = new int[targetValue + 1]; // to keep track of which coins are used to get to a value
	int* minimum = new int[targetValue + 1]; // to hold the minimum number of coins required to get to that value

  // set all values to infinity. (it takes an infinite amount of coins to get to minimum[i])
	for (int i = 1; i <= targetValue; i++)
	{
		minimum[i] = inf;
	}

	minimum[0] = 0; // the minimum number of coins to get a value of "0" (minimum[i]) will always be 0
	///printArr(minimum, targetValue + 1);

	// step thru each value from 1 to targetValue (in this case 42)
	for (int i = 1; i <= targetValue; i++)
	{
		// step thru each different type of coin
		for (int j = 0; j < num_diff_coins; j++)
		{
			// if targetValue is less than the current coin denomination we don't care about it - cannot make change less than coin denomination
			// if using 1 of our current coin + the minimum coins required to make change of minimum[currentValue - currentCoin]
			// is less than the current minimum[currentValue], update it to use the current coin type
			if (i >= coinTypes[j] && 1 + minimum[i - coinTypes[j]] < minimum[i])
			{
				minimum[i] = 1 + minimum[i - coinTypes[j]]; // update
				sequence[i] = j; // record what coin we used to get to this value
				///printArr(minimum, targetValue + 1);
			}
		}
	}

	// the min coins to make change of 42 will be found in the 42nd element of the array 
	cout << "The minimum number of coins to make change is: " << minimum[targetValue] << endl;
	cout << "Coins required:";
	while (targetValue)
	{
		// look at the coin needed to get to targetValue, print it, then look at the coin needed to get to targetValue - printed coin 
		cout << " " << coinTypes[sequence[targetValue]];
		targetValue = targetValue - coinTypes[sequence[targetValue]];
	}
	cout << endl;

	delete[] sequence;
	delete[] minimum;
}

int main()
{
	int* coinTypes;
	int num_diff_coins;
  int targetValue;

	cout << "This program dynamically calulates change based on different denominations of coin" << endl << endl;
	cout << "number of different coin denominations? : ";
	cin >> num_diff_coins;
	
	coinTypes = new int[num_diff_coins];

	for (int i = 0; i < num_diff_coins; i++)
	{
		cout << "coin denomination [" << (i + 1) << "]? : ";
		cin >> coinTypes[i];
	}

	cout << "value to make change for? : ";
	cin >> targetValue;

	makeChange(coinTypes, num_diff_coins, targetValue);

	delete [] coinTypes;

	cin.get();
	cin.get();

	return 0;
}