#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <algorithm>
using namespace std;

typedef class LCS {
public:
	int i;
	int j;
	int length;
	vector<string> output;
};

void qswap(vector<string>& v, int x, int y) {
	string temp = v[x];
	v[x] = v[y];
	v[y] = temp;

}
void quicksort(vector<string>& vec, int l, int r) {
	int i = l, j = r, mid;
	string pivot;
	mid = l + (r - l) / 2;
	pivot = vec[mid];

	while (i<r || j>l) {
		while (vec[i] < pivot)
			i++;
		while (vec[j] > pivot)
			j--;

		if (i <= j) {
			qswap(vec, i, j);
			i++;
			j--;
		}
		else {
			if (i < r)
				quicksort(vec, i, r);
			if (j > l)
				quicksort(vec, l, j);
			return;
		}
	}
}

void lcs_length(string a, string b, vector<vector<LCS> >& lcs, int(&len)[101][101]) {
	for (int i = 1; i < a.size() + 1; i++) {
		for (int j = 1; j < b.size() + 1; j++) {
			if (a[i - 1] == b[j - 1]) {
				// 如果字元相同，length = 左上方 + 1
				len[i][j] = len[i - 1][j - 1] + 1;
				LCS temp;
				temp.i = i;
				temp.j = j;
				temp.length = len[i][j];
				// 如果此格的length在lcs中是一個新的長度(代表他是第一個出現這個長度的)，在lcs的row中新增一個位置給他
				if (lcs.size() < len[i][j]) {
					vector<LCS> new_length;
					new_length.push_back(temp);
					lcs.push_back(new_length);
				}
				// 在lcs中已經有這個長度的位置的話就直接塞進去
				else {
					lcs[len[i][j] - 1].push_back(temp);
				}
			}
			else {
				len[i][j] = max(len[i - 1][j], len[i][j - 1]);
			}
		}
	}
}

void LCS_result(string a, vector<vector<LCS> >& lcs, vector<string>& result) {
	// 先初始化lcs[-1]那層的點的output(把它對應的字元加進output vector) 
	for (int z = 0; z < lcs[lcs.size() - 1].size(); z++) {
		// 字母在a中的index跟在lcs和len中的index差1 
		int char_index = (lcs[lcs.size() - 1][z].i) - 1;
		string temp_output;
		temp_output = a[char_index] + temp_output;
		lcs[lcs.size() - 1][z].output.push_back(temp_output);
	}
	// 從length最大那層開始 traverse，i為層的index 
	for (int i = lcs.size() - 1; i > 0; i--) {
		// j為length較大那層個數的index 
		for (int j = 0; j < lcs[i].size(); j++) {
			// k為length較小那層個數的index 
			for (int k = 0; k < lcs[i - 1].size(); k++) {
				// 如果length - 1 那層的點 i 跟 j 都小於length那層的點，就把lcs[-1]的output接在lcs[-2]的output的後面(紀錄在lcs[-2][].output的vector裡面)
				if (lcs[i - 1][k].i < lcs[i][j].i && lcs[i - 1][k].j < lcs[i][j].j) {
					for (int z = 0; z < lcs[i][j].output.size(); z++) {
						string temp_output;
						int char_index = lcs[i - 1][k].i - 1;
						temp_output = a[char_index] + lcs[i][j].output[z];
						lcs[i - 1][k].output.push_back(temp_output);;
					}
				}
			}

		}
	}
	// 最終所有lcs[0]裡的點的output vector即是解，把它們都插進result vector 
	for (int i = 0; i < lcs[0].size(); i++) {
		result.insert(result.end(), lcs[0][i].output.begin(), lcs[0][i].output.end());
	}
}

int main() {
	string a, b;
	cin >> a >> b;
	int len[101][101] = { 0 };
	// 等等用來記錄"可能"貢獻LCS的人(出現斜箭頭的，即a[] == b[])，儲存的格式為: 他在LCS中表格的座標i, j, length(最長長度)，
	// lcs[0]存了所有length為1且"可能"貢獻LCS的格子資訊，lcs[1]存length為2,,,，最終print所有結果的時候從lcs[-1]開始traverse所有lcs[-1]的點，
	// 看他們跟lcs[-2]的所有點會不會match變成LCS(lcs[-2]裡的點只要i跟j小於lcs[-1]的點就會)，有的話就把lcs[-1]的點的output vector裡面的字串加給lcs[-2]的點的output vector，
	// 依序做到lcs[0]，最終lcs[0]裡面所有點的output vector就是所有的LCS可能字串 
	vector<vector<LCS> > lcs;
	// 建出LCS的表格，裡面存到此格最長LCS的length
	lcs_length(a, b, lcs, len);
	// 由lcs[-1]開始做traverse，跟他的length - 1那層(lcs[-2])有match的就把lcs[-1]的output接在lcs[-2]的output的後面(紀錄在lcs[-2][].output的vector裡面)，依序做下去 
	vector<string> result;
	LCS_result(a, lcs, result);


	quicksort(result, 0, result.size() - 1);
	printf("%d %d\n", lcs.size(), result.size());

	for (int i = 0; i < result.size(); i++) {
		puts(result[i].c_str());
	}
}