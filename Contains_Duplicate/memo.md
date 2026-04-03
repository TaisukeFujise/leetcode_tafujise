## Step1 ([step1.cpp](./step1.cpp))

### 考えたこと

<!-- どのように問題を読み解き、解法を思いついたか -->
- 前から一つずつ比較する二重ループだと計算量がO(N ^ 2)なので改善したい
- vectorをsetに格納するのは、O(logN) ← setの内部実装が木構造のため
- setもvectorも.sizeは計算量O(1)なので、変換後のサイズが一致すれば重複がなく、一致しなければ重複があったと判断できる。
-> 最終的に時間計算量はO(NlogN)で空間計算量はO(N)となる

※ unordered_setに格納するやり方であれば、ハッシュテーブルを使用するため、計算量をO(NlogN)からO(N)に減らせることにあとから気づいた。

```
class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> s(nums.begin(), nums.end());
        if (s.size() != nums.size())
            return (true);
        else
            return (false);
    }
};
```
---

## Step2 ([step2.cpp](./step2.cpp))

### 参考にしたコード

- [leetcodeのsolutions](https://leetcode.com/problems/contains-duplicate/solutions/3672475/4-methods-c-java-python-beginner-friendl-zozw)
	- sortした後に隣接する値を比較する方式はシンプルだけど、思い付いてなかった
	- unordered_setとunordered_mapの方式があるが、setのメソッドを無駄に覚えるよりもmapの方がシンプルで可読性が高い気がする

- [ryosuketc/leetcode_grind75/pull/24/changes](https://github.com/ryosuketc/leetcode_grind75/pull/24/changes)
  - setには.containsと.emplaceもあるのか。

### コードの修正方針

<!-- 参考コードを読んで考えたことと自分のコードをどう直すか -->
<!-- 「他の人のコードを読んで考えたこと」と「改善するときに考えたこと」-->
- unordered_mapで実装

```
class Solution {
public:
    bool containsDuplicate(const vector<int>& nums) {
        unordered_map<int, int> hash;

        for (int i : nums) {
            if (hash[i] > 0)
                return (true);
            hash[i]++;
        }
        return (false);
    }
};
```
