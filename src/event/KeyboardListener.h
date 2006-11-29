#ifndef KEYLISTENER_H
#define KEYLISTENER_H

#include <stdlib.h>

#include "Timer.h"
#include "RegularKeyEvent.h"
#include "SpecialKeyEvent.h"


namespace XOR {

/**
 * Implementer agrees to handle regular key presses as well as "special"
 * ones like PAGE_UP and such
 */
class KeyboardListener
{

public:

	KeyboardListener() { 
        Keyboard::GetInstance()->addListener(this); 
    }

	virtual void handleKey(RegularKeyEvent *)=0;
	virtual void handleKey(SpecialKeyEvent *)=0;

	/**
	 * Regular key handlers
	 */
	inline virtual void handleKeyAscii_1() {}
	inline virtual void handleKeyAscii_2() {}
	inline virtual void handleKeyAscii_3() {}
	inline virtual void handleKeyAscii_4() {}
	inline virtual void handleKeyAscii_5() {}
	inline virtual void handleKeyAscii_6() {}
	inline virtual void handleKeyAscii_7() {}
	inline virtual void handleKeyAscii_8() {}
	inline virtual void handleKeyAscii_9() {}
	inline virtual void handleKeyAscii_10() {}
	inline virtual void handleKeyAscii_11() {}
	inline virtual void handleKeyAscii_12() {}
	inline virtual void handleKeyAscii_13() {}
	inline virtual void handleKeyAscii_14() {}
	inline virtual void handleKeyAscii_15() {}
	inline virtual void handleKeyAscii_16() {}
	inline virtual void handleKeyAscii_17() {}
	inline virtual void handleKeyAscii_18() {}
	inline virtual void handleKeyAscii_19() {}
	inline virtual void handleKeyAscii_20() {}
	inline virtual void handleKeyAscii_21() {}
	inline virtual void handleKeyAscii_22() {}
	inline virtual void handleKeyAscii_23() {}
	inline virtual void handleKeyAscii_24() {}
	inline virtual void handleKeyAscii_25() {}
	inline virtual void handleKeyAscii_26() {}
	inline virtual void handleKeyAscii_27() {}
	inline virtual void handleKeyAscii_28() {}
	inline virtual void handleKeyAscii_29() {}
	inline virtual void handleKeyAscii_30() {}
	inline virtual void handleKeyAscii_31() {}
	inline virtual void handleKeyAscii_32() {}
	inline virtual void handleKeyAscii_33() {}
	inline virtual void handleKeyAscii_34() {}
	inline virtual void handleKeyAscii_35() {}
	inline virtual void handleKeyAscii_36() {}
	inline virtual void handleKeyAscii_37() {}
	inline virtual void handleKeyAscii_38() {}
	inline virtual void handleKeyAscii_39() {}
	inline virtual void handleKeyAscii_40() {}
	inline virtual void handleKeyAscii_41() {}
	inline virtual void handleKeyAscii_42() {}
	inline virtual void handleKeyAscii_43() {}
	inline virtual void handleKeyAscii_44() {}
	inline virtual void handleKeyAscii_45() {}
	inline virtual void handleKeyAscii_46() {}
	inline virtual void handleKeyAscii_47() {}
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
	inline virtual void handleKeyAscii_58() {}
	inline virtual void handleKeyAscii_59() {}
	inline virtual void handleKeyAscii_60() {}
	inline virtual void handleKeyAscii_61() {}
	inline virtual void handleKeyAscii_62() {}
	inline virtual void handleKeyAscii_63() {}
	inline virtual void handleKeyAscii_64() {}
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
	inline virtual void handleKeyAscii_91() {}
	inline virtual void handleKeyAscii_92() {}
	inline virtual void handleKeyAscii_93() {}
	inline virtual void handleKeyAscii_94() {}
	inline virtual void handleKeyAscii_95() {}
	inline virtual void handleKeyAscii_96() {}
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
	inline virtual void handleKeyAscii_123() {}
	inline virtual void handleKeyAscii_124() {}
	inline virtual void handleKeyAscii_125() {}
	inline virtual void handleKeyAscii_126() {}
	inline virtual void handleKeyAscii_127() {}

};

}

#endif			//KEYLISTENER_H

