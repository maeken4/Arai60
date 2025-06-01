# step1
優先度付きキューをそのまま使えばよさそう。上位K個をpriority_queueに保持しておく。
```cpp
#include <vector>
#include <queue>
#include <algorithm>
class KthLargest {
public:
    KthLargest(int k, std::vector<int>& nums) {
        this->threshold = k;
        std::sort(nums.begin(), nums.end(), std::greater<int>());
        for (int i = 0; i < std::min(threshold, static_cast<int>(nums.size())); i++) {
            this->pq.push(nums[i]);
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
