#include <fstream>
#include <iostream>
#include <vector>
#include <string.h>
#include "TracedNeighborsConfig.h"
#include "TracedNeighbors.h"
#include "SimpleMath.h"
#include "Print.h"

void Help(char *name)
{
	fprintf(stdout,"\n%s Version %d.%d\n",
	        name,
	        TraceHBonds_VERSION_MAJOR,
	        TraceHBonds_VERSION_MINOR);

	std::cerr << std::endl;
	std::cerr << "Usage: " << name;
	std::cerr << " -[h] -p <prefix> -s <suffix> -f <1st index #> -l <last index #>" << std::endl;
	std::cerr << std::endl;
	std::cerr << "-p <prefix>   Prefix of filenames to process (e.g. -p HBonds)" <<std::endl;
	std::cerr << "-s <suffix>   Suffix of filenames to process (e.g. -s .txt)" <<std::endl;
	std::cerr << "-f <#>        Initial index of files to process (e.g. -f 1)" <<std::endl;
	std::cerr << "-l <#>        Final index of files to process (e.g. -l 200)" <<std::endl;
	std::cerr << "-h            This help screen." <<std::endl;
	std::cerr << std::endl;
	std::cerr << "With the example values listed above, files HBonds1.txt through" << std::endl;
	std::cerr << " HBonds200.txt would be processed." << std::endl;
	std::cerr << std::endl;
	std::cerr << "Compiled on " << __DATE__;
	std::cerr << " at " << __TIME__ << "." <<std::endl;
	std::cerr << "Author: Brian G. Olson (olsonbg@gmail.com)" <<std::endl;
}

void Print_XYZ( std::vector<double> x,
                std::vector<double> y,
                std::vector<double> z)
{
	if ( (x.size() != y.size() ) ||
	     (x.size() != z.size() ) ||
	     (y.size() != z.size() ) )
	{
		std::cout << "# Error: Vectors not all the same size." << std::endl;
		return;
	}

	unsigned int n = x.size();

	for(unsigned int i=0; i < n; ++i)
		std::cout << x[i] << "\t" << y[i] << "\t" << z[i] << std::endl;

	return;
}

void Print_AllFrames(std::vector<struct s_frame> *frame, unsigned int chains)
{
	for(unsigned int f=0; f< frame->size();++f)
	{
		if (f!=0) std::cout << "\t";
		std::cout << "\t\t" << frame->at(f).filename;
	}
	std::cout << std::endl;

	std::cout << "Atoms in chain\tNth n.n.";
	for(unsigned int f=0; f< frame->size();++f)
		std::cout << "\tCount\tAverage\tStdDev";
	std::cout << std::endl;

	for( unsigned int i = 0; i < chains; i++)
	{
		std::cout <<  2*i+3 << "\t";
		for( unsigned int j=0; j < i+1; j++ )
		{
			if ( j!=0 ) std::cout << " \t";
			std::cout << j+1;
			for( unsigned int f=0; f < frame->size(); ++f)
			{
				double avg = 0.0;
				double err = 0.0;
				unsigned int count = 0.0;
				if ( i < frame->at(f).ChainLength.size() )
				{
					avg = SimpleMath::average(frame->at(f).ChainLength.at(i).Nth[j]);
					err = SimpleMath::stddev(frame->at(f).ChainLength.at(i).Nth[j], avg);
					count = frame->at(f).ChainLength.at(i).Nth[j].size();
				}
				std::cout << "\t" << count << "\t" << avg << "\t" << err;
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

void Print_CombineFrames(std::vector<struct s_frame> *frame, unsigned int chains)
{
	// Combine all frames for an overall average.
	std::cout << "Combining all columns:" << std::endl;
	std::cout << "Atoms in chain\tNth n.n.";
	std::cout << "\tCount\tAverage\tStdDev" << std::endl;

	for( unsigned int i = 0; i < chains; i++)
	{
		std::cout <<  2*i+3 << "\t";
		for( unsigned int j=0; j < i+1; j++ )
		{
			if ( j!=0 ) std::cout << " \t";
			std::cout << j+1;
			double sum=0.0;
			unsigned int count = 0;
			double SumSqDiff = 0.0;
			double avg = 0.0;
			double err = 0.0;

			for( unsigned int f=0; f < frame->size(); ++f)
			{
				if ( i < frame->at(f).ChainLength.size() )
				{
					count += frame->at(f).ChainLength.at(i).Nth[j].size();
					sum += SimpleMath::Sum(frame->at(f).ChainLength.at(i).Nth[j]);
				}
			}
			if (count != 0) avg = sum/count;

			for( unsigned int f=0; f < frame->size(); ++f)
			{
				if ( i < frame->at(f).ChainLength.size() )
					SumSqDiff += SimpleMath::SumSquaredDifferences(frame->at(f).ChainLength.at(i).Nth[j], avg);
			}
			err = SimpleMath::stddev(SumSqDiff,count);

			std::cout << "\t" << count << "\t" << avg << "\t" << err;
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}

void Print_CombineNeighbors(std::vector<struct s_frame> *frame,
                            unsigned int chains)
{
	// Combine all frames and all Nth nearest ChainLengths.
	std::cout << "Combining all columns and Chains:" << std::endl;
	std::cout << "Nth n.n.";
	std::cout << "\tCount\tAverage\tStdDev" << std::endl;

	for( unsigned int j=0; j < chains; j++ )
	{
		std::cout << j+1;
		double sum=0.0;
		unsigned int count = 0;
		double SumSqDiff = 0.0;
		double avg = 0.0;
		double err = 0.0;

		for( unsigned int f=0; f < frame->size(); ++f)
			for( unsigned int i=0; i < frame->at(f).ChainLength.size(); i++)
			{
				if ( j < frame->at(f).ChainLength.at(i).Nth_max )
				{
					count += frame->at(f).ChainLength.at(i).Nth[j].size();
					sum += SimpleMath::Sum(frame->at(f).ChainLength.at(i).Nth[j]);
				}
			}
		if (count != 0) avg = sum/count;

		for( unsigned int f=0; f < frame->size(); ++f)
			for( unsigned int i=0; i < frame->at(f).ChainLength.size(); i++)
			{
				if ( j < frame->at(f).ChainLength.at(i).Nth_max )
				SumSqDiff += SimpleMath::SumSquaredDifferences(frame->at(f).ChainLength.at(i).Nth[j], avg);
			}
		if ( count > 2 ) err = sqrt(SumSqDiff/(count - 2));

		std::cout << "\t" << count << "\t" << avg << "\t" << err;
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

// vim:tw=76:ts=4:sw=2
