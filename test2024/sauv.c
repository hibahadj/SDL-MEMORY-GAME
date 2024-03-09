#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

FILE *file;
char dates[8];
// Define a structure to represent user data
typedef struct UserData
{
    char name[15];
    int score;
    int level;
    char date[9];
} UserData;

void writeData(UserData users)
{
    int userFound = 0;
    UserData user;

    file = fopen("file/user_data.bin", "r+b");
    if (file == NULL)
    {
        perror("Error opening file");
    }

    newDate();
    strcpy(users.date,dates);

    while (fread(&user, sizeof(UserData), 1, file) == 1)
    {
        if (strcmp(user.name, users.name) == 0)
        {
            fseek(file, -sizeof(UserData), SEEK_CUR);
            fwrite(&users, sizeof(UserData), 1, file);
            userFound = 1;
            break;
        }
    }

    if (!userFound)
    {
        fseek(file, 0, SEEK_END); // Move the cursor to the end of the file
        fwrite(&users, sizeof(UserData), 1, file);
    }
    fclose(file);
}

UserData getData(UserData users)
{
    int userFound = 0;
    UserData user;

    file = fopen("file/user_data.bin", "r+b");
    if (file == NULL)
    {
        perror("Error opening file");
        return users;
    }

    while (fread(&user, sizeof(UserData), 1, file) == 1)
    {
        if (strcmp(user.name, users.name) == 0)
        {
            if(user.level > 15 || users.level == -1)
            {
                user.level = 1;
                user.score = 0;
                fseek(file, -sizeof(UserData), SEEK_CUR);
                fwrite(&user, sizeof(UserData), 1, file);
            }
            fclose(file);
            return user;
        }
    }

    users.score = 0;
    users.level = 1;
    newDate();
    strcpy(users.date,dates);
    fwrite(&users, sizeof(UserData), 1, file);
    fclose(file);
    return users;
}

void bestScore(UserData player)
{
    int userFound = 0, cpt=0, minScore;
    long minPos=0;
    UserData user;
    // find user in file user data
    file = fopen("file/user_data.bin", "r+b");
    if (file == NULL)
    {
        perror("Error opening file");
        return;
    }

    while (fread(&user, sizeof(UserData), 1, file) == 1)
    {
        if (strcmp(user.name, player.name) == 0)
        {
            player = user;
            break;
        }
    }
    fclose(file);

    //update file best score
    if(player.score>0)
    {
        file = fopen("file/best_score.bin", "r+b");
        if (file == NULL)
        {
            perror("Error opening file");
            return;
        }

        minScore = player.score;
        while (fread(&user, sizeof(UserData), 1, file) == 1)
        {
            if (strcmp(user.name, player.name) == 0)
            {
                if(player.score > user.score)
                {
                    fseek(file, -sizeof(UserData), SEEK_CUR);
                    fwrite(&player, sizeof(UserData), 1, file);
                    userFound = 1;
                }
                break;
            }
            else
            {
                cpt++;
                if(user.score<minScore)
                {
                    minPos = cpt;
                    minScore = user.score;
                }
            }
        }

        if(userFound == 0)
        {
            if(cpt < 5)
            {
                fwrite(&player, sizeof(UserData), 1, file);
            }
            else
            {
                if(minPos != 0)
                {
                    int currentPosition = (minPos-1) * sizeof(UserData);
                    fseek(file, currentPosition, SEEK_SET);
                    fwrite(&player, sizeof(UserData), 1, file);
                }
            }
        }
        fclose(file);
    }
}

int ordreBestScore(UserData players[5])
{
    int i = 0;
    UserData user;

    file = fopen("file/best_score.bin", "r+b");
    if (file == NULL)
    {
        perror("Error opening file");
        return 0;
    }

    while (fread(&user, sizeof(UserData), 1, file) == 1)
    {
        players[i] = user;
        i++;
    }
    fclose(file);

    // boucle tri
    int n = i;
    for (int k = 0; k < n - 1; k++) {
        for (int j = 0; j < n - k - 1; j++) {
            if (players[j].score < players[j + 1].score) {
                user = players[j];
                players[j] = players[j + 1];
                players[j + 1] = user;
            }
        }
    }
    return i;
}

void newDate()
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dates,"%02d-%02d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}
