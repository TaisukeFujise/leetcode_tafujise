## Step1

### 考えたこと

<!-- どのように問題を読み解き、解法を思いついたか -->
- 時間計算量の制約がO(log(m * n))は、log(m) (= 何行目かを探す二分探索) + log(n) (= 何行目かを探す二分探索)を意味していると考えられる。 

- 行の探索：matrix[i][0] <= targetとなる最大のiの行が欲しい -> 半開区間での二分探索で初めてtarget < matrix[j][0]となるjを探して-1すれば求まる。
- 列の探索：単純な二分探索。targetと一致する要素を探す。-> 半開区間での二分探索で初めてtarget <= metrix[ROW][i]となるiを求めてそれがtargetと一致するかを見る。



```cpp
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int top = 0;
        int bottom = matrix.size();

        while (top < bottom) {
            int middle = top + (bottom - top) / 2;
            if (matrix[middle][0] <= target) {
                top = middle + 1;
            } else {
                bottom = middle;
            }
        }
        if (top == 0) {
            return false;
        }
        int row = top - 1;

        int left = 0;
        int right = matrix[row].size();
        while (left < right) {
            int middle = left + (right - left) / 2;
            if (matrix[row][middle] < target) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }
        if (left < matrix[row].size() && matrix[row][left] == target) {
            return true;
        }
        return false;
    }
};

```
---

## Step2

### 参考にしたコード

- [github.com/yamashita-ki/codingTest/pull/14](https://github.com/yamashita-ki/codingTest/pull/14/changes)
    - step1 二次元配列を一次元配列に変換してから二分探索を実行していた。
    ```cpp
    int totalElement = matrix.size() * matrix[0].size();
    vector<int> flag_matrix(totalElement);
    // forループで格納
    ```
    => 新たにvector<int>を作成するため空間計算量が余分にかかっているとPR作成者も言及されていた。空間計算量O(m * n)
    - step2 一次元配列とみなすが、変換せずにrows, colsを用いてleft, rightを更新する方式（閉区間）
    ```cpp
    int rows = matrix.size();
    int cols = matrix[0].size();

    int left = 0;
    int right = rows * cols - 1;
    while (left < right) {
        int middle = left + (right - left) / 2;
        int row = middle / cols;
        int col = middle % cols;
        if (target > matrix[row][col]) {
            left = middle + 1;
        } else if (target < matrix[row][col]) {
            right = middle - 1;
        } else {
            return true;
        }
    }
    return false;
    ```
- [【Video】Simple Solution](https://leetcode.com/problems/search-a-2d-matrix/solutions/6750177/video-simple-solution-by-niits-xp0d)
    - solution1は自分の解法と同じ発想。
    - solution2は前述の参考コードのstep2だった。
    -> やはりmatrixを1つの昇順の配列としてみなし、一回のbinary searchで可能か」という発想に辿り着くべきだった。

### コードの修正方針

<!-- 参考コードを読んで考えたことと自分のコードをどう直すか -->
<!-- 「他の人のコードを読んで考えたこと」と「改善するときに考えたこと」-->
- flatten indexして、一度のbinary searchで探す方式で進める。

```cpp
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


```

