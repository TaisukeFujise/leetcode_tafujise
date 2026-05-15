## Step1

### 考えたこと

<!-- どのように問題を読み解き、解法を思いついたか -->
- keyとtimestampを合わせて一意なdataを格納するtimemapを作成し、setとgetを作る

- constrainsから、"At most 2 * 10^5 calls will be made to set and get"とあるので、最大のデータサイズは2 * 10^5
- 単純な線形探索の場合、keyを探すのにO(N)とtimestampを探すのにO(N)かかるので、O(N ^ 2) 。一回の探索だけで、実行時間概算としては、(2 * 10^5)^2 / 10 ^ 8 = 400 sかかるので、データ構造は工夫が必要。

- データ形式についての方針
    - (i) unordered_map<string, map<int, string>>でいけそう
        - unordered_mapは、keyをkeyとして、valueをtimestamp-valueのmapとしたもの
        - timestamp-valueをmapとするのは、get(Stirng key, int timestamp)で取得するのは、timestamp以下の最大となるtimestampのデータのため、timestampを昇順にset(string key, int timestamp)して、getの際に二分探索で探す方針-> なんかうまく書けなかったので、map::upper_boundを使う
        - map::upper_bound(timestamp)を使うとtimestampより大きい要素のイテレータを返すので、一個前のiteratorを使用すればget関数をかける. あと、この場合、平衡木を使った探索のため、木探索。
```cpp
 class TimeMap {
 public:
  TimeMap() {}

  void set(string key, string value, int timestamp) {
    timemap[key][timestamp] = value;
  }

  string get(string key, int timestamp) {
    //  これってcontains結構計算量かかるの？
    if (!timemap.contains(key)) {
      return "";
    }
    map<int, string> timestamp_to_value = timemap[key];

    auto it = timestamp_to_value.upper_bound(timestamp);
    if (it == timestamp_to_value.begin()) {
      return "";
    }
    --it;
    return it->second;
  }

 private:
  unordered_map<string, map<int, string>> timemap;
};

```

- (ii) unordered_map<stirng, vector(pair<int, string>) (※ by ChatGPT)
        - vector(pair<int, string>)で格納するとbinary searchでのupper boundの導出ができる。
        - "All the timestamps timestamp of set are strictly increasing"とあるので、timestampは昇順に与えられるから、setはそのままpush_back
        - getはbinary searchで与えられたtimestampより小さい最大のtimestampのvalueを返す。

```cpp
class TimeMap {
 public:
  TimeMap() {}

  void set(string key, string value, int timestamp) {
    timemap[key].push_back({timestamp, value});
  }

  string get(string key, int timestamp) {
    if (!timemap.contains(key)) {
      return "";
    }
    vector<pair<int, string>> timestamp_to_value = timemap[key];

    int left = 0;
    int right = timestamp_to_value.size();
    while (left < right) {
      int mid = left + (right - left) / 2;
      if (timestamp < timestamp_to_value[mid].first) {
        right = mid;
      } else {
        left = mid + 1;
      }
    }
    if (left == 0) {
      return "";
    }
    return timestamp_to_value[left - 1].second;
  }

 private:
  unordered_map<string, vector<pair<int, string>>> timemap;
};

```

- 計算量・実行時間について
    - そのため、総時間計算量はkeyの走査でO(1) と timestamp-valueの走査でO(logN), これがN回繰り返されるので、-> O(1 * logN * N) = O(NlogN)
    - 実行時間概算としては、
        2 * 10^5 * log(2 * 10^5) / 10^8 <= 3.8 * 10^6 / 10^8 = 3.8 * 10^(-2) = 38ms
 => それなのに、Time Limit Exceededでどちらもpassしなかった。なぜ？？？
    - ChatGPTによる指摘1
     ```cpp
     vector<pair<int, string>> timestamp_to_value = timemap[key];
    ```
    => この部分がコピーとして書いていたので、O(M)の時間計算量がかかっていた。修正が以下。
    ```cpp
    vector<pair<int, string>> &timestamp_to_value = timemap[key];
    ```
    - ChatGPTによる指摘2
    ```cpp
    if(!timemap.contains(key))
    ```
    => この部分がunordered_mapのためO(1)ではあるが、その後にtimemap[key]を使用しており、二度のハッシュ探索をしている。
    → findを使って一度に済ませた方がいい。
    ```cpp
    auto it_key = timemap.find(key);
    if (it_key == timemap.end()) {
        return "";
    }
    auto &timestamp_to_value = it_key.second;
    ```


---

## Step2

### 参考にしたコード

- [Binary Search per Key | Time Based Key-Value Store | O(log n) | C++](https://leetcode.com/problems/time-based-key-value-store/solutions/7489071/binary-search-per-key-time-based-key-val-mna6)
    - unordered_map<string, vector<pair<int, string>>>の解法
    - publicにこのデータ構造を定義していたが、privateの方が適切な気がする。
- [Beats 99%✅ | O( log n )✅ | C++ (Step by step explanation)
](https://leetcode.com/problems/time-based-key-value-store/solutions/4175579/beats-99-o-log-n-c-step-by-step-explanat-pffq)
    - 上に同じだが、privateにデータ構造の定義をおいているのと、get関数の中のkey, timestampに一致するデータを探索する処理を関数化してprivateで定義してた。


### コードの修正方針

<!-- 参考コードを読んで考えたことと自分のコードをどう直すか -->
<!-- 「他の人のコードを読んで考えたこと」と「改善するときに考えたこと」-->
- 参照とcontainsの部分を修正する。

```cpp
class TimeMap {
public:
    TimeMap() {
        
    }
    
    void set(string key, string value, int timestamp) {
        timemap[key].push_back({timestamp, value});
    }
    
    string get(string key, int timestamp) {
        auto it = timemap.find(key);
        if (it == timemap.end()) {return "";}

        vector<pair<int, string>> &time_to_value =  it->second;
        int left = 0;
        int right = time_to_value.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (timestamp < time_to_value[mid].first) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        if (left == 0) {return "";}
        return time_to_value[left - 1].second;
    }
    unordered_map<string, vector<pair<int, string>>> timemap;
};

```

