#include "OthelloMove.h"
#include <sstream>
using namespace std;

bool OthelloMove::operator==(const OthelloMove &rhs)
{
    return (mPosition == rhs.mPosition);
}

OthelloMove::operator std::string() const
{
    std::ostringstream os;
    os << "(" << (int)mPosition.getRow() << "," << (int)mPosition.getCol() << ")";
    return os.str();
}