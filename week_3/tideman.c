#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
bool search_cycle(int current_candidate, int target_candidate);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
// TODO
// 1. Look for a candidate called name
// 2. If candidate found, update 'ranks' and return true. ranks[i] is the voter's 'i'th preference
// 3. If no candidate found, don't update any ranks and return false
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
// TODO
// 1. Update the preferences array based on the current voter's ranks
void record_preferences(int ranks[])
{
    // Searching candidates who are below the selected rank 1 and rank 2
    for (int i = 0; i < candidate_count; i++)
    {
        // We ignore the position that compares the candidates with themselves
        // Rank 1:
        if (ranks[0] != i)
        {
            preferences[ranks[0]][i]++;
        }

        // Rank 2
        if (ranks[1] != i && ranks[0] != i)
        {
            preferences[ranks[1]][i]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
// TODO
// 1. Add each pair of candidates to pairs array if one candidate is preferred over the other
// 2. Update global variable pair_count to be the total number of pairs
void add_pairs(void)
{
    // Go through every candidate
    for (int i = 0; i < candidate_count; i++)
    {
        // For every candidate check its "matchup"
        // j = i + 1, so we dont check the candidate against itself and repeat previous matchups
        for (int j = i + 1; j < candidate_count; j++)
        {
            // Saving winner "i"
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            // Saving winner "j"
            else if ((preferences[i][j] < preferences[j][i]))
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
// TODO
// 1. Sort pairs in order by decreasing strength of victory
void sort_pairs(void)
{
    // Check every winner/loser
    // pair_count - 1 since everytime there is one winner less to check
    for (int i = 0, possible_best = 0; i < pair_count - 1; i++)
    {
        possible_best = i;
        //
        for (int j = i + 1; j < pair_count; j++)
        {
            int previous_best =
                preferences[pairs[possible_best].winner][pairs[possible_best].loser] -
                preferences[pairs[possible_best].loser][pairs[possible_best].winner];
            int candidate_j = preferences[pairs[j].winner][pairs[j].loser] -
                              preferences[pairs[j].loser][pairs[j].winner];

            if (candidate_j > previous_best)
            {
                possible_best = j;
            }
        }

        if (possible_best != i)
        {
            pair temporary_pair = pairs[i];
            pairs[i] = pairs[possible_best];
            pairs[possible_best] = temporary_pair;
        }
    }
    return;
}

// Function that searches for possible cycles
bool search_cycle(int current_candidate, int target_candidate)
{
    // Checking if we found a cycle back to the target candidate
    if (current_candidate == target_candidate)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[current_candidate][i] && search_cycle(i, target_candidate))
        {
            return true;
        }
    }

    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
// TODO
// 1. Update locked to create the locked graph by adding all edges in
// decreasing order of victory strength, as long as there is no cylce
void lock_pairs(void)
{

    // Going through every winner/loser pair and lock them
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        if (!search_cycle(loser, winner))
        {
            locked[winner][loser] = true;
        }
    }
    return;
}

// Print the winner of the election
// TODO
// 1. Print out the winner of the election, who will be the source of the graph
// 2. You may assume there will not be more than one source
void print_winner(void)
{
    // Looking for the source
    for (int i = 0; i < candidate_count; i++)
    {
        // Checking every candidate to see if is locked over the candidate i
        bool contains_arrow = false;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                contains_arrow = true;
                break;
            }
        }

        if (!contains_arrow)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
