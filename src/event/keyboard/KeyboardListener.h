#ifndef KEYLISTENER_H
#define KEYLISTENER_H


#include "KeyEvent.h"


namespace XOR {

/**
 * Implementer agrees to handle regular key presses as well as "special"
 * ones like PAGE_UP and such
 */
class KeyboardListener
{

public:

    /**
     * Specifies the interface for key listening.
     */
    virtual void handleKeyEvent(KeyEvent * ke)=0;


protected: 

	/**
	 * Regular key handlers
	 */
	inline virtual void handleKey_0() {}
	inline virtual void handleKey_1() {}
	inline virtual void handleKey_2() {}
	inline virtual void handleKey_3() {}
	inline virtual void handleKey_4() {}
	inline virtual void handleKey_5() {}
	inline virtual void handleKey_6() {}
	inline virtual void handleKey_7() {}
	inline virtual void handleKey_8() {}
	inline virtual void handleKey_9() {}
	inline virtual void handleKey_Keypad0() {}
	inline virtual void handleKey_Keypad1() {}
	inline virtual void handleKey_Keypad2() {}
	inline virtual void handleKey_Keypad3() {}
	inline virtual void handleKey_Keypad4() {}
	inline virtual void handleKey_Keypad5() {}
	inline virtual void handleKey_Keypad6() {}
	inline virtual void handleKey_Keypad7() {}
	inline virtual void handleKey_Keypad8() {}
	inline virtual void handleKey_Keypad9() {}
	inline virtual void handleKey_KeypadPeriod() {}
	inline virtual void handleKey_KeypadDivide() {}
	inline virtual void handleKey_KeypadMultiply() {}
	inline virtual void handleKey_KeypadMinus() {}
	inline virtual void handleKey_KeypadPlus() {}
	inline virtual void handleKey_KeypadEnter() {}
	inline virtual void handleKey_KeypadEqual() {}
	inline virtual void handleKey_A() {}
	inline virtual void handleKey_B() {}
	inline virtual void handleKey_C() {}
	inline virtual void handleKey_D() {}
	inline virtual void handleKey_E() {}
	inline virtual void handleKey_F() {}
	inline virtual void handleKey_G() {}
	inline virtual void handleKey_H() {}
	inline virtual void handleKey_I() {}
	inline virtual void handleKey_J() {}
	inline virtual void handleKey_K() {}
	inline virtual void handleKey_L() {}
	inline virtual void handleKey_M() {}
	inline virtual void handleKey_N() {}
	inline virtual void handleKey_O() {}
	inline virtual void handleKey_P() {}
	inline virtual void handleKey_Q() {}
	inline virtual void handleKey_R() {}
	inline virtual void handleKey_S() {}
	inline virtual void handleKey_T() {}
	inline virtual void handleKey_U() {}
	inline virtual void handleKey_V() {}
	inline virtual void handleKey_W() {}
	inline virtual void handleKey_X() {}
	inline virtual void handleKey_Y() {}
	inline virtual void handleKey_Z() {}
	inline virtual void handleKey_a() {}
	inline virtual void handleKey_b() {}
	inline virtual void handleKey_c() {}
	inline virtual void handleKey_d() {}
	inline virtual void handleKey_e() {}
	inline virtual void handleKey_f() {}
	inline virtual void handleKey_g() {}
	inline virtual void handleKey_h() {}
	inline virtual void handleKey_i() {}
	inline virtual void handleKey_j() {}
	inline virtual void handleKey_k() {}
	inline virtual void handleKey_l() {}
	inline virtual void handleKey_m() {}
	inline virtual void handleKey_n() {}
	inline virtual void handleKey_o() {}
	inline virtual void handleKey_p() {}
	inline virtual void handleKey_q() {}
	inline virtual void handleKey_r() {}
	inline virtual void handleKey_s() {}
	inline virtual void handleKey_t() {}
	inline virtual void handleKey_u() {}
	inline virtual void handleKey_v() {}
	inline virtual void handleKey_w() {}
	inline virtual void handleKey_x() {}
	inline virtual void handleKey_y() {}
	inline virtual void handleKey_z() {}
	inline virtual void handleKey_F1() {}
	inline virtual void handleKey_F2() {}
	inline virtual void handleKey_F3() {}
	inline virtual void handleKey_F4() {}
	inline virtual void handleKey_F5() {}
	inline virtual void handleKey_F6() {}
	inline virtual void handleKey_F7() {}
	inline virtual void handleKey_F8() {}
	inline virtual void handleKey_F9() {}
	inline virtual void handleKey_F10() {}
	inline virtual void handleKey_F11() {}
	inline virtual void handleKey_F12() {}
	inline virtual void handleKey_Backspace() {}
	inline virtual void handleKey_Tab() {}
	inline virtual void handleKey_Return() {}
	inline virtual void handleKey_Escape() {}
	inline virtual void handleKey_Space() {}
	inline virtual void handleKey_Exclaim() {}
	inline virtual void handleKey_DblQuote() {}
	inline virtual void handleKey_Hash() {}
	inline virtual void handleKey_Dollar() {}
	inline virtual void handleKey_Ampersand() {}
	inline virtual void handleKey_SnglQuote() {}
	inline virtual void handleKey_LParen() {}
	inline virtual void handleKey_RParen() {}
	inline virtual void handleKey_Asterisk() {}
	inline virtual void handleKey_Plus() {}
	inline virtual void handleKey_Comma() {}
	inline virtual void handleKey_Minus() {}
	inline virtual void handleKey_Period() {}
	inline virtual void handleKey_FwdSlash() {}
	inline virtual void handleKey_Colon() {}
	inline virtual void handleKey_Semicolon() {}
	inline virtual void handleKey_Less() {}
	inline virtual void handleKey_Equal() {}
	inline virtual void handleKey_Greater() {}
	inline virtual void handleKey_Question() {}
	inline virtual void handleKey_At() {}
	inline virtual void handleKey_LBracket() {}
	inline virtual void handleKey_RBracket() {}
	inline virtual void handleKey_BackSlash() {}
	inline virtual void handleKey_Caret() {}
	inline virtual void handleKey_Underscore() {}
	inline virtual void handleKey_BackQuote() {}
	inline virtual void handleKey_Delete() {}
	inline virtual void handleKey_Up() {}
	inline virtual void handleKey_Down() {}
	inline virtual void handleKey_Left() {}
	inline virtual void handleKey_Right() {}
	inline virtual void handleKey_Insert() {}
	inline virtual void handleKey_Home() {}
	inline virtual void handleKey_End() {}
	inline virtual void handleKey_PageUp() {}
	inline virtual void handleKey_PageDown() {}
	inline virtual void handleKey_NumLock() {}
	inline virtual void handleKey_CapsLock() {}
	inline virtual void handleKey_ScrlLock() {}
	inline virtual void handleKey_PrtScrn() {}
	inline virtual void handleKey_SysReq() {}
	inline virtual void handleKey_Break() {}

};

}

#endif			//KEYLISTENER_H

