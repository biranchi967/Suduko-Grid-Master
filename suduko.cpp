#include<bits/stdc++.h>
using namespace std;

const int BoardSize = 9;
const int CellSize = 3;

int board[BoardSize][BoardSize];

/*
0 1 0 0
0 0 4 0
0 4 0 0
0 0 3 0
*/

bool check(int ch,int row,int col){
	// check in row
	for(int c=0;c<BoardSize;c++){
		if(c!=col && board[row][c]==ch){
			return false;
		}
	}
	// check in col
	for(int r=0;r<BoardSize;r++){
		if(r!=row && board[r][col]==ch){
			return false;
		}
	}
	// check in square
	int str = (row/CellSize)*CellSize;
	int stc = (col/CellSize)*CellSize;
	for(int dx = 0;dx<CellSize;dx++){
		for(int dy =0;dy<CellSize;dy++){
			if(str+dx==row && stc+dy==col)continue;
			if(board[str+dx][stc+dy]==ch)return false;
		}
	}
	return true;
}

int ans = 0;

void rec(int row,int col){
	if(col==BoardSize){
		rec(row+1,0);
		return;
	}
	if(row==BoardSize){
		// base case
		ans++;

		// cout<<"Answer "<<ans<<endl;
		for(int i=0;i<BoardSize;i++){
			for(int j=0;j<BoardSize;j++){
				cout<<board[i][j]<<" ";
			}
			cout<<endl;
		}
		return;
	}

	if(board[row][col]==0){
		// we need to fill.
		for(int ch=1;ch<=BoardSize;ch++){
			if(check(ch,row,col)){
				board[row][col] = ch;
				rec(row,col+1);
				board[row][col] = 0;
			}
		}

	}else{
		// pre-filled.
		if(check(board[row][col],row,col)){
			rec(row,col+1);
		}
	}
}

/*
3 0 6 5 0 8 4 0 0
5 2 0 0 0 0 0 0 0
0 8 7 0 0 0 0 3 1
0 0 3 0 1 0 0 8 0
9 0 0 8 6 3 0 0 5
0 5 0 0 9 0 6 0 0
1 3 0 0 0 0 2 5 0
0 0 0 0 0 0 0 7 4
0 0 5 2 0 6 3 0 0
*/

void solve(){
	for(int i=0;i<BoardSize;i++){
		for(int j=0;j<BoardSize;j++){
			cin>>board[i][j];
		}
	}
	rec(0,0);
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int t=1;
	// cin>>t;
	for(int i=0;i<t;i++){
		solve();
	}
}
white_check_mark
eyes
raised_hands
React
Reply



Vivek Gupta
  10:00 PM
#include<bits/stdc++.h>
using namespace std;

const int BoardSize = 4;
const int CellSize = 2;

int board[BoardSize][BoardSize];

/*
0 1 0 0
0 0 4 0
0 4 0 0
0 0 3 0
*/

int takenRow[BoardSize];
int takenCol[BoardSize];
int takenGrid[CellSize][CellSize];

int ans = 0;

int makemove(int ch,int row,int col){
	board[row][col]=ch;
	takenRow[row]^=(1<<ch);
	takenCol[col]^=(1<<ch);
	takenGrid[row/CellSize][col/CellSize]^=(1<<ch);
}

int revertmove(int ch,int row,int col){
	board[row][col]=0;
	takenRow[row]^=(1<<ch);
	takenCol[col]^=(1<<ch);
	takenGrid[row/CellSize][col/CellSize]^=(1<<ch);
}

int getchoices(int row,int col){
	int taken = (takenRow[row]|takenCol[col]|takenGrid[row/CellSize][col/CellSize]);
	int nottaken = ((1<<(BoardSize+1))-1)^taken;
	// int nottaken = (~taken)&((1<<(BoardSize+1))-1);
	if(nottaken&1)nottaken^=1;
	return nottaken;
}

void rec(int row,int col){
	if(col==BoardSize){
		rec(row+1,0);
		return;
	}
	if(row==BoardSize){
		// base case
		ans++;

		cout<<"Answer "<<ans<<endl;
		for(int i=0;i<BoardSize;i++){
			for(int j=0;j<BoardSize;j++){
				cout<<board[i][j]<<" ";
			}
			cout<<endl;
		}
		return;
	}

	if(board[row][col]==0){
		// we need to fill.
		int chmask = getchoices(row,col);
		for(int ch=1;ch<=BoardSize;ch++){
			if(chmask&(1<<ch)){
				makemove(ch,row,col);
				rec(row,col+1);
				revertmove(ch,row,col);
			}
		}
	}else{
		// pre-filled (Assume there is a solution (prefilled values don't collide))
		rec(row,col+1);
	}
}

/*
3 0 6 5 0 8 4 0 0
5 2 0 0 0 0 0 0 0
0 8 7 0 0 0 0 3 1
0 0 3 0 1 0 0 8 0
9 0 0 8 6 3 0 0 5
0 5 0 0 9 0 6 0 0
1 3 0 0 0 0 2 5 0
0 0 0 0 0 0 0 7 4
0 0 5 2 0 6 3 0 0
*/

void solve(){
	for(int i=0;i<BoardSize;i++){
		for(int j=0;j<BoardSize;j++){
			int ch;
			cin>>ch;
			makemove(ch,i,j);
		}
	}
	rec(0,0);
	cout<<ans<<endl;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int t=1;
	// cin>>t;
	for(int i=0;i<t;i++){
		solve();
	}
}


Vivek Gupta
  10:07 PM
#include<bits/stdc++.h>
using namespace std;

const int BoardSize = 9;
const int CellSize = 3;

int board[BoardSize][BoardSize];

/*
0 1 0 0
0 0 4 0
0 4 0 0
0 0 3 0
*/
int log2arr[10010];
int takenRow[BoardSize];
int takenCol[BoardSize];
int takenGrid[CellSize][CellSize];

int ans = 0;

void makemove(int ch,int row,int col){
	board[row][col]=ch;
	takenRow[row]^=(1<<ch);
	takenCol[col]^=(1<<ch);
	takenGrid[row/CellSize][col/CellSize]^=(1<<ch);
}

void revertmove(int ch,int row,int col){
	board[row][col]=0;
	takenRow[row]^=(1<<ch);
	takenCol[col]^=(1<<ch);
	takenGrid[row/CellSize][col/CellSize]^=(1<<ch);
}

int getchoices(int row,int col){
	int taken = (takenRow[row]|takenCol[col]|takenGrid[row/CellSize][col/CellSize]);
	int nottaken = ((1<<(BoardSize+1))-1)^taken;
	// int nottaken = (~taken)&((1<<(BoardSize+1))-1);
	if(nottaken&1)nottaken^=1;
	return nottaken;
}

void rec(int row,int col){
	if(col==BoardSize){
		rec(row+1,0);
		return;
	}
	if(row==BoardSize){
		// base case
		ans++;

		cout<<"Answer "<<ans<<endl;
		for(int i=0;i<BoardSize;i++){
			for(int j=0;j<BoardSize;j++){
				cout<<board[i][j]<<" ";
			}
			cout<<endl;
		}
		return;
	}

	if(board[row][col]==0){
		// we need to fill.
		int chmask = getchoices(row,col);

		while(chmask){
			// get last 1
			int last1 = chmask^(chmask&(chmask-1));
			// find position of last 1
			int last1pos = log2arr[last1];

			// use that as a valid move.
			makemove(last1pos,row,col);
			rec(row,col+1);
			revertmove(last1pos,row,col);
			// remove last 1.
			chmask = chmask&(chmask-1);
		}

	}else{
		// pre-filled (Assume there is a solution (prefilled values don't collide))
		rec(row,col+1);
	}
}

/*
3 0 6 5 0 8 4 0 0
5 2 0 0 0 0 0 0 0
0 8 7 0 0 0 0 3 1
0 0 3 0 1 0 0 8 0
9 0 0 8 6 3 0 0 5
0 5 0 0 9 0 6 0 0
1 3 0 0 0 0 2 5 0
0 0 0 0 0 0 0 7 4
0 0 5 2 0 6 3 0 0
*/

void solve(){
	for(int i=0;i<=9;i++){
		log2arr[1<<i]=i;
	}
	for(int i=0;i<BoardSize;i++){
		for(int j=0;j<BoardSize;j++){
			int ch;
			cin>>ch;
			makemove(ch,i,j);
		}
	}

	rec(0,0);
	//cout<<ans<<endl;
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

	int t=1;
	// cin>>t;
	for(int i=0;i<t;i++){
		solve();
	}
}