#if LANGUAGE == CPP
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#endif

#if LANGUAGE == GNUC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#endif

#include <SDL.h>

#ifndef BYTE
#define BYTE unsigned char
#endif