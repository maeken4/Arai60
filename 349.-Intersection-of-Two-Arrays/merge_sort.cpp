#include <iostream>
#include <iterator>
#include <vector>

// 自前のマージ関数
template <typename RandomIt, typename Compare>
void merge(RandomIt first, RandomIt mid, RandomIt last, Compare comp) {
    using ValueType = std::iter_value_t<RandomIt>;  // C++20
    // using ValueType = typename std::iterator_traits<RandomIt>::value_type;
    std::vector<ValueType> buffer;
    buffer.reserve(std::distance(first, last));

    RandomIt left = first;
    RandomIt right = mid;
    // どちらかに要素がある限りループ
    while (left != mid || right != last) {
        if (left == mid) {
            // 左がなければ右だけを吸い出す
            buffer.push_back(*right++);  // 後置インクリメントなので評価されてから++
        } else if (right == last) {
            // 右がなければ左だけを吸い出す
            buffer.push_back(*left++);
        } else if (comp(*left, *right)) {
            buffer.push_back(*left++);
        } else {
            buffer.push_back(*right++);
        }
    }
    // 元の範囲に書き戻す
    std::copy(buffer.begin(), buffer.end(), first);
}

// 再帰的なマージソート本体（比較関数あり）
template <typename RandomIt, typename Compare>
void merge_sort(RandomIt first, RandomIt last, Compare comp) {
    auto n = std::distance(first, last);
    if (n < 2) return;  // 要素数0または1ならソート不要

    RandomIt mid = first;
    std::advance(mid, n / 2);

    merge_sort(first, mid, comp);
    merge_sort(mid, last, comp);
    merge(first, mid, last, comp);
}

// デフォルト比較（operator<）を使うオーバーロード
template <typename RandomIt>
void merge_sort(RandomIt first, RandomIt last) {
    using ValueType = std::iter_value_t<RandomIt>;  // C++20
    // using ValueType = typename std::iterator_traits<RandomIt>::value_type;
    merge_sort(first, last, std::less<ValueType>{});
}

int main() {
    std::vector<int> v = {324, 32, 33, 22, 1, 1, 3};
    merge_sort(v.begin(), v.end());
    for (auto x : v) {
        std::cout << x << std::endl;
    }
}
