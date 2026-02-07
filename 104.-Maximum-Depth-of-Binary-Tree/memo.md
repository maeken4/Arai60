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
