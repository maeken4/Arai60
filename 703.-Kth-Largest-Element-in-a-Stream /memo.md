# step1
優先度付きキューをそのまま使えばよさそう。上位K個をpriority_queueに保持しておく。
```cpp
#include <vector>
#include <queue>
#include <algorithm>
class KthLargest {
public:
    KthLargest(int k, std::vector<int>& nums) {
        threshold = k;
        std::sort(nums.begin(), nums.end(), std::greater<int>());
        for (int i = 0; i < std::min(threshold, static_cast<int>(nums.size())); i++) {
            pq.push(nums[i]);
        }
    }
    
    int add(int val) {
        if (pq.size() < threshold) {
            pq.push(val);
        }
        else {
            int comp = pq.top();
            if (comp < val) {
                // もともとk番目に大きい元だったやつは不適となる
                pq.pop();
                pq.push(val);
            }
        }
        return pq.top();
    }
   private:
    int threshold;
    std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
};
```


# step2
- 何はともかく突っ込んでheapがk個のままであるように調整するほうがシンプルに書けた。
- ヒープの実装を知りたい気持ちになって[discordのコメント](https://discord.com/channels/1084280443945353267/1301559648922501182/1312819361312018516)あたりとかchatGPTで調べてみた。
- だいたい、内部的にvectorとかを持っておいて、make_heapすることで配列をヒープ化して(ここはまた気になったときにちゃんと読む)、push_heapとかでheapの構造を保っておいて、キューのインターフェイスだけ持たせる的な感じっぽい。
```cpp:step2.cpp
#include <queue>
class KthLargest {
   public:
    KthLargest(int k, vector<int>& nums) {
        _k = k;
        for (const auto& n : nums) {
            push_and_trim(n);
        }
    }
    int add(int val) {
        push_and_trim(val);
        return pq.top();
    }
   private:
    int _k;
    std::priority_queue<int, vector<int>, std::greater<int>> pq;
    void push_and_trim(int val) {
        pq.push(val);
        if(pq.size() > _k) {
            pq.pop();
        }
    }
};
```


# step3
- クラス変数名は末尾に`_`とあったので変更。[google style guide](https://google.github.io/styleguide/cppguide.html#Variable_Names)
- 問題文の状況を考えval(int)をscoreに変更
- k個入っていない状況でaddが呼ばれたら例外を投げたいがC++の例外をよく知らず…コメントで注意はするが、例外を使わないとすると成功のフラグを参照で受け渡すとかになりそう。
```cpp
#include <vector>
#include <queue>

class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) {
        k_ = k;
        for (const auto& score : nums) {
            add_and_trim(score);
        }
    }
    // this method should be called after k elements were pushed.
    int add(int score) {
        add_and_trim(score);
        return top5_queue_.top();
    }
private:
    int k_;
    std::priority_queue<int, std::vector<int>, std::greater<int>> top5_queue_;

    void add_and_trim(int score) {
        top5_queue_.push(score);
        if (top5_queue_.size() > k_) {
            top5_queue_.pop();
        }
    }
};
```
