#include "header.h"

/**
 * @brief Main function to start the Naval Battle game.
 */
void main() {
    int boat_number = 0;       // Number of ships in the fleet
    int plate_height = 0;      // Height of the battle zone

    // User input for number of ships and height of the battle zone
    do{
        printf("Welcome to Naval Battle,\nPlease choose the number of ships in your fleet: ");
    scanf("%d", &boat_number);
    printf("Now, choose the height of the battle zone: ");
    scanf("%d", &plate_height);
    }while(boat_number>plate_height);

    // Check if the input values are valid
    if (boat_number <= 0 || plate_height <= 0) {
        exit(0);
    }

    // Create the game with the given parameters
    Game* current_game = create_game(plate_height, boat_number);
    printf("Your navy\n");
    display_plate(current_game->j1, 0);
    printf("Enemy fleet\n");
    display_plate(current_game->j2, 1);
    int end = 0;    // Variable to control game ending

    // Main game loop
    while (!end) {
        // Player's turn
        player_round(current_game, plate_height);
        

        // Computer's turn
        npc_round(current_game, plate_height);
        printf("Your navy\n");
        display_plate(current_game->j1, 0);
        printf("Enemy fleet\n");
        display_plate(current_game->j2, 1);

        int player_destroyed = 0;    // Count of player's destroyed ships
        int npc_destroyed = 0;       // Count of computer's destroyed ships

        // Check if all ships of a player have been destroyed
        for (int i = 0; i < boat_number; i++) {
            if (!boat_status(current_game->j2_first_ship[i], current_game->j2)) {
                printf("\n 🛟  Enemy Ship N°%d has been disintegrated.\n\n", i);
                npc_destroyed++;
            }

            if (!boat_status(current_game->j1_first_ship[i], current_game->j1)) {
                printf("\n 🛟  Player Ship N°%d has been disintegrated.\n\n", i);
                player_destroyed++;
            }
        }

        // Game ending conditions
        if (player_destroyed == boat_number && npc_destroyed == boat_number) {
            printf("Everybody died...\nIt's a draw.\n\n");
            end = 1;
        } else if (player_destroyed == boat_number) {
            printf("This was our last boat...\n\n-------------DEFEAT-------------\n\n");
            end = 1;
        } else if (npc_destroyed == boat_number) {
            printf("You obliterated them! Going back to the base.\n\n-------------VICTORY-------------\n\n");
            end = 1;
        }
    }

    // End of the game, free memory
    free_all(current_game, plate_height, boat_number);
}
