//Authors: Ashton Foulger and Tenace Crane
//Assignment: A5
//Class: CS 3505 Spring 2022

#include "model.h"
#include "QTimer"
#include <iostream>

/**
 * @brief Model Constructor
 * @param parent
 */
Model::Model(QObject *parent) : QObject{parent}
{
}

/**
 * @brief Starts the Simon Game and begins process
 * for generating the sequence for the player.
 */
void Model::startGame()
{
    emit disableStartButton();
    gameSequence.clear();
    playerScore = 0;
    emit updateProgressBar(0);
    emit updateScore(playerScore);
    nextRound();
}

/**
 * @brief Starts the sequence display process
 * for the player and updates round values.
 */
void Model::beginSequence(){
    emit disableColorButtons();
    sequenceItr = gameSequence.begin();
    playerSequence.clear();
    playerSequenceLocation = 0;
    emit updateProgressBar(0);
    stepSequence();
}

/**
 * @brief Displays current step in playable sequence of the game.
 */
void Model::stepSequence(){
    int playSpeed = 5000/(0.5*gameSequence.size()+1);

    if(sequenceItr==gameSequence.end()-1){
        emit displayMove(*sequenceItr, true);
    }
    else{
        emit displayMove(*sequenceItr, false);
        sequenceItr++;
        QTimer::singleShot(playSpeed, this, &Model::stepSequence);
    }
}

/**
 * @brief Checks for player input on red button press and appends check
 * to the players sequence list.
 */
void Model::redButtonPressed(){
    playerSequence.append(0);
    compareSequences();
}

/**
 * @brief Checks for player input on blue button press and appends check
 * to the players sequnce list.
 */
void Model::blueButtonPressed(){
    playerSequence.append(1);
    compareSequences();
}

/**
 * @brief Checks current player input against computer generated sequence,
 * if the player is incorrect then we display the game over message. Otherwise
 * we move on to checking the next step in the sequence and begin the process over again.
 */
void Model::compareSequences(){
    //if player chose wrong button
    if(playerSequence[playerSequenceLocation]!=gameSequence[playerSequenceLocation])
        emit gameOver();
    //if player chose correct button
    else{
        playerSequenceLocation++;
        double barProgress = (double(playerSequenceLocation)/double(gameSequence.size()))*100;
        emit updateProgressBar(qIntCast(barProgress));
    }

    //if player finishes sequence correctly
    if(playerSequenceLocation == gameSequence.size()){
        endRound();
    }
}

/**
 * @brief Ends the current round if the player finished the sequence,
 * starting the next generation of the computer generated sequence.
 * Updating the high score and current score.
 */
void Model::endRound(){
    playerScore++;
    emit updateScore(playerScore);
    //Disable buttons immediately so player can't accidentally click extra button before their turn.
    emit disableColorButtons();
    QTimer::singleShot(2000, this, &Model::nextRound);

    //Update high score.
    if(playerScore>playerHighScore){
        emit updateHighScore(playerHighScore);
    }
}

/**
 * @brief Adds next step in sequence to computer generated sequence,
 * and begins the next round sequence for the player to see the new
 * sequence and then allow the player to play.
 */
void Model::nextRound(){
    gameSequence.append(rand() % 2);
    beginSequence();
}
