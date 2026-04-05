## Step1

### 考えたこと

<!-- どのように問題を読み解き、解法を思いついたか -->
- 二つの文字列が一致するかどうかは、frequency mapを使う or a~zの配列でfrequencyを表現することでできる。(<-constrains lowercase English)
  - isAnagram関数で分離か
- 文字列をどのようにAnagram groupにまとめるか
  1.  strsをfor文で回して、Anagramが一致するものがあればそのvector<string>に追加して、なければ新たにvector<string>をvector<vector<string>>に追加するという方式
     -  時間計算量がO(N^2 + N)かかってそう？
    
		-> Time limit Exceededとなるので条件に`if (result[i][0].length() != str.length()) {break};`を追加。

		-> hash mapを採用した方が良さそう
     -  空間計算量はresultのO(N)か
    ```cpp
	class Solution {
	public:
		vector<vector<string>> groupAnagrams(vector<string>& strs) {
			vector<vector<string>> result;

			for (const auto& str : strs) {
				int new_flag = true;
				for (int i = 0; i < result.size(); i++) {
					if (result[i][0].length() != str.length())
						continue;
					if (isAnagram(result[i][0], str)) {
						result[i].emplace_back(str);
						new_flag = false;
						break;
					}
				}
				if (new_flag)
					result.push_back({str});
			}
			return (result);
		}

		bool isAnagram(string str1, string str2) {
			int charmap[26] = {};

			if (str1.length() != str2.length())
				return (false);
			for (int i = 0; i < str1.length(); i++) {
				charmap[str1[i] - 'a']++;
				charmap[str2[i] - 'a']--;
			}
			for (int i = 0; i < 26; i++) {
				if (charmap[i] != 0)
					return (false);
			}
			return (true);
		}
	};
	```
  2. hash mapを採用。sortした文字列をkeyとするhash mapを作成して、最後にmapのvalueを取り出してvector<vector<string>> resultに格納する
	- isAnagramでの比較はBrute forceにならざるを得ないので、最初っからこの方式の方が良かった。
	- 時間計算量としては、
    	- sort部分：O(NlogN)
		- hash map検索 : O(1 * N);
		- 最後の取り出す部分: O(N)
	従って、全体のオーダーはsort部分のO(NlogN)になる
	- 空間計算量はanagram_mapとresultのO(N)か

   ```cpp
       vector<vector<string>> groupAnagrams(const vector<string>& strs) {
		unordered_map<string, vector<string>> anagram_map;
        vector<vector<string>> result;

		for (const auto &str: strs) {
			string sorted_str = str;
			sort(sorted_str.begin(), sorted_str.end());
			if (anagram_map.find(sorted_str) != anagram_map.end())
				anagram_map[sorted_str].emplace_back(str);
			else
				anagram_map[sorted_str] = {str};
		}
		for (const auto &p: anagram_map){
			result.emplace_back(p.second);
		}
        return (result);
    }
   ```

---

## Step2

### 参考にしたコード

- [【Video】Create keys for group of strings - 2 solutions](https://leetcode.com/problems/group-anagrams/solutions/6113105/video-create-keys-for-group-of-strings-2-tqdx)
  - mapなので、以下のようにkeyを指定して、push_backで最後に追加すればいいのか。
	```cpp
    sort(key.begin(), key.end());
    ans[key].push_back(s);
	```
  - solution2では、keyをa~zのcountを文字列に変換したものになってる。→ 配列をキーにできない場合の対処法として文字列変換は結構使えそう
- [Shunii85/arai60/pull/12/changes](https://github.com/Shunii85/arai60/pull/12/changes)
  - 計算量の算出において、文字列の長さを考慮している。→ 実際にはソートの時間計算量はO(NLlogL)なのか。
  - step3.cppのmapから取り出す箇所以外は自分のコードと方向性が同じだった


### コードの修正方針

<!-- 参考コードを読んで考えたことと自分のコードをどう直すか -->
<!-- 「他の人のコードを読んで考えたこと」と「改善するときに考えたこと」-->
- a~zの登場回数を配列化して文字列にしたものをkeyとする方が、sort後のstrをkeyとするものよりも時間計算量で勝るが、後者の方が簡潔でわかりやすいから選択するというのは正しい選択なのか？？
- てことでsort後のstrをkeyとする方式を修正してstep2とする
  - 冗長だったmapへの追加部分の修正

```cpp
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> anagram_map;
        vector<vector<string>> result;

        for (const string& str : strs) {
            string sorted_str = str;
            sort(sorted_str.begin(), sorted_str.end());
            anagram_map[sorted_str].push_back(str);
        }
        for (const auto& p : anagram_map)
            result.push_back(p.second);
        return (result);
    }
};
```
