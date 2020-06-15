#pragma once
#ifndef GROUPS_H
#define GROUPS_H
#include <iostream>
enum Groups {
	BROWN, LTBLUE, PURPLE, ORANGE, RED, YELLOW, GREEN, BLUE, LUX_TAX, INC_TAX,STATION,UTIL,
	FREE_PARKING, VISIT_JAIL, GO_JAIL, START,CHEST,CHANCE,CORNER
};
inline std::ostream& operator << (std::ostream& out, const Groups& groupId) {
	std::string color;
	switch (groupId) {
	case BROWN: color = "BROWN";
		break;
	case LTBLUE: color = "LTBLUE";
		break;
	case PURPLE: color = "PURPLE";
		break;
	case ORANGE: color = "ORANGE";
		break;
	case RED: color = "RED";
		break;
	case YELLOW: color = "YELLOW";
		break;
	case GREEN: color = "GREEN";
		break;
	case BLUE: color = "BLUE";
		break;
	case LUX_TAX: color = "LUX_TAX";
		break;
	case INC_TAX: color = "INC_TAX";
		break;
	case STATION: color = "STATION";
		break;
	case UTIL: color = "UTIL";
		break;
	case FREE_PARKING: color = "FREE_PARKING";
		break;
	case VISIT_JAIL: color = "VISIT_JAIL";
		break;
	case GO_JAIL: color = "GO_JAIL";
		break;
	case START: color = "START";
		break;
	case CHEST: color = "CHEST";
		break;
	case CHANCE: color = "CHANCE";
		break;
	case CORNER: color = "CORNER";
		break;

	}
	return out << color;
}
inline std::istream& operator>>(std::istream& in, Groups& groupId) {

}
#endif // !GROUPS_H
