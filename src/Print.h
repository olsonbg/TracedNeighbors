#ifndef _Print_h
#define _Print_h
#include <vector>
#include <math.h>
#include "TracedNeighbors.h"
#include "SimpleMath.h"

/*
 * Frame         : File
 *   ChainLength : A Specific chain length
 *     Nth       : Vector containing the Nth nearest ChainLength distances
 */

void Print_XYZ( std::vector<double> x,
                std::vector<double> y,
                std::vector<double> z);

void Print_AllFrames(std::vector<struct s_frame> *frame,
                     unsigned int max);
void Print_CombineFrames(std::vector<struct s_frame> *frame,
                         unsigned int max);
void Print_CombineNeighbors(std::vector<struct s_frame> *frame,
                            unsigned int max);
void Help(char *callname);

#endif
// vim:tw=76:ts=4:sw=2
