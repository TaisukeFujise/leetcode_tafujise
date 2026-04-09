## Step1

### 考えたこと

<!-- どのように問題を読み解き、解法を思いついたか -->
- keyをnum、valueをfrequencyにしたunordered_mapを作成
- valueの大きい要素から、k個とり出す？
  - k個のwhile文を回して、その中でunordered_mapのvalueのmaxpairを取り出して、vector<int>にそのkeyを格納する。

- 計算量的にはより良い解法がありそう
  - 時間計算量：mapの構築でO(N)、Mを配列のkeyの種類の数とするとk組のwhileを回すのはO(kM)→ O(N + kM)で最悪O(N^2)
  - 実行時間の概算: 
  ```
  最大データ量：10^5
  c++は約1~10億ステップ（10^8~10^9）ステップ / 秒
  実行時間 = 10 ~ 100 s
  ```
  実行時間の概算をした時に、どれくらいが目安とかあるのか？？？（ex. 実行時間は1秒以内が目安→時間計算量（ステップ数概算）は10^8以内が目安みたいな？）

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> num_map;
        vector<int> result;

        for (const auto &num: nums) {
            num_map[num]++;
        }
        while (k > 0) {
            pair<int, int> max_pair = {0, 0};

            for (const auto &p: num_map) {
                if (max_pair.second < p.second)
                    max_pair = p;
            }
            result.push_back(max_pair.first);
            num_map.erase(max_pair.first);
            k--;
        }
        return (result);
    }
};
```
---

## Step2

### 参考にしたコード

- [【Video】2 solutions](https://leetcode.com/problems/top-k-frequent-elements/solutions/6744160/video-2-solutions-by-niits-u7uv)
  - heapを用いた解法
    - unordered_mapにfrequentをmappingするのは同じ
    - pair<int, int>（＝ 数値と頻度のpair）同士を比較する関数を作成　→ priority queueの第三引数に渡す
    - priority_queue<...>を使用 -> k回のループのなかで、priority_queue.top().firstを取り出し、.pop()でキューから取り出す作業を繰り返す。
    ```cpp
	priority_queue<
	pair<int, int> //要素の型
	vector<pair<int, int>> // vectorが基本
	decltype(comp) // 比較関数の型
	>
	```
  	※ heap関連の時間計算量
	- priority_queueのpushとpopはO(log N)　← 二分木のためlogN
  	- topはO(1)

  - 数字と頻度を入れ替えたvector<vector<int>> freq(nums.size() + 1)を使用してる。
- [github.com/dxxsxsxkx/leetcode/pull/9/](https://github.com/dxxsxsxkx/leetcode/pull/9/changes)
  >「参照渡しにすると、値にアクセスする際に参照を経由する必要があり、アセンブリレベルでは間接アドレッシングが発生する可能性があります。これは直接アドレッシングに比べて余分な処理になることがあります。」*
  - int型などの軽めの方の場合は、参照渡しにするとむしろ余計な処理（間接アドレッシング）が発生するから、コピーを渡すようにした方がいいのか
  - vecotrなどの場合は、参照渡しで渡すのは先頭アドレスだけだから、全てをコピーするよりも圧倒的に速いのか。
  ```
    型のサイズ ≤ ポインタサイズ（8byte）  →  値渡し
    型のサイズ >  ポインタサイズ（8byte）  →  const参照渡し  
  ```
  - 辞書型の変数名について
    - ~~~_to_~~~という命名が結構使用されるし、良さそう？
  - priority_queueの実装が前者とは違って、pair<int, int>を<頻度, 要素>としていることで、比較関数を自作せずに済んでいる。
  - しかも、ヒープの大きさをk以下に限定して、比較関数をgreaterにすることで小さいものをpopしていく方式にしている。
    - それによって余分な木を作るのを避けることができており、メモリ効率の良い実装になっている。
    - greater<pair<int, int>>（※firstが同じ場合にsecondを比較するらしい）。

### コードの修正方針

<!-- 参考コードを読んで考えたことと自分のコードをどう直すか -->
<!-- 「他の人のコードを読んで考えたこと」と「改善するときに考えたこと」-->
- priority_queueは使う場面が多そうなので、練習も兼ねてpriority_queueを使用して書く。
- 命名規則が雑になりがちなので、シンプルでそれとわかる命名に修正する
- 「比較関数をgreaterにし、heapの要素数をk以下に維持する方式」が効率的だが、「比較関数をlessにし、全ての要素でheapを構築してk回topを取得するという方式」の方が完結にかけるためそちらを選択するが、前者の方がいいですかね、、、
- 時間計算量は、heapの構築部分でO(NlogN)で、最大入力データ量は10^5なので、
  - 実行時間概算は10^8ステップ/秒とすると、
  ```
  10^5 log(10^5) = 10^5 * (16.6) = 1.7 * 10^6
  実行時間 = 1.7 * 10^6 / (10^8)= 17ms
  ```

```cpp
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
		unordered_map<int, int> num_to_freq;
		for (const int num: nums) {
			num_to_freq[num]++;
		}

		priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>> freq_to_num;
		for (const auto &p: num_to_freq) {
			freq_to_num.push({p.second, p.first});
		}

		vector<int> result;
		while (k > 0) {
			result.push_back(freq_to_num.top().second);
			freq_to_num.pop();
			k--;
		}
		return (result);
    }
};
```
