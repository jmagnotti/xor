#include "InterpolationDemo.h"
#include <string>

using namespace XOR;

InterpolationDemo::InterpolationDemo(int rows, int cols)
{
	_rows = rows;
	_cols = cols;

	Controller * ctrl = Controller::GetInstance(new NoFogConfig());
	ctrl->getKeyboard()->addListener(new Transformer(this));
	ctrl->getMouse()->addListener(new DefaultMouseListener());

	const float size = 1.0f;
	const int startx = 0;
	const int starty = 0;
	const int offsetx = 1;
	const int offsety = 1;
	float depth = 0.0f;

	cubes = new Transformable3D ** [rows];
	centers = new Vector3D ** [rows];

	Paint * paint = new Paint(Color::WHITE, Paint::HEIGHT_BASED);

	for (int i=0; i < rows; i++)
	{
		cubes[i] = new Transformable3D * [cols];
		centers[i] = new Vector3D * [cols];

		for (int j=0; j < cols; j++)
		{
			float xpos = startx + size*j + j*offsetx;
			float ypos = starty + size*i + i*offsety;

			Paint * p = paint->clone();
			p->setColorFrom(0, (float)(i/(float)rows));
			p->setColorFrom(1, (float)(j/(float)cols));

			cubes[i][j] = new Transformable3D(new Cube(
							new Vector3D(xpos, ypos, depth), size, p));
			centers[i][j] = new Vector3D(xpos + size/2.0, ypos + size/2.0, depth + size/2.0);

			cout << "Cube "<< i << ", "<< j << " at: "<< xpos << " "<< ypos
					<< "\t";
			//            cout << "Center at: " << centers[i][j]->toString() << endl;
		}
		cout << endl << endl;;
	}

	//ctrl->getCamera()->getOrientation()->moveAlongFocalVector(-10);
	//ctrl->getCamera()->getOrientation()->incrementPosition(new Vector3D(0, 0, -10));

	ctrl->setModel(new String2D("Interpolation Demo"));

	Object3DCollection * collection = new Object3DCollection();
	char buffer[rows*cols][10];
	for (int i=0; i<rows; i++)
	{
		for (int j=0; j<cols; j++)
		{
			//cout << i*cols + j << " "; 
			sprintf(buffer[i*cols + j], "%d,%d", i, j);
			ctrl->getModel()->addObject(buffer[i*_cols+j], cubes[i][j]);
		}
		//cout << endl;
	}

	/*
	 Cube * c = new Cube(new Vector3D(1,1,1), 2.0f, new Paint(Color::BLUE));
	 Cube * c2 = new Cube(new Vector3D(1,1,1), 2.0f, new Paint(Color::RED));

	 Transformable3D * cube = new Transformable3D(c);
	 cube->addTransform(Rotate::CreateRotate(360, Rotate::ROLL, 
	 InterpolationDemo::LENGTH, new Vector3D(2.0, 2.0, 2.0)));
	 */

	//ctrl->getModel()->addObject("all", collection);
	// ctrl->getModel()->addObject("all", cube);
}

void InterpolationDemo::run()
{
	Controller::GetInstance()->run();
}

void InterpolationDemo::roll(int which)
{
	World * world = Controller::GetInstance()->getModel();
	Action * left, * right, * down;
	Transformable3D * temp;

	static char buffer[100][10];
	for (int i=0; i < _rows; i++)
	{

		for (int j=0; j < _cols; j++) {
			sprintf(buffer[i*_cols + j], "%d,%d", i, j);

			temp = (Transformable3D*) (world->getObject(buffer[i*_cols+j]));
			if (temp != NULL) {

                srand(time(NULL));      //seed the generator
                int wait = rand() % 1000;

                // move LEFT->DOWN->RIGHT, so we need to create them in the reverse order
                right = new DelayedAction(new MoveAction(buffer[i*_cols+j], new Vector3D(1, 0, 0), NULL), 1000);
                down = new MoveAction(buffer[i*_cols+j], new Vector3D(0, -1, 0), right);
                left = new DelayedAction(new MoveAction(buffer[i*_cols+j], new Vector3D(-1, 0, 0), down), 1000);

                temp->addTransform(Translate::CreateTranslate(new
                            Vector3D(0,1,0), InterpolationDemo::LENGTH, left));

				temp->addTransform(Rotate::CreateRotate (360, Rotate::ROLL,
						InterpolationDemo::LENGTH, centers[i][j]));
				temp->addTransform(Rotate::CreateRotate (360, Rotate::YAW,
						InterpolationDemo::LENGTH, centers[i][j]));
				temp->addTransform(Rotate::CreateRotate (360, Rotate::PITCH,
						InterpolationDemo::LENGTH, centers[i][j]));
			}
			else
			{
				cout << "\tCouldn't find item: "<< buffer[i*_cols+j]<< endl;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	InterpolationDemo * demo = new InterpolationDemo(10,10);
	demo->run();
	return 0;
}

