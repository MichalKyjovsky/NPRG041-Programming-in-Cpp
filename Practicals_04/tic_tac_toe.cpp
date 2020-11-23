//
// Created by mkyjovsky01 on 10/24/2020.
//

#include "tic_tac_toe.hpp"

TicTacToe::game_map TicTacToe::create_game_board(int width, int height) {
    TicTacToe::game_map board(height);
    TicTacToe::row_t row(width);
    std::fill(row.begin(), row.begin() + width, TicTacToe::FieldState::EMPTY);
    for (int i = 0; i < height; i++) {
        board[i] = row;
    }
    return board;
}

void TicTacToe::Game() {
    int round = 0;
    std::vector<int> coordinates(2);

    while (this->game) {
        coordinates = PromptCoordinates(round);
        UpdateGameBoard(coordinates[0], coordinates[1], (round % 2) + 1);
        PrintGameBoard();
        this->winner = EvaluateGameState(
                (round % 2) == 0 ? TicTacToe::FieldState::PLAYER_1 : TicTacToe::FieldState::PLAYER_2);
        round += 1;
    }
    std::cout << "Player " << this->winner << " has WON!" << std::endl;
}

void TicTacToe::UpdateGameBoard(int coord_x, int coord_y, int player) {
    this->game_board[coord_x][coord_y] =
            player == 1 ? TicTacToe::FieldState::PLAYER_1 : TicTacToe::FieldState::PLAYER_2;
}

void TicTacToe::PrintGameBoard() {
    std::cout << "********************" << std::endl;
    for (auto &&line : this->game_board) {
        for (auto field : line) {
            std::cout << field;
        }
        std::cout << std::endl;
    }
    std::cout << "********************" << std::endl;
}

std::vector<int> TicTacToe::PromptCoordinates(int round) {
    std::vector<int> coords(2);
    bool valid_input = false;

    while (!valid_input) {
        std::cout << "Player " << (round % 2) + 1 << "\nPlease set coordinates.\nPossible interval 1-10." << std::endl;
        std::cout << "Coordinate X:";
        std::cin >> coords[0];
        std::cout << "Coordinate Y:";
        std::cin >> coords[1];
        if (((coords[0] > 0 && coords[0] < 11)
              && (coords[1] > 0 && coords[1] < 11))
            && this->game_board[coords[0]][coords[1]] == FieldState::EMPTY) {
            valid_input = true;
        }
    }

    coords[0] -= 1;
    coords[1] -= 1;

    return coords;
}

TicTacToe::FieldState TicTacToe::EvaluateGameState(TicTacToe::FieldState player) {
    this->game = !(CheckRows(player) || CheckColumns(player) || CheckDiagonals(player));
    return player;
}

bool TicTacToe::CheckRows(TicTacToe::FieldState fieldState) {
    for (int row = 0; row < this->game_board[0].size(); row++) {
        for (int col = 0; col < this->game_board.size() - 5; col++) {
            if (this->game_board[row][col] == fieldState &&
                this->game_board[row][col] == this->game_board[row][col + 1] &&
                this->game_board[row][col + 1] == this->game_board[row][col + 2] &&
                this->game_board[row][col + 2] == this->game_board[row][col + 3] &&
                this->game_board[row][col + 3] == this->game_board[row][col + 4]) {
                return true;
            }
        }
    }
    return false;
}

bool TicTacToe::CheckColumns(TicTacToe::FieldState fieldState) {
    for (int row = 0; row < this->game_board[0].size() - 5; row++) {
        for (int col = 0; col < this->game_board.size(); col++) {
            if (this->game_board[row][col] == fieldState &&
                this->game_board[row][col] == this->game_board[row + 1][col] &&
                this->game_board[row + 1][col] == this->game_board[row + 2][col] &&
                this->game_board[row + 2][col] == this->game_board[row + 3][col] &&
                this->game_board[row + 3][col] == this->game_board[row + 4][col]) {
                return true;
            }
        }
    }
    return false;
}

bool TicTacToe::CheckDiagonals(TicTacToe::FieldState fieldState) {
    for (int row = 0; row < this->game_board[0].size() - 5; row++) {
        for (int col = 0; col < this->game_board.size() - 5; col++) {
            if (this->game_board[row][col] == fieldState &&
                this->game_board[row][col] == this->game_board[row + 1][col + 1] &&
                this->game_board[row + 1][col + 1] == this->game_board[row + 2][col + 2] &&
                this->game_board[row + 2][col + 2] == this->game_board[row + 3][col + 3] &&
                this->game_board[row + 3][col + 3] == this->game_board[row + 4][col + 4]) {
                return true;
            }
        }
    }

    for (int row = this->game_board[0].size() - 1; row > 4; row--) {
        for (int col = this->game_board.size() - 1; col > 4; col--) {
            if (this->game_board[row][col] == fieldState &&
                this->game_board[row][col] == this->game_board[row - 1][col - 1] &&
                this->game_board[row - 1][col - 1] == this->game_board[row - 2][col - 2] &&
                this->game_board[row - 2][col - 2] == this->game_board[row - 3][col - 3] &&
                this->game_board[row - 3][col - 3] == this->game_board[row - 4][col - 4]) {
                return true;
            }
        }
    }
    return false;
}

