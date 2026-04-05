# step1
なんか制約とか条件がすっきりしてなくて実務っぽい...
- endwordはwordlistに入っている必要がある。入っているとは言っていない。
- beginwordは入っているかもしれないし入っていないかもしれない
- beginword.len = endword.lenは保証されている。
単語を頂点、遷移できるときに辺を考えれば最短経路の問題に帰着しそう。
各単語の長さをL, 単語数をNとすると、グラフ構築にO(N**2 * L), BFSにO(N)でグラフ構築のほうに時間がかかる？
847msですごく遅いように見える。

# step2
他の人のコードを読む
https://github.com/t0hsumi/leetcode/pull/20
https://github.com/goto-untrapped/Arai60/pull/57#discussion_r1781365485
https://github.com/shining-ai/leetcode/pull/20#discussion_r1517026158
> この関数は２つの文字列の違いが1文字かどうかを返していると思うのですが、2つの文字列の違いのことをhamming distanceと呼びEdit Distanceの一種です。他にはLevenshtein distanceなどがあります。こちらは2つの文字列の距離を追加、削除、置換のオペレーションの数で表します。テキストエディタとかのauto correction機能とかで使われます。
> 
https://discord.com/channels/1084280443945353267/1201211204547383386/1215702126945112094
https://discord.com/channels/1084280443945353267/1201211204547383386/1215702126945112094
https://github.com/tarinaihitori/leetcode/pull/20

https://github.com/docto-rin/leetcode/pull/19

考えると単語の長さもチェックする必要がありそう。->一応問題文で保障されている
文字列のビューを使う
イテレーターを使う
パターンを使う
size() length()　文字列の場合使い分ける？
beginwordとendwordの変な非対称はこういう解法があるからなのね
