/* Class: Mainwindow
 * -----------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -----------------
 * Class that creates a graphical user interface for the path game.
 *
 * Program author --
 * Name: Jukka Hirvonen
 * Student number: H218618
 * UserID: cnjuhi ( Git-repository directory name. )
 * E-Mail: jukka.hirvonen@tuni.fi
 *
 * Note:
 *
 * */

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"

#include <QMainWindow>
#include <vector>
#include <QTimer>
#include <QTime>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    /**
     * @brief resetButtonClicked
     * When reset button is clicked, resets the game board, moves count and
     * timer. Timer is also stopped, colored pieces enabled to select for move
     * and clicking empty slots is disabled.
     */
    void resetButtonClicked();

    /**
     * @brief boardButtonClicked
     * Keeps track of clicks on game board buttons for making moves. The first
     * click selects a piece to move and the second one the destination.
     * Separate method is called to determine results of the move.
     */
    void boardButtonClicked();

    /**
     * @brief updateTime
     * Updates the time value and display every sec when the timer is running.
     */
    void updateTime();

    /**
     * @brief pauseButtonClicked
     * When pause button is clicked, disables all board buttons, stops timer
     * and displays pause message.
     */
    void pauseButtonClicked();

private:
    Ui::MainWindow *ui;

    // situation on the gameboard
    GameBoard gb_ = GameBoard();

    /**
     * @brief updateColors
     * Updates the colors of the game board buttons based on the situation on
     * the game board. Occupied slots are colored with piece colors and empty
     * slots are set to grey.
     */
    void updateColors();

    /**
     * @brief move_feedback
     * @param start: point selected to move
     * @param destination: where to move the piece
     * Determines the result of the move based on points received from the
     * boardButtonClicked method. Checks if the move is legal and calls the
     * method to end the game if move finishes the game.
     */
    void moveFeedback(const Point& start, const Point& destination);

    /**
     * @brief disableButtons
     * @param disableGreys true if empty places need to be disabled
     * Disables the grey (empty) buttons on the board if disableGreys is true.
     * Also enables colored buttons. If disableGreys is false, enables grey
     * buttons and disables colored buttons. This is done to make the game easy
     * to play.
     */
    void disableButtons(bool disableGrey);

    /**
     * @brief gameOver
     * Disables the game board buttons, stops the timer, displays winning
     * message.
     */
    void gameOver();

    // true if player has clicked a piece to move
    bool firstClickPressed_ = false;

    // names of game board buttons
    const std::vector<QString> buttons_ = {"button11", "button21", "button31",
                                           "button41", "button22","button23",
                                           "button33", "button24", "button15",
                                          "button25", "button35", "button45"};

    // names of colors for the empty slots and pieces
    const std::vector<QString> colors_ = {"red","green","slategray"};

    // number of moves done in this game
    int moves_ = 0;

    // to keep track of time elapsed during the game
    QTimer* timer_;
    QTime time_;
    bool timeStarted_ = false;
    bool gamePaused_ = false;
};
#endif // MAINWINDOW_HH
