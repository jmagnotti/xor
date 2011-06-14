#include "../../xor.h"
#include "Session.h"
#include "CDGrid.h"
#include "Trial.h"
#include "Vector.h"

#include "iostream.h"

using namespace XOR;
using namespace std;

void replaceString(Session * s)
{
    int start           = CDGrid::GetLineUpStartPosition(s->getChoiceDisplaySize());
    int finish          = start + s->getChoiceDisplaySize();
	vector<string> pics = s->getChoiceStimulusFiles();

    int j=0;
    cout << "Trial: " << s->getCurrentTrial() << endl;
    for(int i=start; i<finish; i++) {
        cout << "\tPos: " << i << ", img: " << pics[j] << endl;
        j++;
    }
}

int main() {
    Session * s = Session::GetInstance("mitsTrialsLong.xml", "result.tmp", 1000);

    replaceString(s);
    while (s->nextTrial()) {
        replaceString(s);
    }

    return 0;
}

