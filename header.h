#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * @brief Enum representing different cases in the game matrix.
 */
typedef enum {
    WATER,          /**< Represents water */
    WATER_SHOT,     /**< Represents water after being shot */
    BOAT,           /**< Represents a boat */
    WRECK           /**< Represents a wreck */
} Case;

/**
 * @brief Structure representing a boat.
 */
typedef struct {
    int size;           /**< Size of the boat */
    int x;              /**< X-coordinate of the boat's position */
    int y;              /**< Y-coordinate of the boat's position */
    int orientation;    /**< Orientation of the boat: 0 for horizontal, 1 for vertical */
} Boat;

/**
 * @brief Structure representing a plate (game matrix).
 */
typedef struct {
    int** matrix;   /**< 2D array representing the matrix */
    int length;     /**< Length of the matrix */
} Plate;

/**
 * @brief Structure representing the game with two plates and boat lists.
 */
typedef struct {
    Plate* j1;              /**< Plate for player 1 */
    Plate* j2;              /**< Plate for player 2 */
    Boat** j1_first_ship;   /**< List of boats for player 1 */
    Boat** j2_first_ship;   /**< List of boats for player 2 */
} Game;

Game* create_game(int side, int boat_number);
int boat_status(Boat* temp_boat, Plate* temp_plate);
Boat* create_boat(int boat_size, int temp_x, int temp_y, int temp_orientation);
Boat** create_boat_list(int boat_number);
Plate* create_plate(int side);
int collide(Boat** boat_list, Boat* temp, int n, int side);
void display_plate(Plate* current_plate, int who);
void player_round(Game* current_game, int side);
void npc_round(Game* current_game, int side);
void free_all(Game* current_game, int side, int n);
void place_boat(Plate* current_plate, Boat** boat_list, int boat_number);

#endif
