**************************************************
MATLAB
**************************************************

handle files::
==================================================

::
 
 % Create a file with an exponential table
 x = 0:.1:1;
 y = [x; exp(x)];

 fid = fopen('exp.txt', 'w');
 fprintf(fid, '%6.2f %12.8f\n', y);
 fclose(fid);

 % Read the data, filling A in column order
 % First line of the file:
 %    0.00    1.00000000

 fid = fopen('exp.txt');
 A = fscanf(fid, '%g %g', [2 inf]);
 fclose(fid);
 
 % Transpose so that A matches
 % the orientation of the file
 A = A';

