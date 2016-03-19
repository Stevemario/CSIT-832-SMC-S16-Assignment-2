#ifndef DISTANCE_H
#define DISTANCE_H
#include <string>
typedef unsigned int wholeNumber;
typedef wholeNumber distance;
void setWeight (
	distance&,
	const std::string&
);
void getWeight (
	std::string&,
	const distance&
);
void setEmpty (
	distance&
);
#endif