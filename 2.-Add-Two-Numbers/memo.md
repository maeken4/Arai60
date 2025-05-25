レビューの利便性のため、各ステップで書いたコードはこちらにも転記してみます。

# step1
元のリストに対して非破壊的であるようにしたい。素直に繰り上がりを記録しながら足していく方針で解いた。
```cpp
class Solution {
   public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(0, nullptr);
        ListNode* tail = &dummy;
        int carry = 0;
        while (l1 != nullptr || l2 != nullptr || carry != 0) {
            int val = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
            carry = val / 10;
            ListNode* append = new ListNode(val % 10, nullptr);
            tail->next = append;
            l1 = l1 ? l1->next : nullptr;
            l2 = l2 ? l2->next : nullptr;
            tail = tail->next;
        }
        return dummy.next;
    }
};
```

# step2
他の人のコードを見る。
- [ryosuketcさんのコード](https://github.com/ryosuketc/leetcode_arai60/blob/2_add_two_numbers/2_add_two_numbers/step3.py)と本質的に同じだがこちらのほうが丁寧に関数や定数を切り出している。
- 他の演算も実装する必要があったら補助関数を設定すると思う。
- 他のコメントでも三項演算子は避けられているようだが、今回のようなnullでないことだけ判定するくらいなら左から右に読みやすいと思うので許されたい…
- l1, l2がnullptrだったときだけ使うfakeを置いたら場合分けする部分が集約できた。

```cpp
class Solution {
   public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy(-1, nullptr);
        ListNode* tail = &dummy;
        int carry = 0;
        while (l1 || l2 || carry) {
            // l1, l2がnullptrだった場合0ノードを一時的に設定する。このブロックを抜けると解放される。
            ListNode fake(0);
            l1 = l1 ? l1 : &fake;
            l2 = l2 ? l2 : &fake;

            int total = l1->val + l2->val + carry;
            carry = total / 10;
            tail->next = new ListNode(total % 10, nullptr);
            tail = tail->next;
            l1 = l1->next;
            l2 = l2->next;
        }
        return dummy.next;
    }
};

```

# step3
fakeをwhileの外においてみた。
```cpp
class Solution {
   public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode dummy = ListNode(-1);
        ListNode* tail = &dummy;
        int carry = 0;

        ListNode fake = ListNode(0);
        while (l1 || l2 || carry) {
            l1 = l1 ? l1 : &fake;
            l2 = l2 ? l2 : &fake;
            int total = l1->val + l2->val + carry;
            carry = total / 10;
            tail->next = new ListNode(total % 10);

            tail = tail->next;
            l1 = l1->next;
            l2 = l2->next;
        }
        return dummy.next;
    }
};
```
