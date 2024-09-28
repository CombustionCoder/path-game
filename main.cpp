/* Path_gui
 *
 * Desc:
 * A problem game with a graphical user interface.
 *
 * Game starts with color 1 pieces at the top row and color 2 pieces at the
 * bottom row. User must try to move color 2 pieces to the top row and color 1
 * pieces to the bottom row. A timer will start when the player makes the first
 * move.
 *  Player can click a piece on the game board and then an empty space to make
 * a move. Once a piece is selected to move, a move must be attempted with that
 * piece. Pieces may not move over other pieces. If an illegal move is
 * attempted, an error will be displayed and the player may select a new piece
 * to move. Each succesful move made adds to the counter keeping track of
 * moves.
 *  When the player manages to get all the color 2 pieces to the top row and all
 * the color 1 pieces to the bottom row, the game will end. All the game board
 * buttons will be disabled and the player must click reset to start another
 * game.
 *  Clicking the reset button at any point during or after the game will reset
 * the board, timer and moves count.
 *  When the game ends, the game calculates the final score. Moves made and
 * time elapsed reduce the score. The score starts at 10000 and every move
 * reduces the score by 10. Every second spent playing reduces the score by 1.
 * The score is meant to reward quick and correct decision making.
 * If the game is completed in 31 moves, the background of the ui window turns
 * light green in celebration.
 *  Clicking the pause button stops the timer and disables the game board
 * buttons. The text changes to unpause. Clicking the button again unpauses
 * the game, enabling the buttons and starting the timer. Pausing is not
 * available if the game is not started or has ended.
 *
 * Started with template code for backend (gameboard class), which was not
 * edited.
 *
 * Program author: Jukka Hirvonen
 */

#include "mainwindow.hh"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
