#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define BOARD_SIZE 8 // Size of the chessboard
#define QUEEN 1 // Queen representation
#define NOT_QUEEN 0 // Not a queen representation


int check_direction(int board[][BOARD_SIZE], int row, int col, int direction_row, int direction_col)
{
	if (row < 0 || row >= BOARD_SIZE || col < 0 || col >= BOARD_SIZE)
		return 0; // Out of bounds
	if (board[row][col] == QUEEN)
		return 1; // Found a queen

	return check_direction(board, row + direction_row, col + direction_col, direction_row, direction_col);

}

int check_place(int board[][BOARD_SIZE], int row, int col)
{
	int counter = 0, direction_row, direction_col;
	direction_row = 0;
	direction_col = 1; // check right
	counter += check_direction(board, row + direction_row, col + direction_col, direction_row, direction_col);

	direction_row = 0;
	direction_col = -1; // check left
	counter += check_direction(board, row + direction_row, col + direction_col, direction_row, direction_col);

	direction_row = 1;
	direction_col = 0; // check down
	counter += check_direction(board, row + direction_row, col + direction_col, direction_row, direction_col);

	direction_row = -1;
	direction_col = 0; // check up
	counter += check_direction(board, row + direction_row, col + direction_col, direction_row, direction_col);

	direction_row = 1;
	direction_col = 1; // check down-right
	counter += check_direction(board, row + direction_row, col + direction_col, direction_row, direction_col);

	direction_row = 1;
	direction_col = -1; // check down-left
	counter += check_direction(board, row + direction_row, col + direction_col, direction_row, direction_col);

	direction_row = -1;
	direction_col = 1; // check up-right
	counter += check_direction(board, row + direction_row, col + direction_col, direction_row, direction_col);

	direction_row = -1;
	direction_col = -1; // check up-left
	counter += check_direction(board, row + direction_row, col + direction_col, direction_row, direction_col);

	if (counter == 0)
		return 1; // No queens in the way
	else
		return 0; // There is a queen in the way
}

void print_board(int board[][BOARD_SIZE], int row, int col)
{
	if (col >= BOARD_SIZE) // we finished printing the row  
	{
		printf("\n");
		col = 0;
		row++;
	}
	if (row >= BOARD_SIZE)  // we finished printing the board 
		return;
	if (col > 0 && col < BOARD_SIZE)
		printf(" ");

	printf("%d", board[row][col]);

	print_board(board, row, col + 1); // Recur to print the next column  
}

int mark_queens(int board[][BOARD_SIZE], int solution_num, int col)
{
	int row;
	if (col >= BOARD_SIZE) // We have placed all queens 
	{
		if (solution_num < 2) // Print only the first solution
			print_board(board, 0, 0);

		return (solution_num - 1); // return the number of solutions
	}

	for (row = 0; row < BOARD_SIZE && solution_num > 0; row++) // try to place a queen in each row
	{
		if (check_place(board, row, col) == 1) // check if the place is valid

		{
			board[row][col] = QUEEN; // Place the queen
			solution_num = mark_queens(board, solution_num, col + 1); // Recur to place the next queen
			board[row][col] = 0; // Backtrack
		}
	}
	return solution_num; // return the number of solutions
}

void queens(int board[][BOARD_SIZE], int solution_num)
{
	if (solution_num > 92 || solution_num < 1)
		print_board(board, 0, 0); // print empty board
	else
		mark_queens(board, solution_num, 0); // start marking queens
}

int main()
{
	int solution_num;
	int board[BOARD_SIZE][BOARD_SIZE] = { 0 }; // Initialize the board
	printf("Enter the number of the requested solution: ");
	scanf("%d", &solution_num); // Read the number of the requested solution

	queens(board, solution_num);
	return 0;
}