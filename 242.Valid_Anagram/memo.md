## Step1 

### 考えたこと

<!-- どのように問題を読み解き、解法を思いついたか -->
- 一つの文字列の中に同じ文字も登場するため、登場回数が必要そう
- 文字列sを文字をkey、登場回数をvalueとするmapに変換して、文字列tの文字それぞれに対してそのmapと照合したらできそう。
- hash[c]という検索部分は、map(O(logN))よりもunordered_map(O(1))の方が時間計算量が早いので、そちらを採用。

```cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map<char, int> hash;

        for (char c : s) {
            hash[c]++;
        }
        for (char c : t) {
            if (hash[c] == 0) {
                return (false);
            }
            hash[c]--;
        }
        for (char c : s) {
            if (hash[c] > 0) {
                return (false);
            }
        }
        return (true);
    }
};
```
---

## Step2 

### 参考にしたコード

- [【Video】4 Solutions](https://leetcode.com/problems/valid-anagram/solutions/6101148/video-4-solutions-by-niits-x6b2)
  - 小文字という制約から、a~zの登場回数を保持する固定長配列を使用する解法もあるのか。hashよりも早いし、メモリ効率も良さそう。
  - 最初に文字列sとtの長さの比較をすることで、同時にsとtのmapを作成する手法は、オーダーはO(n)で同じだが定数倍速そう。
- [ryosuketc/leetcode_grind75/pull/7/changes](https://github.com/ryosuketc/leetcode_grind75/pull/7/changes)
  - atと[]の範囲外アクセスについて。
    - []は未定義で、atは例外を投げるのはvectorで、今回のmapでは存在しなければ新たにキーを作成する
  - containerのfor文について
    - for (auto &x: container) → 読み取りのみ
    - for (auto& x: container) → 書き換えたい
    - for (auto  x: container) → 軽い型でコピーしていいなら
      - 小さい（int, char） → コピーOK
      - 大きい（string, pair, struct） → 参照
 こんな整理でいいのかも？


### コードの修正方針

<!-- 参考コードを読んで考えたことと自分のコードをどう直すか -->
<!-- 「他の人のコードを読んで考えたこと」と「改善するときに考えたこと」-->
- a~zの配列にしてカウントする方式が、計算量は変わらず、要素数26のint型配列でメモリ効率が良いので、採用して修正
- 最初に長さ比較を入れることで同時にカウントする方式に
  - map[s[i] - 'a']はインクリメント
  - map[t[i] - 'a']はディクリメント

```cpp
class Solution {
public:
    bool isAnagram(string s, string t) {
        vector<int> count_map(26, 0);

        if (s.length() != t.length())
            return (false);
        for (int i = 0; i < s.length(); i++) {
            count_map[s[i] - 'a']++;
            count_map[t[i] - 'a']--;
        }
        for (int i = 0; i < 26; i++) {
            if (count_map[i] != 0)
                return (false);
        }
        return (true);
    }
};
```
