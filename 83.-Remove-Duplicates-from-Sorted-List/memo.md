# step1
考えたこと
- setで通った値を管理して重複していたら組み換える。でもaccendingだったら切り替わりだけ見れば十分か。組み替えると破壊的なのでちょっと微妙
- 新しく単方向リストを作る。入力を順にたどって切り替わりでリストを伸ばす。
- ポインタに慣れておらず、newをつけておらず合わない。


# step2
- アルゴリズムは本質的に同じだけど、新井さんの解答をリストに対して破壊的なのでどっちがよいかは状況によりそう。面接なら確認しながら確認する。
- 変数名がnow, ans, ansNowがわかりにくいのでchatpgtに代替案を考えてもらった。それぞれcurrentNode, resultHead, resultTailを採用。

| 役割           | 変数名候補（20個）                                                                 |
|----------------|------------------------------------------------------------------------------------|
| **now**        | current, currNode, traverse, cursor, walker, scan, nodePtr, reader, iterator, scanPtr, listWalker, inputCursor, explorer, readHead, probe, listPtr, sourcePtr, originWalker, traversePtr, scanNode |
| **ans**        | resultHead, outputHead, newListHead, headOfResult, dedupedHead, uniqueListHead, resultList, filteredHead, cleanedListHead, distinctHead, newHead, answerHead, finalList, resultStart, startNode, processedHead, rootNode, firstNode, topOfResult, primaryNode |
| **ansNow**    | resultTail, lastNode, resPtr, builder, insertPos, resultCursor, tail, constructPtr, appendNode, writer, resBuilder, outPtr, resultWalker, resultCurrent, collector, newTail, sinkPtr, outputTail, outCursor, resultIterator |

- whileとifが入り乱れてデバッグに時間がかかってしまった。次のように整理した.
今見ているノード(!= nullptr)を基準に次の3パターンがある。
1. 次がnullptr
2. 次のノードが今見ているノードと値が異なる。
3. 次のノードが今見ているノードと値が等しい。


1,2のときは見るノードを次に進めればよく、3のときだけ次のノードを組み替える。組み替えた先のノードが妥当かは次のループで見る。
