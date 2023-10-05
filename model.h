//Authors: Ashton Foulger and Tenace Crane
//Assignment: A5
//Class: CS 3505 Spring 2022

#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include "QVector"

class Model : public QObject
{
    Q_OBJECT
public:
    explicit Model(QObject *parent = nullptr);

    //Class Variables
    QList<int> gameSequence;
    QList<int> playerSequence;
    QList<int>::iterator sequenceItr;
    int playerSequenceLocation;
    int playerScore;
    int playerHighScore;

    //Methods
    void beginSequence();
    void stepSequence();
    void compareSequences();

public slots:
    void startGame();
    void redButtonPressed();
    void blueButtonPressed();

private:
    void endRound();
    void nextRound();

signals:
    void displayMove(int, bool);
    void resetColor();
    void gameOver();
    void updateScore(int);
    void updateProgressBar(int);
    void disableStartButton();
    void disableColorButtons();
    void updateHighScore(int);
};

#endif
