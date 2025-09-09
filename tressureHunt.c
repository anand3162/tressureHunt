#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#define MAXIMUM_PATH 70
#define MINIMUM_PATH 10

#define MAX_NUM_LIVES 10
#define MIN_NUM_LIVES 1

struct PlayerInfo
{
    int num_lives;
    char character_symbol;
    int num_treasure;
    int positions[MAXIMUM_PATH];
};

struct GameInfo
{
    int max_num_move;
    int path_length;
    int bombs[MAXIMUM_PATH];
    int treasure[MAXIMUM_PATH];
};

int main(void)
{
    struct PlayerInfo player;
    struct GameInfo game;
    int remaining_lives, remaining_moves, nextmove = MAXIMUM_PATH+1, flag=0, x, y, flag2=0,flag3=0;
    char recentposition[MAXIMUM_PATH], position_display[MAXIMUM_PATH];

    printf("================================\n");
    printf("         Treasure Hunt!\n");
    printf("================================\n");
    printf("\n");

    printf("PLAYER Configuration\n");
    printf("--------------------\n");

    printf("Enter a single character to represent the player: ");
    scanf(" %c", &player.character_symbol);

    do
    {
        printf("Set the number of lives: ");
        scanf("%d", &player.num_lives);
        if (player.num_lives < MIN_NUM_LIVES || player.num_lives > MAX_NUM_LIVES)
        {
            printf("     Must be between %d and %d!\n", MIN_NUM_LIVES, MAX_NUM_LIVES);
        }

    } while (player.num_lives < MIN_NUM_LIVES || player.num_lives > MAX_NUM_LIVES);

    player.num_treasure = 0;
    int i;
    for (i = 0; i < MAXIMUM_PATH; i++)
    {
        player.positions[i] = 0;
    }
    printf("Player configuration set-up is complete\n");
    printf("\n");

    // Game configuration
    printf("GAME Configuration\n");
    printf("------------------\n");

    do
    {
        printf("Set the path length (a multiple of 5 between 10-70): ");
        scanf("%d", &game.path_length);
        if (game.path_length < MINIMUM_PATH || game.path_length > MAXIMUM_PATH || game.path_length % 5 != 0)
        {
            printf("     Must be a multiple of 5 and between %d-%d!!!\n", MINIMUM_PATH, MAXIMUM_PATH);
        }
    } while (game.path_length < MINIMUM_PATH || game.path_length > MAXIMUM_PATH || game.path_length % 5 != 0);

    do
    {
        printf("Set the limit for number of moves allowed: ");
        scanf("%d", &game.max_num_move);
        if (game.max_num_move < player.num_lives || game.max_num_move > .75 * game.path_length)
        {
            printf("    Value must be between %d and %d\n", player.num_lives, (int)(.75 * game.path_length));
        }
    } while (game.max_num_move < player.num_lives || game.max_num_move > .75 * game.path_length);

    printf("\n");
    printf("BOMB Placement\n");
    printf("--------------\n");
    printf("Enter the bomb positions in sets of 5 where a value\n");
    printf("of 1=BOMB, and 0=NO BOMB. Space-delimit your input.\n");
    printf("(Example: 1 0 0 1 1) NOTE: there are 20 to set!\n");

    for (i = 0; i < game.path_length; i += 5)
    {
        printf("   Positions [%2d-%2d]: ", i + 1, i + 5);
        int j;
        for (j = i; j < i + 5; j++)
        {
            scanf("%d", &game.bombs[j]);
        }
    }
    printf("BOMB placement set\n");

    printf("\n");
    printf("TREASURE Placement\n");
    printf("------------------\n");
    printf("Enter the treasure placements in sets of 5 where a value\n");
    printf("of 1=TREASURE, and 0=NO TREASURE. Space-delimit your input.\n");
    printf("(Example: 1 0 0 1 1) NOTE: there are 20 to set!\n");

    for (i = 0; i < game.path_length; i += 5)
    {
        printf("   Positions [%2d-%2d]: ", i + 1, i + 5);
        int j;
        for (j = i; j < i + 5; j++)
        {
            scanf("%d", &game.treasure[j]);
        }
    }
    printf("TREASURE placement set\n");
    printf("\n");
    printf("GAME configuration set-up is complete...\n");
    printf("\n");

    printf("------------------------------------\n");
    printf("TREASURE HUNT Configuration Settings\n");
    printf("------------------------------------\n");

    printf("Player:\n");
    printf("   Symbol     : %c\n", player.character_symbol);
    printf("   Lives      : %d\n", player.num_lives);
    printf("   Treasure   : [ready for gameplay]\n");
    printf("   History    : [ready for gameplay]\n");

    printf("\n");
    printf("Game:\n");
    printf("   Path Length: %d\n", game.path_length);
    printf("   Bombs      : ");
    for (i = 0; i < game.path_length; i++)
    {
        printf("%d", game.bombs[i]);
    }
    printf("\n");
    printf("   Treasure   : ");
    for (i = 0; i < game.path_length; i++)
    {
        printf("%d", game.treasure[i]);
    }
    printf("\n\n");
    printf("====================================\n");
    printf("~ Get ready to play TREASURE HUNT! ~\n");
    printf("====================================\n");

    remaining_lives = player.num_lives;
    remaining_moves = game.max_num_move;

    player.num_treasure = 0;

    for (x = 0; x < game.path_length; x++)
    {
        player.positions[x] = 0;
    }

    for (y = 0; y < game.path_length; y++)
    {
        position_display[y] = '-';
    }

    for (y = 0; y < game.path_length; y++)
    {
        recentposition[y] = ' ';
    }

    do // 1st do while
    {
        for (y = 0; y < game.path_length; y++) // line1
        {
            if (recentposition[y] == player.character_symbol)
            {
                flag = 1;
            }
        }

        if (flag == 0)
        {
            printf("\n");
        } // to print if there is no character

        else
        {
            printf("  ");
            for (y = 0; (y < game.path_length) || (flag2 == 0); y++)
            {
                if (recentposition[y] == player.character_symbol)
                {
                    printf("%c\n", recentposition[y]);
                    break;
                }
                else
                {
                    printf("%c", recentposition[y]);
                }
            }
        }
        for (y = 0; y < game.path_length; y++) // replacing the recent psition to default
        {
            recentposition[y] = ' ';
        }

        printf("  "); // line2
        for (y = 0; y < game.path_length; y++)
        {
            printf("%c", position_display[y]);
        }
        printf("\n");

        printf("  "); // line3
        for (i = 1; i <= game.path_length; i++)
        {
            if (i % 10 == 0)
            {
                printf("%d", (int)i / 10);
            }
            else
            {
                printf("|");
            }
        }
        printf("\n");

        printf("  "); // line4
        for (i = 0; i < game.path_length; i += 10)
        {
            printf("1234567890");
        }

        printf("\n+---------------------------------------------------+");
        printf("\n  Lives: %2d  | Treasures: %2d  |  Moves Remaining: %2d", remaining_lives, player.num_treasure, remaining_moves);
        printf("\n+---------------------------------------------------+\n");

        if(remaining_lives==0)
        {
            flag3=1;
        }

        if (remaining_moves==0)
        {
            flag3 = 1;
        }
        if (flag3)
        {
            break;
        }

        do // 2nd do while
        {
            printf("Next Move [1-20]: "); // checking if the next move is out of range
            scanf("%d", &nextmove);

            if ((nextmove < 1) || (nextmove > game.path_length))
            {
                printf("  Out of Range!!!");
            }
            printf("\n");
        } while ((nextmove < 1) || (nextmove > game.path_length)); // 2nd do while

        // main loop for tressure hunt
        if (player.positions[nextmove - 1] == 1) // came already
        {
            printf("===============> Dope! You've been here before!\n\n");
            recentposition[nextmove - 1] = 'V';
            remaining_moves++;
        }
        else if ((game.bombs[nextmove-1] == 1) && (game.treasure[nextmove-1] == 1)) // both
        {
            printf("===============> [&] !!! BOOOOOM !!! [&]\n");
            printf("===============> [&] $$$ Life Insurance Payout!!! [&]\n\n");
            position_display[nextmove-1] = '&';
            recentposition[nextmove-1] = 'V';
            remaining_lives--;
            player.num_treasure++;
        }
        else if (game.treasure[nextmove-1] == 1) // treasure
        {
            printf("===============> [$] $$$ Found Treasure! $$$ [$]\n\n");
            position_display[nextmove-1]='$';
            recentposition[nextmove-1] ='V';
            player.num_treasure++;
        }
       
        else if (game.bombs[nextmove - 1] == 1) // bomb
        {
            printf("===============> [!] !!! BOOOOOM !!! [!]\n\n");
            position_display[nextmove - 1] = '!';
            recentposition[nextmove - 1] = 'V';
            remaining_lives--;
        }
        else//nothing
        {
            printf("===============> [.] ...Nothing found here... [.]\n\n");
            position_display[nextmove-1]='.';
            recentposition[nextmove-1]='V';
        }

        remaining_moves--;//updating moves and adding the history
        player.positions[nextmove-1]=1;

        if (remaining_lives==0)//checking if the player is game over
        {
            printf("No more LIVES remaining!\n\n");
            
        }
        if (remaining_moves==0)
        {
            printf("No more MOVES remaining!\n\n");
            
        }
    }
    while(!flag3);// 1st do while

    printf("\n");
    printf("##################\n");
    printf("#   Game over!   #\n");
    printf("##################\n\n");
    printf("You should play again and try to beat your score!\n\n");

    return 0;
}
