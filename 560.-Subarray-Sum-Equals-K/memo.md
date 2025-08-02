# step1
累積和を考えたら、vectorの二点の差がKであるようなペアを考える問題になることがわかる。
負の項も存在しうるのでここから簡単にする方法が思いつかず愚直に二重ループした。
実行時間が1954msで遅い…
ここまで20分ほど。

## step1-2
散歩しながらだらだら考えていたら今まで登場した累積数をカウントすればよいことがわかる。71ms！

# step2
他の人のPRを見る
- https://github.com/Hurukawa2121/leetcode/pull/16
- https://github.com/katataku/leetcode/pull/15



## step1の見直し
- countで存在しないのにアクセスすると回数カウントがずれるのではとか思ってcontains判定を入れていたが、存在しないkeyに対してはデフォルトコンストラクタ(intに対しては0)が呼ばれるので問題ない。
- と思ったが、少なくともこの関数が呼ばれている間は余分なメモリ領域を使ってしまうので、この処理が長時間・大量データにわたる場合は注意したほうがよい。
- ループのどのタイミングでaccumulate_countをやるかを変更。各ループの最後でやった方が意味が明確。step1の書き方だとaccumulateとaccumulate_countの更新されるタイミングがずれてわかりにくい。
- 戻り値を格納するのにansはよくなさそう。せめてresultにする。

### その他
本問にはほぼ関係ないけどunordered_mapの効率化バージョン?であるflat_hash_mapというのがabseil?にあるらしい
https://hackmd.io/@elkurin/BJgKkoii3
Googleの人は標準ライブラリを作ってしまうのですごい…
