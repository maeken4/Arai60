# step1
- fast, slowだとループの開始点がわからないからだめ。とりあえず141でやりかけたsetの解法で解いた。
- setのfindの仕様に自信なし。

# step2
## 新井さん解法
- 各地点の距離をおいて説明されれば確かにそうなっているけど、141と同じで思いつけるかと言われれば微妙…

## std::set.find()について
- 戻り値はiteratorで見つからなかった場合、s.end()になる。
- >=C++20ではcontains()が使える。
- setは引数にCompareを渡されなかった場合デフォルトでstd::lessクラスで比較するらしい。 https://cpprefjp.github.io/reference/set/set.html