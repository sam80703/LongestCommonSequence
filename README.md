# LongestCommonSequence
Solve longest common sequence problem by dynamic programming

## Description
一個字串的子序列，是由字串中若干個字元(不一定連續)以相同的順序所組成的字串，例如：AB、ACE、E 都是 ABCDE 的子序列。兩個字串的最長共同子序列 (LCS) 即為兩個字串的共同子序列中長度最大者。

## Input
每組測資包含兩個字串，每個字串長度不超過 100，且全部都是由大寫英文字母組成。

## Output
第一行請輸出 LCS 的長度和個數，下一行開始請依字典順序輸出所有的 LCS 。注意答案中可能包含相同的子序列，因為同一個子序列在兩個輸入字串中的位置可能不同。保證 LCS 的個數不超過 200000 個，LCS 長度 > 0。

