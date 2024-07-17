In the run-up to an automated video-recording interview incl. code challenge (which turned out to be based on Verilog), I was doing Project Euler challenges for practice.

Challenge 96 is about solving a series of sudokus, and so I instantly knew the most appropriate algorithm that would work for any sudoku difficulty - brute-force backtracking.

I originally implemented this algorithm in Ruby, in 2016 (see [src.xza.fr](https://src.xza.fr) for a copy), but it was relatively slow, mainly as a result of being implemented in an interpreted language.

So, this repo features a re-implementation in C.

Note: this repo was cloned from my [bitbucket account](https://bitbucket.org/thomas-xza/96_sudoku_solver/)
