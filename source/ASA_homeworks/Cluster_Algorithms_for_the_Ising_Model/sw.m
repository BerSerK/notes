function [C,U] = sw(m,n,T)
% 用Swendsen-Wang 算法计算 m*n的晶格规模的Ising模型在绝对温度为T时的
% magnetic susceptibility.
    k=1;%k=8.6173324e-5;
    beta=1/(k*T);
    J=1;
    p=1-exp(-2*beta*J);
    spins=ones(m,n);%
    %spins=2*round(rand(m,n))-1;
    %bond_vertical(i,j)表示spins(i,j)和spins(i+1,j)之间的bond情况，i=m时
    %j+1表示1
    bond_horizontal = zeros(m,n);
    %bond_horizontal(i,j)表示spins(i,j)和spins(i,j+1)之间的bond情况,j=n时
    %i+1表示1
    bond_vertical = zeros(m,n);
    %mark 用于分组的时候标记一个晶格是否被分组
    mark=zeros(m,n);
    N=1e3;
    Hv=zeros(1,N);
    for step=1:N
        bond_horizontal = zeros(m,n);
        bond_vertical = zeros(m,n);
        %初始化连接
        for i=1:m
            for j=1:n-1
                if spins(i,j)==spins(i,j+1) && rand()<p
                    bond_horizontal(i,j)=1;
                end
            end
            if spins(i,n)==spins(i,1) && rand()<p
                bond_horizontal(i,n)=1;
            end
        end
        for i=1:m-1
            for j=1:n
                if spins(i,j)==spins(i+1,j) && rand()<p
                    bond_vertical(i,j)=1;
                end
            end
        end
        for j=1:n
            if spins(m,j)==spins(1,j) && rand()<p
                bond_vertical(m,j)=1;
            end
        end
        %初始化连接结束，开始分组（cluster）
        mark=zeros(m,n);
        l=0;
        queue=zeros(m*n*2,1);
        for i=1:m
            for j=1:n
                if mark(i,j)==0
                    flip=2*round(rand())-1;
                    l = 1;
                    queue(2*l-1)=i;
                    queue(2*l)=j;
                    mark(i,j)=1;
                    while l ~= 0
                        x=queue(2*l-1);
                        y=queue(2*l);
                        spins(x,y)=spins(x,y)*flip;
                        l=l-1;
                        I=x;
                        if y==n
                            J=1;
                        else
                            J=y+1;
                        end
                        if bond_horizontal(x,y)==1 && mark(I,J)==0
                            l=l+1;
                            queue(2*l-1)=I;
                            queue(2*l)=J;
                            mark(I,J)=1;
                        end
                        
                        I=x;
                        if y==1
                            J=n;
                        else
                            J=y-1;
                        end
                        if bond_horizontal(I,J)==1 && mark(I,J)==0
                            l=l+1;
                            queue(2*l-1)=I;
                            queue(2*l)=J;
                            mark(I,J)=1;
                        end
                   
                        J=y;
                        if x==m
                            I=1;
                        else
                            I=x+1;
                        end
                        if bond_vertical(i,j)==1 && mark(I,J)==0
                            l=l+1;
                            queue(2*l-1)=I;
                            queue(2*l)=J;
                            mark(I,J)=1;
                        end
                        
                        J=y;
                        if x==1
                            I=m;
                        else
                            I=x-1;
                        end
                        if bond_vertical(I,J)==1 && mark(I,J)==0
                            l=l+1;
                            queue(2*l-1)=I;
                            queue(2*l)=J;
                            mark(I,J)=1;
                        end                        
                    end
                end
            end
        end
        %draw(spins)
        %pause(0.04)
        H=energy(spins);
        Hv(step)=H;
    end
    
    H2=0;%能量二阶矩
    H1=0;%能量一阶矩
    for s=(N/2+1):N
        H=Hv(s);
        H2=H2+H*H;
        H1=H1+H;
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

function r=energy(data)
    r=0;
    [dimX,dimY]=size(data);
    for x=1:dimX
        for y=1:dimY-1
            r=r-(data(x,y)*data(x,y+1));
        end 
        r=r-(data(x,dimY)*data(x,1));
    end
    for y=1:dimY
        for x=1:dimX-1
            r=r-(data(x,y)*data(x+1,y));
        end 
        r=r-(data(dimX,y)*data(1,y));
    end 
end
