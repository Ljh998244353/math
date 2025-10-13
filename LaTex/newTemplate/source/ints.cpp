
using ld = long double;
/**
 * @brief 计算两个不跨越 (-PI, PI] 边界的区间 [a1, b1] 和 [a2, b2] 的交集长度。
 */
ld intersect_non_crossing(ld a1, ld b1, ld a2, ld b2) {
  // 交集的左端点是 max(a1, a2)
  ld start = max(a1, a2);
  // 交集的右端点是 min(b1, b2)
  ld end = min(b1, b2);

  // 只有当 start < end 时，交集才存在
  if (start < end) {
    return end - start;
  } else {
    return 0.0;
  }
}

ld ints(ld l1, ld r1, ld l2, ld r2) {
  ld total_intersection = 0.0;

  vector<pair<ld, ld>> segs1;
  if (l1 <= r1) {
    segs1.push_back({l1, r1});
  } else {
    segs1.push_back({l1, PI});
    segs1.push_back({-PI, r1});
  }

  vector<pair<ld, ld>> segs2;
  if (l2 <= r2) {
    segs2.push_back({l2, r2});
  } else {
    segs2.push_back({l2, PI});
    segs2.push_back({-PI, r2});
  }
  for (const auto& seg1 : segs1) {
    ld a1 = seg1.first;
    ld b1 = seg1.second;

    for (const auto& seg2 : segs2) {
      ld a2 = seg2.first;
      ld b2 = seg2.second;
      total_intersection += intersect_non_crossing(a1, b1, a2, b2);
    }
  }
  return min(total_intersection, PI * 2);
}