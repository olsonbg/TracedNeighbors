#include <cstdlib>
#include <unistd.h>
#include "TracedNeighbors.h"
#include "Print.h"

int main(int argc, char *argv[])
{
	char *fPrefix     = NULL; // Prefix for filename.
	char *fSuffix     = NULL; // Suffix for filename.
	int   fidx_f      = 0;    // First number for file index.
	int   fidx_l      = 0;    // Last number for file index.
	bool  flag_fidx_f = false;// Flag indicating whether fidx_f is defined.
	bool  flag_fidx_l = false;// Flag indicating whether fidx_l is defined.


	// Read command line arguments.
	int c;
	while ((c = getopt (argc, argv, "p:s:f:l:h")) != -1)
		switch (c)
		{
			case 'p':
				fPrefix = optarg;
				break;
			case 's':
				fSuffix = optarg;
				break;
			case 'f':
				fidx_f = atoi(optarg);
				flag_fidx_f = true;
				break;
			case 'l':
				fidx_l = atoi(optarg);
				flag_fidx_l = true;
				break;
			case 'h':
			case '?':
			default:
				Help(argv[0]);
				return(1);
		}

	if ( (flag_fidx_f == false) ||
	     (flag_fidx_l == false) ||
	     (fidx_l < fidx_f)      ||
	     (fidx_l < 0)           ||
	     (fidx_f < 0)          )
	{
		Help(argv[0]);
		return(1);
	}

	// Done reading command line arguments
	int retval=doAllFrames(argv[0],fPrefix, fSuffix, fidx_f, fidx_l);

	return(retval);
}

// vim:tw=76:ts=4:sw=2
