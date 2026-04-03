#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

// bool containsDuplicate(const vector<int>& nums) {
// 	unordered_map<int, int> hash;

// 	for (int i : nums) {
// 		if (hash[i] > 0)
// 			return (true);
// 		hash[i] ++;
// 	}
// 	return (false);
// }

int main() {
	cout << containsDuplicate({1, 2, 3, 1}) << endl;
	cout << containsDuplicate({1, 2, 3, 4}) << endl;
	cout << containsDuplicate({1, 1, 1, 3, 3, 4, 3, 2, 4, 2}) << endl;
}
