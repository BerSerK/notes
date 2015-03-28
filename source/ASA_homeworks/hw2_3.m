function hw2_3()
    
    num =10000;
    subplot(2,2,1);
    [a,b,c]=sphere();
    mesh(a,b,c);
    hold
    Title('Method a');
    tic
    [x,y,z]=sphere1(num);
    toc
    plot3(x,y,z,'.');


    subplot(2,2,2);
    [a,b,c]=sphere();
    mesh(a,b,c);
    hold
    Title('Method b');
    tic
    [x,y,z]=sphere2(num);
    toc
    plot3(x,y,z,'.');
    
    subplot(2,2,3);
    [a,b,c]=sphere();
    mesh(a,b,c);
    hold
    Title('Method c');
    tic
    [x,y,z]=sphere3(num);
    toc
    plot3(x,y,z,'.');
end

function [x,y,z]=sphere1(n)
    x=zeros(1,n);
    y=zeros(1,n);
    z=zeros(1,n);
    for i=1:n
        theta = 2*pi*rand;
        phi = acos(1-2*rand);
        s = sin(phi);
        x(i) = cos(theta)*s;
        y(i) = sin(theta)*s;
        z(i) = cos(phi);
    end
end

function [x,y,z]=sphere2(n)

    x=zeros(1,n);
    y=zeros(1,n);
    z=zeros(1,n);
    for i=1:n

        theta = 2*pi*rand;
        u = rand*2-1;
        s = sqrt(1-u^2);
        x(i) = s*cos(theta);
        y(i) = s*sin(theta);
        z(i) = u;
    end
    
end

function [x,y,z]=sphere3(n)

    x=zeros(1,n);
    y=zeros(1,n);
    z=zeros(1,n);
    for i=1:n
        
        x1 =2*rand-1;
        x2 =2*rand-1;
        p = x1^2+x2^2;
        while p>=1 
            x1 =2*rand-1;
            x2 =2*rand-1;
            p = x1^2+x2^2;
        end
        s =sqrt(1-p);
        x(i) = 2*x1*s;
        y(i) = 2*x2*s;
        z(i) = 1-2*p;    
    end
end