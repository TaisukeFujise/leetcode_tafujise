## Step1

### 考えたこと

<!-- どのように問題を読み解き、解法を思いついたか -->
- brute forceでは、以下を総当たりでvalidateする流れ
  - row: board[i][j]のj(0~8)で重複がないか
  - columns: board[i][j]のi(0~8)で重複がないか
  - 3*3 box: i(0~2, 3~5, 6~8)とj(0~2, 3~5, 6~8)の組み合わせ
→ これだと、O(3 * N^2) = O(N^2)の時間計算量となるが、めちゃ早く終わった。
これは、入力のNが9のため、O(81) = O(1)という定数倍の計算量となるからだと考えられる。

ただ、より良い走査方法がありそうではある。

以下実装。
```cpp
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        if (!isValidRow(board))
            return false;
        if (!isValidColumn(board))
            return false;
        if (!isValidBox(board))
            return false;
        return true;
    }
    bool isValidRow(vector<vector<char>>& board) {
        for (int i = 0; i < 9; i++) {
            bool row[9] = {0};
            for (int j = 0; j < 9; j++) {
                if (board[i][j] == '.')
                    continue;
                if (row[board[i][j] - '1'])
                    return false;
                row[board[i][j] - '1'] = 1;
            }
        }
        return true;
    }
    bool isValidColumn(vector<vector<char>>& board) {
        for (int j = 0; j < 9; j++) {
            bool column[9] = {0};
            for (int i = 0; i < 9; i++) {
                if (board[i][j] == '.')
                    continue;
                if (column[board[i][j] - '1'])
                    return false;
                column[board[i][j] - '1'] = 1;
            }
        }
        return true;
    }
    bool isValidBox(vector<vector<char>>& board) {
        for (int boxRow = 0; boxRow < 3; boxRow++) {
            for (int boxCol = 0; boxCol < 3; boxCol++) {
                bool box[9] = {0};
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        if (board[i + 3*boxRow][j + 3*boxCol] == '.')
                            continue;
                        if (box[board[i + 3*boxRow][j + 3*boxCol] - '1'])
                            return false;
                        box[board[i + 3*boxRow][j + 3*boxCol] - '1'] = 1;
                    }
                }
            }
        }
        return true;
    }
};
```
---

## Step2

### 参考にしたコード

- [Valid Sudoku | 100% Beat | O (1) | Java | C++ | C | C# | Python3 | Go | JavaScript | TypeScript](https://leetcode.com/problems/valid-sudoku/solutions/7136639/valid-sudoku-100-beat-java-c-c-c-python3-cfql)
  - rows[row number][number]で、その行にすでにnumberが存在しているかどうかを保持するrows[9][9]の二次元配列を作り、これをcolsとboxesも同様にすることでboardを一回で走査できる→ 賢い。

- [【Video】Keep number we found and find duplicate](https://leetcode.com/problems/valid-sudoku/solutions/5272799/video-keep-number-we-found-and-find-dupl-4unj)
  - こちらはrows[9], cols[9], boxes[9]をunordered_setで定義しているので、valueが直接入るという感じだから、前者のsolutionと本質は同じ。→ こちらのほうがメモリ使用量は少ないけど、入力文字列が9の時点で定数倍のため誤差かな？けど、


### コードの修正方針

<!-- 参考コードを読んで考えたことと自分のコードをどう直すか -->
<!-- 「他の人のコードを読んで考えたこと」と「改善するときに考えたこと」-->
- 3回の走査を1回にまとめる意識で実装する。rowsとcolsとboxesで二次元配列を用意するsolutionが、unordered_setにinsertするよりも直感的？な気がして、そっちが良いと思ったけどどうだろうか。
-> 前者を採用する。
- あと、forループに使用する変数をiとjではなく, rとcにしているのはわかりやすいと思ったので参考にする。

```cpp
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        bool rows[9][9] = {0};
        bool cols[9][9] = {0};
        bool boxes[9][9] = {0};

        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                if (board[r][c] == '.')
                    continue;
                if (rows[r][board[r][c] - '1'])
                    return false;
                if (cols[c][board[r][c] - '1'])
                    return false;
                if (boxes[r / 3 + 3 * (c / 3)][board[r][c] - '1'])
                    return false;
                rows[r][board[r][c] - '1'] = 1;
                cols[c][board[r][c] - '1'] = 1;
                boxes[r / 3 + 3 * (c / 3)][board[r][c] - '1'] = 1;
            }
        }
        return true;
    }
};
```
