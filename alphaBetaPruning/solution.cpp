#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007
#define pii pair<int, int>
#define pll pair<long long, long long>
#define vi  vector<int>
#define pb  push_back
#define mp  make_pair
#define ALL(x) x.begin(),x.end()
#define M(a,x) memset(a,x,sizeof(a))
#define sci(x) scanf("%d",&x);
#define scl(x) scanf("%lld",&x);
#define scs(x) scanf("%s",x);
#define SZ(x) (int)x.size()
#define print(x) printf("%d",x);
#define nl printf("\n")
#define fr first
#define se second
#define printl(x) printf("%lld",x)
#define F(i,a,n) for(int i=a;i<n;i++)
#define INF 100000000000000000LL
#define LL long long
int n,d,m;
int board[20][20];
const int dx[] = {0,1,1,1,0,  -1,-1,-1};
const int dy[] = {1,1,0,-1,-1,-1,0,1};
int f[2];
int cnt[3];
const double inf = 1000000000000000.00;
void cpy(int a[][20],int b[][20]) {
  F(i,0,n) {
    F(j,0,n) {
      a[i][j] = b[i][j];
    }
  }
}
 
void show() {
  F(i,0,n) {
    F(j,0,n) {
      printf("%d ",board[i][j]);
    }
    nl;
  }
  printf("-\n");
}
 
bool isterminal() {
  return (cnt[0] == 0);
}
bool valid(int x,int y,int turn) {
  if(board[x][y] != 0 ) return false;
  int val = f[turn];
  bool flag = false;
  for(int i = 7 ; i>= 0 ; i--) {
    int nx = x;
    int ny = y;
    int g = 0;
    while(true) {
      nx += dx[i];
      ny += dy[i];
      if(nx >= 0 && nx < n && ny >= 0 && ny < n) {
	if(board[nx][ny] == (f[1-turn]) ) {
	  g = 1;
	  continue;
	}
	if(board[nx][ny] == f[turn] && g) {
	  return true;
	}
	break;
      }
      else {
	break;
      }
    }
  }
  return false;
}
void play(int x,int y,int turn) {
  cnt[board[x][y]]--;
  board[x][y] = f[turn];
  cnt[f[turn]]++;
  F(i,0,8) {
    int nx = x;
    int ny = y;
    bool ok = false;
    int g = 0;
    while(true) {
      nx += dx[i];
      ny += dy[i];
      if(nx >= 0 && nx < n && ny >= 0 && ny < n) {
	if(board[nx][ny] == (f[1-turn]) ) {
	  g = 1;
	  continue;
	}
	if(board[nx][ny] == f[turn] && g) {
	  ok |= 1;
	  break;
	}
	break;
      }
      else {
	break;
      }
    }
    if(ok) {
      nx = x;
      ny = y;
      while(true) {
	nx += dx[i];
	ny += dy[i];
	if(nx >= 0 && nx < n && ny >= 0 && ny < n) {
	  if(board[nx][ny] == f[turn]) break;
	  cnt[board[nx][ny]]--;
	  board[nx][ny] = f[turn];
	  cnt[board[nx][ny]]++;
	}
      }
    }
  }
}
int getcount(int val) {
  return cnt[val];
}
double func(int turn){
  double ret = 0.00;
  int Dmax = getcount(1);
  int Dmin = getcount(2);
  int movemax = 0 , movemin = 0;
  F(i,0,n) {
    F(j,0,n) {
      if(valid(i,j,0)) {
	movemax++;
      }
      if(valid(i,j,1)) {
	movemin++;
      }
    }
  }
  int cmax = 0, cmin = 0;
  cmax += (board[0][0] == 1);
  cmax += (board[0][n-1] == 1);
  cmax += (board[n-1][0] == 1);
  cmax += (board[n-1][n-1] == 1);
  cmin += (board[0][0] == 2);
  cmin += (board[0][n-1] == 2);
  cmin += (board[n-1][0] == 2);
  cmin += (board[n-1][n-1] == 2);
 
 
  if( (Dmax + Dmin) != 0) {
    ret += 1.0 * (Dmax - Dmin)/(Dmax +Dmin);
  }
  if( (movemax + movemin) != 0 ) {
    ret += 100.0 * (movemax - movemin)/(movemax +movemin);
  }
  if( (cmax+cmin) != 0) {
    ret += 1000 * (cmax - cmin)/(cmax + cmin);
  }
  return ret;
}
double get_util(int turn,int depth,double a,double b) {
  if(isterminal()) {
    int temp1 = getcount(1);
    int temp2 = getcount(2);
    if(temp1-temp2 == 0) {
      return 0.00;
    }
    if(temp1 - temp2 < 0) {
      return -inf/10.0;
    }
    return inf/10.0;
  }
  if(depth == 0) {
    return func(turn);
  }
  int save[20][20];
  int C[3];
  F(i,0,3) C[i] = cnt[i];
  cpy(save,board);
  double ret;
  if(turn == 0) {
    ret = -inf;
    F(i,0,n) {
      bool f =0 ;
      F(j,0,n) {
	if(valid(i,j,turn)) {
	  play(i,j,turn);
	  ret = max(ret , get_util(1-turn,depth-1,a,b));
	  a = max(a,ret);
	  cpy(board,save);
	  F(i,0,3) cnt[i] = C[i]; 
	  if(b <= a){
	    return ret;
	  }
	}
      }
    }
  }
  if(turn == 1) {
    ret = inf;
    F(i,0,n) {
      F(j,0,n) {
	bool f = 0;
	if(valid(i,j,turn)) {
	  play(i,j,turn);
	  ret = min(ret , get_util(1-turn,depth-1,a,b));
	  b = min(b,ret);
	  cpy(board,save);
	  F(i,0,3) cnt[i] = C[i]; 
	  if(b <= a) {
	    return ret;
	  }
	}
      }
    }
  }
  return ret;
}
void rec(int turn,int moves) {
  if( moves == m ) {
    return ;
  }
  int save[20][20];
  int C[3];
  F(i,0,3) C[i] = cnt[i];
  cpy(save,board);
  double mx = -inf;
  double mn = inf;
  pii idx = mp(-1,-1);
  if(turn == 0) {
    F(i,0,n) {
      F(j,0,n) {
	if(valid(i,j,turn)) {
	  play(i,j,turn);
	  double val = get_util(1-turn,d,-inf,inf);
	  if(val > mx ) {
	    mx = val;
	    idx = mp(i,j);
	  }
	  cpy(board,save);
	  F(i,0,3) cnt[i] = C[i];
	}
      }
    }
  }
  else if(turn == 1 ) {
    F(i,0,n) {
      F(j,0,n) {
	if(valid(i,j,turn)) {
	  play(i,j,turn);
	  double val = get_util(1-turn,d,-inf,inf);
	  if(val < mn) {
	    mn = val;
	    idx = mp(i,j);
	  }
	  cpy(board,save);
	  F(i,0,3) cnt[i] = C[i];
	}
      }
    }
  }
  if(idx!=mp(-1,-1)) {
    play(idx.fr,idx.se,turn);
  }
  show();
  rec(1-turn,moves+1);
}
int main() {
  f[0] = 1;
  f[1] = 2;
  int t;
  sci(t);
  while(t--) {
    sci(n);
    F(i,0,3) cnt[i] = 0;
    F(i,0,n) {
      F(j,0,n) {
	sci(board[i][j]);
	cnt[board[i][j]]++;
      }
    }
    sci(m) ; sci(d);
    rec(0,0); // 0 = max , 1 = min
  }
}

