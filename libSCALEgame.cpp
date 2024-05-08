// Including the SCALE game library
#include "libSCALEgame.h"

namespace ScaleSpace {
    // Creating the environment
    TWOd create_environment(int int_rows,int int_columns) {
        // Allocating memory for the 2D ARRAy
        TWOd environment = new ONEd[int_rows];

        for (int row = 0; row < int_rows; row++) {
            environment[row] = new CELL[int_columns];

            // Initializing the array with EMPTY spaces
            for (int column = 0; column < int_columns; column++) {
                environment[row][column].feature = EMPTY;
                environment[row][column].weight = 0;
                environment[row][column].scale = false;
            }
        }

        return environment;
    };

    // Placing game features
    void place_feature(GAME& world,FEATURE feature,int int_count) {
        for (int c = 0; c < int_count; c++) {
            int int_column = RANDOM_NUMBER(0,world.int_columns - 1);
            int int_row = RANDOM_NUMBER(0,world.int_rows - 1);

            while (world.environment[int_row][int_column].feature != EMPTY) {
                int_column = RANDOM_NUMBER(0,world.int_columns - 1);
                int_row = RANDOM_NUMBER(0,world.int_rows - 1);
            }

            if (feature == WEIGHT) {
                world.environment[int_row][int_column].feature = WEIGHT;
                world.environment[int_row][int_column].weight = 1;
            }

            if (feature == PLAYER) {
                world.environment[int_row][int_column].feature = PLAYER;
                world.environment[int_row][int_column].weight = INITIAL_WEIGHT;

                // Storing the player's initial location
                world.int_player_column = int_column;
                world.int_player_weight = INITIAL_WEIGHT;
                world.int_player_row = int_row;
            }
        }
    };

    // Placing the scales
    void place_scale(GAME& world,FEATURE feature,int int_weight) {
        int int_column = RANDOM_NUMBER(0,world.int_columns - 1);
        int int_row = RANDOM_NUMBER(0,world.int_rows - 1);

        while (world.environment[int_row][int_column].feature != EMPTY) {
            int_column = RANDOM_NUMBER(0,world.int_columns - 1);
            int_row = RANDOM_NUMBER(0,world.int_rows - 1);
        }

        world.environment[int_row][int_column].weight = int_weight;
        world.environment[int_row][int_column].feature = feature;
        world.environment[int_row][int_column].scale = true;
    };

    // Placing the player
    void place_player(GAME& world) {
        for (int row = world.int_player_row - 1; row <= world.int_player_row + 1; row++) {
            for (int column = world.int_player_column - 1; column <= world.int_player_column + 1; column++) {
                cout << row << "," << column << " ";
            }
        }
    };

    // Initializing the game environment
    GAME initialize_environment(int int_weights,int int_columns,int int_scales,int int_rows) {
        GAME world;

        world.environment = create_environment(int_rows,int_columns);
        world.int_weights = int_weights;
        world.int_columns = int_columns;
        world.int_scales = int_scales;
        world.int_rows = int_rows;

        int int_temp_weights = int_weights;

        // Placing game features

        // Creating a weight for each scale and placing it in the game environment
        for (int scale = 1; scale <= int_scales; scale++) {
            int weight = RANDOM_NUMBER(0,int_temp_weights);
            int_temp_weights -= weight;

            if (scale == int_scales && int_temp_weights > 0) {
                weight = int_temp_weights + weight;
            }

            place_scale(world,SCALE,weight);
        }

        // Placing the weights
        place_feature(world,WEIGHT,int_weights);

        // Placing the player
        place_feature(world,PLAYER,1);

        return world;
    };

    // Printing the game environment back to the user
    void print_environment(GAME& world) {
        // Clearing the display
        system("cls");

        cout << endl;

        for (int row = 0; row < world.int_rows; row++) {
            for (int column = 0; column < world.int_columns; column++) {
                if (world.environment[row][column].scale) {
                    cout << world.environment[row][column].weight << " ";
                } else {
                    cout << FEATURE_ARRAY[world.environment[row][column].feature] << " ";
                }
            }
            cout << endl;
        }

        cout << endl;

        // Control instructions
        cout << "W. Move Up." << endl;
        cout << "S. Move Down." << endl;
        cout << "A. Move Left." << endl;
        cout << "D. Move Right." << endl;
        cout << "Q. Move Up-Left." << endl;
        cout << "E. Move Up-Right." << endl;
        cout << "Z. Move Down-Left." << endl;
        cout << "X. Move Down-Right." << endl;
        cout << "C. Drop a weight" << endl;

        cout << endl;
    };

    // Checking if the destination row and column exists inside the game world
    bool within_world(GAME& world,int int_row,int int_column) {
        return (int_row >= 0 && int_row < world.int_rows && int_column >= 0 && int_column < world.int_columns);
    };

    // Moving the player
    void move_player(GAME& world,char ch_option) {
        // Storing the initial row and column for the player
        int int_column = world.int_player_column;
        int int_row = world.int_player_row;

        // Switch-case containing movements
        switch(toupper(ch_option)) {
            case 'W': {
                int_row--;
                break;
            }
            case 'S': {
                int_row++;
                break;
            }
            case 'A': {
                int_column--;
                break;
            }
            case 'D': {
                int_column++;
                break;
            }
            case 'Q': {
                int_column--;
                int_row--;
                break;
            }
            case 'E': {
                int_column++;
                int_row--;
                break;
            }
            case 'Z': {
                int_column--;
                int_row++;
                break;
            }
            case 'X': {
                int_column++;
                int_row++;
                break;
            }
        }

        // Checking if the destination row and column is within world
        if (within_world(world,int_row,int_column)) {
            // Checking if the destination contains an EMPTY space
            if (world.environment[int_row][int_column].feature == EMPTY) {
                // If the previous position was not initially set for a scale set weight to 0,else re-introduce the scale
                if (!world.environment[world.int_player_row][world.int_player_column].scale) {
                    // Removing the player and weight from its initial row and column to the destination
                    world.environment[world.int_player_row][world.int_player_column].feature = EMPTY;
                    world.environment[world.int_player_row][world.int_player_column].weight = 0;
                } else {
                    world.environment[world.int_player_row][world.int_player_column].weight = world.int_previous_scale_weight;
                }

                // Moving the player to the destination row and column
                world.environment[int_row][int_column].feature = PLAYER;
                // Ensuring that the player's weight is stored to the player's position
                world.environment[int_row][int_column].weight = world.int_player_weight;

                // Updating the position of the player
                world.int_player_column = int_column;
                world.int_player_row = int_row;
            } else if (world.environment[int_row][int_column].feature == WEIGHT) {
                // If the destination contains a WEIGHT

                // If the previous position was not initially set for a scale,set weight to 0,else re-introduce the scale
                if (!world.environment[world.int_player_row][world.int_player_column].scale) {
                    // Removing the player and weight from its initial row and column to the destination
                    world.environment[world.int_player_row][world.int_player_column].feature = EMPTY;
                    world.environment[world.int_player_row][world.int_player_column].weight = 0;
                } else {
                    world.environment[world.int_player_row][world.int_player_column].weight = world.int_previous_scale_weight;
                }

                // Updating the player's weight
                world.int_player_weight += world.environment[int_row][int_column].weight;

                // Moving the player to the destination row and column
                world.environment[int_row][int_column].feature = PLAYER;
                // Ensuring that the player's weight is stored to the player's position
                world.environment[int_row][int_column].weight = world.int_player_weight;

                // Updating the position of the player
                world.int_player_column = int_column;
                world.int_player_row = int_row;
            } else if (world.environment[int_row][int_column].scale && world.int_player_weight >= 0) {
                // Subtracting the player's weight with the weight of the scale
                int int_weight_difference = world.environment[int_row][int_column].weight - world.int_player_weight;

                // Checking if the weight difference is equal to 0
                // If true remove the scale from the environment and move the player to the destination position
                // Else move the player to the destination position and set the game state to DEFEAT
                if (int_weight_difference == 0) {
                    world.environment[int_row][int_column].feature = PLAYER;
                    world.environment[int_row][int_column].weight = 0;
                    world.environment[int_row][int_column].scale = false;

                    // Removing the player and its weight from its initial row and column to the destination
                    world.environment[world.int_player_row][world.int_player_column].feature = EMPTY;

                    // Removing the weights from the player
                    world.int_player_weight = 0;

                    // Updating the position of the player
                    world.int_player_column = int_column;
                    world.int_player_row = int_row;

                    // After each successful move to the destination containing a scale, the number of scales inside the game are decremented
                    world.int_scales--;

                    if (world.int_scales == 0) {
                        // Setting the game state to victory
                        world.state = VICTORY;
                    }
                } else {
                    world.environment[int_row][int_column].feature = PLAYER;
                    world.environment[int_row][int_column].weight = 0;
                    world.environment[int_row][int_column].scale = false;

                    // Removing the player and its weight from its initial row and column to the destination
                    world.environment[world.int_player_row][world.int_player_column].feature = EMPTY;

                    // Updating the position of the player
                    world.int_player_column = int_column;
                    world.int_player_row = int_row;

                    // Setting the game state to defeat
                    world.state = DEFEAT_WRONG_SCALE;
                }


            }
        }
    }

    // Drops a weight
    void drop_weight(GAME& world) {
        // Creating a random number which will determine the destination location of the dropped weight
        int int_random = RANDOM_NUMBER(1,8);

        // Getting the player's current position
        int int_column = world.int_player_column;
        int int_row = world.int_player_row;

        switch(int_random) {
            case 1: {
                int_row--;
                break;
            }
            case 2: {
                int_row++;
                break;
            }
            case 3: {
                int_column--;
                break;
            }
            case 4: {
                int_column++;
                break;
            }
            case 5: {
                int_column--;
                int_row--;
                break;
            }
            case 6: {
                int_column++;
                int_row--;
                break;
            }
            case 7: {
                int_column--;
                int_row++;
                break;
            }
            case 8: {
                int_column++;
                int_row++;
                break;
            }
        }

        // Checking if the destination row and column is within world
        if (within_world(world,int_row,int_column) && world.environment[int_row][int_column].feature == EMPTY && world.int_player_weight > 0) {
            if (world.int_scales > 0) {
                // Updating the player's weight
                world.int_player_weight -= 1;

                // Dropping the weight to the row and column
                world.environment[int_row][int_column].feature = WEIGHT;
                // Ensuring that the weight has weight
                world.environment[int_row][int_column].weight = 1;
            }
        } else {
            // Setting the game state to defeat
            world.state = DEFEAT_DROP_FAILURE;
        }
    };

    // Random number generator
    int RANDOM_NUMBER(int int_minimum,int int_maximum) {
        int int_range = (int_maximum - int_minimum) + 1;

        return (rand() % int_range) + int_minimum;
    };

    // String to Integer converter
    int STRING_TO_INTEGER(string str_num) {
        int int_num = 0;

        stringstream ss {str_num};

        ss >> int_num;

        // Checking if the conversion was successful
        if (ss.fail()) {
            cerr << "The conversion of " << str_num << " to an Integer was unsuccessful." << endl;
            exit(ERROR_CONV);
        }

        return int_num;
    };

    // Memory deallocation
    void deallocate(GAME& world) {
        for (int row = 0; row < world.int_rows; row++) {
            delete [] world.environment[row];
        }

        delete [] world.environment;
        world.environment = nullptr;
    };

    // Pausing
    void pause() {
        cin.ignore(100, '\n');
        cout << "Press any key to continue..." << endl;
        cin.get();
    };
};
