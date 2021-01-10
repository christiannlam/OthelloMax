#include "OthelloBoard.h"
#include "BoardDirection.h"
#include "BoardPosition.h"
#include <string>
#include <vector>
using namespace std;

OthelloBoard::OthelloBoard() : mCurrentValue(0), mCurrentPlayer(Player::BLACK) {
    mBoard = { Player::EMPTY }, mBoard[3][3] = { Player::WHITE }, mBoard[3][4] = { Player::BLACK },
        mBoard[4][3] = { Player::BLACK }, mBoard[4][4] = { Player::WHITE };
}

void OthelloBoard::ApplyMove(std::unique_ptr<OthelloMove> m) {
    if (!m->IsPass())
    {
        // Sets parameters of row and col to currentPlayer
        mBoard[m->mPosition.getRow()][m->mPosition.getCol()] = mCurrentPlayer;
        mCurrentPlayer == Player::BLACK ? (mCurrentValue++) : (mCurrentValue--);
        // 8 Directions:
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                int tempI = i, tempJ = j, pieceCounter = 0;
                while (InBounds(BoardPosition(m->mPosition.getRow() + tempI, m->mPosition.getCol() + tempJ)) &&
                    mBoard[m->mPosition.getRow() + tempI][m->mPosition.getCol() + tempJ] != mCurrentPlayer &&
                    mBoard[m->mPosition.getRow() + tempI][m->mPosition.getCol() + tempJ] != Player::EMPTY)
                {
                    tempI += i;
                    tempJ += j;
                    pieceCounter++;
                }
                if (InBounds(BoardPosition(m->mPosition.getRow() + tempI, m->mPosition.getCol() + tempJ)) &&
                    mBoard[m->mPosition.getRow() + tempI][m->mPosition.getCol() + tempJ] == mCurrentPlayer)
                {
                    m->AddFlipSet(OthelloMove::FlipSet(pieceCounter, BoardDirection(i, j)));
                    while (pieceCounter > 0)
                    {
                        tempI = tempI - i;
                        tempJ = tempJ - j;
                        mBoard[m->mPosition.getRow() + tempI][m->mPosition.getCol() + tempJ] = mCurrentPlayer;
                        pieceCounter--;
                        mCurrentPlayer == Player::BLACK ? (mCurrentValue = mCurrentValue + 2) : (mCurrentValue = mCurrentValue - 2);
                    }
                }
            }
        }
    }
    mHistory.push_back(move(m));
    mCurrentPlayer = (GetCurrentPlayer() == Player::BLACK) ? Player::WHITE : Player::BLACK;
}

void OthelloBoard::UndoLastMove()
{
    unique_ptr<OthelloMove> lastMove = move(mHistory.back());
    auto& moves = lastMove->mFlips;
    mCurrentValue += (GetCurrentPlayer() == Player::BLACK) ? 1 : -1;
    // Loops through FlipSet
    for (int i = 0; i < moves.size(); i++)
    {
        // Creates BoardPosition Object
        BoardPosition first = lastMove->mPosition;
        // Removes the last move from board
        mBoard[lastMove->mPosition.getRow()][lastMove->mPosition.getCol()] = Player::EMPTY;
        for (int j = 0; j < moves[i].mFlipCount; j++)
        {
            mCurrentValue += (GetCurrentPlayer() == Player::BLACK) ? 2 : -2;
            first = first + moves[i].mDirection;
            mBoard[first.getRow()][first.getCol()] = mCurrentPlayer;
            
        }
    }
    mCurrentPlayer = (GetCurrentPlayer() == Player::BLACK) ? Player::WHITE : Player::BLACK;
    mHistory.pop_back();
}

bool OthelloBoard::isFinished()
{
    auto &moves = GetMoveHistory();
        if (moves.size() != 0) {
            for (int i = 0; i < moves.size()-1; i++) {
                // If (-1,-1) was played twice
                if (moves[i]->IsPass() && moves[i + 1]->IsPass()) {
                    return true;
                }
            }
        }
        return false;
}

vector<unique_ptr<OthelloMove>> OthelloBoard::GetPossibleMoves() const {
    vector<unique_ptr<OthelloMove>> moves;
    // Loops through Board
    for (int i = 0; i < mBoard.size(); i++) {
        for (int j = 0; j < mBoard[0].size(); j++) {
            // Creates new BoardPosition
            BoardPosition begin = BoardPosition{ static_cast<char>(i), static_cast<char>(j) };
            // Loops through 8 Directions
            for (BoardDirection dir : BoardDirection::CARDINAL_DIRECTIONS)
            {
                BoardPosition current = begin;
                int dirRow = dir.getRowChange(), dirCol = dir.getColChange(), enemyCounter = 0;
                // Counts the enemy pieces
                while (InBounds(current + dir) && mBoard[current.getRow() + dirRow][current.getCol() + dirCol] != Player::EMPTY && PositionIsEnemy(current + dir, mCurrentPlayer))
                {
                    current = current + dir;
                    enemyCounter++;
                }
                if (enemyCounter == 0 || !InBounds(current + dir) || mBoard[begin.getRow()][begin.getCol()] != Player::EMPTY || mBoard[current.getRow() + dirRow][current.getCol() + dirCol] == Player::EMPTY)
                {
                    continue;
                }
                // If there are no enemies
                else {
                    moves.push_back(make_unique<OthelloMove>(OthelloMove(begin)));
                    break;
                }
            }
        }
    }
    if (moves.size() == 0)
    {
        moves.push_back(make_unique<OthelloMove>(OthelloMove(BoardPosition{ -1, -1 })));
    }
    return moves;
}




