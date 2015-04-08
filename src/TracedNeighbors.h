#ifndef _TracedNeighbors_h
#define _TracedNeighbors_h

#include<vector>
const double ENDOFCHAINMARKER = -99.0;

int doAllFrames(char *, char *fprefix, char *fsuffix, int first, int last);

/*
 * Frame         : File
 *   ChainLength : A Specific chain length
 *     Nth       : Vector containing the Nth nearest ChainLength distances
 */


struct s_ChainLength
{
	/*
	 * 1st element of Nth, Nth[0]:vector of nearest neighbor distances.
	 * 2nd element of Nth, Nth[1]:vector of next nearest neighbor distances.
	 * 3rd element of Nth, Nth[2]:vector of nextnext nearest neighbor distances.
	 * ...
	 * nth element of Nth, Nth[n]:vector of nth nearest neighbor distances.
	 */
	
	std::vector<double> *Nth; // Distances for Nth nearest neighbor
	unsigned int Nth_max;     // Number of Nth elements.
};

struct s_frame
{
	std::vector<struct s_ChainLength> ChainLength;
	int num;
	char *filename;
};


#endif
