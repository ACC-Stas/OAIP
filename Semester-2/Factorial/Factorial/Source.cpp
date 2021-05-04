#include <iostream>
#include <ccomplex>
#include <Windows.h>
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
		this->NumberOfXPixels = NumberOfXPixels;
		this->NumberOfYPixels = NumberOfYPixels;
		this->centreX = centreX;
		this->centreY = centreY;
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
int currentX = 0, currentY = 0;
double depth = 4;
int bypasStep = 4;

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
	ManDelBrot mandel(depth, depth, currentX, currentY, WinWid, WinHei);

	for (int x = -WinWid/2; x < WinWid/2; x+=bypasStep) {
		for (int y = -WinHei / 2; y < WinHei/2; y+=bypasStep) {
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
			//std::cout << it << " ";
		}
		//std::cout << '\n';
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
	switch (key) {
	case 100:  //left arrow
		currentX -= 50;
		draw();
		break;
	case 101:
		currentY += 50;
		draw();
		break;
	case 102:
		currentX += 50;
		draw();
		break;
	case 103:
		currentY -= 50;
		draw();
		break;
	case 104:  //page up
		if (bypasStep >= 2) {
			bypasStep--;
			draw();
		}
		break;
	case 105:  //page down
		bypasStep++;
		draw();
		break;
	case 107:  //end
		exit(0);
		break;
	default:
		break;
	}
}

void charKey(unsigned char key, int x, int y) {
	std::cout << (int)key << " " << x << " " << y << '\n';
	switch ((int)key) {
	case '+':
		depth /= 2;
		draw();
		break;
	case '-':
		depth *= 2;
		draw();
		break;
	case 1:  //ctrl + a
		if (WinWid < 1900) {
		WinWid += 100;
		draw();
	}
	break;
	case 19:  //ctrl + s
		if (WinWid >= 200) {
			WinWid -= 100;
			draw();
		}
		break;
	case 17: //ctrl + q
		if (WinHei < 900) {
			WinHei += 100;
			draw();
		}
		break;
	case 23: //ctrl + w
		if (WinHei >= 200) {
			WinHei -= 100;
			draw();
		}
		break;
	default:
		break;
	}
}

int main(int argc, char** argv) {

	HWND hConsole = GetConsoleWindow();//Если компилятор старый заменить на GetForegroundWindow()
	ShowWindow(hConsole, SW_HIDE);//собственно прячем оконо консоли

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(WinWid, WinHei);

	glutInitWindowPosition(0, 0);

	glutCreateWindow("WebWindow");

	glutDisplayFunc(draw);

	glutMouseFunc(mouse);

	glutSpecialFunc(key);

	glutKeyboardFunc(charKey);

	init();

	glutMainLoop();

}