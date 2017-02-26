** TITLE:  readme.txt
** PROGRAM: p2p.exe
** AUTHOR: Maryniuk
**
The data set (input file) has a specific format defined by the program Delaunay.exe
with an appropriate output file created by that
application.  It is not possible to modify the contents of that output file without
affecting the purity of the DTM...

3.1  Spatial Extent:
The squared area of the job is displayed.  The domain
displayed should only be used as a guide, and it can at times be deceiving as points
near the extremities of the job may lay outside of the terrain model (the triangulation).
Quearies outside of the dtm will be flagged as undefinable, and a re-prompt will occur.

5.  Interval Size:
Intervals must be in the domain of the natural numbers.

5.1  Line number name:
Can be any character string null terminated.  "r101" is perfectly acceptable.

5.2  Start Station number:
Like the interval size, must be a whole number (it can be negative, but why would you want it to be?)
