#include <fstream>
#include <vector>
#include <time.h>
#include <conio.h>
#include "getInput.h"

int main()
{
  // File IO Stuff
  fstream infile;
  fstream outfile;
  char fname[LONG_STR];
  char outname[LONG_STR];

  // Other Locals
  int i=0, j=0, ecode=0;
  int count=0;
  double time=0, start=0, end=0;
  vector<Location> v;

  cout.setf(ios::fixed);
  cout.precision(3);

  startup(fname, infile, ecode);

  if (ecode)	// open successful?
    {
      cout << "Fatal error encountered: " << ecode << endl;
      cout << "Press any key to continue";
      while(1)
         if(kbhit())
            break;
      exit(-1);
    }

  start=clock();

  loadLocations(infile, v);
  end=clock(); time=end-start; time/=CLOCKS_PER_SEC;
  cout << "Time: " << time << endl << endl;

  time=0; start=0; end=0;
  start=clock();

  cleanse(v);

  end=clock();
  time=end-start; time/=CLOCKS_PER_SEC;
  cout << "Time: " << time << endl;

  finish(infile, outfile, outname, v);

  cout << "Press any key to continue";
  while(1)
     if(kbhit())
        break;

  return 0;
}
