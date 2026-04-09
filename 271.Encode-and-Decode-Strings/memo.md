## Step1

### 考えたこと

<!-- どのように問題を読み解き、解法を思いついたか -->
- 文字列をくぎり文字で区切ればいいと思ったが、区切り文字を「元々文字列に含まれていた場合」と「区切り文字の場合」のどちらかどうかを判定する仕組みが必要

- 思いつかなかったので、hintを見たが、もう回答のようなものだったため見るべきではなかった
  - 長さ情報を`<長さ情報><区切り文字><文字列>`のように先頭に置いて、読み出す長さを指定する方式を採用していた。

- 時間計算量は、文字列の長さをmとすると、encodeとdecodeともにO(m)、空間計算量は文字列の個数をnとするとO(m + n)
- 実行時間は、最大の文字列の長さは200 * 200 = 4.0 * 10^4なので、4.0 * 10^(-4)＝0.4ms。

- 工夫の余地が少なそう。これ以上の高速化も難しそうだし。

```cpp
class Solution {
	public:
	string encode(vector<string> &strs) {
		string result;

		for (string str : strs) {
			result += to_string(str.length());
			result += '#';
			result += str;
		}
		return result;
	}

	vector<string> decode(string s) {
		vector<string> result;

		auto it = s.begin();
		while (it != s.end()) {
			string len_str = "";

			while (*it != '#') {
				len_str += *it;
				++it;
			}
			++it;
			int len = stoi(len_str);
			string str = "";
			while (len-- > 0) {
				str += *it;
				++it;
			}
			result.push_back(str);
		}
		return result;
	}
};

```
---

## Step2

### 参考にしたコード

- [neetcode/solution](https://neetcode.io/problems/string-encode-and-decode/solution)
  - 空文字列の場合のガードを入れている。

  - solution1
    - `"0番目の長さ, ... , n番目の長さ, #連結した文字列"`の形にencodeしていたが、encodingに2回forループが必要で、時間計算量的にも冗長な形式な気がする
    - 自分が採用した`"<0番目の長さ>#<0番目の文字列>...<n番目の長さ>#<n番目の文字列>"`の方が、一度のループで構築できるため早いはず。
  - solution2
    - 自分の採用したものと同じ形式にencodingしてる。
    - 以下の部分を一文で`result += to_string(str.length()) + "#" + str;`と書いていた。確かに。
	```cpp
	result += to_string(str.length());
	result += '#';
	result += str;
	```
	- インデックスとsubstrをうまく使えているコードだと思う。<=> 自分はiteratorを使用したが、どっちを採用しても冗長さや計算量は変わらなさそう。


### コードの修正方針

<!-- 参考コードを読んで考えたことと自分のコードをどう直すか -->
<!-- 「他の人のコードを読んで考えたこと」と「改善するときに考えたこと」-->
- indexを用いたdecodeを一応試してみる程度

```cpp
class Solution {
	public:
	string encode(vector<string> &strs) {
		string result;

		for (string str : strs) {
			result += to_string(str.length()) + "#" + str;
		}
		return result;
	}
	
	vector<string> decode(string s) {
		vector<string> result;

		int i = 0;
		while (i < s.length()) {
			int j = i;
			while (s[j] != '#') {
				++j;
			}
			int len = stoi(s.substr(i, j));
			i = j + 1;
			result.push_back(s.substr(i, len));
			i += len;
		}
		return result;
	}
};
```

