#include "Globales.h"
#include "InithPathfinding.h"


/*= {
		// 0  1  2  3  4
		{0, 0, 0, 0, 1},   // 00
		{0, 0, 1, 0, 0},   // 01
		{0, 1, 0, 0, 0},   // 02
		{1, 0, 0, 1, 1},   // 03
		{0, 0, 0, 0, 1},   // 04
		{0, 0, 1, 0, 1},   // 05
		{0, 1, 0, 0, 0},   // 06
		{0, 0, 1, 0, 1},   // 07
		{0, 0, 1, 0, 0},   // 08
		{0, 0, 0, 1, 0},   // 09 ;
};*/

int main() {

InithPathfinding* Gladiador1 = new InithPathfinding();
Gladiador1->ejecutarPathFinding(50,100);
Gladiador1->ejecutarPathFinding(50,100);

	return 0;
}
