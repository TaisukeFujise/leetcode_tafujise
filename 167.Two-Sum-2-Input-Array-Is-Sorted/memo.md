## Step1

### 考えたこと

<!-- どのように問題を読み解き、解法を思いついたか -->
- Two Sumは、一つの値との差分を探す問題だったが、今回はすでにsort済みのものが与えられ、返り値も値のセットではなく値のindexのセットを返すようになっている。
	-> unordered_map<int, int> でvalueに対するindexを持つ解き方より、最初からsortされてるから元のvector<int>を使うことを想定していそう。
- index二つを変数においてtwo pointerの問題みたいにしたら、vector<int>のまま解けるそう
  - index1 = 0、index2 = numbers.size() - 1とおく
  - numbers[index1] + numbers[index2] がtargetより小さくなるまでindex2--
  - numbers[index1] + numbers[index2] == targetであれば、その時点の{index1 + 1, index2 + 1}を返す。そうでなければ、index1++でループ継続。

- 時間計算量は、indexを両端から動かしていくだけなので、O(N)
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int index1 = 0;
        int index2 = numbers.size() - 1;

        while(index1 < index2) {
            while (numbers[index1] + numbers[index2] > target) {
                index2--;
            }
            if (numbers[index1] + numbers[index2] == target)
                return {index1 + 1, index2 + 1};
            index1++;
        }
        return {};
    }
};
```
---

## Step2

### 参考にしたコード

- [Best Optimal Solution | Beats 100% | Java | C++ | Python | JavaScript](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/solutions/7652313/best-optimal-solution-beats-100-java-c-p-57x6)
  - index1を始点、index2を終点としてwhileループを回し以下のような条件分岐としていた。こちらの方が素直で良い。（自分のコードは、index2だけに注目してtargetより小さくなるまで減らすwhileループを内部に書いていた）
    - numbers[index1] + index2[index2] == targetならreturn {index1 + 1, index2 + 1}
    - numbers[index1] + index2[index2] < target なら index1++;
    - numbers[index1] + index2[index2] > target なら index2--;
  
- [【Video】Using Two Pointers to solve the question with O(1) space](https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/solutions/6744142/video-using-two-pointers-to-solve-the-qu-udto)
  - 上に同じ。

### コードの修正方針

<!-- 参考コードを読んで考えたことと自分のコードをどう直すか -->
<!-- 「他の人のコードを読んで考えたこと」と「改善するときに考えたこと」-->
- two pointerを動かすという着眼点は間違っていなかったが、whileループの条件分岐が直感的ではなかったので、そこを修正
  - < targetならindex1++
  - \> targetならindex2--
  - == targetならreturn {index1 + 1, index2 + 1}

```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int start = 0;
        int end = numbers.size() - 1;
        
        while (start < end) {
            int two_sum = numbers[start] + numbers[end];

            if (two_sum == target)
                return {start + 1, end + 1};
            else if (two_sum < target)
                start++;
            else if (two_sum > target)
                end--;
        }
        return {};
    }
};
```

### memo
- 
- 
