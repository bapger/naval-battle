#include "header.h"

/**
 * @brief Function to create a plate.
 * 
 * @param side The side length of the plate.
 * @return Plate* Pointer to the created plate.
 */
Plate* create_plate(int side){

    Plate* temp_plate=NULL;
    temp_plate=malloc(sizeof(Plate));
    
    if(temp_plate==NULL){
        printf("Plate Creation Failed");
        exit(1);
    
    }
    temp_plate->length=side;
    
    //matrix creation
    int** temp_matrix=malloc(sizeof(int*)*side);
    
    if(temp_matrix==NULL){
        printf("Matrix Creation Failed");
        exit(1);
    }

    for(int i=0;i<side;i++){
        int* temp_column=malloc(sizeof(int)*side);
        
        if(temp_column==NULL){
            printf("Column Creation Failed");
            exit(1);
        }
        for(int j=0;j<side;j++){
            temp_column[j]=0;
        }
        temp_matrix[i]=temp_column;
    }

    temp_plate->matrix=temp_matrix;
    
    return temp_plate;
}

/**
 * @brief Function to create a list of boats.
 * 
 * @param boat_number Number of boats to create.
 * @return Boat** Pointer to the created boat list.
 */
Boat** create_boat_list(int boat_number) {
    Boat** boat_list = malloc(sizeof(Boat*) * boat_number);
    if (boat_list == NULL) {
        printf("Boat List Creation Failed");
        exit(2);
    }

    for (int i = 0; i < boat_number; i++) {
        boat_list[i] = malloc(sizeof(Boat)); // malloc for each boat of the list
        if (boat_list[i] == NULL) {
            printf("Boat Creation Failed");
            exit(2);
        }
    }

    return boat_list;
}

/**
 * @brief Function to create a boat.
 * 
 * @param boat_size Size of the boat.
 * @param temp_x X-coordinate of the boat's position.
 * @param temp_y Y-coordinate of the boat's position.
 * @param temp_orientation Orientation of the boat.
 * @return Boat* Pointer to the created boat.
 */
Boat* create_boat(int boat_size,int temp_x,int temp_y,int temp_orientation){
    Boat* temp_boat=malloc(sizeof(Boat));
    
    if(temp_boat==NULL){
        printf("Boat Creation Failed");
        exit(2);
    }
 
    if(boat_size==-1||temp_x==-1||temp_y==-1||temp_orientation==-1){
        printf("Wrong data send by user.");
        exit(2);
    }

    temp_boat->orientation=temp_orientation;
    temp_boat->x=temp_x;
    temp_boat->y=temp_y;
    temp_boat->size=boat_size;
    

    return temp_boat;
}

Game* create_game(int side, int boat_number) {
    Game* temp_game = malloc(sizeof(Game));
    Plate* plate1 = NULL;
    Plate* plate2 = NULL;
    Boat** boat1 = NULL;
    Boat** boat2 = NULL;

    srand(time(NULL));

    if (temp_game == NULL) {
        printf("Game Creation Failed");
        exit(3);
    }

    plate1 = create_plate(side);
    plate2 = create_plate(side);
    boat1 = create_boat_list(boat_number);
    boat2 = create_boat_list(boat_number);
    if (plate1 == NULL || plate2 == NULL || boat1 == NULL || boat2 == NULL) {
        printf("Plate or Boat Creation Failed");
        exit(3);
    }
    temp_game->j1 = plate1;
    temp_game->j2 = plate2;
    temp_game->j1_first_ship = boat1;
    temp_game->j2_first_ship = boat2;

    // Creation of each boat of the player
    int count = 0;
    int X=0, Y=0, s=0, o=0;
    int turn_count=0;

    while (count != boat_number) {
        Boat* temp_boat=malloc(sizeof(Boat));
        if (temp_boat == NULL) {
            printf("Boat Creation Failed");
            exit(2);
        }
        o = rand() % 2;
        s = (rand() % side) + 1;
        X = rand() % side;
        Y = rand() % side;
        temp_boat->orientation = o;
        temp_boat->size = s;
        temp_boat->x = X;
        temp_boat->y = Y;
        // see if a collision occure with the new boat
        if (!collide(boat1, temp_boat, boat_number, side)) {
//            boat1[count] = malloc(sizeof(Boat));
            boat1[count]->orientation = o;
            boat1[count]->size = s;
            boat1[count]->x = X;
            boat1[count]->y = Y;
            count++;
        }
        turn_count++;
        if(turn_count>100){
            for(int j=0;j<=count;j++){
                boat1[j]->orientation=0;
                boat1[j]->size=0;
                boat1[j]->x=0;
                boat1[j]->y=0;
            }
        }
        free(temp_boat);
        

    }

    count = 0;
    while (count != boat_number) {
        Boat* temp_boat=malloc(sizeof(Boat));
        if (temp_boat == NULL) {
            printf("Boat Creation Failed");
            exit(2);
        }
        o = rand() % 2;
        s = (rand() % side) + 1;
        X = rand() % side;
        Y = rand() % side;
        temp_boat->orientation = o;
        temp_boat->size = s;
        temp_boat->x = X;
        temp_boat->y = Y;
        // see if a collision occure with the new boat
        if (!collide(boat2, temp_boat, boat_number, side)) {
//            boat2[count] = malloc(sizeof(Boat));
            boat2[count]->orientation = o;
            boat2[count]->size = s;
            boat2[count]->x = X;
            boat2[count]->y = Y;
            count++;
        }
        turn_count++;
        if(turn_count>100){
            for(int j=0;j<=count;j++){
                boat2[j]->orientation=0;
                boat2[j]->size=0;
                boat2[j]->x=0;
                boat2[j]->y=0;
            }
        }
        free(temp_boat);

    }
    
    place_boat(plate1, boat1, boat_number);
    place_boat(plate2, boat2, boat_number);
    
    return temp_game;
}
/**
 * @brief Frees memory allocated for the game.
 * 
 * @param current_game Pointer to the current game.
 * @param side Side length of the game's plates.
 * @param n Number of boats.
 */
void free_all(Game* current_game, int side,int n) {
    if (current_game == NULL) {
        exit(6);
    }
    for (int i = 0; i < side; i++) {
        free(current_game->j1->matrix[i]);
        free(current_game->j2->matrix[i]);
    }
    free(current_game->j1->matrix);
    free(current_game->j2->matrix);
    free(current_game->j1);
    free(current_game->j2);
    for (int i = 0; i < n; i++) {
        free(current_game->j1_first_ship[i]);
        free(current_game->j2_first_ship[i]);
    }

    free(current_game->j1_first_ship);
    free(current_game->j2_first_ship);
    free(current_game);
}