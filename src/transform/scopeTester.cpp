#include <iostream>


using namespace std;

class Tester
{
    public:

        Tester(int x, int y, int z)
        {
            a = x;
            b = y;
            c = z;
        } 

        void clone(Tester * other)
        {
            a = other->a;
            b = other->b;
            c = other->c; 
        }

        void print()
        {
            cout << a << " " << b << " " << c << endl;
        }
        
    protected:
        int a,b,c;
};


int main()
{
    Tester * a = new Tester(1,2,3);
    Tester * b = new Tester(4,5,6);
    
    cout << "values before clone for Tester: " << endl;
    a->print();

    cout << "values before clone for B: " << endl;
    b->print();

    a->clone(b);
   
    cout << "new values for a: " << endl;
    a->print();

    return 0;
}

