#ifndef GAME_H
#define GAME_H


class Game
{
    int status = 0;
    int score = 0;
    int time = 0;

    public:
        int statusIdle = 0;
        int statusStart = 1;
        int statusStop = 2;

        int getStatus();

        int  getScore();
        void addScore(int score);
        void removeScore(int score);

        int getTime();
        void increaseTime();

        void start();
        void stop();
};

#endif // GAME_H
