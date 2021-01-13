# 情報工学総合演習課題 B - 多腕バンディットアルゴリズム

作成者： ハララノフ・ヴァレリ

## 準備

このプロジェクトは `make` ではなく [`rake`](https://github.com/ruby/rake/) というツールで組まれている．

## それぞれの課題のバイナリ生成

```bash
rake bin/k1 # k[1-6] は基本課題，kadv-1-[1-3] は発展課題
```

### PDF 図の生成

```bash
rake k1 # 選択肢: k[1-6], kadv1
```

もしくは名前を指定して

```bash
rake plots/k1/avg_reward.pdf
```

### レポート PDF の生成

```bash
rake report/rp.pdf
```
