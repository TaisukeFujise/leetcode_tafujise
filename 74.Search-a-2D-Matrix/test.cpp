#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int rows = matrix.size();
    int cols = matrix[0].size();

    int left = 0;
    int right = rows * cols;
    while (left < right) {
      int middle = left + (right - left) / 2;
      int row = middle / cols;
      int col = middle % cols;
      if (matrix[row][col] < target) {
        left = middle + 1;
      } else {
        right = middle;
      }
    }
    if (left < rows * cols && matrix[left / cols][left % cols] == target) {
      return true;
    }
    return false;
  }
};

int main() {
  vector<vector<int>> matrix = {{1}, {3}};

  Solution solution;

  bool ans = solution.searchMatrix(matrix, 3);
  if (ans) {
    cout << "true" << endl;
  } else {
    cout << "false" << endl;
  }
}
