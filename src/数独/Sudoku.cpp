#include "pch.h"
#include <iostream> 
#include <fstream> 
using namespace std;
int m, n;
ofstream outfile;
int Sudoku[9][9];

bool isValid(int row, int col, int val)//检查填入数字的合法性 
{
	if (row < 0 || row >= m || col < 0 || col >= m)
	{
		return false;
	}

	if (Sudoku[row][col] != 0)
	{
		return false;
	}

	for (int i = 0; i < m; i++)
	{
		if (Sudoku[row][i] == val)
		{
			return false;
		}
	}

	for (int i = 0; i < m; i++)
	{
		if (Sudoku[i][col] == val)
		{
			return false;
		}
	}


	if (m == 4)
	{
		int row1 = row / 2;
		int col1 = col / 2;
		int rowstart = row1 * 2;
		int colstart = col1 * 2;
		for (int i = rowstart; i < rowstart + 2; i++)
		{
			for (int j = colstart; j < colstart + 2; j++)
			{
				if (Sudoku[i][j] == val)
				{
					return false;
				}
			}
		}
	}


	if (m == 6)
	{
		int row1 = row / 2;
		int col1 = col / 3;
		int rowstart = row1 * 2;
		int colstart = col1 * 3;
		for (int i = rowstart; i < rowstart + 2; i++)
		{
			for (int j = colstart; j < colstart + 3; j++)
			{
				if (Sudoku[i][j] == val)
				{
					return false;
				}
			}
		}
	}

	if (m == 8)
	{
		int row1 = row / 4;
		int col1 = col / 2;
		int rowstart = row1 * 4;
		int colstart = col1 * 2;
		for (int i = rowstart; i < rowstart + 4; i++)
		{
			for (int j = colstart; j < colstart + 2; j++)
			{
				if (Sudoku[i][j] == val)
				{
					return false;
				}
			}
		}
	}

	if (m == 9)
	{

		int row1 = row / 3;
		int col1 = col / 3;
		int rowstart = row1 * 3;
		int colstart = col1 * 3;
		for (int i = rowstart; i < rowstart + 3; i++)
		{
			for (int j = colstart; j < colstart + 3; j++)
			{
				if (Sudoku[i][j] == val)
				{
					return false;
				}
			}
		}
	}

	return true;

}


void SolveSudoku(int i, int j)//从a【0】【0】开始一个一个试 
{
	if (i >= m)
	{
		for (int j1 = 0; j1 < m; j1++)
		{
			for (int j2 = 0; j2 < m; j2++)
				outfile << Sudoku[j1][j2] << " ";
			outfile << endl;
		}
	}//i>=m的时候说明，一计算完数独。打印即可。


	if (j >= m)
	{
		SolveSudoku(i + 1, 0);
	}//j>=m的时候说明当前的行已经匹配完成。

	if (Sudoku[i][j] == 0)
	{
		for (int num = 1; num <= m; num++)
		{
			if (isValid(i, j, num))//判断num合法性 
			{
				Sudoku[i][j] = num;//回溯算法一定要保留现场和恢复现场。这样下次计算不会出现问题。
				SolveSudoku(i, j + 1);
				Sudoku[i][j] = 0; //【i】【j+1】不满足时退回来，说明此时【i】【j】不满足，置零重新开始 
			}
		}
	}
	else if (i < m && j < m)//判断是否到最后一个了 
		SolveSudoku(i, j + 1);

}




int main(int argc, char* argv[])
{
	m = *argv[2] - 48;
	n = *argv[4] - 48;
	char a[1000]={0};
	char p;

	ifstream infile;
	infile.open(argv[6]);
	outfile.open(argv[8]);
	int i = 0;
	while (!infile.eof())
	{
		infile.get(p);
		if ('0' <= p && p <= '9')
		{
			a[i] = p;
			i++;
		}
	}
	infile.close();//读取文件结束

	int flag, now;
	flag = 1;
	now = 0;//数组a下标 
	while (flag <= n)//m阶数独个数 
	{
		int j1, j2;
		for (j1 = 0; j1 < m; j1++)
			for (j2 = 0; j2 < m; j2++)
			{
				Sudoku[j1][j2] = (int)a[now] - 48;
				now++;
			}
		outfile << flag << ":" << endl;

		SolveSudoku(0, 0);
		flag++;


	}

	outfile.close();




	return 0;
}






