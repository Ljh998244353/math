struct Bitset {
  Bitset() : Bitset(0) {}
  Bitset(int _sz) {
    sz = _sz;
    ptr = 0;
    vec.resize((_sz + 63) >> 6);
  }
  void Add(int cnt, uLL val) {
    if (cnt <= 64 - (ptr & 63))
      vec[ptr >> 6] |= val << (ptr & 63);
    else {
      uLL mask = BitBetween(0, 64 - (ptr & 63) - 1);
      vec[ptr >> 6] |= (val & mask) << (ptr & 63);
      vec[(ptr >> 6) + 1] = val >> (64 - (ptr & 63));
    }
    ptr += cnt;
  }
  void GetSame(const Bitset& rhs) {
    while (sz != ptr || rhs.sz != rhs.ptr);
    for (int i = 0; i < vec.size(); i++) vec[i] ^= ~rhs.vec[i];
    int mn_sz = min(sz, rhs.sz);
    for (int i = mn_sz >> 6; i < vec.size(); i++) {
      int l_bit = max(0, mn_sz - (i << 6));
      int r_bit = 63;
      vec[i] &= ~BitBetween(l_bit, r_bit);
    }
  }
  uLL Calc() const {
    uLL ret = 0;
    for (int i = 0, ri = 0; i < vec.size(); i++) {
      Update(vec[i] & (S - 1), ret, ri);
      Update(vec[i] >> 16 & (S - 1), ret, ri);
      Update(vec[i] >> 32 & (S - 1), ret, ri);
      Update(vec[i] >> 48 & (S - 1), ret, ri);
    }
    return ret;
  }
  void out() const {
    fprintf(stderr, "sz = %d : ", sz);
    for (int i = 0; i < sz; i++)
      fprintf(stderr, "%llu", (vec[i >> 6] >> (i & 63)) & 1);
    fprintf(stderr, "\n");
  }

  int sz, ptr;
  vector<uLL> vec;
};