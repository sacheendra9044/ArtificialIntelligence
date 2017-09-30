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
int f[3];
int cnt[4];
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
	if(board[nx][ny] !=0 && board[nx][ny] != (f[turn]) ) {
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
	if(board[nx][ny] != 0 && board[nx][ny] != (f[turn]) ) {
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
struct triple {
  double x[3];
  triple() {}
  triple(double _x,double _y,double _z) {
    x[0] = _x ; x[1] = _y ; x[2] = _z;
  }
};
triple func(){
  int d[3],m[3],c[3];
  F(i,0,3) {
    d[i] = c[i] = m[i] = 0;
  }
  d[0] = getcount(1);
  d[1] = getcount(2);
  d[2] = getcount(3);
  F(i,0,n) {
    F(j,0,n) {
      if(valid(i,j,0)) {
	m[0]++;
      }
      if(valid(i,j,1)) {
	m[1]++;
      }
      if(valid(i,j,2)) {
	m[2]++;
      }
    }
  }
  c[0] += (board[0][0] == 1);
  c[0] += (board[0][n-1] == 1);
  c[0] += (board[n-1][0] == 1);
  c[0] += (board[n-1][n-1] == 1);
  c[1] += (board[0][0] == 2);
  c[1] += (board[0][n-1] == 2);
  c[1] += (board[n-1][0] == 2);
  c[1] += (board[n-1][n-1] == 2);
  c[2] += (board[0][0] == 3);
  c[2] += (board[0][n-1] == 3);
  c[2] += (board[n-1][0] == 3);
  c[2] += (board[n-1][n-1] == 3);
  triple ret = triple(0.0 , 0.0 , 0.0);
  F(i,0,3) {
    if( (d[0] + d[1] + d[2]) != 0) {
      ret.x[i] += 1.0 * (d[i] - max(d[(i+1)%3],d[(i+2)%3]))/(d[0] + d[1] + d[2]);
    }
    if( (m[0] + m[1] + m[2]) != 0) {
      ret.x[i] += 100.0 * (m[i] - max(m[(i+1)%3],m[(i+2)%3]))/(m[0] + m[1] + m[2]);
    }
    if((c[0] + c[1] + c[2]) != 0) {
      ret.x[i] += 1000.0 * (c[i] - max(c[(i+1)%3],c[(i+2)%3]))/(c[0] + c[1] + c[2]);
    }
  }
  return ret;
}
triple get_util(int turn,int depth) {
  if(isterminal()) {
    triple temp;
    for(int i = 0 ; i < 3 ; i++) {
      double val = getcount(f[i])-max(getcount( f[(i+1)%3]),getcount( f[(i+2)%3]));
      temp.x[i] = val;
    }
    F(i,0,3) {
      if(temp.x[i] > 0.0) {
	temp.x[i] += inf/10.0;
      }
      else if(temp.x[i] < 0.0 ) {
	temp.x[i] += -inf/10.0;
      }
    }
    return temp;
  }
  if(depth == 0) {
    return func();
  }
  bool flag = false;
  int save[20][20];
  int C[4];
  F(i,0,4) C[i] = cnt[i];
  cpy(save,board);
  triple ret = triple(-inf,-inf,-inf);
  F(i,0,n) {
    F(j,0,n) {
      if(valid(i,j,turn)) {
	flag = true;
	play(i,j,turn);
	triple temp = get_util((turn+1)%3,depth-1);
	if(temp.x[turn] > ret.x[turn]) {
	  ret = temp;
	}
	cpy(board,save);
	F(i,0,4) cnt[i] = C[i]; 
      }
    }
  }
  if(!flag) {
    ret = get_util((turn+1)%3,depth-1);
  }
  return ret;
}
void rec(int turn,int moves) {
  if( moves == m ) {
    return ;
  }
  int save[20][20];
  int C[4];
  F(i,0,4) C[i] = cnt[i];
  cpy(save,board);
  double mx = -inf;
  pii idx = mp(-1,-1);
  F(i,0,n) {
    F(j,0,n) {
      if(valid(i,j,turn)) {
	play(i,j,turn);
	double val = get_util((turn+1)%3,d).x[turn];
	if(val > mx) {
	  mx = val;
	  idx = mp(i,j);
	}
	cpy(board,save);
	F(i,0,4) cnt[i] = C[i];
      }
    }
  }
  if(idx != mp(-1,-1)) {
    play(idx.fr,idx.se,turn);
  }
  show();
  rec((turn+1)%3,moves+1);
}
int main() {
  f[0] = 1;
  f[1] = 2;
  f[2] = 3;
  int t;
  sci(t);
  while(t--) {
    sci(n);
    F(i,0,4) cnt[i] = 0;
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
