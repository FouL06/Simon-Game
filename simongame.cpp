//Authors: Ashton Foulger and Tenace Crane
//Assignment: A5
//Class: CS 3505 Spring 2022

#include "simongame.h"
#include "ui_simongame.h"
#include "model.h"
#include "QObject"
#include "QStyle"
#include "QTimer"
#include <iostream>

/**
 * @brief SimonGame::SimonGame is our Simon Game's view. It sets up the style of the window
 * and has signals that are connected to slots in the model for game functionality.
 * @param model - This model parameter is how we form connections between the view and model.
 * @param parent
 */
SimonGame::SimonGame(Model &model, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SimonGame)
{
    //Set up the nice retro-style Simon Game.
    ui->setupUi(this);
    this->setStyleSheet("QMainWindow {background-color: qlineargradient( x1:0 y1:0, x2:1 y2:1, stop:0 rgb(255,148,130), stop:1 rgb(125,119,255));}");
    ui->startButton->setStyleSheet("QPushButton{background: rgb(234,242,245); border-radius: 15px;}");
    ui->blueButton->setStyleSheet( QString("QPushButton {background-color: rgb(0,0,255);font: bold 20px;color: rgb(0,0,0);} QPushButton:pressed {background-color: rgb(52,153,255);}"));
    ui->redButton->setStyleSheet( QString("QPushButton {background-color: rgb(240,11,81);font: bold 20px; color: rgb(0,0,0);} QPushButton:pressed {background-color: rgb(255,150,150);}"));


    //Make connections from view to the model.
    connect(ui->startButton, &QPushButton::clicked, &model, &Model::startGame);
    connect(ui->redButton, &QPushButton::clicked, &model, &Model::redButtonPressed);
    connect(ui->blueButton, &QPushButton::clicked, &model, &Model::blueButtonPressed);
    connect(this, &SimonGame::newRound, &model, &Model::beginSequence);
    connect(&model, &Model::displayMove, this, &SimonGame::displayMove);
    connect(&model, &Model::gameOver, this, &SimonGame::gameOver);
    connect(&model, &Model::updateScore, this, &SimonGame::updateScore);
    connect(&model, &Model::updateScore, this, &SimonGame::updateHighScore);
    connect(&model, &Model::updateProgressBar, this, &SimonGame::updateProgressBar);
    connect(&model, &Model::disableStartButton, this, &SimonGame::disableStartButton);
    connect(&model, &Model::disableColorButtons, this, &SimonGame::disableColorButtons);

    //Disable buttons when the window is originally created.
    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
}

/**
 * @brief Descturctor for SimonGame
 */
SimonGame::~SimonGame()
{
    delete ui;
}

/**
 * @brief Disables the startButton upon starting a game.
 */
void SimonGame::disableStartButton()
{
    ui->startButton->setEnabled(false);
}

void SimonGame::disableColorButtons(){
    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
}

/**
 * @brief Displays the current move sequence for the player in order
 * for the player to follow the sequence on the players turn. By flashing
 * the buttons in the sequence they need to be pressed.
 * @param step
 * @param finalMove
 */
void SimonGame::displayMove(int step, bool finalMove){
    if(step == 0){
        ui->redButton->setDown(true);
    }
    else{
        ui->blueButton->setDown(true);
    }

    QTimer::singleShot(5000/(0.5*ui->progressBar->maximum()+1), this, &SimonGame::resetColorButtons);

    if(finalMove){
        //disableColorButtons();
        QTimer::singleShot(5000/(0.5*ui->progressBar->maximum()+1), this, &SimonGame::startPlayerTurn);
    }
}

/**
 * @brief Resets Buttons after displaying the current move in the sequence.
 */
void SimonGame::resetColorButtons(){
    ui->redButton->setDown(false);
    ui->blueButton->setDown(false);
}

/**
 * @brief Allows the player to press the buttons on players turn.
 */
void SimonGame::startPlayerTurn(){
    ui->redButton->setEnabled(true);
    ui->blueButton->setEnabled(true);
}

/**
 * @brief Displays the Game over Message to the player when the sequence is failed.
 */
void SimonGame::gameOver(){
    ui->redButton->setText("Game");
    ui->blueButton->setText("Over");
    ui->startButton->setEnabled(true);
    ui->redButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
}

/**
 * @brief Displays the current round score for the player.
 * @param score
 */
void SimonGame::updateScore(int score){
    ui->scoreLabel->setText(QString::number(score));
}

/**
 * @brief Updates the current High score for the player.
 * @param highScore
 */
void SimonGame::updateHighScore(int highScore){
    ui->highScoreLabel->setText(QString::number(highScore));
}

/**
 * @brief Updates the progress bar fill during the players sequence progress.
 * @param currentProgress
 */
void SimonGame::updateProgressBar(int currentProgress){
    ui->progressBar->setValue(currentProgress);
}
