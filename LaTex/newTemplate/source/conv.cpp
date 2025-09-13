template <class T>
struct Convo {
  // 快速幂
  long long qpow(long long a, long long b) const {
    long long res = 1;
    while (b) {
      if (b & 1) res = res * a % mod;
      a = a * a % mod;
      b >>= 1;
    }
    return res;
  }

  // SOS 前缀和
  void sos_prefix(vector<T>& f, int n) {
    int N = 1 << n;
    for (int i = 0; i < n; ++i) {
      for (int mask = 0; mask < N; ++mask) {
        if (mask & (1 << i)) {
          f[mask] = (f[mask] + f[mask ^ (1 << i)]) % mod;
        }
      }
    }
  }
  // SOS 逆
  void sos_inverse(vector<T>& f, int n) {
    int N = 1 << n;
    for (int i = 0; i < n; ++i) {
      for (int mask = 0; mask < N; ++mask) {
        if (mask & (1 << i)) {
          f[mask] = (f[mask] - f[mask ^ (1 << i)] + mod) % mod;
        }
      }
    }
  }
  // SOS 后缀和
  void sos_suffix(vector<T>& f, int n) {
    int N = 1 << n;
    for (int i = 0; i < n; ++i) {
      for (int mask = 0; mask < N; ++mask) {
        if (!(mask & (1 << i))) {
          f[mask] = (f[mask] + f[mask | (1 << i)]) % mod;
        }
      }
    }
  }
  // SOS 后缀逆
  void sos_suffix_inverse(vector<T>& f, int n) {
    int N = 1 << n;
    for (int i = 0; i < n; ++i) {
      for (int mask = 0; mask < N; ++mask) {
        if (!(mask & (1 << i))) {
          f[mask] = (f[mask] - f[mask | (1 << i)] + mod) % mod;
        }
      }
    }
  }

  // 线性筛及 Möbius
  vector<int> primes, mu;
  vector<bool> is_comp;
  void init_sieve(int N) {
    mu.assign(N + 1, 1);
    is_comp.assign(N + 1, false);
    for (int i = 2; i <= N; ++i) {
      if (!is_comp[i]) {
        primes.push_back(i);
        mu[i] = -1;
      }
      for (int p : primes) {
        if ((long long)i * p > N) break;
        is_comp[i * p] = true;
        mu[i * p] = (i % p == 0 ? 0 : -mu[i]);
        if (i % p == 0) break;
      }
    }
  }
  // Dirichlet 前缀和
  void dirichlet_prefix(vector<T>& F, int n) {
    for (int p : primes) {
      if (p > n) break;
      for (int i = 1; i * p <= n; ++i) {
        F[i * p] = (F[i * p] + F[i]) % mod;
      }
    }
  }
  // Dirichlet 前缀逆
  void dirichlet_prefix_inverse(vector<T>& G, int n) {
    for (int i = (int)primes.size() - 1; i >= 0; --i) {
      int p = primes[i];
      if (p > n) continue;
      for (int j = 1; j * p <= n; ++j) {
        G[j * p] = (G[j * p] - G[j] + mod) % mod;
      }
    }
  }
  // Dirichlet 后缀和
  void dirichlet_suffix(vector<T>& F, int n) {
    for (int p : primes) {
      if (p > n) break;
      for (int i = n / p; i >= 1; --i) {
        F[i] = (F[i] + F[i * p]) % mod;
      }
    }
  }
  // Dirichlet 后缀逆
  void dirichlet_suffix_inverse(vector<T>& H, int n) {
    for (int i = (int)primes.size() - 1; i >= 0; --i) {
      int p = primes[i];
      if (p > n) continue;
      for (int j = n / p; j >= 1; --j) {
        H[j] = (H[j] - H[j * p] + mod) % mod;
      }
    }
  }

  // OR 卷积
  void OR(vector<T>& F, vector<T>& G, int n) {
    sos_prefix(F, n);
    sos_prefix(G, n);
    int N = 1 << n;
    for (int i = 0; i < N; ++i) F[i] = (long long)F[i] * G[i] % mod;
    sos_inverse(F, n);
  }
  // AND 卷积
  void AND(vector<T>& F, vector<T>& G, int n) {
    sos_suffix(F, n);
    sos_suffix(G, n);
    int N = 1 << n;
    for (int i = 0; i < N; ++i) F[i] = (long long)F[i] * G[i] % mod;
    sos_suffix_inverse(F, n);
  }
  // GCD 卷积
  void GCD(vector<T>& F, vector<T>& G, int n) {
    dirichlet_suffix(F, n);
    dirichlet_suffix(G, n);
    for (int i = 1; i <= n; ++i) F[i] = (long long)F[i] * G[i] % mod;
    dirichlet_suffix_inverse(F, n);
  }
  // LCM 卷积
  void LCM(vector<T>& F, vector<T>& G, int n) {
    dirichlet_prefix(F, n);
    dirichlet_prefix(G, n);
    for (int i = 1; i <= n; ++i) F[i] = (long long)F[i] * G[i] % mod;
    dirichlet_prefix_inverse(F, n);
  }
  // 子集卷积
  void SUBSET(vector<T>& A, vector<T>& B, int n) {
    int N = 1 << n;
    vector<vector<T>> f(n + 1, vector<T>(N)), g(n + 1, vector<T>(N));
    for (int mask = 0; mask < N; ++mask) {
      int pc = __builtin_popcount(mask);
      f[pc][mask] = A[mask];
      g[pc][mask] = B[mask];
    }
    for (int i = 0; i <= n; ++i) {
      sos_prefix(f[i], n);
      sos_prefix(g[i], n);
    }
    vector<vector<T>> h(n + 1, vector<T>(N));
    for (int mask = 0; mask < N; ++mask) {
      for (int i = 0; i <= n; ++i) {
        long long sum = 0;
        for (int j = 0; j <= i; ++j) {
          sum += (long long)f[j][mask] * g[i - j][mask] % mod;
        }
        h[i][mask] = sum % mod;
      }
    }
    for (int i = 0; i <= n; ++i) sos_inverse(h[i], n);
    for (int mask = 0; mask < N; ++mask)
      A[mask] = h[__builtin_popcount(mask)][mask];
  }

  // FWT 异或卷积
  void FWT(vector<T>& F, int n, bool inverse = false) {
    int N = 1 << n;
    for (int len = 1; len < N; len <<= 1) {
      for (int i = 0; i < N; i += len << 1) {
        for (int j = 0; j < len; ++j) {
          T u = F[i + j], v = F[i + j + len];
          F[i + j] = (u + v) % mod;
          F[i + j + len] = (u - v + mod) % mod;
        }
      }
    }
    if (inverse) {
      long long inv = qpow(N, mod - 2);
      for (int i = 0; i < N; ++i) F[i] = (long long)F[i] * inv % mod;
    }
  }
  // 异或卷积接口
  void XOR(vector<T>& F, vector<T>& G, int n) {
    FWT(F, n, false);
    FWT(G, n, false);
    int N = 1 << n;
    for (int i = 0; i < N; ++i) F[i] = (long long)F[i] * G[i] % mod;
    FWT(F, n, true);
  }
};