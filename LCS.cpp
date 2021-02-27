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
				// �p�G�r���ۦP�Alength = ���W�� + 1
				len[i][j] = len[i - 1][j - 1] + 1;
				LCS temp;
				temp.i = i;
				temp.j = j;
				temp.length = len[i][j];
				// �p�G���檺length�blcs���O�@�ӷs������(�N��L�O�Ĥ@�ӥX�{�o�Ӫ��ת�)�A�blcs��row���s�W�@�Ӧ�m���L
				if (lcs.size() < len[i][j]) {
					vector<LCS> new_length;
					new_length.push_back(temp);
					lcs.push_back(new_length);
				}
				// �blcs���w�g���o�Ӫ��ת���m���ܴN������i�h
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
	// ����l��lcs[-1]���h���I��output(�⥦�������r���[�ioutput vector) 
	for (int z = 0; z < lcs[lcs.size() - 1].size(); z++) {
		// �r���ba����index��blcs�Mlen����index�t1 
		int char_index = (lcs[lcs.size() - 1][z].i) - 1;
		string temp_output;
		temp_output = a[char_index] + temp_output;
		lcs[lcs.size() - 1][z].output.push_back(temp_output);
	}
	// �qlength�̤j���h�}�l traverse�Ai���h��index 
	for (int i = lcs.size() - 1; i > 0; i--) {
		// j��length���j���h�Ӽƪ�index 
		for (int j = 0; j < lcs[i].size(); j++) {
			// k��length���p���h�Ӽƪ�index 
			for (int k = 0; k < lcs[i - 1].size(); k++) {
				// �p�Glength - 1 ���h���I i �� j ���p��length���h���I�A�N��lcs[-1]��output���blcs[-2]��output���᭱(�����blcs[-2][].output��vector�̭�)
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
	// �̲שҦ�lcs[0]�̪��I��output vector�Y�O�ѡA�⥦�̳����iresult vector 
	for (int i = 0; i < lcs[0].size(); i++) {
		result.insert(result.end(), lcs[0][i].output.begin(), lcs[0][i].output.end());
	}
}

int main() {
	string a, b;
	cin >> a >> b;
	int len[101][101] = { 0 };
	// �����ΨӰO��"�i��"�^�mLCS���H(�X�{�׽b�Y���A�Ya[] == b[])�A�x�s���榡��: �L�bLCS����檺�y��i, j, length(�̪�����)�A
	// lcs[0]�s�F�Ҧ�length��1�B"�i��"�^�mLCS����l��T�Alcs[1]�slength��2,,,�A�̲�print�Ҧ����G���ɭԱqlcs[-1]�}�ltraverse�Ҧ�lcs[-1]���I�A
	// �ݥL�̸�lcs[-2]���Ҧ��I�|���|match�ܦ�LCS(lcs[-2]�̪��I�u�ni��j�p��lcs[-1]���I�N�|)�A�����ܴN��lcs[-1]���I��output vector�̭����r��[��lcs[-2]���I��output vector�A
	// �̧ǰ���lcs[0]�A�̲�lcs[0]�̭��Ҧ��I��output vector�N�O�Ҧ���LCS�i��r�� 
	vector<vector<LCS> > lcs;
	// �إXLCS�����A�̭��s�즹��̪�LCS��length
	lcs_length(a, b, lcs, len);
	// ��lcs[-1]�}�l��traverse�A��L��length - 1���h(lcs[-2])��match���N��lcs[-1]��output���blcs[-2]��output���᭱(�����blcs[-2][].output��vector�̭�)�A�̧ǰ��U�h 
	vector<string> result;
	LCS_result(a, lcs, result);


	quicksort(result, 0, result.size() - 1);
	printf("%d %d\n", lcs.size(), result.size());

	for (int i = 0; i < result.size(); i++) {
		puts(result[i].c_str());
	}
}