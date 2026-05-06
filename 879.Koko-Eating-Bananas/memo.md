## Step1

### 考えたこと

<!-- どのように問題を読み解き、解法を思いついたか -->
- "Return the minimum integer k"とあり、最小となるkを探す問題。かつ、k（1<=k<=最大のpile）は単調増加でkが増えればhも単調に減少する。よって、binary searchが適用できる？
- 判定関数が、単純なtargetと一致する要素を探すbinary searchではなく、そのkによってhを満たすことができるかどうか。

- binary search自体はO(logN), 判定関数の適用にはO(N)かかる。-> O(logN) * O(N) = O(NlogN)
    - constrainsはpiles.Length <= 10 ^ 4 , piles.length <= h <= 10 ^ 9, piles[i] <= 10 ^ 9より
    - 最悪時間計算量は、log(10 ^ 9) * 10 ^ 4 ≒ 10 ^ 5なので、実行時間としては10 ^ 5 / 10 ^ 8 = 1.0ms
    - 判定関数は改善できそう。
```cpp

class Solution {
 public:
  int minEatingSpeed(const vector<int>& piles, int h) {
    int left = 1;
    int right = *max_element(piles.begin(), piles.end()) + 1;

    while (left < right) {
      int mid = left + (right - left) / 2;
      if (canEatAll(mid, h, piles)) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }
    return left;
  }
  bool canEatAll(int k, int h, const vector<int>& piles) {
    int total_hour = 0;
    for (int i = 0; i < piles.size(); i++) {
      total_hour += (piles[i] - 1) / k + 1;
    }
    return total_hour <= h;
  }
};
```
---

## Step2

### 参考にしたコード

- [simple solution](https://leetcode.com/problems/koko-eating-bananas/solutions/7047251/simple-solution-by-harshita_114-3c0a)
    - 判定関数の部分の改善点が見つかった。
    - このsolutionでは、total_hourの計算をpileごとにしていくが、hを超えた時点ですぐにfalseを返していた。（早期リターンをすべきだった。）
    - また、total_hourをintではなくlong longにすることでオーバーフローを防いでいた。(hは10 ^ 9まであるため)
- [yamashita-ki/codingTest/pull/15](https://github.com/yamashita-ki/codingTest/pull/15/changes)
    - 二分探索だが、left, rightという命名よりも, minSpeed, maxSpeedという命名はいいと思った。
    - 閉区間による二分探索のため、ansという変数をおく必要が出ているが、半開区間での探索でなくせる部分だと思う。

### コードの修正方針

<!-- 参考コードを読んで考えたことと自分のコードをどう直すか -->
<!-- 「他の人のコードを読んで考えたこと」と「改善するときに考えたこと」-->
- 命名には気をつける。
- intを超えるオーバーフローに対応する
- 早期リターンによる判定関数の改善


```cpp
class Solution {
 public:
  int minEatingSpeed(const vector<int>& piles, int h) {
    int minSpeed = 1;
    int maxSpeed = *max_element(piles.begin(), piles.end()) + 1;

    while (minSpeed < maxSpeed) {
      int midSpeed = minSpeed + (maxSpeed - minSpeed) / 2;
      if (canEatAll(midSpeed, h, piles)) {
        maxSpeed = midSpeed;
      } else {
        minSpeed = midSpeed + 1;
      }
    }
    return minSpeed;
  }

 private:
  bool canEatAll(int k, int h, const vector<int>& piles) {
    long long total_hour = 0;

    for (int pile : piles) {
      total_hour += (pile - 1) / k + 1;
      if (total_hour > h) {
        return false;
      }
    }
    return true;
  }
}

```
