/**

* The algorithm goes as follow:

1. Sort the jobs based on their deadlines.

2. Iterate from the end and calculate the available slots between every two consecutive deadlines. 
	Include the profit, deadline, and job ID of ith job in the max heap.

3. While the slots are available and there are jobs left in the max heap, 
	include the job ID with maximum profit and deadline in the result.

4. Sort the result array based on their deadlines.


**/

#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

// A structure to represent a job
struct Job {
	char id; // Job Id
	int dead; // Deadline of job
	int profit; // Profit earned if job is completed before
				// deadline
};

// Custom sorting helper struct which is used for sorting
// all jobs according to profit
struct jobProfit {
	bool operator()(Job const& a, Job const& b)
	{
		return (a.profit < b.profit);
	}
};

// Returns minimum number of platforms required
void printJobScheduling(Job arr[], int n)
{
	vector<Job> result;
	sort(arr, arr + n,[](Job a, Job b) { return a.dead < b.dead; });
	// set a custom priority queue
	priority_queue<Job, vector<Job>, jobProfit> pq;
	for (int i = n - 1; i >= 0; i--) {
		int slot_available;
		// we count the slots available between two jobs
		if (i == 0) {
			slot_available = arr[i].dead;
		}
		else {
			slot_available = arr[i].dead - arr[i - 1].dead;
		}
		// include the profit of job(as priority),
		// deadline and job_id in maxHeap
		pq.push(arr[i]);
		while (slot_available > 0 && pq.size() > 0) {
			// get the job with the most profit
			Job job = pq.top();
			pq.pop();
			// reduce the slots
			slot_available--;
			// add it to the answer
			result.push_back(job);
		}
	}
	// sort the result based on the deadline
	sort(result.begin(), result.end(),[&](Job a, Job b) { return a.dead < b.dead; });
	// print the result
	for (int i = 0; i < result.size(); i++)
		cout << result[i].id << ' ';
	cout << endl;
}

int main()
{
	// Driver code
	Job arr[] = { { 'a', 2, 100 },
				{ 'b', 1, 19 },
				{ 'c', 2, 27 },
				{ 'd', 1, 25 },
				{ 'e', 3, 15 } };
	int n = sizeof(arr) / sizeof(arr[0]);
	cout << "Following is maximum profit sequence of jobs "
			"\n";

	// Function call
	printJobScheduling(arr, n);
	return 0;
}

// This code is contributed By Reetu Raj Dubey

