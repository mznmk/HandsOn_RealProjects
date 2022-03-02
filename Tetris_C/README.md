# Tetris_C

テトリスを作ろう  
http://www3.nit.ac.jp/~tamura/pdf/tetris.pdf  


## 特徴・注意点

- 文章で詳細に解説されていて、とても理解しやすいです。  

- 学習目的のものなので、最適化はされていません。  

- ところどころバグがあります。  
（ブロックを回転させる時に当たり判定をしていない など）  

- C言語の伝統的な流儀で、各種判定関数の戻り値に True=0 False=-1 を使っています。  
Truty の感覚がかなり異なるので注意が必要です。  

- `'\0'` : 何もなし `' '`: ブロック です。各種判定に使われています。  

- ワンライナーの関数は、関数としてではなくマクロで定義されています。  


## 参考資料

碧色工房 - エスケープシーケンス  
https://www.mm2d.net/main/prog/c/console-01.html  

select関数を用いた標準入力の監視【Linux / C言語】  
https://zenn.dev/kedama_nth/articles/13a40615312460  

C言語 extern宣言とグローバル変数【宣言不要な設計手法】  
https://monozukuri-c.com/langc-funclist-extern/  

C言語でシグナルをハンドルする  
https://qiita.com/supaiku2452/items/10772cbd2706dede06b9  

Linux シグナルの基本と仕組み (カーネル v5.5 時点)   
https://qiita.com/Kernel_OGSun/items/e96cef5487e25517a576  
