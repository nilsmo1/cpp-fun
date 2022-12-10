# Minesweeper
A terminal based minesweeper game written in C++.

## Installation
The [Makefile](https://github.com/nilsmo1/cpp-fun/blob/main/minesweeper/Makefile) is simple and just produces an exacutable. If you want this program in your path, you will have to do that yourself.
## Demo
**Initial state**
```console
(.). . . . . . . . . . . . . . 
 . . . . . . . . . . . . . . . 
 . . . . . . . . . . . . . . . 
 . . . . . . . . . . . . . . . 
 . . . . . . . . . . . . . . . 
 . . . . . . . . . . . . . . . 
 . . . . . . . . . . . . . . . 
 . . . . . . . . . . . . . . . 
 . . . . . . . . . . . . . . . 
 . . . . . . . . . . . . . . . 
 . . . . . . . . . . . . . . . 
 . . . . . . . . . . . . . . . 
 . . . . . . . . . . . . . . . 
 . . . . . . . . . . . . . . . 
 . . . . . . . . . . . . . . . 
```
**Loss screen**
```console
 . @ . . . @ @ . . . . . @ . . 
 1 2 @ . @ . . . . @ . . . . . 
   1 1 2 1 1 1 . . . @ . . . . 
             1 @ . . . . . . . 
             1 2 . . . . . . . 
     1 1 1     1 @ . . . @ . . 
 1 1 2 @ 1     1 1 3 @ . . @ . 
 . @ . . 2 1       3 @ . @ . . 
 . @ . . @ 2 1 1   2 @ . . . @ 
 . @ @ . . . @ 1   1 . . @ . @ 
 . . @ . @ @ . 1   1 . . . . . 
 . . . 2 . @ . 1 1 2 @ . .(@). 
 . . . . . . . . @ . . @ @ . @ 
 . . . @ . . . . . @ . . . . @ 
 . . . . . @ . . @ @ @ . . @ . 
You lose..
```

## Key bindings
| Key | Action |
| --- | --- |
| w/a/s/d | move the cursor | 
| e | open cell |
| f | flag cell |
