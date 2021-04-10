#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <exception>
#include <chrono>
#include <vector>
#include <iomanip>

//#include "date.h"
#include "exception_classes.h"

namespace helper{
	std::vector<int> ProcessShift(double timeshift);
	std::string GetNewFilePath(std::string OriginalFilePath);
/**
 * @brief Applies a shift to a line in file.
 * @param Origin Original line string.
 * @param Shift	 Shift value in string format.
 * @return ShiftedString a string representing the line after modification.
 */
	std::string ApplyShiftToLine(std::string Origin,
		std::vector<int> Shifts);
}
#endif