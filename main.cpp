// Including the SCALE game library
#include "libSCALEgame.h"

// The SCALE game namespace
using namespace ScaleSpace;

// Overloading the main function with command-line arguments
int main(int argc,char** argv) {
    // Seeding the random number generator
    srand(time(nullptr));

    // Checking the number of arguments passed
    if (argc != 5) {
        cerr << "NOTE: The application can only run using these arguments: " << argv[0] << " <TotalNumberOfRows> <TotalNumberOfColumns> <TotalAmountOfWeights> <TotalNumberOfScales>" << endl;
        exit(ERROR_ARGC);
    }

    // Fetching the variables from the command-line
    int int_weights = STRING_TO_INTEGER(argv[3]);
    int int_columns = STRING_TO_INTEGER(argv[2]);
    int int_scales = STRING_TO_INTEGER(argv[4]);
    int int_rows = STRING_TO_INTEGER(argv[1]);

    // Initializing the game environment
    GAME environment = initialize_environment(int_weights,int_columns,int_scales,int_rows);

    // Printing the game environment back to the user
    print_environment(environment);

    // Global Variables
    char ch_option = '\0';
    bool bln_state = true;

    // do-while
    do {
        // Fetching input from the user
        cin >> ch_option;

        switch(toupper(ch_option)) {
            case 'W':
            case 'S':
            case 'A':
            case 'D':
            case 'Q':
            case 'E':
            case 'Z':
            case 'X': {
                // Moving the player
                move_player(environment,ch_option);

                // Re-printing game environment back to the user after a move
                print_environment(environment);
                break;
            }
            case 'C': {
                // Drops a weight
                drop_weight(environment);

                // Re-printing game environment back to the user after a move
                print_environment(environment);
                break;
            }
            default: {
                cerr << "You entered a wrong input. Please re-enter." << endl;
                pause();
                break;
            }
        }

        // Checking the game state
        // If the game state is defeat or victory end game
        if (environment.state == VICTORY || environment.state == DEFEAT_DROP_FAILURE || environment.state == DEFEAT_WRONG_SCALE) {
            bln_state = false;
        }

    } while(bln_state);

    // Re-printing game environment back to the user after a move
    print_environment(environment);

    // Displaying a message for the results depending on the game state
    switch (environment.state) {
        case VICTORY: {
            cout << "WON: You stepped on all scales successfully." << endl;
            break;
        }
        case DEFEAT_DROP_FAILURE: {
            cout << "DEFEAT: YOU FAILED TO DROP A WEIGHT." << endl;
            break;
        }
        case DEFEAT_WRONG_SCALE: {
            cout << "DEFEAT: YOU STEPPED ON A WRONG SCALE." << endl;
            cout << "Your weight was: " << environment.int_player_weight << endl;
            break;
        }
    }

    // Memory deallocation
    deallocate(environment);

    return SUCCESS;
};
