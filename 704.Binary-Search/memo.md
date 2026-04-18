## Step1

### 考えたこと

<!-- どのように問題を読み解き、解法を思いついたか -->
- unordered_map<int, int>のkeyにnum[index], valueにindexを格納する方式であっても、格納でO(N)と検索でO(1)なので時間計算量O(N)。
- 課題要件で時間計算量O(logN)があるので、不可。
```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        unordered_map<int, int> num_to_index;

        for (int i = 0; i < nums.size(); i++) {
            num_to_index[nums[i]] = i;
        }
        if (num_to_index.contains(target)) {
                return num_to_index[target];
        }
        return -1;
    }
};
```
- ただ、すでにsortされたvector<int>が渡されているため、おそらくそのまま使用することが想定されており、時間計算量O(logN)という指示からも二分探索だとわかる
- 時間計算量は、1回調べるごとに探索範囲が半分になり、1以下になれば探索終了なので、
```
k回後の候補数はN / 2^kとかけるので
N / 2^k <= 1
N <= 2^k
log_2 N <= k
```
よって高々O(logN)で探索できる。

```cpp
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int start = 0;
        int end = nums.size() - 1;

        while (start <= end) {
            int middle = start + (end - start) / 2;

            if (nums[middle] == target) {
                return middle;
            } else if (nums[middle] < target) {
                start = middle + 1;
            } else if (nums[middle] > target) {
                end = middle - 1;
            }
        }
        return -1;
    }
};
```


## Step2

### 参考にしたコード

leetcodeのsolutionも基本的には同じ解法だったので、省略します

