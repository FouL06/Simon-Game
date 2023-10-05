//Authors: Ashton Foulger and Tenace Crane
//Assignment: A5
//Class: CS 3505 Spring 2022

#ifndef SIMONGAME_H
#define SIMONGAME_H

#include <QMainWindow>
#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SimonGame; }
QT_END_NAMESPACE

class SimonGame : public QMainWindow
{
    Q_OBJECT

signals:
    void newRound();

public:
    SimonGame(Model &model, QWidget *parent = nullptr);
    ~SimonGame();

public slots:
    void displayMove(int, bool);
    void resetColorButtons();
    void startPlayerTurn();
    void gameOver();
    void updateScore(int);
    void updateHighScore(int);
    void updateProgressBar(int);

private slots:
    void disableStartButton();
    void disableColorButtons();

private:
    Ui::SimonGame *ui;
};
#endif // SIMONGAME_H
