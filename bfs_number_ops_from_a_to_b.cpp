
/*
find the min number of operations to change number a to number b, allowing (1) add 1, 
(2) multiplied by 2 (3) divided by 2
for example: 2 operations for 12 -->8: 
12-->6-->7-->8
*/

#include <bits/stdc++.h>
using namespace std;


long long minOperations(long long x, long long y)
{
	set<long long> visit;

	queue<pair<long long, long long> > q;
	q.push({ x, 0 });
	pair<long long, long long> node;

	while (!q.empty()) {
		node = q.front();
		q.pop();

		if (node.first == y)
			return node.second;

		visit.insert(node.first);

		if (node.first * 2 == y || node.first + 1 == y)
			return node.second + 1;
		if (node.first%2==0 && node.first/2==y) return node.second + 1;

		if (!visit.count(node.first * 2)) {
			q.push({node.first * 2, node.second+1});
		}
		if (!visit.count(node.first + 1)) {
			q.push({node.first + 1, node.second+1});
		}
		if (node.first%2==0 && !visit.count(node.first / 2)) {
			q.push({node.first/2, node.second+1});
		}
	}
	return -1;
}

// Driver code
int main()
{
	long long n, x, y;
	cin >> n;
	for(int i=0; i<n; i++)
	{
        cin >> x >> y;
        cout << minOperations(x, y) << endl;
	}
}

