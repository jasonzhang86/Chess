# Chess

This chess game is inplemented using Objected-Oriented Programming. The six kinds of pieces (pawn, castle, knight, bishop, queen and king) are derived from one "piece" base class.<br>
The game contains all valid moves of a real world chess game, including the special moves (castling, promotion and en passant). <br>
<br>

There are three game modes: player vs player, player vs computer, and computer vs computer. <br>
The AI has three different levels: 1) random move 2) priortize capturing opponent pieces 3) priortize protecting own pieces <br>
The AI will choose to capture/protect more valuable pieces when there are multiple possible moves (e.g. capture queen > capture castle) <br>
<br>

The game supports graphical display. However, moving the pieces requires entering commands from the command line. <br>
There is a scoreboard that keeps track of play scores after each individual games. <br>
<br>

This project is completed with the help of Gloria Peng, who was my project partner in CS246 at the University of Waterloo.
