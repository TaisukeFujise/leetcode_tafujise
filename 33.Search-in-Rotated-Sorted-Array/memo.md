## Step1

### 考えたこと

<!-- どのように問題を読み解き、解法を思いついたか -->
- "you must write an algorithm with O(log n) runtime complexity"とあるので、二分探索等が必要。

- "153.Find-Minimum-in-Rotated-Sorted-Array"のように、middleとrightの比較をして配列が循環しているかを確認してから、targetの比較をした方がいい？
    - nums[left] <= nums[middle]の場合：左半分が昇順 -> target が左半分に含まれているなら、right = middle - 1。そうでないなら、left = middle + 1;
    - nums[left] > nums[middle]の場合： 右半分が昇順 -> target が右半分に含まれているなら、left = middle + 1。そうでないなら、right = middle - 1;

- rightをtargetが含まれるかどうかの比較の際にindexとして使用したいので、閉区間を使用して実装した。

```cpp
class Solution {
 public:
  int search(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;

    while (left <= right) {
      int middle = left + (right - left) / 2;
      if (nums[middle] == target) {
        return middle;
      }
      if (nums[left] <= nums[middle]) {
        if (nums[left] <= target && target < nums[middle]) {
          right = middle - 1;
        } else {
          left = middle + 1;
        }
      } else {
        if (nums[middle] < target && target <= nums[right]) {
          left = middle + 1;
        } else {
          right = middle - 1;
        }
      }
    }
    return -1;
  }
};
```

## Step2

### 参考にしたコード

- [【Video】Find a sorted part in ascending order](https://leetcode.com/problems/search-in-rotated-sorted-array/solutions/6753669/video-find-a-sorted-part-in-ascending-or-x2pn)
 - 同じ解法
- [github.com/5103246/LeetCode_Arai60/pull/41](https://github.com/5103246/LeetCode_Arai60/pull/41/changes)
    - 確かに、前回の内容（153. Find-Minimum-in-Rotated-Sorted-Array）から、配列を一度昇順に直して、simpleな二分探索によりtargetを探したとしても、時間計算量としてはO(logN + logN) = O(logN)なのか。定数倍は違うけども。

- [github.com/dxxsxsxkx/leetcode/pull/43](https://github.com/dxxsxsxkx/leetcode/pull/43/changes)
    *Left-rotation の結果として左側に置かれた値は全て nums.back() より大きく、そうでない値は全て小さい。このことを利用して、mid と target がどちら側の部分配列にあるかを知ることができる。
両方が同じ側の部分配列に属していればその中で通常の二分探索をすれば良い。そうでない場合は target が存在する側の部分配列で二分探索をすれば良い。*
    - この解法は、与えられた配列を最後の要素last_numでLHSとRHSで分けて、midとtargetが同じ領域に含まれているかどうかで、探索幅を縮めていっている。
    - 私の解法では、毎回middleを基準として左側と右側のどちらが昇順かどうかを判断して、探索幅を狭める方式で、このかたの解法は与えられた配列を最初から集合として適切に捉えられており、意図が明確でいいと思った。

### コードの修正方針

<!-- 参考コードを読んで考えたことと自分のコードをどう直すか -->
<!-- 「他の人のコードを読んで考えたこと」と「改善するときに考えたこと」-->

- nums.back()で配列を区分けする方式でといてみる。
```cpp

class Solution {
 public:
  int search(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size() - 1;
    int last_num = nums.back();

    while (left <= right) {
      int middle = left + (right - left) / 2;
      if (nums[middle] == target) {
        return middle;
      }

      bool middle_in_lhs = nums[middle] > last_num;
      bool target_in_lhs = target > last_num;

      if (middle_in_lhs == target_in_lhs) {
        if (target < nums[middle]) {
          right = middle - 1;
        } else {
          left = middle + 1;
        }
      } else {
        if (middle_in_lhs) {
          left = middle + 1;
        } else {
          right = middle - 1;
        }
      }
    }
    return -1;
  }
};
```

