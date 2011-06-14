#include "../../xor.h"
#include "Session.h"
#include "Trial.h"

#include <fstream>
#include <iostream>

#include "stdio.h"

using namespace XOR;
using namespace std;

double offset;

Session *s;


void printEncode()
{
    ofstream fout("encode.txt", ios::app);
    fout << " " << offset; // << "*" << s->getSampleDisplaySize();
    fout.close();
}


void printDelay()
{
    ofstream fout("delay.txt", ios::app);
    fout << " " << offset;
    fout.close();
}

void printDecide()
{
    ofstream fout("decide.txt", ios::app);
    fout << " " << offset; //<< "*" << s->getChoiceDisplaySize();
    fout.close();
}

void printChoice()
{
    ofstream fout("choice.txt", ios::app);
    fout << " " << offset; // << "*" << s->getChoiceDisplaySize();
    fout.close();
}



int main() {
    //s = Session::GetInstance("fmriTrials001.xml", "result.tmp");
    s = Session::GetInstance("fmriTrials002.xml", "result.tmp");

    double tr = 1.58; 
    offset = tr * 4;
     
    int steps=0;
    while (s->nextTrial()) {
        steps = s->getSampleDisplayDuration();
        while(steps>0) { printEncode(); offset+=tr; steps--; }

        steps = s->getRetentionInterval();
        while(steps>0) { printDelay(); offset+=tr; steps--; }

        steps = s->getDecideDuration();
        while(steps>0) { printDecide(); offset+=tr; steps--; }

        steps = s->getChoiceDuration();
        while(steps>0) { printChoice(); offset+=tr; steps--; }

        steps = s->getInterTrialInterval();
        while(steps>0) { offset+=tr; steps--; }
    }

    ofstream fout0("encode.txt", ios::app);
    fout0 << "\n";
    fout0.close();

    ofstream fout3("delay.txt", ios::app);
    fout3 << "\n";
    fout3.close();

    ofstream fout1("decide.txt", ios::app);
    fout1 << "\n";
    fout1.close();

    ofstream fout2("choice.txt", ios::app);
    fout2 << "\n";
    fout2.close();
    
/*
    cout << "offset: " << offset;
    s = Session::GetInstance("fmriTrials002.xml", "result.tmp");
    offset = tr * 4;

     
    steps=0;
    while (s->nextTrial()) {
        steps = s->getSampleDisplayDuration();
        while(steps>0) { printEncode(); offset+=tr; steps--; }
        steps = s->getRetentionInterval();
        while(steps>0) { printDelay(); offset+=tr; steps--; }
        printChoice(); offset+=tr;
        steps = s->getInterTrialInterval();
        while(steps>0) { offset+=tr; steps--; }
    }
*/
    
    return 0;
}

