#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string.h>
#include "TracedNeighborsConfig.h"
#include "TracedNeighbors.h"
#include "SimpleMath.h"
#include "Print.h"
#include "ReadData.h"

int doAllFrames(char *, char *fprefix, char *fsuffix, int first, int last);


// Use CLidx to convert length to ChainLength index number.
inline unsigned int CLidx( unsigned int length )
{
	return( length - 2);
}

// Allocate ChainLength for a chain length of 'length' atoms
bool alloc_chains(std::vector<struct s_ChainLength> *ChainLength,
                 unsigned int length)
{
	/*
	 * Minimum chainlength is 2.
	 *   Use CLidx to convert length to ChainLength index number.
	 * ChainLength[0] == Chainlength of 2 -> Nth_max = 1
	 * ChainLength[1] == Chainlength of 3 -> Nth_max = 2
	 * ChainLength[2] == Chainlength of 4 -> Nth_max = 3
	 * ...
	 */

	unsigned int nelements = CLidx(length)+1;

	for ( unsigned int n=ChainLength->size(); n < nelements; n++)
	{
		struct s_ChainLength Chain;
		Chain.Nth_max = n+1;
		try
		{
			Chain.Nth = new std::vector<double> [Chain.Nth_max];
		}
		catch( std::exception const &e)
		{
			std::cout << "Exception: " << e.what();
			std::cout << ". Ran out of memory?" << std::endl;
			return false;
		}

		try
		{
			ChainLength->push_back(Chain);
		}
		catch( std::exception const &e)
		{
			std::cout << "Exception: " << e.what();
			std::cout << ". Ran out of memory?" << std::endl;
			return false;
		}
	}

	return true;
}

void free_chains(std::vector<struct s_ChainLength> *ChainLength)
{
	for( unsigned int n=0; n< ChainLength->size(); ++n)
		delete[] ChainLength->at(n).Nth;
}

/*
 * Tabulate the end to end distance of all chains in the (x,y,z) vectors,
 * ordered by number of elements in each chain ( ChainLength->at() ) , and Nth
 * nearest neighbor ( ChainLength->at().Nth[] ). The calling function gets the
 * results from the ChainLength variable.
 */
void get_list(std::vector<struct s_ChainLength> *ChainLength,
              std::vector<double> *x,
              std::vector<double> *y,
              std::vector<double> *z)
{
	int first = 0;
	int last = 0;

	for( unsigned int i = 1; i < x->size(); i++)
	{
		if ( (x->at(i) == ENDOFCHAINMARKER) &&
		     (y->at(i) == ENDOFCHAINMARKER) &&
		     (z->at(i) == ENDOFCHAINMARKER) )
		{
			// Found the end of a chain and it has more than one (1) element.
			last = i;

			unsigned int length = last - first; // Length of this chain.

			if ( length > 1 )
			{
				// Index of ChainLength corresponding the 'length.'
				unsigned int c = CLidx(length);

				/*
				 * make sure ChainLength has enough elements, and
				 * allocate space for Nth vector.
				 */
				if ( !alloc_chains(ChainLength, length) )
					return;

				for( unsigned int j=0; j < length-1; j++ )
					for (unsigned int k=j+1; k < length; k++)
					{
						double d = SimpleMath::distance(x->at(first+j),
						                                y->at(first+j),
						                                z->at(first+j),
						                                x->at(first+k),
						                                y->at(first+k),
						                                z->at(first+k));
						// Record Nth nearest neighbor distance. (N=k-j).
						try
						{
							ChainLength->at(c).Nth[k-j-1].push_back(d);
						}
						catch( std::exception const &e)
						{
							std::cout << "Exception: " << e.what();
							std::cout << ". Ran out of memory?" << std::endl;
						}
					}
				}
			// done with this chain; set first counter to just past this chain.
			first = last + 1;
		}
	}
}

int doAllFrames(char *progname, char *fPrefix, char *fSuffix, 
                int first, int last)
{
	unsigned int max_atoms = 0; // Used for printing tables.

	/*
	 * Each element of 'frame' holds the data for a single file.
	 * When running MD simulations, it's not uncommon to have 100s or even
	 * 1000s of files, so 1000s of elements of 'frame' are possible. 
	 */
	std::vector<struct s_frame> frame;
	// Reserve space for the total number of frames (files).
	try
	{
		frame.reserve(last-first+1);
	}
	catch( std::exception const &e)
	{
		std::cout << "Exception: " << e.what();
		std::cout << ". Ran out of memory?" << std::endl;
		return 1;
	}

	std::clock_t readingtime=0;
	std::clock_t processingtime=0;

	std::clock_t start;
	for (int fidx=first; fidx <= last; fidx++)
	{
		std::stringstream filename;
		filename << fPrefix << fidx << fSuffix;

		if (filename == NULL)
		{
			Help(progname);
			return(1);
		}

		/*
		 * Reserve space to prevent reallocation. If more than
		 * 5000 elements, it will start reallocation.
		 */
		std::vector<double> Ox;
		std::vector<double> Oy;
		std::vector<double> Oz;

		try
		{
			Ox.reserve(5000);
			Oy.reserve(5000);
			Oz.reserve(5000);
		}
		catch( std::exception const &e)
		{
			std::cout << "Exception: " << e.what();
			std::cout << ". Ran out of memory?" << std::endl;
			return 1;
		}


		struct s_frame iframe;
		iframe.num = fidx;
		iframe.filename = (char *)malloc(strlen(filename.str().c_str())+1);
		strcpy(iframe.filename, basename((char *)filename.str().c_str()));

		// Reserve space for chains of up to 20 elements long.
		try
		{
			iframe.ChainLength.reserve(20);
		}
		catch( std::exception const &e)
		{
			std::cout << "Exception: " << e.what();
			std::cout << ". Ran out of memory?" << std::endl;
			return 1;
		}

		start = std::clock();
		if( ReadData( filename.str().c_str(), &Ox, &Oy, &Oz ) )
		{
			// Error Reading data!
			// Cleanup: delete each pointer in the vector
			Ox.clear();
			Oy.clear();
			Oz.clear();
			// Skip this file and go to the next one.
			break;
		}
		readingtime += std::clock() - start;

		start = std::clock();
		get_list(&iframe.ChainLength, &Ox, &Oy, &Oz);
		try
		{
			frame.push_back(iframe);
		}
		catch( std::exception const &e)
		{
			std::cout << "Exception: " << e.what();
			std::cout << ". Ran out of memory?" << std::endl;
		}

		if ( max_atoms < iframe.ChainLength.size() )
			max_atoms = iframe.ChainLength.size();

		/*
		 * Cleanup.
		 * delete each pointer in the vector
		 */
		Ox.clear();
		Oy.clear();
		Oz.clear();

		processingtime += std::clock() - start;
	}

	std::cout << "Oxygen neighbor distances." << std::endl;
	std::cout << "n.n. = Nearest neighbor" << std::endl;
	Print_AllFrames(&frame,max_atoms);
	Print_CombineFrames(&frame,max_atoms);
	Print_CombineNeighbors(&frame,max_atoms);

	// Cleanup.
	for( unsigned int i=0; i < frame.size(); i++)
	{
		free_chains(&(frame.at(i).ChainLength));
		free(frame.at(i).filename);
	}

	std::cerr << "Time spent reading data   : " << readingtime / (double)(CLOCKS_PER_SEC/1000) << " ms" << std::endl;
	std::cerr << "Time spent processing data: " << processingtime / (double)(CLOCKS_PER_SEC/1000) << " ms" << std::endl;

	return(0);
}
// vim:tw=76:ts=4:sw=4
