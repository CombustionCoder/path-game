#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // connect button signals
    connect(ui->resetButton, &QPushButton::clicked, this,
            &MainWindow::resetButtonClicked);

    connect(ui->pauseButton, &QPushButton::clicked, this,
            &MainWindow::pauseButtonClicked);

    for (QString button : buttons_)
    {
        connect(findChild<QPushButton *>(button), &QPushButton::clicked, this,
                &MainWindow::boardButtonClicked);
    }

    // set board to beginning state
    updateColors();
    disableButtons(true);

    // initialize timekeeping
    timer_ = new QTimer(parent);
    connect(timer_,&QTimer::timeout,this,&MainWindow::updateTime);
    time_.setHMS(0,0,0);
    ui->timeLcdNumber->display(time_.toString("mm:ss"));
    ui->pauseButton->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer_;
}

void MainWindow::resetButtonClicked()
{
    // reset game situation
    gb_ = GameBoard();
    updateColors();
    firstClickPressed_ = false;

    ui->calloutLabel->setText("Game reset! Make a move to start playing!");
    disableButtons(true);

    // reset moves
    moves_=0;
    ui->movesLcdNumber->display(moves_);

    // reset timer
    time_.setHMS(0,0,0);
    timer_->stop();
    ui->timeLcdNumber->display(time_.toString("mm:ss"));
    timeStarted_=false;

    this->setStyleSheet(("background-color: "));
    ui->pauseButton->setText("Pause");
    gamePaused_ = false;
    ui->pauseButton->setDisabled(true);
}

void MainWindow::boardButtonClicked()
{
    QString clickedName = sender()->objectName();
    static Point firstPoint = {6, 6};
    Point secondPoint = {6, 6};
    if(!firstClickPressed_)
    {
        firstClickPressed_ = true;
        firstPoint.x = clickedName.at(6).digitValue()-1;
        firstPoint.y = clickedName.at(7).digitValue()-1;
        qDebug() << "x1:" << firstPoint.x << " y1:" << firstPoint.y;
        ui->calloutLabel->setText("Select destination!");
        disableButtons(false);
        ui->pauseButton->setDisabled(false);
    }
    else
    {
        secondPoint.x = clickedName.at(6).digitValue()-1;
        secondPoint.y = clickedName.at(7).digitValue()-1;
        qDebug() << "x2:" << secondPoint.x << " y2:" << secondPoint.y;

        moveFeedback(firstPoint,secondPoint);

        firstClickPressed_=false;
    }
    updateColors();
}

void MainWindow::updateTime()
{
    time_ = time_.addSecs(1);
    ui->timeLcdNumber->display(time_.toString("mm:ss"));
}

void MainWindow::pauseButtonClicked()
{
    if(!gamePaused_)
    {
        timer_->stop();
        ui->calloutLabel->setText("Game paused.");
        ui->pauseButton->setText("Unpause");
        gamePaused_=true;

        // disable all game board buttons
        for (QString button : buttons_)
        {
            findChild<QPushButton *>(button)->setDisabled(true);
        }
        return;
    }
    // if the game is already paused
    timer_->start(1000);
    ui->calloutLabel->setText("Game resumed! Select a piece to move!");
    ui->pauseButton->setText("Pause");
    firstClickPressed_=false;
    disableButtons(true);
    gamePaused_=false;
}

void MainWindow::updateColors()
{
    // loop through all buttons
    Point currentPoint;
    int color;
    for (QString button : buttons_)
    {
        currentPoint.x = button.at(6).digitValue()-1;
        currentPoint.y = button.at(7).digitValue()-1;

        // get slot situation from gameboard class
        color = gb_.which_slot(currentPoint);

        findChild<QPushButton *>(button)->setStyleSheet(("background-color: "
                                                         + colors_.at(color)));
    }
}

void MainWindow::moveFeedback(const Point& start, const Point& destination)
{
    if (gb_.move(start,destination))
    {        
        ui->calloutLabel->setText("Move made! Select next piece to move.");
        disableButtons(true);
        moves_++;
        ui->movesLcdNumber->display(moves_);
        if (gb_.is_game_over())
        {
            gameOver();
            return;
        }

        if(!timeStarted_)
        {
        timer_->start(1000);
        timeStarted_=true;
        }
    }
    else
    {
        ui->calloutLabel->setText("Illegal move! Try again.");
        disableButtons(true);
    }
}



void MainWindow::disableButtons(bool disableGrey)
{
    Point currentPoint;
    for (QString button : buttons_)
    {
        // parse point from button name
        currentPoint.x = button.at(6).digitValue()-1;
        currentPoint.y = button.at(7).digitValue()-1;

        // get color from gameboard situation method
        if(gb_.which_slot(currentPoint) == 2) // 2 means button is grey
        {
            findChild<QPushButton *>(button)->setDisabled(disableGrey);
        }
        else
        {
            findChild<QPushButton *>(button)->setDisabled(!disableGrey);
        }
    }
}

void MainWindow::gameOver()
{
    timer_->stop();
    ui->pauseButton->setDisabled(true);

    // calculate score, making many moves or taking a long time reduces score
    QString score = QString::number(10000 - moves_*10 - QTime(0,0).secsTo(time_));

    ui->calloutLabel->setText("You win! Congratulations! Final score: " + score);

    // flawless victory
    if (moves_ < 32)
    {
        this->setStyleSheet(("background-color: lightgreen"));
    }

    // disable all game board buttons
    for (QString button : buttons_)
    {
        findChild<QPushButton *>(button)->setDisabled(true);
    }
}
