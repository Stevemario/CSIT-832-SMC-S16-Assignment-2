#include "distance.h"
void setWeight (
	distance& weight,
	const std::string& sWeight
) {
	weight = std::stoi (sWeight);
}
void getWeight (
	std::string& sWeight,
	const distance& weight
) {
	sWeight = std::to_string (weight);
}
void setEmpty (
	distance& weight
) {
	weight = 0;
}