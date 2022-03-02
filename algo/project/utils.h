#ifndef __UTILS_H__
#define __UTILS_H__

#include <cstdlib>
#include <cmath>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

//----------------------------------------------------------------------------
//	some random number functions.
//----------------------------------------------------------------------------

//returns a random integer between x and y
inline int RandInt(int x,int y){
	return rand()%(y-x+1)+x;
}

//returns a random float between zero and 1
inline float RandFloat(){
	return (rand())/(RAND_MAX+1.0);
}


#endif