## Step1

### 考えたこと

<!-- どのように問題を読み解き、解法を思いついたか -->
- 「重複があり、sortされていないvector<int> numsが入力に与えられ、nums[i] + nums[j] + nums[k] = 0となる組み合わせ全てを返す。」
  -> 頻度をカウントするmapか、そのままvectorのデータ構造を使用した方がいい？
  -> 先にsortしないとキツいか？O(logN)＝あと、今回はindexを返す必要がないからsortしても問題はなさそう。

- sort後のvectorから、どう組み合わせを探すか。
	- 2つの数字のsumなら、前から進めるポインタ(start)と後ろから進めるポインタ(end)でよかった
	- forループで一つの数字を前から決めて、2sumに落とし込む？ but 時間計算量はO(N ^ 2)になる

	- 重複を考慮できていなかった（以下のコードは同じ組み合わせだが異なるindexをカウントしてしまっている）
	->[参考コード](https://leetcode.com/problems/3sum/solutions/5055810/video-two-pointer-solution-by-niits-cl7y)より、
	「重複のnumの時のスキップがうまくいってない」「解を一つ見つけた後に、breakしてしまっているが、他の解がある可能性もある」ことがわかったので、二つ目のコードに反映する。
	sortごの配列において、nums[i] == nums[i - 1]、nums[start] == nums[start - 1]、nums[end] == nums[end - 1]という条件で重複を排除するという発想が出てこなかった。

	<最初に作成したコード（誤り）>
	```cpp
	class Solution {
	public:
		vector<vector<int>> threeSum(vector<int>& nums) {
			vector<vector<int>> result;

			sort(nums.begin(), nums.end());
			for (int i = 0; i < nums.size() - 2; i++) {
				int two_sum = (-1) * nums[i];

				int start = i + 1;
				int end = nums.size() - 1;
				while (start < end) {
					if (two_sum == nums[start] + nums[end])
					{
						result.push_back({nums[i], nums[start], nums[end]});
						break;
					}
					else if (two_sum < nums[start] + nums[end])
						end--;
					else if (two_sum > nums[start] + nums[end])
						start++;
				}
			}
			return result;
		}
	};
	```
	<修正後のコード>
	```cpp
	class Solution {
	public:
		vector<vector<int>> threeSum(vector<int>& nums) {
			vector<vector<int>> result;

			sort(nums.begin(), nums.end());
			for (int i = 0; i < nums.size(); i++) {
				if (i > 0 && nums[i] == nums[i - 1])
					continue;
				int start = i + 1;
				int end = nums.size() - 1;

				while (start < end) {
					int sum = nums[i] + nums[start] + nums[end];

					if (sum == 0) {
						result.push_back({nums[i], nums[start], nums[end]});
						start++;
						end--;

						while (start < end && nums[start] == nums[start - 1]) {
							start++;
						}
						while (start < end && nums[end] == nums[end + 1]) {
							end--;
						}
					}
					else if (sum < 0) {
						start++;
					}
					else if (sum > 0) {
						end--;
					}
				}
			}
			return result;
		}
	};
	```


---

## Step2

### 参考にしたコード

- [Just Keep Things Simple](https://leetcode.com/problems/3sum/solutions/7448027/just-keep-things-simple-by-gsai122-9if7)
  - 最初に参考にしたコードと同じ解法ではあったが、重複スキップが二つのポインタあるうちの片方のみだった。
- [github.com/ryosuketc/leetcode_grind75/pull/30](https://github.com/ryosuketc/leetcode_grind75/pull/30/changes)
  - 「ソート+2ポインタ」ではなく、「ソート＋hash set」の解法でも解かれていた。空間計算量的には、新たにhash setを作成するという点において劣っているものの、選択肢に出てきてもよかった。（重複除去をしてるし）


### コードの修正方針

<!-- 参考コードを読んで考えたことと自分のコードをどう直すか -->
<!-- 「他の人のコードを読んで考えたこと」と「改善するときに考えたこと」-->
- 「ソート+2ポインタ」と「ソート+hash set」の両方で解いておく。

<ソート+2ポインタ>
```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<vector<int>> result;

        for (int i = 0; i < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            
            int start = i + 1;
            int end = nums.size() - 1;
            while (start < end) {
                int sum = nums[i] + nums[start] + nums[end];
                if (sum == 0) {
                    result.push_back({nums[i], nums[start], nums[end]});
                    start++;
                    end--;
                    while (start < end && nums[start] == nums[start - 1]) 
                        start++;
                    while (start < end && nums[end] == nums[end + 1])
                        end--;
                }
                else if (sum < 0)
                    start++;
                else if (sum > 0)
                    end--;
            }
        }
        return result;
    }
};
```

```cpp
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> result;

        for (int i = 0; i < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i - 1])
                continue;
            unordered_set<int> seen;
            for (int j = i + 1; j < nums.size(); j++) {
                int diff = -1 * (nums[i] + nums[j]);

                if (seen.contains(diff)) {
                    result.push_back({nums[i], diff, nums[j]});
                    while (j < nums.size() - 1 && nums[j] == nums[j + 1]) 
                        j++;
                }
                seen.insert(nums[j]);
            }
        }
        return result;
    }
};
```
