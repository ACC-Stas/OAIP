#include <iostream>
#include <ccomplex>
#include <glut.h>

class ManDelBrot {
private:
	double fieldHeight;
	double fieldWidth;
	int NumberOfXPixels;
	int NumberOfYPixels;
	const int maxIterationNumber = 100;
	const int determingNumber = 2;
	double centreX;
	double centreY;
public:
	ManDelBrot(double fieldHeight, double fieldWidth, double centreX, double centreY, int NumberOfXPixels, int NumberOfYPixels) {
		this->fieldHeight = fieldHeight;
		this->fieldWidth = fieldWidth;
		this->centreX = centreX;
		this->centreY = centreY;
		this->NumberOfXPixels = NumberOfXPixels;
		this->NumberOfYPixels = NumberOfYPixels;
	};
	void setCentreX(double centreX) {
		this->centreX = centreX;
	}
	void setCentreY(double centreY) {
		this->centreY = centreY;
	}
	void setFieldHeight(double fieldHeight) {
		this->fieldHeight = fieldHeight;
	}
	void setFieldWidth(double fieldWidth) {
		this->fieldWidth = fieldWidth;
	}
	int getIterations(int x, int y) {
		if (x > NumberOfXPixels / 2 || x < - NumberOfXPixels / 2) {
			throw std::out_of_range("x is out of range\n");
		}
		if (y > NumberOfYPixels / 2 || y < - NumberOfYPixels / 2) {
			throw std::out_of_range("y is out of range\n");
		}
		int iterations = 0;
		double mandelX = (x + centreX) * (fieldWidth / NumberOfXPixels);
		double mandelY = (y + centreY) * (fieldHeight / NumberOfYPixels);
		std::complex<double> z(0, 0);
		std::complex<double> c(mandelX, mandelY);
		do {
			z = z * z + c;
			iterations++;
		} while (iterations < maxIterationNumber && std::abs(z) < determingNumber);
		return iterations;
	}

};

float WinWid = 400, WinHei = 400;

void init() {

	glClearColor(0.0, 0.0, 0.0, 1.0);

	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();

	glOrtho(-WinWid / 2, WinWid / 2, -WinHei / 2, WinHei / 2, -200.0, 200.0);

	glMatrixMode(GL_MODELVIEW);

}

void draw() {

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

	glBegin(GL_POINTS);

	int it;
	ManDelBrot mandel(1, 1, 50, 50, WinWid, WinHei);

	for (int x = -WinWid/2; x < WinWid/2; x+=1) {
		for (int y = -WinHei / 2; y < WinHei/2; y+=1) {
			try {
				it = mandel.getIterations(x, y);
			}
			catch (std::out_of_range& ex) {
				std::cout << ex.what();
				break;
			}
			if (it == 100) {
				glColor3b(255, 255, 255);
			}
			else {
				glColor3b(it%2*128, it%4*33, it%2*66);
			}
			glVertex2i(x, y);
			std::cout << it << " ";
		}
		std::cout << '\n';
	}

	glEnd();

	glPopMatrix();

	glutSwapBuffers();

}

void mouse(int button, int state, int x, int y) {
	std::cout << button << " " << state << " " << x << " " << y << "\n";
}

void key(int key, int x, int y) {
	std::cout << key << " " << x << " " << y << '\n';
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(WinWid, WinHei);

	glutInitWindowPosition(400, 150);

	glutCreateWindow("WebWindow");

	glutDisplayFunc(draw);

	glutMouseFunc(mouse);

	glutSpecialFunc(key);

	init();

	glutMainLoop();

}