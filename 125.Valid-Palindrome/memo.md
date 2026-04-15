## Step1

### 考えたこと

<!-- どのように問題を読み解き、解法を思いついたか -->
- 順番が大事なのでvector<char>に「小文字化」＋「文字と数字のみ」を格納
- forループで、i < vector size / 2までを[i] と [size - 1 - i]が一致するかどうか確認する。
  → これのことをtwo pointerと言ってるのか？

- 時間計算量は、前から探索するだけなので、O(N)


```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        vector<char> chars;

        int OFFSET = 'A' - 'a';
        for (char c : s) {
            if ('A' <= c && c <= 'Z')
                chars.push_back(c - OFFSET);
            else if ('a' <= c && c <= 'z')
                chars.push_back(c);
            else if ('0' <= c && c <= '9')
                chars.push_back(c);
        }

        int chars_size = chars.size();
        for (int i = 0; i < chars_size / 2; i++) {
            if (chars[i] != chars[chars_size - 1 - i])
                return false;
        }
        return true;
    }
};
```
---

## Step2

### 参考にしたコード

- [【Video】Transforming the input string](https://leetcode.com/problems/valid-palindrome/solutions/6170976/video-transforming-the-input-string-by-n-8qyj)
  - vector<char>ではなく、stringを使用しており、またstd::isalnum関数とstd::tolower関数を使用していた。確かに。
  - また、leftとrightでindexを二つおき、while (left < right)で回す方式をとっていたが、そちらの方がわかりやすいと感じた。
- chatGPT
  - 最初に変換せずに、left, right のインデックスをおいて、元の入力文字列sを探索していく方式→空間計算量最小O(1)


### コードの修正方針

<!-- 参考コードを読んで考えたことと自分のコードをどう直すか -->
<!-- 「他の人のコードを読んで考えたこと」と「改善するときに考えたこと」-->

- 文字列変換をライブラリで行い、二つのポインタを明示的に使いたい。
- また、空間計算量も最小になるように、元の文字列を活用するようにする。

```cpp
class Solution {
public:
    bool isPalindrome(string s) {
        int left = 0;
        int right = s.size() - 1;

        while (left < right) {
            if (!isalnum(s[left])) {
                left++;
                continue;
            }
            if (!isalnum(s[right])) {
                right--;
                continue;
            }
            if (tolower(s[left]) != tolower(s[right]))
                return false;
            left++;
            right--;
        }
        return true;
    }
};

```
