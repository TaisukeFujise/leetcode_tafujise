## Step1

### 考えたこと

<!-- どのように問題を読み解き、解法を思いついたか -->
-　"You must write an algorithm that runs in O(log N) time." とあるので、単純な探索ではなく、二分探索による探索が必要。 
- 今回与えられる配列はsorted in ascending ではあるが、循環配列のため、二分探索でmidより前を探すか、midより後を探すかは、leftとrightのindexにある数値との大小関係で求められそう？
- 循環配列のため、left, mid, rightの関係は3通り
    - left < mid < right の場合 -> leftが最小値
    - mid  < right < left の場合 -> left < x < midの間に最小値があるので、rightをmidに更新(※right自体が最小の可能性があるため)
    - right < left < mid の場合 -> mid < x < rightの間に最小値があるので、leftをmid + 1に更新（※ left自体は最小値になる可能性がないため）


- 今回の二分探索には端点の値の参照をするため、閉区間を使用した。
- 探索の終了条件としては、残りの要素が2つになった時に終了し、min(nums[left], nums[right])を返すようにしている（条件：left + 1 < right)

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;

        while (left + 1 < right) {
            int mid = left + (right - left) / 2;

            if (nums[left] < nums[mid] && nums[mid] < nums[right]) {
                return nums[left];
            } else if (nums[mid] < nums[right] && nums[right] < nums[left]) {
                right = mid;
            } else if (nums[right] < nums[left] && nums[left] < nums[mid]) {
                left = mid + 1;
            } else {
                return -1;
            }
        }
        return min(nums[left], nums[right]);
    }
};
```
---

## Step2

### 参考にしたコード

- [【Video】Using part of input array to compare numbers.](https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/solutions/6750367/video-using-part-of-input-array-to-compa-q291)
    - midとrightの比較だけで済むのか。自身のコードは少し冗長だった。
        - mid < right → 「left < mid < right」 or 「mid < right < left」のみ
        - mid > right -> 「right < left < mid」のみ
    以下のように自分のコードは改善できそう。
    ```cpp
    if (nums[mid] <= nums[right]) {
        if (nums[left] < nums[mid]){
            return nums[left];
        }
        right = mid;
    } else {
        left = mid + 1;
    }
    - また、nums[mid] <= nums[right]と等号が入っていることで、whileの条件もシンプルにleft < rightにできて、returnも nums[left]で済んでいる。
    ```
- [github.com/5ky7/arai60/pull/42](https://github.com/5ky7/arai60/pull/42/changes)
    - 配列numsからテキトーにとった要素nums[0]より、小さい要素が初めて出てくる場所を残りの配列から探す二分探索。値を探すというよりも境界に着目した視点が二分探索の解像度が高そうなコードだと思った。

### コードの修正方針

<!-- 参考コードを読んで考えたことと自分のコードをどう直すか -->
<!-- 「他の人のコードを読んで考えたこと」と「改善するときに考えたこと」-->
- エラー処理ってする必要あるのかな。Constrainsで`1 <= n <= 5000`とあるからない方が適切なのかと思った。
- 早期リターンで、rotatedされていない場合の処理は残しておく。

```cpp
class Solution {
public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;

        while (left < right) {
            int middle = left + (right - left) / 2;
            if (nums[middle] <= nums[right]) {
                if (nums[left] < nums[middle]) {
                    return nums[left];
                }
                right = middle;
            } else {
                left = middle + 1;
            }
        }
        return nums[left];
    }
};
```
