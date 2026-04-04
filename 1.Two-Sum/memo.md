## Step1

### 考えたこと

<!-- どのように問題を読み解き、解法を思いついたか -->
- vecorを前から一つ取り出して, targetとの差分に一致するものを探す方式
  - これだと、forループを二重にする必要もあり、時間計算量がO(n^2)かかる
<一応コード>
```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int diff;

        for (int i = 0; i < nums.size() - 1; i++) {
            diff = target - nums[i];
            for (int j = i + 1; j < nums.size(); j++) {
                if (diff == nums[j])
                    return {i, j};
            }
        }
        return {};
    }
};
```

- 差分と一致するものを探す検索部分で、hash mapを使用したら良さそう
- 一致するかを確認した後に、hash mapに追加していく方式が最短かも。
- 時間計算量は平均O(N)、空間計算量はかわらずO(N)


```cpp
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> num_map;
        int diff;

        for (int i = 0; i < nums.size(); i++) {
            diff = target - nums[i];
            if (num_map.contains(diff))
                return {num_map[diff], i};
            num_map[nums[i]] = i;
        }
        return {};
    }
};
```
---

## Step2

### 参考にしたコード

- [editorial](https://leetcode.com/problems/two-sum/editorial)
  - Brute Forceっていうのか総当たりって。
  - two pass hashは、一度全て格納（同じkeyは上書き）してから、`hash.find(complement) != hash.end() && hash[complement] != i`がtrueで返してる。なるほど
  - one pass hashは、ほとんど自分の回答と同じ。findかcontainsの違い。findだと1回の検索で書けそうで良いからこっちに慣れたい。
	```cpp
	auto it = hash.find(diff);
	if (it != hash.end())
		return {it->second, i};
	```

- [Shunii85/arai60/pull/11](https://github.com/Shunii85/arai60/pull/11/changes)
  - 実行時間の推定の話
    - 時間計算量の式に、データの最大サイズを代入　→ ステップ数概算
      - ex）O(N) にN = 10^4を代入 ※ constrainsより、今回は`2 <= nums.length <= 10^4`
      - 言語ごとの1秒あたりに処理可能なステップ数概算によって割れば、実行時間算出できる
        - C++: 約1~10億（10^8 ~ 10^9）ステップ / 秒
  ```
  実行時間 = 10^-4 ~ 10^-5 秒 = 0.1ms ~ 0.01ms
  ```
  - 実装について
    - num_to_indexという命名がわかりやすくて良さそう
    - insertによって追加しているかどうかとif文の条件がcontainsがfalseの時という条件が自分と違う点だったが、解法の方向性は同じ。


### コードの修正方針

<!-- 参考コードを読んで考えたことと自分のコードをどう直すか -->
<!-- 「他の人のコードを読んで考えたこと」と「改善するときに考えたこと」-->
- 命名の修正とfindを使用することで無駄なアクセスを減らす。

```cpp
class Solution {
public:
    vector<int> twoSum(const vector<int>& nums, int target) {
        unordered_map<int, int> num_index;
        int diff;

        for (int i = 0; i < nums.size(); i++) {
            diff = target - nums[i];
            auto it = num_index.find(diff);
            if (it != num_index.end())
                return {it->second, i};
            num_index[nums[i]] = i;
        }
        return {};
    }
};
```
