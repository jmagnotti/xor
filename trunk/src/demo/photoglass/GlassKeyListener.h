#ifndef GLASSKEYLISTENER_H
#define GLASSKEYLISTENER_H

#include "../../xor.h"
#include "PhotoGlass.h"

using namespace std;
using namespace XOR;

class GlassKeyListener : public DefaultKeyboardListener
{
	public:
		GlassKeyListener(PhotoGlass * photoglass);
		
		// Resets all of the cubes
		void handleKey_F5();
/*
		void handleKey_S();
		void handleKey_A();
		//void handleKey_0();
		void handleKey_3();
//		void handleKey_p();
		void handleKey_a();
	
		void handleKey_d();
		void handleKey_w();
		void handleKey_s();
		void handleKey_q();

		void handleKey_e();
		void handleKey_c();
		void handleKey_z();
*/

		// These four highlight cubes in the grid
		void handleKey_Up();
		void handleKey_Left();
		void handleKey_Down();
		void handleKey_Right();
		
		// vi keybindings 
		void handleKey_k();
		void handleKey_h();
		void handleKey_j();
		void handleKey_l();
	
		// space will bring a photo to the front
		void handleKey_Space();

	private:
		//Controller * _ctrl;
		PhotoGlass * _photoglass;
		
};

#endif

