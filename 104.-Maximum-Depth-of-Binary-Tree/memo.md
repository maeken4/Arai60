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
  
  step1の書き方だと探索の帰りに値を足している(下から上げる)が、2-1の書き方だと、行きに値を足している(上から配る)。2-2でstack,下から上げる、2-3で再帰、上から配るで実装してみた。

- https://github.com/Yuto729/leetcode/pull/26
  レベルごとに走査する方法もある。

再帰で書いたほうが簡潔だが、スタック領域の限界(スタックオーバーフロー)に達する危険性がある。

stackで書き直すとヒープ領域にデータが置かれるのでより大きなデータを持つことができる。

## step2-1 stackで書き直す

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

## step2-2 stackで値を下から上げる
C++の初期化の文法がいつもこんがらがってわからなくなってしまう。


```cpp
class Solution {
public:
    int maxDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }

        std::stack<Frame> call_stack;
        call_stack.push(Frame{.node = root, .left_length = 0, .right_length = 0});

        int returned_depth = 0;
        while (!call_stack.empty()) {
            Frame& frame = call_stack.top();

            if (frame.state == State::Enter) {
                frame.state = State::LeftDone;
                if (frame.node->left != nullptr) {
                    call_stack.push(Frame{.node = node->left,})
                }
            }
            else if (frame.state == State::LeftDone) {
                frame.state = State::RightDone;
                if (frame.node->right != nullptr) {
                    call_stack.push()
                }
            }
            else {  // RightDone

            }
        }
    }
private:
    enum class State {
        Enter,  // これから左部分木を処理
        LeftDone,  // これから右部分木を処理
        RightDone  // 右部分木の処理が完了し自身の深さを確定する
    };

    struct Frame {
        TreeNode* node;
        State state = State:::Enter;
        int left_length;
        int right_length;
    };
};
```

## step2-3 再帰で上から配る
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

max_depthに関する扱いがきれいでなくchatGPTに聞いた
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
