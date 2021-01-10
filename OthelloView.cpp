#include "OthelloView.h"
#include <sstream>
using namespace std;

void OthelloView::PrintBoard(std::ostream& s) const {
    int columnCounter = 0;
    cout << "- 0 1 2 3 4 5 6 7" << endl;
    for (int row = 0; row < mOthelloBoard->BOARD_SIZE; row++)
    {
        cout << columnCounter << " ";
        columnCounter++;
        for (int col = 0; col < mOthelloBoard->BOARD_SIZE; col++)
        {
            // Default
            if ((int)mOthelloBoard->mBoard[row][col] == 0)
            {
                cout << "." << " ";
            }
            // X Player
            else if ((int)mOthelloBoard->mBoard[row][col] == 1)
            {
                cout << "B" << " ";
            }
            // O Player
            else if ((int)mOthelloBoard->mBoard[row][col] == -1)
            {
                cout << "W" << " ";
            }
        }
        cout << endl;
    }
}

std::unique_ptr<OthelloMove> OthelloView::ParseMove(const std::string& strFormat) {
    istringstream parse{ strFormat };
    char dummy;
    int row, col;
    parse >> dummy >> row >> dummy >> col >> dummy;
    unique_ptr<OthelloMove> move = make_unique<OthelloMove>(OthelloMove(BoardPosition(row, col)));
    return move;

}

std::ostream& operator<<(std::ostream& lhs, const OthelloView& rhs) {
    rhs.PrintBoard(lhs);
    lhs << (rhs.mOthelloBoard->GetCurrentPlayer() == OthelloBoard::Player::WHITE ? "White's turn" : "Black's turn");
    return lhs;

}
std::ostream& operator<<(std::ostream& lhs, const OthelloMove& rhs) {
    return lhs << string(rhs);
}