#include <iostream>
#include <string>
#include <vector>
#include <cstring> // 用于 memset 和 memcpy

using namespace std;

// 定义你需要的最大字符串长度
const int MAXN = 1000005; 

struct SAM {
    // N 是最大状态数，大约是 MAXN 的 2 倍
    static const int N = MAXN * 2;
    // A 是字符集大小
    static const int A = 26;

    // tr: 转移状态
    // link: 后缀链接 (fail 指针)
    // len: 该状态代表的最长字符串的长度
    int tr[N][A], link[N], len[N];
    int sz, last; // sz: 状态总数, last: 当前整个字符串对应的状态

    // cnt: end-pos 集合大小 (用于计算出现次数)
    // c: 基数排序辅助数组
    // a: 按 len 排序后的状态ID
    int cnt[N], c[N], a[N];

    /**
     * @brief 初始化 SAM
     * 状态 0 为根节点，len=0, link=-1 (哨兵)
     */
    void init() {
        // 确保所有内容都被清零
        // 注意：在多组数据时，只需重置 sz, last 和 0 号状态
        // memset(tr, 0, sizeof(tr)); 
        // memset(link, 0, sizeof(link));
        // memset(len, 0, sizeof(len));
        
        sz = 1; // 初始只有根节点 0
        last = 0;
        len[0] = 0;
        link[0] = -1; // -1 表示空
        memset(tr[0], 0, sizeof(tr[0]));
    }

    /**
     * @brief 插入一个新字符
     * @param c 字符 (0-25)
     */
    void extend(int c) {
        int cur = sz++; // 创建新状态
        len[cur] = len[last] + 1;
        cnt[cur] = 1; // 这是一个新的 end-pos
        memset(tr[cur], 0, sizeof(tr[cur]));
        
        int p = last; // 从上一个状态开始跳 link

        // 1. 沿着 link 链向上，为所有没有 c 转移的祖先添加到 cur 的转移
        while (p != -1 && !tr[p][c]) {
            tr[p][c] = cur;
            p = link[p];
        }

        if (p == -1) {
            // Case 1: 到了根节点
            link[cur] = 0;
        } else {
            int q = tr[p][c];
            if (len[q] == len[p] + 1) {
                // Case 2: 找到了一个节点 q，且 len[q] == len[p] + 1 (连续的)
                link[cur] = q;
            } else {
                // Case 3: 状态 q 需要被拆分
                int clone = sz++; // 创建克隆状态
                len[clone] = len[p] + 1;
                link[clone] = link[q];
                cnt[clone] = 0; // 克隆节点不是一个 "真实" 的 end-pos
                
                // 复制 q 的转移
                memcpy(tr[clone], tr[q], sizeof(tr[q]));

                // 2. 将 p 和 p 的祖先中原先指向 q 的转移重定向到 clone
                while (p != -1 && tr[p][c] == q) {
                    tr[p][c] = clone;
                    p = link[p];
                }

                // 3. 将 q 和 cur 的 link 指向 clone
                link[q] = link[cur] = clone;
            }
        }
        last = cur;
    }

    /**
     * @brief 计算所有状态的 end-pos 集合大小 (子树大小)
     * 必须在 SAM 构建完毕后调用
     */
    void calc_subtree_size() {
        // 1. 基数排序 (按 len 排序) O(n)
        // memset(c, 0, sizeof(c[0]) * (len[last] + 1)); // 如果多组数据，需要清零
        for (int i = 0; i < sz; ++i) c[len[i]]++;
        for (int i = 1; i <= len[last]; ++i) c[i] += c[i - 1];
        for (int i = 0; i < sz; ++i) a[--c[len[i]]] = i;

        // 2. 按照长度从大到小 (拓扑序的逆序) 
        //    在 link 树 (parent tree) 上累加子树大小
        for (int i = sz - 1; i >= 0; --i) {
            int v = a[i];
            if (link[v] != -1) {
                cnt[link[v]] += cnt[v];
            }
        }
    }

    // --- 模板应用示例 ---

    /**
     * @brief 计算不同子串的数量
     * 每个状态 i 贡献的新子串数量为 len[i] - len[link[i]]
     * @return long long 不同子串总数
     */
    long long count_distinct_substrings() {
        long long ans = 0;
        for (int i = 1; i < sz; ++i) { // 从 1 开始，跳过根
            ans += (len[i] - len[link[i]]);
        }
        return ans;
    }

    /**
     * @brief 查找字符串 P 的出现次数
     * @note 必须先调用 calc_subtree_size()
     * @param P 要查找的模式串
     * @return 出现次数
     */
    int count_occurrences(const string& P) {
        int v = 0;
        for (char ch : P) {
            int c = ch - 'a';
            if (!tr[v][c]) return 0; // 不存在该子串
            v = tr[v][c];
        }
        return cnt[v]; // v 状态的 end-pos 集合大小即为出现次数
    }
};

// --- 主函数示例 ---

// 全局声明 SAM 对象
SAM sam;
char s[MAXN]; // 使用 char 数组 配合 scanf/printf 加快 IO

int main() {
    // 提高 IO 效率 (ICPC 常用)
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    scanf("%s", s);
    int n = strlen(s);

    // 1. 初始化
    sam.init();

    // 2. 构建 SAM
    for (int i = 0; i < n; ++i) {
        sam.extend(s[i] - 'a');
    }

    // 3. (可选) 计算子树大小，用于查询出现次数
    sam.calc_subtree_size();

    // 4. (可选) 计算不同子串数量
    printf("Distinct substrings: %lld\n", sam.count_distinct_substrings());

    // 5. (可选) 查询特定子串出现次数
    // 示例：查询 "aba" (假设它在 s 中)
    // string pattern = "aba";
    // printf("Occurrences of '%s': %d\n", pattern.c_str(), sam.count_occurrences(pattern));

    return 0;
}