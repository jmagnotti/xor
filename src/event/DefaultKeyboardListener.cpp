#include "DefaultKeyboardListener.h"

namespace XOR {

// set the static instance to 0
DefaultKeyboardListener * DefaultKeyboardListener::_defaultKeyboardListener = 0;


/* 
 * Protected Constructor
 */
DefaultKeyboardListener::DefaultKeyboardListener()
{}


/*
 * Singleton accessor
 */
DefaultKeyboardListener * DefaultKeyboardListener::GetInstance()
{
	if (_defaultKeyboardListener == NULL)
		_defaultKeyboardListener = new DefaultKeyboardListener();

	return _defaultKeyboardListener;
}


/* 
 * Handle ascii
 * Note that ESC is ascii 0x1B
 */
void DefaultKeyboardListener::handleKey(RegularKeyEvent* rke)
{
	switch (rke->getKeyPressed()) {
		case 1: 	handleKeyAscii_1();  	break;
		case 2: 	handleKeyAscii_2();  	break;
		case 3: 	handleKeyAscii_3();  	break;
		case 4: 	handleKeyAscii_4();  	break;
		case 5: 	handleKeyAscii_5();  	break;
		case 6: 	handleKeyAscii_6();  	break;
		case 7: 	handleKeyAscii_7();  	break;
		case 8: 	handleKeyAscii_8();  	break;
		case 9: 	handleKeyAscii_9();  	break;
		case 10: 	handleKeyAscii_10();  	break;
		case 11: 	handleKeyAscii_11();  	break;
		case 12: 	handleKeyAscii_12();  	break;
		case 13: 	handleKeyAscii_13();  	break;
		case 14: 	handleKeyAscii_14();  	break;
		case 15: 	handleKeyAscii_15();  	break;
		case 16: 	handleKeyAscii_16();  	break;
		case 17: 	handleKeyAscii_17();  	break;
		case 18: 	handleKeyAscii_18();  	break;
		case 19: 	handleKeyAscii_19();  	break;
		case 20: 	handleKeyAscii_20();  	break;
		case 21: 	handleKeyAscii_21();  	break;
		case 22: 	handleKeyAscii_22();  	break;
		case 23: 	handleKeyAscii_23();  	break;
		case 24: 	handleKeyAscii_24();  	break;
		case 25: 	handleKeyAscii_25();  	break;
		case 26: 	handleKeyAscii_26();  	break;
		case 27: 	handleKeyAscii_27();  	break;
		case 28: 	handleKeyAscii_28();  	break;
		case 29: 	handleKeyAscii_29();  	break;
		case 30: 	handleKeyAscii_30();  	break;
		case 31: 	handleKeyAscii_31();  	break;
		case 32: 	handleKeyAscii_32();  	break;
		case 33: 	handleKeyAscii_33();  	break;
		case 34: 	handleKeyAscii_34();  	break;
		case 35: 	handleKeyAscii_35();  	break;
		case 36: 	handleKeyAscii_36();  	break;
		case 37: 	handleKeyAscii_37();  	break;
		case 38: 	handleKeyAscii_38();  	break;
		case 39: 	handleKeyAscii_39();  	break;
		case 40: 	handleKeyAscii_40();  	break;
		case 41: 	handleKeyAscii_41();  	break;
		case 42: 	handleKeyAscii_42();  	break;
		case 43: 	handleKeyAscii_43();  	break;
		case 44: 	handleKeyAscii_44();  	break;
		case 45: 	handleKeyAscii_45();  	break;
		case 46: 	handleKeyAscii_46();  	break;
		case 47: 	handleKeyAscii_47();  	break;
		case 48: 	handleKey_0();  		break;
		case 49: 	handleKey_1();  		break;
		case 50: 	handleKey_2();  		break;
		case 51: 	handleKey_3();  		break;
		case 52: 	handleKey_4();  		break;
		case 53: 	handleKey_5();  		break;
		case 54: 	handleKey_6();  		break;
		case 55: 	handleKey_7();  		break;
		case 56: 	handleKey_8();  		break;
		case 57: 	handleKey_9();  		break;
		case 58: 	handleKeyAscii_58();  	break;
		case 59: 	handleKeyAscii_59();  	break;
		case 60: 	handleKeyAscii_60();  	break;
		case 61: 	handleKeyAscii_61();  	break;
		case 62: 	handleKeyAscii_62();  	break;
		case 63: 	handleKeyAscii_63();  	break;
		case 64: 	handleKeyAscii_64();  	break;
		case 65: 	handleKey_A();  		break;
		case 66: 	handleKey_B();  		break;
		case 67: 	handleKey_C();  		break;
		case 68: 	handleKey_D();  		break;
		case 69: 	handleKey_E();  		break;
		case 70: 	handleKey_F();  		break;
		case 71: 	handleKey_G();  		break;
		case 72: 	handleKey_H();  		break;
		case 73: 	handleKey_I();  		break;
		case 74: 	handleKey_J();  		break;
		case 75: 	handleKey_K();  		break;
		case 76: 	handleKey_L();  		break;
		case 77: 	handleKey_M();  		break;
		case 78: 	handleKey_N();  		break;
		case 79: 	handleKey_O();  		break;
		case 80: 	handleKey_P();  		break;
		case 81: 	handleKey_Q();  		break;
		case 82: 	handleKey_R();  		break;
		case 83: 	handleKey_S();  		break;
		case 84: 	handleKey_T();  		break;
		case 85: 	handleKey_U();  		break;
		case 86: 	handleKey_V();  		break;
		case 87: 	handleKey_W();  		break;
		case 88: 	handleKey_X();  		break;
		case 89: 	handleKey_Y();  		break;
		case 90: 	handleKey_Z();  		break;
		case 91: 	handleKeyAscii_91();  	break;
		case 92: 	handleKeyAscii_92();  	break;
		case 93: 	handleKeyAscii_93();  	break;
		case 94: 	handleKeyAscii_94();  	break;
		case 95: 	handleKeyAscii_95();  	break;
		case 96: 	handleKeyAscii_96();  	break;
		case 97: 	handleKey_a();  		break;
		case 98: 	handleKey_b();  		break;
		case 99: 	handleKey_c();  		break;
		case 100: 	handleKey_d();  		break;
		case 101: 	handleKey_e();  		break;
		case 102: 	handleKey_f();  		break;
		case 103: 	handleKey_g();  		break;
		case 104: 	handleKey_h();  		break;
		case 105: 	handleKey_i();  		break;
		case 106: 	handleKey_j();  		break;
		case 107: 	handleKey_k();  		break;
		case 108: 	handleKey_l();  		break;
		case 109: 	handleKey_m();  		break;
		case 110: 	handleKey_n();  		break;
		case 111: 	handleKey_o();  		break;
		case 112: 	handleKey_p();  		break;
		case 113: 	handleKey_q();  		break;
		case 114: 	handleKey_r();  		break;
		case 115: 	handleKey_s();  		break;
		case 116: 	handleKey_t();  		break;
		case 117: 	handleKey_u();  		break;
		case 118: 	handleKey_v();  		break;
		case 119: 	handleKey_w();  		break;
		case 120: 	handleKey_x();  		break;
		case 121: 	handleKey_y();  		break;
		case 122: 	handleKey_z();  		break;
		case 123: 	handleKeyAscii_123();  	break;
		case 124: 	handleKeyAscii_124();  	break;
		case 125: 	handleKeyAscii_125();  	break;
		case 126: 	handleKeyAscii_126();  	break;
		case 127: 	handleKeyAscii_127();  	break;
	}
}


/* 
 * Handle non ascii
 */
void DefaultKeyboardListener::handleKey(SpecialKeyEvent* ske)
{}


void DefaultKeyboardListener::handleKey_w()
{
	Controller::GetInstance()->getViewer()->getOrientation()->walk(0.05f);
}

void DefaultKeyboardListener::handleKey_s()
{
	Controller::GetInstance()->getViewer()->getOrientation()->walk(-0.05f);
}

void DefaultKeyboardListener::handleKey_q()
{
	Controller::GetInstance()->getViewer()->getOrientation()->incrementRotation(2, 5.0f);
}

void DefaultKeyboardListener::handleKey_e()
{
	Controller::GetInstance()->getViewer()->getOrientation()->incrementRotation(2, -5.0f);
}

void DefaultKeyboardListener::handleKey_F()
{
	Controller::GetInstance()->getViewer()->toggleFullScreen();
}

void DefaultKeyboardListener::handleKeyAscii_27()
{
	Controller::CleanUpAndExit();
}

}

