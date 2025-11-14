#include <iostream>
#include <string>
#include <vector>
#include <array>    // 用于低常数的转移表
#include <numeric>  // 用于 std::iota (可选)

using namespace std;

// 字符集大小 (a-z)
const int ALPHABET_SIZE = 26;

struct SAM {

    struct State {
        int len = 0;   // 该状态代表的最长字符串长度
        int link = 0;  // 后缀链接 (fail 指针), 0 表示哨兵
        array<int, ALPHABET_SIZE> tr; // 转移
        int cnt = 0;   // end-pos 集合大小 (用于计算出现次数)

        State() {
            tr.fill(0); // 默认所有转移都指向 0 (空)
        }
    };

    vector<State> st; // 存储所有状态
    int sz;           // 状态总数
    int last;         // 当前整个字符串对应的状态

    // 基数排序辅助数组
    vector<int> c; // 计数
    vector<int> a; // 排序后的状态 ID (1-based)

    /**
     * @brief 初始化 SAM
     * 状态 0 作为哨兵节点 (dummy node)
     * 状态 1 作为根节点, len=0, link=0
     */
    void init() {
        st.clear();
        st.resize(2); // 0号为哨兵, 1号为根
        
        sz = 1;       // 只有一个根节点
        last = 1;     // 初始时 last 指向根
        
        st[1].len = 0;
        st[1].link = 0; // 根的 link 指向哨兵 0
        st[1].cnt = 0; // 根节点不代表任何 end-pos
    }

    /**
     * @brief 插入一个新字符
     * @param c 字符 (0-25)
     */
    void extend(int c) {
        int cur = ++sz; // 创建新状态 (ID 为 sz)
        st.emplace_back(); // 动态添加一个新状态
        
        st[cur].len = st[last].len + 1;
        st[cur].cnt = 1; // 这是一个新的 end-pos
        
        int p = last;

        // 1. 沿着 link 链向上，为所有没有 c 转移的祖先添加到 cur 的转移
        while (p != 0 && !st[p].tr[c]) {
            st[p].tr[c] = cur;
            p = st[p].link;
        }

        if (p == 0) {
            // Case 1: 到了根 (的 link，即哨兵)
            st[cur].link = 1; // 新节点的 link 指向根
        } else {
            int q = st[p].tr[c];
            if (st[q].len == st[p].len + 1) {
                // Case 2: 连续的转移
                st[cur].link = q;
            } else {
                // Case 3: 状态 q 需要被拆分
                int clone = ++sz; // 创建克隆状态
                st.push_back(st[q]); // 复制 q 的所有信息 (tr, link)
                
                st[clone].len = st[p].len + 1;
                st[clone].cnt = 0; // 克隆节点不是一个 "真实" 的 end-pos

                // 2. 将 p 和 p 的祖先中原先指向 q 的转移重定向到 clone
                while (p != 0 && st[p].tr[c] == q) {
                    st[p].tr[c] = clone;
                    p = st[p].link;
                }

                // 3. 将 q 和 cur 的 link 指向 clone
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    /**
     * @brief 计算所有状态的 end-pos 集合大小 (子树大小)
     * 必须在 SAM 构建完毕后调用
     */
    void calc_subtree_size() {
        int max_len = st[last].len;
        
        // 调整辅助数组大小
        c.assign(max_len + 1, 0);
        a.assign(sz, 0); // 存储 sz 个状态的 ID

        // 1. 计数
        for (int i = 1; i <= sz; ++i) {
            c[st[i].len]++;
        }
        
        // 2. 计算前缀和
        for (int i = 1; i <= max_len; ++i) {
            c[i] += c[i - 1];
        }

        // 3. 放置 (基数排序)
        //    a 是 0-based 数组, 存储 1-based 的状态 ID
        for (int i = 1; i <= sz; ++i) {
            a[--c[st[i].len]] = i;
        }

        // 4. 按照长度从大到小 (拓扑序的逆序) 
        //    在 link 树 (parent tree) 上累加子树大小
        for (int i = sz - 1; i >= 0; --i) {
            int v = a[i]; // v 是 1-based 状态 ID
            if (st[v].link != 0) { // 只要不是根节点 (link=0)
                st[st[v].link].cnt += st[v].cnt;
            }
        }
    }

    // --- 模板应用示例 ---

    /**
     * @brief 计算不同子串的数量
     * @return long long 不同子串总数
     */
    long long count_distinct_substrings() {
        long long ans = 0;
        // 从 2 开始，跳过根节点 1 (根的 link=0, len=0)
        for (int i = 2; i <= sz; ++i) {
            ans += (st[i].len - st[st[i].link].len);
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
        int v = 1; // 从根节点开始
        for (char ch : P) {
            int c = ch - 'a';
            if (!st[v].tr[c]) return 0; // 不存在该子串
            v = st[v].tr[c];
        }
        // v 状态的 end-pos 集合大小即为出现次数
        return st[v].cnt;
    }
};

// --- 主函数示例 ---

// 全局声明 SAM 对象
SAM sam;
char s[1000005]; // 使用 char 数组配合 scanf/printf 加快 IO

int main() {
    // 提高 IO 效率 (ICPC 常用)
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    scanf("%s", s);
    string str = s; // C++ 风格处理

    // 1. 初始化
    sam.init();

    // 2. 构建 SAM
    for (char ch : str) {
        sam.extend(ch - 'a');
    }

    // 3. (可选) 计算子树大小，用于查询出现次数
    sam.calc_subtree_size();

    // 4. (可选) 计算不同子串数量
    printf("Distinct substrings: %lld\n", sam.count_distinct_substrings());

    // 5. (可选) 查询特定子串出现次数
    string pattern = "aba"; // 仅为示例
    printf("Occurrences of '%s': %d\n", pattern.c_str(), sam.count_occurrences(pattern));

    return 0;
}