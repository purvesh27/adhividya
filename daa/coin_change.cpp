#include <iostream>
#include <vector>
using namespace std;

/* We have input values of N and an array Coins
that holds all of the coins. We use data type
of long because we want to be able to test
large values
without integer overflow*/
long getNumberOfWays(long N, vector<long> Coins)
{
	
	// Create the ways array to 1 plus the amount
	// to stop overflow
	vector<long> ways(N + 1);

	// Set the first way to 1 because its 0 and
	// there is 1 way to make 0 with 0 coins
	ways[0] = 1;

	// Go through all of the coins
	for(int i = 0; i < Coins.size(); i++)
	{
		
		// Make a comparison to each index value
		// of ways with the coin value.
		for(int j = 0; j < ways.size(); j++)
		{
			if (Coins[i] <= j)
			{
				
				// Update the ways array
				ways[j] += ways[(j - Coins[i])];
			}
		}
	}

	// Return the value at the Nth position
	// of the ways array.
	return ways[N];
}

void printArray(vector<long> coins)
{
	for(long i : coins)
		cout << i << "\n";
}

// Driver Code
int main()
{
	vector<long> Coins(3);
	Coins[0] = 1;
	Coins[1] = 5;
	Coins[2] = 10;
	
	cout << "The Coins Array:" << endl;
	printArray(Coins);
	
	cout << "Solution:" << endl;
	cout << getNumberOfWays(12, Coins) << endl;
}

// This code is contributed by mohit kumar 29

