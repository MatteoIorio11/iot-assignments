#ifndef STATUS_H
#define STATUS_H

using namespace std;

enum STATUS{
    SELECT_DIFFICULTY = 0,
    INPUT_WAIT = 1,
    GAME_START = 2,
    DEEP_SLEEP = 3, 
    GAME_OVER = 4,
    RECREATE_PATTERN = 5,
    GAME_SCORE = 6,
    PENALTY = 7,
    SHOW_PATTERN = 8,
    VOID = -1
};

#endif