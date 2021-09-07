#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <stdio.h>
using namespace std;

template < typename T > void
print (T t)
{
 for (const auto & e:t) cout << e << " ";
  cout << endl;
}

vector <vector <int> > permutations(vector <int> &nums)
{
    if (nums.size() == 1) return {{nums[0]}};
    vector <vector <int> > res;
    for (int x = 0; x < nums.size(); x++)
    {
        int n = nums[0];
        nums.erase(nums.begin());
        vector <vector <int> > p = permutations(nums);
        for (auto &a : p)
        {
            a.emplace_back(n);
        }
        res.insert(res.end(), p.begin(), p.end());
        nums.emplace_back(n);
    }
    return res;
}

int main()
{
    vector <int> nums = {1, 2, 3};
    vector <vector <int> > ans = permutations(nums);
    for (auto &a : ans)
    {
        reverse(a.begin(), a.end());
        for (auto b : a) cout << b << " ";
        cout << endl;
    }
}
