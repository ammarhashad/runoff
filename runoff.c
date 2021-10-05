#include<stdio.h>
#include<cs50.h>
#include<string.h>

#define MAX_CANDIDATES 9
#define MAX_voter_count  100

typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;
candidate candidates[MAX_CANDIDATES];
int candidate_count = 0;
int voter_count  = 0;
int preferences[MAX_voter_count ][MAX_CANDIDATES];
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    candidate_count = argc - 1;
    if (argc == 1 || argc > 9)
    {
        return 1;
    }
    //this for for hundle if 2 name are the same go out
    for (int i = 1; i < argc - 1; i++)
    {
        if (strcmp(argv[i], argv[i + 1]) == 0)
        {
            return 1;
        }
    }
    for (int i = 1; i < argc; i++)
    {
        candidates[i - 1].name = argv[i];
        candidates[i - 1].eliminated = false;
        candidates[i - 1].votes = 0;
    }
    voter_count  = get_int("Number of namers: ");
    for (int j = 0; j < voter_count ; j++)
    {
        for (int i = 0; i < argc - 1; i++)
        {
            string name = get_string("Rank %i: ", i);
            bool fVoteReturn = vote(j, i, name);
            if (!fVoteReturn)
            {
                return 4;
            }
        }
        printf("\n");
    }
    tabulate();
    bool maint;
    bool x = false;
    while (1)
    {
        x = print_winner();
        if (x == true)
        {
            maint = 0;
            break;
        }
        int minn = find_min();
        printf("min is fro, while %i\n", minn);
        bool y = is_tie(minn);
        if (y == true)
        {
            maint = 5;
            break;
        }
        else
        {
            eliminate(minn);
            printf("the state of Bob%d\n", candidates[1].eliminated);
            printf("the state of Charlie%d\n", candidates[2].eliminated);
            printf("the state of David%d\n", candidates[3].eliminated);

            tabulate();
        }
    }
    printf("min is %i\n", find_min());
    return maint;
    /*
    candidates[0].eliminated = true;
    candidates[1].eliminated = true;
    candidates[3].eliminated = true;
    candidates[4].eliminated = true;*/



    /*printf("\n votes [a] : %i",candidates[0].votes);
    printf("\n votes [b] : %i",candidates[1].votes);
    printf("\n votes [c] : %i",candidates[2].votes);
    printf("\n votes [v] : %i",candidates[3].votes);
    printf("\n votes [k] : %i\n",candidates[4].votes);*/



    //for print the 2 matrix to check
    /*
    for (int j = 0; j < voter_count ; j++)
    {
        printf("|");
        for (int i = 0; i < argc - 1; i++)
        {
            printf("%i |", preferences[j][i]);
        }
        printf("\n");
    }*/
}
bool vote(int voter, int rank, string name)
{
    bool x = false;
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            x = true;
            i = candidate_count;
        }
    }
    return x;
}
void tabulate(void)
{
    int min = 1;
    // make all value equal zero when statr to make sure every time call calculate from first
    for (int i = 0; i < candidate_count ; i++)
    {
        candidates[i].votes = 0;
    }

    /*for (int i = 0; i < voter_count ; i++)
    {

        for (int j = 0; j < candidate_count ; j++)
        {
            if (candidates[j].eliminated == false && preferences[i][j] == 0)
            {
                candidates[j].votes++;
                printf("\nvote go to: %s\n",candidates[j].name);
            }
            else if (candidates[j].eliminated == true && preferences[i][j] == 0)
            {
                for (int z = 0; z < candidate_count ; z++)
                {
                    for (int k = 0; (k < candidate_count  && min != 0); k++)
                    {
                        if (preferences[i][k] == min && candidates[k].eliminated == false)
                        {
                                        printf("\nvote go to: %s\n",candidates[k].name);

                            candidates[k].votes++;
                            min = 0;
                            break;
                        }
                        else if (candidates[k].eliminated == true && preferences[i][k] == min)
                        {
                            ++min;
                        }

                    }
                }
                min = 1;
            }
        }
    }*/

    for (int i = 0; i < voter_count; i++)
    {

        for (int j = 0; j < candidate_count; j++)
        {
            if (!candidates[preferences[i][j]].eliminated)
            {
                candidates[preferences[i][j]].votes++;
                printf("\nvote go to: %s\n", candidates[j].name);
                break;
            }

        }
    }
}

bool print_winner(void)
{
    bool x = false;
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes > (voter_count  / 2))
        {
            printf("%s\n", candidates[j].name);
            x = true;
        }
    }
    return x;
}
int find_min(void)
{
    int min = 0;
    for (int j = 0; j < voter_count; j++)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (min == candidates[i].votes)
            {
                if (candidates[i].eliminated == true)
                {
                    min++;
                }
                else if (candidates[i].eliminated == false)
                {
                    i = candidate_count;
                    j = voter_count;
                }
            }
        }
        min++;
    }

    min--;
    return min;
}
bool is_tie(int min)
{
    int less_min = 0;
    int min_count = 0;
    bool c;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes < min)
        {
            less_min++;
        }
    }
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            min_count++;
        }
    }
    if (candidate_count - min_count == less_min || candidate_count  == min_count)
    {
        c = true;
    }
    else
    {
        c = false;
    }

    return c;
}
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
}


