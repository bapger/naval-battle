#include "header.h"



/**
 * @brief Function to check the status of a boat.
 * 
 * @param temp_boat Pointer to the boat.
 * @param temp_plate Pointer to the plate containing the boat.
 * @return int Status of the boat.
 */
int boat_status(Boat* temp_boat, Plate* temp_plate) {
    int count = 0;

    if (temp_boat->orientation == 0) {
        for (int i = 0; i < temp_boat->size; i++) {
            if (temp_boat->y + i >= temp_plate->length) {
                return 1; // The boat is out of the game plate y axis
            }
            if (temp_plate->matrix[temp_boat->x][temp_boat->y + i] == WRECK) {
                count++;
            }
        }
    } else if (temp_boat->orientation == 1) {
        for (int i = 0; i < temp_boat->size; i++) {
            if (temp_boat->x + i >= temp_plate->length) {
                return 1; // The boat is out of the game plate x axis
            }
            if (temp_plate->matrix[temp_boat->x + i][temp_boat->y] == WRECK) {
                count++;
            }
        }
    }

    if (count == temp_boat->size) {
        return 0; // Each part of the ship have been shot
    }
    return 1; // The ship is still floating
}

/**
 * @brief Function to check collision between boats.
 * 
 * @param boat_list List of boats to check collision against.
 * @param temp Temporary boat to check for collision.
 * @param n Number of boats.
 * @param side Side length of the plate.
 * @return int 1 if collision is detected, 0 otherwise.
 */
int collide(Boat** boat_list, Boat* temp, int n, int side) {
    if (boat_list == NULL || temp->size == -1 || temp->x == -1 || temp->y == -1 || temp->orientation == -1) {
        printf("Error in Collide");
        exit(2);
    }

    // Checks if the boat is out of the plate's boundaries
    if (temp->orientation == 0) { // Temporary boat is horizontal
        if (temp->x < 0 || temp->x >= side || temp->y < 0 || temp->y + temp->size > side) {
            return 1;
        }
    } else { // Temporary boat is vertical
        if (temp->y < 0 || temp->y >= side || temp->x < 0 || temp->x + temp->size > side) {
            return 1;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (temp->orientation == boat_list[i]->orientation) {
            if (temp->orientation == 0) { // If both boats are horizontal
                // Checks if boats overlap on the Y-axis
                for (int j = 0; j < temp->size; ++j) {
                    if (temp->y + j >= side || boat_list[i]->y < temp->y + j + 1 && boat_list[i]->y + boat_list[i]->size > temp->y + j) {
                        return 1; // Collision detected
                    }
                }
            } else { // Both boats are vertical
                // Checks if boats overlap on the X-axis
                for (int j = 0; j < temp->size; ++j) {
                    if (temp->x + j >= side || boat_list[i]->x < temp->x + j + 1 && boat_list[i]->x + boat_list[i]->size > temp->x + j) {
                        return 1; // Collision detected
                    }
                }
            }
        } else { // One boat is horizontal and the other is vertical
            if (temp->orientation == 0) { // Temporary boat is horizontal
                // Checks if boats overlap on both axes
                for (int j = 0; j < temp->size; ++j) {
                    for (int k = 0; k < boat_list[i]->size; ++k) {
                        if (temp->x + j >= side || boat_list[i]->x + k >= side || temp->y >= side || boat_list[i]->y >= side) {
                            continue;
                        }
                        if ((temp->x + j >= boat_list[i]->x && temp->x + j < boat_list[i]->x + boat_list[i]->size) &&
                            (temp->y <= boat_list[i]->y + k && temp->y >= boat_list[i]->y)) {
                            return 1; // Collision detected
                        }
                    }
                }
            } else { // Temporary boat is vertical
                // Checks if boats overlap on both axes
                for (int j = 0; j < temp->size; ++j) {
                    for (int k = 0; k < boat_list[i]->size; ++k) {
                        if (temp->y + j >= side || boat_list[i]->y + k >= side || temp->x >= side || boat_list[i]->x >= side) {
                            continue;
                        }
                        if ((temp->y + j >= boat_list[i]->y && temp->y + j < boat_list[i]->y + boat_list[i]->size) &&
                            (temp->x <= boat_list[i]->x + k && temp->x >= boat_list[i]->x)) {
                            return 1; // Collision detected
                        }
                    }
                }
            }
        }
    }

    return 0; // No collision detected
}




/**
 * @brief Places boats on the plate based on boat positions.
 * 
 * @param current_plate Pointer to the current plate.
 * @param boat_list List of boats to place.
 * @param boat_number Number of boats.
 */
void place_boat(Plate* current_plate, Boat** boat_list, int boat_number) {
    if (boat_list == NULL || current_plate == NULL || boat_number <= 0) {
        exit(5);
    }
    int temp_x;
    int temp_y;
    int temp_orientation;
    int temp_size;
    for (int i = 0; i < boat_number; i++) {
        temp_x = boat_list[i]->x;
        temp_y = boat_list[i]->y;
        temp_orientation = boat_list[i]->orientation;
        temp_size = boat_list[i]->size;
        if (temp_orientation == 0) {
            for (int j = 0; j < temp_size; j++) {
                if (temp_x + j < current_plate->length && temp_y < current_plate->length) {
                    current_plate->matrix[temp_x + j][temp_y] = 2;
                }
            }
        } else {
            for (int j = 0; j < temp_size; j++) {
                if (temp_x < current_plate->length && temp_y + j < current_plate->length) {
                    current_plate->matrix[temp_x][temp_y + j] = 2;
                }
            }
        }
    }
}

/**
 * @brief Creates a naval battle game.
 * 
 * @param side The side length of the game's plates.
 * @param boat_number Number of boats for each player.
 * @return Game* Pointer to the created game.
 */


/**
 * @brief Displays the contents of a plate.
 * 
 * @param current_plate Pointer to the plate to display.
 * @param who Player identifier (0 for player 1, 1 for player 2).
 */
void display_plate(Plate* current_plate,int who){
    if(current_plate==NULL){
        exit(4);
    }
    int n=current_plate->length;
    int temp_case=0;
    printf("x |");
    for(int j=0;j<n;j++){
        printf(" %d",j);
    }
    printf("\n");
    for(int i=0; i<n; i++){
        printf("%d | ",i);
        for(int j=0;j<n;j++){
            temp_case=current_plate->matrix[i][j];
            switch(temp_case){
                case WATER:
                    printf("💧");
                    break;
                case WATER_SHOT:
                    printf("💦");
                    break;
                case BOAT:
                    if(!who){
                    printf("⛵");
                    }
                    else{
                        printf("💧");
                    }
                    break;
                case WRECK:
                    printf("🔥");
                    break;

            }
            
        }
        printf("\n");
    }
}

/**
 * @brief Handles the player's round.
 * 
 * @param current_game Pointer to the current game.
 * @param side Side length of the game's plates.
 */
void player_round(Game* current_game,int side){
    if(current_game==NULL||side<=0){
        exit(7);
    }
    printf("Where do you want to aim Captain? (first x coord, then y coord)\n");
    int x=0;
    int y=0;
    
    do{ 
        scanf("%d",&y);
        scanf("%d",&x);
    }while(x>=side||y>=side);
    system("clear");
    switch(current_game->j2->matrix[x][y]){
        case WATER:
            printf("MISSED! Reloading...\n");
            current_game->j2->matrix[x][y]=1;
            break;
        case BOAT:
            printf("It's a HIT! Reloading...\n");
            current_game->j2->matrix[x][y]=3;
            break;
        case WATER_SHOT:
            printf("Why did you do this ?! We missed an opportunity...\n");
            break;
        case WRECK:
            printf("Why did you do this ?! We missed an opportunity...\n");
            break;
    }

}

/**
 * @brief Handles the NPC's round.
 * 
 * @param current_game Pointer to the current game.
 * @param side Side length of the game's plates.
 */
void npc_round(Game* current_game, int side) {
    if (current_game == NULL || side <= 0) {
        exit(7);
    }

    int available_spots[side * side][2]; // Not shot cases
    int count = 0;

    //looking for free case
    for (int i = 0; i < side; i++) {
        for (int j = 0; j < side; j++) {
            if (current_game->j1->matrix[i][j] == 0 || current_game->j1->matrix[i][j] == 2) {
                available_spots[count][0] = i; // save of x if not shot
                available_spots[count][1] = j; // save of y if not shot
                count++;
            }
        }
    }

    if (count == 0) {
        printf("No available spots for firing!\n");
        exit(8);
        return; // No way to fire
    }

    srand(time(NULL));
    int random_index = rand() % count; // random choice of one of the empty case
    int x = available_spots[random_index][0];
    int y = available_spots[random_index][1];

    switch (current_game->j1->matrix[x][y]) {
        case WATER:
            printf("They shot some fishes!\n");
            current_game->j1->matrix[x][y] = 1;
            break;
        case BOAT:
            printf("We took a hit!\n");
            current_game->j1->matrix[x][y] = 3;
            break;
        case WATER_SHOT:
        case WRECK:
            printf("Invalid spot selected!\n");
            break;
    }
}