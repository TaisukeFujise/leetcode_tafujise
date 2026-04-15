## Step1

### 考えたこと

<!-- どのように問題を読み解き、解法を思いついたか -->
- 最初にsortしたほうが良さそう
- brute forceなら、max_lenを更新する方式でできそうだが、与えられた配列の全ての要素について連続するかどうか調べる必要があるので、O(N^2)かかる。
→ Time limit Exceeded
概算としては、最大N=10^5のため、実行時間概算は((10^5)^2) / 10^8 = 10^2 sかかる。

- O(N)にする要件があったが、思いつかず。

以下、Time limit Exceededのコード（時間計算量O(N^2)）
```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        sort(nums.begin(), nums.end());
    
        int nums_size = nums.size();
        int max_len = 0;
        for (int i = 0; i < nums_size; i++) {
            if (nums_size - i < max_len)
                break;
            int len = 1;
            for (int j = i; j < nums_size - 1; j++) {
                if (nums[j] == nums[j + 1])
                    continue;
                if (nums[j] != nums[j + 1] - 1)
                    break;
                len++;
            }
            if (max_len < len)
                max_len = len;
        }
        return max_len;
    }
};
```
---

## Step2

### 参考にしたコード

- [Best C++ 4 solution || Hash Table || Sorting || Brute Force -> Optimize || One Stop Solution.](https://leetcode.com/problems/longest-consecutive-sequence/solutions/3171985/best-c-4-solution-hash-table-sorting-bru-v593)
  - 連続する値の最初(start number of consecutive sequence)に目印をつける解法。
    - unordered_map<int, bool>で最初の地点をtrueとする方式
    - unordered_setにinsertして、set.findをうまく使った方式 => これは[【Video】Check n - 1](https://leetcode.com/problems/longest-consecutive-sequence/solutions/6398280/video-check-n-1-by-niits-b1u0)と同じで、その値が存在しているかどうかをうまく表現するので、自然な気がする。


### コードの修正方針

<!-- 参考コードを読んで考えたことと自分のコードをどう直すか -->
<!-- 「他の人のコードを読んで考えたこと」と「改善するときに考えたこと」-->
- 隣接値の存在確認をunordered_setでする方針で実装する
- n - 1の値が存在するかどうかで、maxlenのcountを始めるため、forループは二重になるが、同じ部分をforループで探索することはないため、時間計算量はO(N)となる。よって実行時間概算は10^5 / 10^8 = 10 ^ (-3) = 10 ms。

```cpp
class Solution {
public:
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> num_set(nums.begin(), nums.end());

        int maxlen = 0;
        for (int num : num_set) {
            if (num_set.find(num - 1) == num_set.end()) {
                int len = 1;
                while(num_set.find(num + len) != num_set.end()) {
                    len++;
                }
                maxlen = max(maxlen, len);
            }
        }
        return maxlen;
    }
};
```

### memo
1. 「問題に必要な情報だけを残す」
   → 配列の順序・重複は捨てて良い。
2. 「データ構造を問題に合わせて選ぶ」
   → 隣接値の存在確認が本質だからunordered_set
3. 無駄な起点を排除
   → 全ての要素から探索しない。開始点だけ選ぶ。

- 「問題で本当に必要なのが「順序」「頻度」「存在」のどれなのかを見極めること」
  -> 順序、頻度は今回不要
  -> 存在＝> unordered_set
  - 「ソートで順序を作る」のではなく、「集合で隣接関係だけ直接調べる」 = 「整列に頼らず、必要な情報だけを高速に引けるデータ構造を選ぶ」
	- sortがまず思い付いたが、sortを使うだけで、O(logN)の計算量がかかってしまうということを考慮しておく必要があったしておく必要があった。

