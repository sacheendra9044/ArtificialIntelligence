Orthello Game Using AI

In this assignment you need to make a game of Othello. It is suggestive to play the game (not too much) before trying this assignment. While there are numerous online sources to play the game, I personally used http://www.othelloonline.org/

Let the two players be called as 1 and 2. You are given a valid Othello game state. Player 1 has to make the next move, followed by player 2 and so on. Play the game for m moves considering both the players play optimally. The program should display the same board again if no move is possible as per the game logic. The preference order of actions is the board traversal in a row major format.

The terminal utility is the difference in the number of disks of the players. The evaluation function for non-terminal states is given by equations (1)-(4). A positive terminal utility must be preferred to any non-terminal utility, a negative terminal utility must be never preferred to any non-terminal utility.

https://user-images.githubusercontent.com/8566240/31045762-2bd75056-a608-11e7-9f38-8f362129c6f3.png

While w1, w2 and w3 are learnt, here assume w1=1, w2=100 and w3=1000.

Input is the number of test cases t, with each test case starting with the number n, the size of the game board. The next n lines have n integers each with 1 denoting position occupied by player 1, 2 denoting position occupied by player 2, and 0 denoting a free position. The last integer in ever test case is m, the number of moves to play and d, the maximum depth after which a cutoff is applied. The cutoff is applied after depth d, meaning that the program should continue at depth d.

Output is the game states at each of the m moves, for every test case. Print “-” between every two game states in a new line.

Warning: Outputs will be truncated online. Please test offline.

Question 1: Implement the game without pruning.
