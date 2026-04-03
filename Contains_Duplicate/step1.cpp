#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

// bool containsDuplicate(const vector<int> &nums) {
// 	for (int i = 0; i < nums.size() - 1; i++) {
// 		for (int j = i + 1; j < nums.size(); j++) {
// 			if (nums[i] == nums[j])
// 				return (true);
// 		}
// 	}
// 	return (false);
// }

bool containsDuplicate(const vector<int> &nums) {
	set<int> s(nums.begin(), nums.end());
	if (s.size() != nums.size())
		return (true);
	else
		return (false);
}

// int main() {
// 	cout << containsDuplicate({1, 2, 3, 1}) << endl;
// 	cout << containsDuplicate({1, 2, 3, 4}) << endl;
// 	cout << containsDuplicate({1, 1, 1, 3, 3, 4, 3, 2, 4, 2}) << endl;
// }

