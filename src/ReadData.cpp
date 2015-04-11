#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/device/file.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/bzip2.hpp>
#include <string>
#include "TracedNeighbors.h"
#include "ReadData.h"

#ifdef TESTOUTOFMEMORY
extern bool memoryAllocFail;
#endif

/*
 * Read atom coordinates of oxygen atoms ([O]) from file, storing x, y, and z
 * in vectors.
 * 
 * Chains of atoms are delimited by a marker (ENDOFCHAINMARKER) in each vector.
 */

int ReadData( const char *filename,
              std::vector<double> *Ox,
              std::vector<double> *Oy,
              std::vector<double> *Oz)
{
	char line[256];
	char atom[4];
	double X, Y, Z;
	bool NEWCHAIN = false;

	/*
	 * Make sure Ox, Oy, and Oz are the same size.
	 * They should almost always by of size zero (0).
	 */
	if ( (Ox->size() != Oy->size()) || // don't start off with a marker.
	     (Oy->size() != Oz->size()) ||
	     (Ox->size() != Ox->size()))
	{
		std::cerr << "Error: The three vectors are not all the same size.";
		std::cerr << std::endl;
		return(1);
	}

	// store the 1st 6 bytes of file to determine the filetype (magic number).
	uint8_t magic[6];

	FILE *fp ;
	fp = fopen(filename,"r");

	if( fp == NULL )
	{
		std::perror(filename);
		return(1) ;
	}
	if ( fread(magic, 1, 6, fp) != 6 )
	{
		std::cerr << "Error reading magic number." << std::endl;
		fclose(fp);
		return(1);
	}
	fclose(fp);

	boost::iostreams::filtering_stream<boost::iostreams::input> in;
	std::ifstream ifp;
	if (ifp == NULL)
		return(1);

	// Determine filetype, then use appropriate boost filter.
#ifdef USE_ZLIB
	if ( (magic[0] == 0x1f) && (magic[1] == 0x8b) && (magic[2] == 0x08) )
	{
		// This is a gzip file.
		in.push(boost::iostreams::gzip_decompressor());
		ifp.open(filename,std::ios::in|std::ios::binary);
	}
#endif
#ifdef USE_BZIP2
	if ( (magic[0] == 0x42) && (magic[1] == 0x5a) && (magic[2] == 0x68) )
	{
		// This is a bzip2 file.
		in.push(boost::iostreams::bzip2_decompressor());
		ifp.open(filename,std::ios::in|std::ios::binary);
	}
#endif
	if ( !ifp.is_open() ) // Assume a plain text file if ifp is not open.
		ifp.open(filename,std::ios::in);

	in.push(ifp);

	int n;
	in.getline(line,255);

	int linen=0;
	while ( !in.eof() )
	{
		linen++;
		if ( line[0] != '#' ) // Ignore comment lines.
		{
			n = sscanf( line, "%le %le %le %3s", &X, &Y, &Z, atom);
			if ( n == 4 )
			{
				/*
				 * Ox, Oy, and Oz are all the same size (as verified at the
				 * beginning of the function) so only need to check the size
				 * of one.
				 */
				if ( (Ox->size() != 0) && (NEWCHAIN) )
				{
					try
					{
						Ox->push_back(ENDOFCHAINMARKER);
						Oy->push_back(ENDOFCHAINMARKER);
						Oz->push_back(ENDOFCHAINMARKER);
					}
					catch( std::exception const &e)
					{
						std::cout << "Exception: " << e.what();
						std::cout << ". Ran out of memory?" << std::endl;
						return 1;
					}
				}

				//We have a chain, so set NEWCHAIN to false.
				NEWCHAIN=false;

				// We are only interested in Oxygen atoms
				if (strncmp( atom, "[O]", 3 ) == 0)
				{
					try
					{
						Ox->push_back(X);
						Oy->push_back(Y);
						Oz->push_back(Z);
					}
					catch( std::exception const &e)
					{
						std::cout << "Exception: " << e.what();
						std::cout << ". Ran out of memory?" << std::endl;
						return 1;
					}
				}
			}
			// A blank line indicates a new chain, set the flag.
			else if (strlen(line) == 0 ) { NEWCHAIN=true; }
			/*
			 * Something is weird with this line. Send an error message
			 * and abort reading this file.
			 */
			else
			{
				std::cerr << "Error on line " << linen;
				std::cerr << " of file " << filename << std::endl;
				std::cerr << "Expected 4 arguments, read "<<n<< "."<<std::endl;
				std::cerr << " L" << linen << ": '" << line << "'" << std::endl;
				return(1);
			}
		}
		in.getline(line,255);
	}
	ifp.close();

	// Add ENDOFCHAINMARKER marker to end of vector.
	if ( (Ox->back() != ENDOFCHAINMARKER) && // Don't duplicate the marker.
	     (Oy->back() != ENDOFCHAINMARKER) &&
	     (Oz->back() != ENDOFCHAINMARKER) &&
		 (Ox->size() != 0)     && // and don't start off with a marker.
		 (Oy->size() != 0)     &&
		 (Oz->size() != 0)    )
	{
		try
		{
			Ox->push_back(ENDOFCHAINMARKER);
			Oy->push_back(ENDOFCHAINMARKER);
			Oz->push_back(ENDOFCHAINMARKER);
		}
		catch( std::exception const &e)
		{
			std::cout << "Exception: " << e.what();
			std::cout << ". Ran out of memory?" << std::endl;
			return 1;
		}
	}

	return(0);
}
// vim:tw=76:ts=4:sw=4
