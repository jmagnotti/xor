#include "DefaultKeyboardListener.h"

namespace XOR {

// set the static instance to 0
DefaultKeyboardListener * DefaultKeyboardListener::_defaultKeyboardListener =
    NULL;


/* 
 * Protected Constructor
 */
DefaultKeyboardListener::DefaultKeyboardListener()
{}


/*
 * handle keys being released.
 */
void DefaultKeyboardListener::handleKeyEvent(KeyEvent * ke)
{
    if (ke->getType() == KeyEvent::KEY_DOWN_EVENT)
        handleKeyDown((KeyDownEvent*)ke);
    else
        handleKeyUp((KeyUpEvent*)ke);

	//cout << ke->toString() << endl;
/*
    cout << "Key stats"             << endl;
    cout << "Shift held down: "     << ke->isShiftPressed()     << endl; 
    cout << "Control held down: "   << ke->isCtrlPressed()      << endl;
    cout << "Alt held down: "       << ke->isAltPressed()       << endl;
    cout << "Meta held down: "      << ke->isMetaPressed()      << endl;
*/
}


void DefaultKeyboardListener::handleKeyUp(KeyUpEvent * kue)
{
	handleKey(kue);
}

     
void DefaultKeyboardListener::handleKeyDown(KeyDownEvent * kde)
{
	// Exit on Esc or Window+q
    if ((kde->getKey() == SDLK_ESCAPE) ||
        (kde->getKey() == SDLK_q && kde->isMetaPressed())) 
	{
        // seems like this should push an exit event
        // #FIXME
        Controller::CleanUpAndExit();
    }
}


/* 
 */
void DefaultKeyboardListener::handleKey(KeyEvent * ke)
{
	bool shift = ke->isShiftPressed();
	
	switch (ke->getKey())
	{
		/* letters (upper- and lower-case are separate events) */
		case SDLK_a: if (shift) handleKey_A(); else handleKey_a(); break; 
		case SDLK_b: if (shift) handleKey_B(); else handleKey_b(); break; 
		case SDLK_c: if (shift) handleKey_C(); else handleKey_c(); break; 
		case SDLK_d: if (shift) handleKey_D(); else handleKey_d(); break; 
		case SDLK_e: if (shift) handleKey_E(); else handleKey_e(); break; 
		case SDLK_f: if (shift) handleKey_F(); else handleKey_f(); break; 
		case SDLK_g: if (shift) handleKey_G(); else handleKey_g(); break; 
		case SDLK_h: if (shift) handleKey_H(); else handleKey_h(); break; 
		case SDLK_i: if (shift) handleKey_I(); else handleKey_i(); break; 
		case SDLK_j: if (shift) handleKey_J(); else handleKey_j(); break; 
		case SDLK_k: if (shift) handleKey_K(); else handleKey_k(); break; 
		case SDLK_l: if (shift) handleKey_L(); else handleKey_l(); break; 
		case SDLK_m: if (shift) handleKey_M(); else handleKey_m(); break; 
		case SDLK_n: if (shift) handleKey_N(); else handleKey_n(); break; 
		case SDLK_o: if (shift) handleKey_O(); else handleKey_o(); break; 
		case SDLK_p: if (shift) handleKey_P(); else handleKey_p(); break; 
		case SDLK_q: if (shift) handleKey_Q(); else handleKey_q(); break; 
		case SDLK_r: if (shift) handleKey_R(); else handleKey_r(); break; 
		case SDLK_s: if (shift) handleKey_S(); else handleKey_s(); break; 
		case SDLK_t: if (shift) handleKey_T(); else handleKey_t(); break; 
		case SDLK_u: if (shift) handleKey_U(); else handleKey_u(); break; 
		case SDLK_v: if (shift) handleKey_V(); else handleKey_v(); break; 
		case SDLK_w: if (shift) handleKey_W(); else handleKey_w(); break; 
		case SDLK_x: if (shift) handleKey_X(); else handleKey_x(); break; 
		case SDLK_y: if (shift) handleKey_Y(); else handleKey_y(); break; 
		case SDLK_z: if (shift) handleKey_Z(); else handleKey_z(); break; 

		/* regular numbers */
        // note that we have to handle the shift case ourselves 
		case SDLK_0: if (shift) handleKey_LParen();    else handleKey_0(); break;
		case SDLK_1: if (shift) handleKey_Exclaim();   else handleKey_1(); break;
		case SDLK_2: if (shift) handleKey_At();        else handleKey_2(); break;
		case SDLK_3: if (shift) handleKey_Hash();      else handleKey_3(); break;
		case SDLK_4: if (shift) handleKey_Dollar();    else handleKey_4(); break;
		case SDLK_5: if (shift) handleKey_Percent();   else handleKey_5(); break;
		case SDLK_6: if (shift) handleKey_Caret();     else handleKey_6(); break;
		case SDLK_7: if (shift) handleKey_Ampersand(); else handleKey_7(); break;
		case SDLK_8: if (shift) handleKey_Asterisk();  else handleKey_8(); break;
		case SDLK_9: if (shift) handleKey_RParen();    else handleKey_9(); break;
		
		/* keypad keys */
		case SDLK_KP0: handleKey_Keypad0(); break;
		case SDLK_KP1: handleKey_Keypad1(); break;
		case SDLK_KP2: handleKey_Keypad2(); break;
		case SDLK_KP3: handleKey_Keypad3(); break;
		case SDLK_KP4: handleKey_Keypad4(); break;
		case SDLK_KP5: handleKey_Keypad5(); break;
		case SDLK_KP6: handleKey_Keypad6(); break;
		case SDLK_KP7: handleKey_Keypad7(); break;
		case SDLK_KP8: handleKey_Keypad8(); break;
		case SDLK_KP9: handleKey_Keypad9(); break;
		case SDLK_KP_PERIOD:	handleKey_KeypadPeriod();	break;
		case SDLK_KP_DIVIDE:	handleKey_KeypadDivide();	break;
		case SDLK_KP_MULTIPLY:	handleKey_KeypadMultiply();	break;
		case SDLK_KP_MINUS:		handleKey_KeypadMinus();	break;
		case SDLK_KP_PLUS:		handleKey_KeypadPlus();		break;
		case SDLK_KP_ENTER:		handleKey_KeypadEnter();	break;
		case SDLK_KP_EQUALS:	handleKey_KeypadEqual();	break;

		/* function keys */
		case SDLK_F1:	 handleKey_F1();	break;
		case SDLK_F2:	 handleKey_F2();	break;
		case SDLK_F3:	 handleKey_F3();	break;
		case SDLK_F4:	 handleKey_F4();	break;
		case SDLK_F5:	 handleKey_F5();	break;
		case SDLK_F6:	 handleKey_F6();	break;
		case SDLK_F7:	 handleKey_F7();	break;
		case SDLK_F8:	 handleKey_F8();	break;
		case SDLK_F9:	 handleKey_F9();	break;
		case SDLK_F10:	 handleKey_F10();	break;
		case SDLK_F11:	 handleKey_F11();	break;
		case SDLK_F12:	 handleKey_F12();	break;

		/* special keys */
		case SDLK_BACKSPACE:	handleKey_Backspace();	break;
		case SDLK_TAB:			handleKey_Tab();		break;
		case SDLK_RETURN:		handleKey_Return();		break;
		case SDLK_ESCAPE:		handleKey_Escape();		break;
		case SDLK_SPACE:		handleKey_Space();		break;

		case SDLK_QUOTE:		handleKey_SnglQuote();	break;
		case SDLK_QUOTEDBL:		handleKey_DblQuote();	break;

        // Do these ever get called?
		case SDLK_BACKQUOTE:	handleKey_BackQuote();	break;
		case SDLK_EXCLAIM:		handleKey_Exclaim();	break;
		case SDLK_AT:			handleKey_At();			break;
		case SDLK_HASH:			handleKey_Hash();		break;
		case SDLK_DOLLAR:		handleKey_Dollar();		break;
		case SDLK_CARET:		handleKey_Caret();		break;
		case SDLK_AMPERSAND:	handleKey_Ampersand();	break;
		case SDLK_ASTERISK:		handleKey_Asterisk();	break;
		case SDLK_LEFTPAREN:	handleKey_LParen();		break;
		case SDLK_RIGHTPAREN:	handleKey_RParen();		break;
        //--

		case SDLK_PLUS:			handleKey_Plus();		break;
		case SDLK_COMMA:		handleKey_Comma();		break;
		case SDLK_MINUS:		handleKey_Minus();		break;
		case SDLK_PERIOD:		handleKey_Period();		break;
		case SDLK_SLASH:		handleKey_FwdSlash();	break;
		case SDLK_COLON:		handleKey_Colon();		break;
		case SDLK_SEMICOLON:	handleKey_Semicolon();	break;
		case SDLK_LESS:			handleKey_Less();		break;
		case SDLK_EQUALS:		handleKey_Equal();		break;
		case SDLK_GREATER:		handleKey_Greater();	break;
		case SDLK_QUESTION:		handleKey_Question();	break;
		case SDLK_LEFTBRACKET:	handleKey_LBracket();	break;
		case SDLK_RIGHTBRACKET:	handleKey_RBracket();	break;
		case SDLK_BACKSLASH:	handleKey_BackSlash();	break;
		case SDLK_UNDERSCORE:	handleKey_Underscore();	break;
		case SDLK_DELETE:		handleKey_Delete();		break;
		case SDLK_UP:			handleKey_Up();			break;
		case SDLK_DOWN:			handleKey_Down();		break;
		case SDLK_LEFT:			handleKey_Left();		break;
		case SDLK_RIGHT:		handleKey_Right();		break;
		case SDLK_INSERT:		handleKey_Insert();		break;
		case SDLK_HOME:			handleKey_Home();		break;
		case SDLK_END:			handleKey_End();		break;
		case SDLK_PAGEUP:		handleKey_PageUp();		break;
		case SDLK_PAGEDOWN:		handleKey_PageDown();	break;
		case SDLK_NUMLOCK:		handleKey_NumLock();	break;
		case SDLK_CAPSLOCK:		handleKey_CapsLock();	break;
		case SDLK_SCROLLOCK:	handleKey_ScrlLock();	break;
		case SDLK_PRINT:		handleKey_PrtScrn();	break;
		case SDLK_SYSREQ:		handleKey_SysReq();		break;
		case SDLK_BREAK:		handleKey_Break();		break;
	}
	
}


void DefaultKeyboardListener::handleKey_w()
{
	//FIXME
	Controller::GetInstance(NULL)->getViewer()->walk(0.5f, new
			TimedInterpolation(1000,NULL));
}

void DefaultKeyboardListener::handleKey_s()
{
	//FIXME
	Controller::GetInstance(NULL)->getViewer()->walk(-0.5f, new
			TimedInterpolation(1000, NULL));
}

/*
void DefaultKeyboardListener::handleKey_q()
{
	Controller::GetInstance()->getViewer()->incrementRotation(2, 5.0f);
}

void DefaultKeyboardListener::handleKey_e()
{
	Controller::GetInstance()->getViewer()->incrementRotation(2, -5.0f);
}

void DefaultKeyboardListener::handleKey_a()
{
	Controller::GetInstance()->getViewer()->incrementRotation(0, -10.0f);
}

void DefaultKeyboardListener::handleKey_d()
{
	Controller::GetInstance()->getViewer()->incrementRotation(0, 10.0f);
}
*/

void DefaultKeyboardListener::handleKey_F()
{
    cout << "Toggle Full Screen" << endl;
	//FIXME
	Controller::GetInstance(NULL)->getViewer()->toggleFullScreen();
}


}

