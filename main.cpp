//PDYSHA009 main.cpp
#include "Image.h"
#include <iostream>

using namespace std;
using namespace PDYSHA009;

int main(int argc, char* argv[])
{

	cout << "Image processing initiated"<<endl;
	cout<<"\n";
    
    if(argv[1][1]=='a')//add
    {
        Image i1;
        i1.load(argv[2]);
        Image i2;
        i2.load(argv[3]);
        Image i3;
        i3 = i1+i2;
        i3.save(argv[4]);
    }
    else if(argv[1][1]=='s')//subtract
    {
        Image i1;
        i1.load(argv[2]);
        Image i2;
        i2.load(argv[3]);
        Image i3;
        i3 = i1-i2;
        i3.save(argv[4]);
    }
    else if(argv[1][1]=='i')//invert
    {
        Image i1;
        i1.load(argv[2]);
        Image i2;
        i2 = !i1;
        i2.save(argv[3]);
    }
    else if(argv[1][1]=='I')//mask
    {
        Image i1;
        i1.load(argv[2]);
        Image i2;
        i2.load(argv[3]);
        Image i3;
        i3 = i1/i2;
        i3.save(argv[4]);
    }
    else if(argv[1][1]=='t')//threshold
    {
        Image i1;
        i1.load(argv[2]);
        
        int threshold = stoi(argv[3]);
        Image i2;
        i2 = i1*threshold;
        i2.save(argv[4]);
    }

	return 0;
}
