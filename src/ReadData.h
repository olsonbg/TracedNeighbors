#ifndef _ReadData_h
#define _ReadData_h

#include<vector>
int ReadData( const char *filename,
              std::vector<double> *Ox,
              std::vector<double> *Oy,
              std::vector<double> *Oz);
#endif
