#ifndef DEFINES_H
#define DEFINES_H


#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <stack>
#include <sstream>

#include "Utils/StrUtils.h"


#define SAFE_DELETE(x)  if (x != NULL) { delete x; x = NULL; }

typedef std::vector< std::vector< int > > vector2int;

#define Vector std::vector
#define debug std::cout


#endif