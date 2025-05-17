# step1
- fast, slowだとループの開始点がわからないからだめ。とりあえず141でやりかけたsetの解法で解いた。
- setのfindの仕様に自信なし。

# step2
前回の指摘を受けvscodeのC++のフォーマッタを入れて見やすいカスタマイズをした。
https://qiita.com/grinpeaceman/items/04b6a973d11442a7ae48

## 新井さんのFloydアルゴリズムによる解法
- 各地点の距離をおいて説明されれば確かにそうなっているけど、141と同じで思いつけるかと言われれば微妙…


## setによる解法
- こっちのほうが素直なのでこっちを標準で考える。
- ずっとnowにheadに書き間違えていてデバッグに時間がかかった。chatptに聞いたら一発だった…
## std::set.find()について
- 戻り値はiteratorで見つからなかった場合、s.end()になる。
- C++20ではcontains()が使える。
### そもそもなんでsetでポインタ型が使えるか
- setは引数にCompareを渡されなかった場合デフォルトでstd::lessクラスで比較するらしい。 https://cpprefjp.github.io/reference/set/set.html
- ポインタ型には総順序が入るのでsetでつかえるらしい。　https://en.cppreference.com/w/cpp/language/operator_comparison


