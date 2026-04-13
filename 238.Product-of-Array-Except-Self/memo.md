## Step1

### 考えたこと

<!-- どのように問題を読み解き、解法を思いついたか -->
- "without using the division operation"なので、割り算ダメだから、すべての掛け算を計算しておいて、nums[i]でわる方式はダメなのか。
- 一応、最初に思いついた解法としては以下のコード
  - numsのすべての積を計算。（product_all）
  - nums[i] == 0の時は、その場で計算。
  - nums[i] != 0の時は、product_all / nums[i]を計算
- 時間計算量は、numsのすべての要素の積を計算する部分でO(N)、res[i]を求めていく部分で0がない場合はO(N)だが、複数箇所0があるとO(N^2)
  - 0の個数で場合分けすれば、最悪計算量もO(N)にできそう。（まあ除算ダメなので意味ないけど）

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int product_all = 1;

        for (int num : nums)
            product_all *= num;

        vector<int> res(nums.size(), 1);
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == 0) {
                for (int j = 0; j < nums.size(); j++) {
                    if (j == i)
                        continue;
                    res[i] *= nums[j];
                }
            }
            else
                res[i] = product_all / nums[i];
        }
        return res;
    }
};

```

- 累積和のような感じにするにしても、"without using the division operation"の項目がクリアできない気がしたが、、、
- nums[i]の左側の積と右側の積を計算しておく感じか。計算はそれぞれdivision operationを使用してはいけないから、左右から乗算を進める感じ？
- 以下のように実装することができた。
  - i番目の数字に関して、それより左の累積積をleft_product[i]、右の累積積をright_product[i]とする。
  - 除算が禁止されているので、左からの累積積と右からの累積積を左右から計算する方式を採用。（時間計算量はforループなので、O(N)）
    - left_product[i] = nums[i - 1] * left_product[i - 1];
    - right_product[nums.size() - i - 1] = nums[nums.size() - i] * right_product[nums.size() - i];
  - res[i] は right_product[i] * left_product[i] で求められる。（時間計算量はforループでO(N)）

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> left_product(nums.size(), 1);
        vector<int> right_product(nums.size(), 1);

        for (int i = 1; i < nums.size(); i++) {
            left_product[i] = nums[i - 1] * left_product[i - 1];
            right_product[nums.size() - i - 1] = nums[nums.size() - i] * right_product[nums.size() - i];
        }

        vector<int> res(nums.size(), 1);

        for (int i = 0; i < nums.size(); i++) {
            res[i] = left_product[i] * right_product[i];
        }
        return res;
    }
};
```

---

## Step2

### 参考にしたコード

- [【Video】Looping the input array twice](https://leetcode.com/problems/product-of-array-except-self/solutions/5833007/video-looping-the-input-array-twice-by-n-tivu)
  - 配列として、leftとrightを用意するのではなく、output[i]に左からのforループと右からのforループの累積積をかける方式
	```cpp
	left = 1;
	for (int i = 0; i < nums.size(); i++) {
		output[i] *= left;
		left *= nums[i];
	}
	```

- [Best C++ 3 Solution || DP || Space optimization || Brute Force -> Optimize || One Stop Solution.](https://leetcode.com/problems/product-of-array-except-self/solutions/3186745/best-c-3-solution-dp-space-optimization-yfv73)
  - solution1. brute force方式。O(N^2)
    - forループでi == j の一致する時にだけcontinueして、あとはすべて積作る方式。
  - solution2. DP
    - 自分の解法と全く同じだった。強いて言えば、nums.size()を変数に格納して、何度も計算していない点ぐらい。
    - これってDPなの？？？
  - solution3. 一個前の参考にしたコード(【Video】Looping the input array twice)と同じ解法。
    - solution2とsolution3の違いは空間計算量にありそう。
      - solution2は補助配列としてleft_productとright_productを使うため、O(N)なのに対し、こちらは補助変数left, rightしか使用しないので、O(1)っぽい。

### コードの修正方針

<!-- 参考コードを読んで考えたことと自分のコードをどう直すか -->
<!-- 「他の人のコードを読んで考えたこと」と「改善するときに考えたこと」-->
- 二つの配列を用意するのではなく、2回のforループを回して累積積をres[i]にかけていく方式がシンプルかつ空間計算量もO(1)なので、それで書く。

```cpp
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> res(nums.size(), 1);

        int left = 1;
        for (int i = 0; i < nums.size(); i++) {
            res[i] *= left;
            left *= nums[i];
        }

        int right = 1;
        for (int i = nums.size() - 1; i >= 0; i--) {
            res[i] *= right;
            right *= nums[i];
        }
        return res;
    }
};

```
