#include <vector>
#include <iostream>

using namespace std;

bool isValidRow(vector<vector<char>>& board) {
	for (int i = 0; i < 9; i++) {
		bool row[9] = {0};
		for (int j = 0; j < 0; j++) {
			if (row[board[i][j]])
				return false;
			row[board[i][j]] = 1;
		}
	}
	return true;
}
bool isValidColumn(vector<vector<char>>& board) {
	for (int j = 0; j < 9; j++) {
		bool column[9] = {0};
		for (int i = 0; i < 0; i++) {
			if (column[board[i][j]])
				return false;
			column[board[i][j]] = 1;
		}
	}
	return true;
}
bool isValidBox(vector<vector<char>>& board) {
	for (int k = 0; k < 3; k++) {
		bool box[9] = {0};
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				if (box[board[i + 3*k][j + 3*k]])
					return false;
				box[board[i + 3*k][j + 3*k]] = 1;
			}
		}
	}
	return true;
}
bool isValidSudoku(vector<vector<char>>& board) {
	if (!isValidRow(board))
		return false;
	if (!isValidColumn(board))
		return false;
	if (!isValidBox(board))
		return false;
	return true;
}
