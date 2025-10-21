// 整数三分
function<int(int)> F = [&](int x) { return x; };
int L = 0, R = 1e9, sg = 1;
// 单谷sg=-1
while (L < R) {
  int lmid = L + (R - L) / 3, rmid = R - (R - L) / 3;
  // cout<<L<<" "<<lmid<<" "<<rmid<<" "<<R<<"\n";
  if (sg * F(lmid) < sg * F(rmid)) {
    L = lmid + 1;
  } else {
    R = rmid - 1;
  }
}
// 实数三分

const double eps = 1e-8;
function<double(double)> F = [&](double x) { return x; };
double L = 1, R = 1e9, sg = 1;
// 单谷sg=-1
while (R - L > eps) {
  double lmid = L + (R - L) / 3, rmid = R - (R - L) / 3;
  if (sg * F(lmid) < sg * F(rmid)) {
    L = lmid;
  } else {
    R = rmid;
  }
}