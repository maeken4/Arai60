# step1
いかにも再帰で書けそうと思い、ベースケースをnullptrに設定し書いた。10分くらい。
```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }
};
```

# step2
他の人の回答を見る
- https://discord.com/channels/1084280443945353267/1227073733844406343/1236235351140339742
  > 二つの DFS は対応しておらず、上から配るのと下から上げてくるのの差があることは認識できますか?
  
  step1の書き方だと探索の帰りに値を足している(下から上げる=bottom-up)が、2-1の書き方だと、行きに値を足している(上から配る=top-down)。2-2でstack,下から上げる、2-3で再帰、上から配るで実装してみた。

- https://github.com/Yuto729/leetcode/pull/26
  レベルごとに走査する方法もある。

再帰で書いたほうが簡潔だが、スタック領域の限界(スタックオーバーフロー)に達する危険性がある。

stackで書き直すとヒープ領域にデータが置かれるのでより大きなデータを持つことができる。

## step2-1 stackで書き直す(top-down)

```cpp
#include <stack>

class Solution {
public:
    int maxDepth(TreeNode* root) {
        int max_depth = 0;
        if (root == nullptr) {
            return max_depth;
        }
        std::stack<std::pair<TreeNode*, int>> node_and_depth;
        node_and_depth.emplace(root, 1);

        while (!node_and_depth.empty()) {
            auto [node, depth] = node_and_depth.top();
            node_and_depth.pop();
            max_depth = std::max(max_depth, depth);

            if (node->left != nullptr) {
                node_and_depth.emplace(node->left, depth + 1);
            }
            if (node->right != nullptr) {
                node_and_depth.emplace(node->right, depth + 1);
            }

        }
        return max_depth;
    }
};
```

## step2-2 stackでbottom-up
liquoreさんの解答を写経。https://discord.com/channels/1084280443945353267/1227073733844406343/1236324993839792149

C++の初期化の文法がいつもこんがらがってわからなくなってしまう。以下はC++20からのdesignated initializers（指示付き初期化子・指定初期化子）というらしい。

step1のように再帰関数の戻り値で値を渡すと、下から値が決まっていくので必然的に下から上にあげていくようなコードになる。一方step2-1のようににスタックで書くと、自分がどこから呼び出されたかは情報として持たず、上から深さ情報を継承して(上から下に配って)コードが進行する。スタックで値を下から上にあげていくには、戻り値の受け渡しを明示的に管理する必要がある。


```cpp

class Solution {
public:
    int maxDepth(TreeNode* root) {
       stack<StackFrame> stack_frames;
       optional<int> result;
       stack_frames.push(StackFrame{.node = root, .depth_output = result});

       while (!stack_frames.empty()) {
        auto& [node, depth_output, left_depth, right_depth] = stack_frames.top();

        if (!node) {
            depth_output = 0;
            stack_frames.pop();
            continue;
        }

        if (!left_depth.has_value()) {
            stack_frames.push(StackFrame{.node = node->left, .depth_output = left_depth});
            continue;
        }
        if (!right_depth.has_value()) {
            stack_frames.push(StackFrame{.node = node->right, .depth_output = right_depth});
            continue;
        }

        depth_output = max(*left_depth, *right_depth) + 1;
        stack_frames.pop();
       }
    return *result;
    }
private:
    struct StackFrame {
        TreeNode* node;
        optional<int>& depth_output;
        optional<int> left_depth;
        optional<int> right_depth;
    };
};
```

## step2-3 再帰でtop-down
自分で書いたもの
```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {
        int max_depth = 0;
        // nodeはnullptrではないとする
        auto traverse_node = [&](this auto self, TreeNode* node, int depth) -> void {
            max_depth = max(max_depth, depth);
            if (node->left) {
                self(node->left, depth + 1);
            }
            if (node->right) {
                self(node->right, depth + 1);
            }
        };
        if (root) {
            traverse_node(root, 1);
        }
        return max_depth;
    }
};
```

max_depthに関する扱いがきれいでなくchatGPTに聞いた.
```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {
        auto traverse_node = [](this auto self, TreeNode* node, int parent_depth) -> int {
            if (node == nullptr) {
                return parent_depth;
            }

            return max(self(node->left, parent_depth + 1), self(node->right, parent_depth + 1));
        };

        return traverse_node(root, 0);
    }
};
```

一つ目の方法だと、DFSの行きがけの経路で順次足し算が行われ、同時にグローバル変数である最大深さが更新される。二つ目の方法だと、行きがけに足し算は実行されていくが、最大値の更新は帰りがけに行われる。

# step3
step2-1の方法

```

class Solution {
public:
    int maxDepth(TreeNode* root) {
        int max_depth = 0;
        std::stack<std::pair<TreeNode*, int>> node_and_depth;
        if (!root) {
            return max_depth;
        }
        node_and_depth.emplace(root, 1);
        while (!node_and_depth.empty()) {
            auto [node, depth] = node_and_depth.top();
            node_and_depth.pop();
            max_depth = max(max_depth, depth);

            if (node->left) {
                node_and_depth.emplace(node->left, depth + 1);
            }
            if (node->right) {
                node_and_depth.emplace(node->right, depth + 1);
            }
        }

        return max_depth;
    }
};
```
