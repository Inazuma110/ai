#include <bits/stdc++.h>

using namespace std;

#define rep(i, n) for(int i = 0; i < (int)(n); i++)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define itn int

typedef long long ll;
typedef pair<ll,ll> p;

#define MAN         0
#define WOLF        1
#define GOAT        2
#define CABBAGE     3

#define SearchMax   20

// 左岸と右岸の状態を表す。
// 0の場合存在せず、1の場合存在する。
vector<vector<int>> rightSide(SearchMax, vector<int>(4, -1));
vector<vector<int>> leftSide(SearchMax, vector<int>(4, -1));

// 与えられた配列から、なにが存在しているかを表示する。
void printState(vector<int> state)
{
   cout << "[ ";
   for(int i = 0; i < 4; i++)
   {
     if(state[i] && i == MAN) cout << "男性 ";
     if(state[i] && i == WOLF) cout << "狼 ";
     if(state[i] && i == GOAT) cout << "羊 ";
     if(state[i] && i == CABBAGE) cout << "キャベツ ";
   }
   cout << "]";
}

// 引数Tステップまでの岸の変異を表示する。
void printAns(int T)
{
  for(int i = 0; i < T+1; i++)
  {
    cout << i << ": " ;
    printState(leftSide[i]);
    cout << " "; 
    printState(rightSide[i]);
    cout << endl;
  }
}

// 与えられた引数の状態が狼と羊、または羊とキャベツが男がいない状態で成り立ってしまっていないかをチェックする。また、過去に同じ状態がなかったかをチェックする。
// あった場合はfalseを返し、なければtrueを返す。
bool checkState(int T, vector<int> state, vector<vector<int>> pastState)
{
  if ((state[GOAT] && (state[WOLF] || state[CABBAGE])) 
    && !state[MAN])
    return false;
  for(int t = 0; t <= T; t++){
    bool flag = true;
    for(int i = 0; i < 4; i++)
    {
      if(state[i] != pastState[t][i]) flag = false;
    }
    if(flag) return false;
  }
  return true;
}

// 探索を行うdfs
void dfs(int T, vector<vector<int>> srcSide, vector<vector<int>> destSide)
{
  vector<int> srcState(4);
  vector<int> destState(4);
  vector<int> newSrcState(4);
  vector<int> newDestState(4);

   for(int i = 0; i < 4; i++)
   {
     srcState[i] = srcSide[T][i];
     destState[i] = destSide[T][i];
   }

  for(int i = 0; i < 4; i++)
  {
    if(srcState[i] == 1)
    {
      // 変異後の配列状態を生成する。
      newSrcState = srcState;
      newDestState = destState;
      newSrcState[MAN] = 0;
      newDestState[MAN] = 1;
      newSrcState[i] = 0;
      newDestState[i] = 1;
      
      // 状態newSrcStateが可能ならば
      if(checkState(T, newSrcState, srcSide))
      {
        // 左岸、右岸に状態を格納する。
        // ステップ数Tが奇数か偶数かで格納する岸を変化させる。
        if(T % 2 == 0)
        {
          leftSide[T+1] = newSrcState;
          destSide = leftSide;
          rightSide[T+1] = newDestState;
          srcSide = rightSide;
        }else{
          rightSide[T+1] = newSrcState;
          srcSide = rightSide;
          leftSide[T+1] = newDestState;
          destSide = leftSide;
        }

        // 検索回数を上限まで行った場合、または右岸に全員が辿りついた場合、経過を表示し、処理を終了する。
        if(T == SearchMax-1 || 
          (rightSide[T+1][1] && rightSide[T+1][2] && 
          rightSide[T+1][3] && rightSide[T+1][0]))
        {
          cout << "Ans" << endl;
          printAns(T);
          exit(0);
        }
        // そうでなかった場合。dfsを続ける。
        // この場合も、ステップ数が奇数が偶数かで処理を分ける。
        else if(T % 2 == 0) dfs(T+1, rightSide, leftSide);
        else dfs(T+1, leftSide, rightSide);
      }
    }
  }
}

int main()
{
  // 岸を初期化する。
  for(int i = 0; i < 4; i++)
  {
    leftSide[0][i]   = 1;
    rightSide[0][i]  = 0;
  }
  // dfsを開始する。
  dfs(0, leftSide, rightSide);
}
