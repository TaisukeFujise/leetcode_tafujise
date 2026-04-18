## Step1

### 考えたこと

<!-- どのように問題を読み解き、解法を思いついたか -->
- vector<int> height配列から、二つの数値を見つける→ two pointer？
- 今回は、(i - j) * min(height[i], height[j])が最大となる2点
  -> sortするとindexが変わってしまう。
  -> brute forceなら、もちろん解けるがO(N^2)
  - tow pointerのどちらを動かすか。
    - 一つ動かすと(i - j - 1) * min(height[i - 1], height[j]) or (i - j - 1) * min(height[i], height[j])
      - かならず幅(i - j - 1)は減る
      - height[i] と height[j]の大きい方を動かすと、minが使われるのでそれ以下にしかならない。
      - height[i] と height[j]の小さい方を動かすと、minが変化するので、面積が増加する可能性がある。
    -> てことは今のheight[i]とheight[j]の大小関係でiとjのどちらを動かすかを決める

  - 時間計算量はポインタはNだけしか移動しないので、O(N)。
```cpp
class Solution {
public:
    int maxArea(vector<int>& height) {
        int left = 0;
        int right = height.size() - 1;

        int max_area = 0;
        while (left < right) {
            int area = (right - left) * min(height[left], height[right]);
            max_area = max(max_area, area);

            if (height[left] < height[right]) {
                ++left;
            } else {
                --right;
            }
        }
        return mex_area;
    }
};

```
---

## Step2

### 参考にしたコード

「Two pointer」の発想に至るまでの過程を「Segment Tree」と「Suffix max/min prerprocessing」という視点から捉えてそうだった。
これは理解した方がいい考え方なのか？それとも、改めてtreeなどの問題に慣れてからでも問題ないのか？
- [github.com/huyfififi/coding-challenges/pull/59](https://github.com/huyfififi/coding-challenges/pull/59/changes)
- [github.com/thonda28/leetcode/pull/16](https://github.com/thonda28/leetcode/pull/16/changes#r1687386128)

<!-- 

### コードの修正方針

<!-- 参考コードを読んで考えたことと自分のコードをどう直すか -->
<!-- 「他の人のコードを読んで考えたこと」と「改善するときに考えたこと」-->

