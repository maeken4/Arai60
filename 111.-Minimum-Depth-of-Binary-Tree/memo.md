# step1
104とほぼ同じ。最初一列に続くやつを見落としていた.
```cpp
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (root == nullptr) {
            return 0;
        }
        if (root->left == nullptr) {
            return minDepth(root->right) + 1;
        }
        if (root->right == nullptr) {
            return minDepth(root->left) + 1;
        }
        return min(minDepth(root->left), minDepth(root->right)) + 1;
    }
};
```

以下のようにすると、片側には葉がないにもかかわらず最小の深さを比較するときに勘案してしまうのでダメ。
```cpp
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        return min(minDepth(root->left), minDepth(root->right)) + 1;
    }
};
```

# step2
上から数字を配るか、下から上げていくか、それぞれ再帰で書くかスタックとループで書くかの選択肢がある。

## step2-1
BFS
```cpp
class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }

        std::queue<std::pair<TreeNode*, int>> node_and_depth;

        node_and_depth.emplace(root, 1);

        while (!node_and_depth.empty()) {
            auto [node, depth] = node_and_depth.front();
            node_and_depth.pop();

            if (!node->left && !node->right) {
                return depth;
            }

            if (node->left) {
                node_and_depth.emplace(node->left, depth + 1);
            }
            if (node->right) {
                node_and_depth.emplace(node->right, depth + 1);
            }
        }
        // 到達しない。c++23ではstd::unreachable()が使える。
        return 0;
    }
};
```

## step2-2
BFSでレベルごとにまとめる
```cpp

class Solution {
public:
    int minDepth(TreeNode* root) {
        if (!root) {
            return 0;
        }
        TreeNode* node = root;
        int depth = 1;
        std::vector<TreeNode*> nodes_in_depth{node};

        while (!nodes_in_depth.empty()) {
            std::vector<TreeNode*> nodes_in_next_depth;

            for (const auto& node : nodes_in_depth) {
                if (!node->left && !node->right) {
                    return depth;
                }
                if (node->left) {
                    nodes_in_next_depth.emplace_back(node->left);
                }
                if (node->right) {
                    nodes_in_next_depth.emplace_back(node->right);
                }
            }

            nodes_in_depth = nodes_in_next_depth;
            ++depth;
        }
        // unreachable
        return 0;
    }
};
```

## step2-3
スタックで下から数字を上げる
