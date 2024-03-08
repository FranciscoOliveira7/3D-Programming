#include "geometric_figure.h"
using namespace geometric_figure;

int main() {
	GeometricFigure *figure[2];

	figure[0] = new Rectangle(1, 1);
	figure[1] = new Circle(1);

	for (int i = 0; i < 2; i++) {
		figure[i]->Print();
	}

	Rectangle r1(1, 1), r2(2, 2), r3;

	r3 = r1 + r2;

	return 0;
}