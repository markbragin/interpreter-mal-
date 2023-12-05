#include <sstream>

#include "utils.h"


unsigned numberOfDigits_(double n) {
	std::ostringstream strs;
	strs << n;
	return strs.str().size();
}


unsigned maxWidthInCol(const Matrix& matrix, int j)
{
    unsigned maxWidth = 0;
    for (int i = 0; i < matrix.m(); i++) {
        unsigned width = numberOfDigits_(matrix[i][j]);
        maxWidth = width > maxWidth ? width : maxWidth;
    }
    return maxWidth;
}
