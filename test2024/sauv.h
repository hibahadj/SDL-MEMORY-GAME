#ifndef SAUV_H_INCLUDED
#define SAUV_H_INCLUDED
typedef struct UserData
{
    char name[15];
    int score;
    int level;
    char date[9];
} UserData;

UserData getData(UserData users);
void writeData(UserData users);
void bestScore(UserData player);
int ordreBestScore(UserData players[5]);
void newDate();
#endif // SAUV_H_INCLUDED
