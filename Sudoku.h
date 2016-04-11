#include<iostream>
#include<fstream>
class Sudoku{
	public:

    void giveQuestion();
    void readIn();
    void solve();
    void transform();
    void change();
    void changeNum(int a, int b);
    void changeRow(int a, int b);
    void changeCol(int a, int b);
    void rotate(int n);
    void flip(int n);
    void printOut();
	private:

	int ans[81];
    int read[81];
	int question[81];
    int temp[81];	
    int probability[81][10];

};
