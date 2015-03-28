fid = fopen('a.txt');
A=ones(512,512);
for i=1:512
A(i,:)=fscanf(fid, '%f\t',512);
end

contourf(A);
title('serial');
fclose(fid);

