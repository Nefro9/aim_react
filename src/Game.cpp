#include "Game.h"

void Game::start()
{
    score  = 0;
    status = 1;
}

void Game::stop()
{
    status = 2;
}

int Game::getStatus()
{
   return status;
}

void Game::addScore(int points)
{
   score += points;
}

void Game::removeScore(int points)
{
   score -= points;
}

int Game::getScore()
{
   return score;
}

void Game::increaseTime()
{
   time += 1;
}

int Game::getTime()
{
   return time;
}
