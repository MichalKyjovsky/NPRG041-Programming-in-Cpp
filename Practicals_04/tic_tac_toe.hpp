//
// Created by mkyjovsky01 on 10/24/2020.
//

#ifndef PRACTICALS_04_TIC_TAC_TOE_HPP
#define PRACTICALS_04_TIC_TAC_TOE_HPP

#include <vector>
#include <iostream>

class TicTacToe {
    enum class FieldState {
        PLAYER_1 = 'X',
        PLAYER_2 = '0',
        EMPTY = '_'
    };


    friend std::ostream &operator<<(std::ostream &strm, const FieldState &fieldState) {
        switch (fieldState) {
            case FieldState::PLAYER_1:
                strm << "X";
                break;
            case FieldState::PLAYER_2:
                strm << "O";
                break;
            case FieldState::EMPTY:
                strm << "_";
                break;
        }
    }

    bool game = true;
    FieldState winner;

private:
    using row_t = std::vector<FieldState>;
    using game_map = std::vector<row_t>;
    int width;
    int height;
    game_map game_board;

    game_map create_game_board(int height, int width);

    std::vector<int> PromptCoordinates(int round);

    void UpdateGameBoard(int coord_x, int coord_y, int player);

    void PrintGameBoard();

    FieldState EvaluateGameState(TicTacToe::FieldState player);

public:
    void Game();

    TicTacToe(int width, int height) : width(width), height(height) {
        std::cout << "***** Game has been initiated. *****" << std::endl;
        this->game_board = create_game_board(height, width);
    }

    TicTacToe(const TicTacToe &ticTacToe) : width(ticTacToe.width), height(ticTacToe.height) {
        std::cout << "***** Game has been initiated. *****" << std::endl;
        std::cout << "***** Copy of the game was created. *****" << std::endl;
    }

    TicTacToe(TicTacToe &&ticTacToe) : width(ticTacToe.width), height(ticTacToe.height) {
        std::cout << "***** Game has been initiated. *****" << std::endl;
        std::cout << "***** Game was moved to another instance. *****" << std::endl;
    }

    ~TicTacToe() = default;

    TicTacToe &operator=(const TicTacToe &ticTacToe) {
        this->width = ticTacToe.width;
        this->height = ticTacToe.height;
        return *this;
    }

    TicTacToe &operator=(TicTacToe &&ticTacToe) {
        this->width = ticTacToe.width;
        this->height = ticTacToe.height;
    }

    bool CheckRows(FieldState fieldState);

    bool CheckColumns(FieldState fieldState);

    bool CheckDiagonals(FieldState fieldState);
};


#endif //PRACTICALS_04_TIC_TAC_TOE_HPP
