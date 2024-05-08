#ifndef LIBSCALEGAME_H_INCLUDED
#define LIBSCALEGAME_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>
#include <ctime>
#include <cmath>

using namespace std;

namespace ScaleSpace {
    // Enumeration type definitions
    enum GAMESTATE {
        DEFEAT_DROP_FAILURE,
        DEFEAT_WRONG_SCALE,
        VICTORY
    };

    enum FEATURE {
        EMPTY,
        SCALE,
        WEIGHT,
        PLAYER
    };

    enum ERROR {
        ERROR_ARGC = -2,
        ERROR_CONV,
        SUCCESS
    };

    // Structure declaration
    struct CELL {
        FEATURE feature;
        bool scale;
        int weight;
    };

    typedef CELL* ONEd;
    typedef ONEd* TWOd;

    struct GAME {
        TWOd environment;
        GAMESTATE state;

        int int_previous_scale_weight;
        int int_player_column;
        int int_player_weight;
        int int_player_row;
        int int_weights;
        int int_columns;
        int int_scales;
        int int_rows;
    };

    // Constants
    const char FEATURE_ARRAY[4] = {' ','S','W','P'};
    const int INITIAL_WEIGHT = 0;

    // Function declarations
    // Creating the environment
    TWOd create_environment(int int_rows,int int_columns);

    // Initializing the game environment
    GAME initialize_environment(int int_weights,int int_columns,int int_scales,int int_rows);

    // Placing game features
    void place_feature(GAME& world,FEATURE feature,int int_count);

    // Placing the scales
    void place_scale(GAME& world,FEATURE feature,int int_weight);

    // Placing the player
    void place_player(GAME& world);

    // Printing the game environment back to the user
    void print_environment(GAME& world);

    // Checking if the destination row and column exists inside the game world
    bool within_world(GAME& world,int int_row,int int_column);

    // Moving the player
    void move_player(GAME& world,char ch_option);

    // Drops a weight
    void drop_weight(GAME& world);

    // Random number generator
    int RANDOM_NUMBER(int int_minimum,int int_maximum);

    // String to Integer converter
    int STRING_TO_INTEGER(string str_num);

    // Memory deallocation
    void deallocate(GAME& world);

    // Pausing
    void pause();
};

#endif
