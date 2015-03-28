function [C,U] = metropolis(m,n,T)
% 用Metropolis 算法计算 m*n的晶格规模的Ising模型在绝对温度为T时的
% magnetic susceptibility.
    k=1;
    beta=1/(k*T);
    J=1;
    %spins=2*round(rand(m,n))-1;
spins=ones(m,n);
    N=1e5;
    H=0;
    Hv=zeros(1,N);
    for i=1:m
        for j=1:(n-1)
            H = H-spins(i,j)*spins(i,j+1);
        end 
        H = H-spins(i,n)*spins(i,1);
    end
    for j=1:n
        for i=1:(m-1)
            H = H-spins(i,j)*spins(i+1,j);
        end 
        H = H-spins(m,j)*spins(1,j);
    end   
 
    x=randi(m,N,1);
    y=randi(n,N,1);
    r=rand(N,1);
    for s=1:N
        i=x(s);
        j=y(s);
        H_new=H;
        I=i;
        if j==n 
            J=1;
        else
            J=j+1;
        end
        H_new=H_new+2*spins(i,j)*spins(I,J);

        I=i;
        if j==1
            J=n;
        else
            J=j-1;
        end
        H_new=H_new+2*spins(i,j)*spins(I,J);
        
        J=j;
        if i==m
            I=1;
        else
            I=i+1;
        end
        H_new=H_new+2*spins(i,j)*spins(I,J);
                            
        J=j;
        if i==1
            I=m;
        else
            I=i-1;
        end
        
        H_new=H_new+2*spins(i,j)*spins(I,J);
        dH=H_new-H;
        if dH <= 0
	    H=H_new;
	    spins(i,j)=-spins(i,j);
        else
            A=exp(-beta*dH);
            if r(s)<=A
        	H=H_new;
        	spins(i,j)=-spins(i,j);
            end
	end
        Hv(s)=H;
        %draw(spins)
        %pause(0.04)
    end
    H2=0;
    H1=0;
    for s=(N/2+1):N
        H=Hv(s);
        H2=H2 + H * H;
        H1=H1 + H;
    end
    H2=2*H2/N;
    H1=2*H1/N;
    C=beta*beta*(H2-H1*H1)/(m*n);
    U=H1/(m*n);
end

function draw(data)
    [dimX,dimY]=size(data);
    clf
    axis([0 dimX 0 dimY])
    for x=1:dimX
        for y=1:dimY
            if data(x,y) == 1
                rectangle('Position', [x-1 y-1 1 1], ...
                          'facecolor','b');
            end
        end
    end
end
