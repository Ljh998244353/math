#include <ext/pb_ds/assoc_container.hpp>  //关联容器，必加
#include <ext/pb_ds/hash_policy.hpp>      //哈希表
#include <ext/pb_ds/priority_queue.hpp>   //优先队列
#include <ext/pb_ds/tree_policy.hpp>      //平衡树
#include <ext/pb_ds/trie_policy.hpp>      //字典树
#include <vector>

template <>
struct std::tr1::hash<std::pair<int, int> > {
  size_t operator()(std::pair<int, int> x) const {
    return x.first ^ x.second;  // 你自定义的 hash 函数。
  }
};
__gnu_pbds::gp_hash_table<std::pair<int, int>, int> Table;
// 此时可以通过编译。
