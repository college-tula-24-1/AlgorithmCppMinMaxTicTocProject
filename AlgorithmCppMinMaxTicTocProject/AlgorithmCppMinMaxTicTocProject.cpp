#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <conio.h>

const int boardSize{ 3 };

const char PLAYER{ 'X' };
const char OPPONENT{ 'O' };
const char EMPTY{ ' ' };

char CheckWinner(std::vector<std::vector<char>>& board);
bool IsMoves(std::vector<std::vector<char>>& board);
int Score(std::vector<std::vector<char>>& board);
int MinMax(std::vector<std::vector<char>>& board, int depth, bool isMaximizing);
std::pair<int, int> BestMove(std::vector<std::vector<char>>& board);

void PrintBoard(std::vector<std::vector<char>>& board);
void PrintMind(std::vector<std::vector<char>>& board, int depth, int best);

int main()
{
    std::vector<std::vector<char>> board(3, std::vector<char>(3, EMPTY));

    
    int row, column;
    int key;
    while (IsMoves(board))
    {
        std::cout << "Input O: ";
        std::cin >> row >> column;

        board[row][column] = OPPONENT;
        PrintBoard(board);

        auto bestMove = BestMove(board);

        if (bestMove.first != -1)
        {
            board[bestMove.first][bestMove.second] = PLAYER;
        }
        
        PrintBoard(board);
        
        std::cout << "press any key...";
        key = _getch();
    }
    
}




char CheckWinner(std::vector<std::vector<char>>& board)
{
    for (int i{}; i < boardSize; i++)
    {
        if (board[i][0] != EMPTY &&
            board[i][0] == board[i][1] &&
            board[i][1] == board[i][2])
            return board[i][0];
        if (board[0][i] != EMPTY &&
            board[0][i] == board[1][i] &&
            board[1][i] == board[2][i])
            return board[0][i];
    }
    if (board[0][0] != EMPTY &&
        board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
        return board[0][0];
    if (board[0][2] != EMPTY &&
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
        return board[0][2];

    return EMPTY;
}

bool IsMoves(std::vector<std::vector<char>>& board)
{
    for (int r{}; r < boardSize; r++)
        for (int c{}; c < boardSize; c++)
            if (board[r][c] == EMPTY) return true;
    return false;
}

int Score(std::vector<std::vector<char>>& board)
{
    char winner = CheckWinner(board);
    if (winner == PLAYER) return 10;
    if (winner == OPPONENT) return -10;
    return 0;
}

int MinMax(std::vector<std::vector<char>>& board, int depth, bool isMaximizing)
{
    int score = Score(board);

    if (score) return score;

    if (!IsMoves(board)) return 0;

    //if (isMaximizing)
    //{
    //    int best = std::numeric_limits<int>::min();
    //    for (int r{}; r < boardSize; r++)
    //        for (int c{}; c < boardSize; c++)
    //            if (board[r][c] == EMPTY)
    //            {
    //                board[r][c] = PLAYER;
    //                best = std::max(best, MinMax(board, depth + 1, false));
    //                board[r][c] = EMPTY;
    //            }
    //    return best;
    //}
    //else
    //{
    //    int best = std::numeric_limits<int>::max();
    //    for (int r{}; r < boardSize; r++)
    //        for (int c{}; c < boardSize; c++)
    //            if (board[r][c] == EMPTY)
    //            {
    //                board[r][c] = OPPONENT;
    //                best = std::min(best, MinMax(board, depth + 1, true));
    //                board[r][c] = EMPTY;
    //            }
    //    return best;
    //}

    int best = isMaximizing ? std::numeric_limits<int>::min() : std::numeric_limits<int>::max();
    for (int r{}; r < boardSize; r++)
        for (int c{}; c < boardSize; c++)
            if (board[r][c] == EMPTY)
            {
                board[r][c] = isMaximizing ? PLAYER : OPPONENT;

                //PrintMind(board, depth, best);

                int currentBest = MinMax(board, depth + 1, !isMaximizing);
                best = isMaximizing ? std::max(best, currentBest) : std::min(best, currentBest);

                //PrintMind(board, depth, best);

                board[r][c] = EMPTY;
            }
    return best;
}

std::pair<int, int> BestMove(std::vector<std::vector<char>>& board)
{
    int bestScore = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove{ -1, -1 };
    for(int r{}; r < boardSize; r++)
        for (int c{}; c < boardSize; c++)
        if(board[r][c] == EMPTY)
        {
            board[r][c] = PLAYER;

            //PrintMind(board, 0, bestScore);

            int currentScore = MinMax(board, 0, false);
            board[r][c] = EMPTY;

            if (currentScore > bestScore)
            {
                bestScore = currentScore;
                bestMove = { r, c };
            }
        }
    return bestMove;
}

void PrintBoard(std::vector<std::vector<char>>& board)
{
    for (int r{}; r < boardSize; r++)
    {
        for (int c{}; c < boardSize; c++)
        {
            std::cout << board[r][c];
            if (c < boardSize - 1)
                std::cout << " | ";
        }
        std::cout << "\n";
        if (r < boardSize - 1)
            std::cout << "--+---+--\n";
    }
    std::cout << "\n";
}

void PrintMind(std::vector<std::vector<char>>& board, int depth, int best)
{
    std::cout << "\nDepth: " << depth << "\n";
    PrintBoard(board);
    std::cout << "Best Score: " << best << "\n";

    int key = _getch();
}
