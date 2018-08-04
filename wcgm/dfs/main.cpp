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

vector<vector<int>> rightSide(SearchMax, vector<int>(4, -1));
vector<vector<int>> leftSide(SearchMax, vector<int>(4, -1));

void printState(vector<int> state)
{
   cout << "[ ";
   for(int i = 0; i < 4; i++)
   {
     if(state[i] == 1 && i == MAN) cout << "男性 ";
     if(state[i] == 1 && i == WOLF) cout << "狼 ";
     if(state[i] == 1 && i == GOAT) cout << "羊 ";
     if(state[i] == 1 && i == CABBAGE) cout << "キャベツ ";
   }
   cout << "]";
}

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

bool checkState(int T, vector<int> state, vector<vector<int>> pastState)
{
  if (((state[GOAT] == 1) && (state[WOLF] == 1 || state[CABBAGE] == 1)) 
    && state[MAN] == 0)
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
      newSrcState = srcState;
      newDestState = destState;
      newSrcState[MAN] = 0;
      newDestState[MAN] = 1;
      newSrcState[i] = 0;
      newDestState[i] = 1;
      
      if(checkState(T, newSrcState, srcSide))
      {
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

        if(T == SearchMax-1 || 
          (rightSide[T+1][1] && rightSide[T+1][2] && 
          rightSide[T+1][3] && rightSide[T+1][0]))
        {
          cout << "Ans" << endl;
          printAns(T);
          exit(0);
        }
        else if(T % 2 == 0) dfs(T+1, rightSide, leftSide);
        else dfs(T+1, leftSide, rightSide);
      }
    }
  }
}

int main()
{
  for(int i = 0; i < 4; i++)
  {
    leftSide[0][i]   = 1;
    rightSide[0][i]  = 0;
  }

  dfs(0, leftSide, rightSide);
}
