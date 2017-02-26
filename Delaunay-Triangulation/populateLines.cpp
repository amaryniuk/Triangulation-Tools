#include "populateLines.h"

void displayJobArea(vector<Location>& v, double& minE, double& maxE, double& minN, double& maxN)
{
   greatestSpatialExtent(v, minE, maxE, minN, maxN);

   cout << "Job Boundary: Please use these coordinates as your guideline.\n"
        << "Northeast Corner: " << maxE << ", " << maxN
        << "\nSouthwest Corner: " << minE << ", " << minN << endl;   
}

void getNewLine(double& BOLEast, double& BOLNorth, double& EOLEast, double& EOLNorth)
{
   cout << "\nEnter Coordinates of BOL:\n";
   cout << "Enter BOL Easting: ";
   cin >> BOLEast;
   cout << "Enter BOL Northing: ";
   cin >> BOLNorth;
   cout << "\nEnter Coordinates of EOL:\n";
   cout << "Enter EOL Easting: ";
   cin >> EOLEast;
   cout << "Enter EOL Northing: ";
   cin >> EOLNorth;
}

void populateLines(vector<Location>& v, Graph& T)
{
   char a;
   bool again=true;
   double minE=0, maxE=0, minN=0, maxN=0;
   double BOLEast=0, BOLNorth=0, EOLEast=0, EOLNorth=0;

   displayJobArea(v, minE, maxE, minN, maxN);

   do
   {
      getNewLine(BOLEast, BOLNorth, EOLEast, EOLNorth);


      cout << "\nCompute another line? ( y or n )  "; 
      cin >> a;
      if(a=='n') again = false;
   } while (again);

}
