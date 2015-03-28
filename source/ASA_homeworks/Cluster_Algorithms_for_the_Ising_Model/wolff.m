function [C,U] = wolff(m,n,T)
% 用Wolff 算法计算 m*n的晶格规模的Ising模型在绝对温度为T时的
% magnetic susceptibility.
    k=1;%k=8.6173324e-5;
    beta=1/(k*T);
    J=1;
    p=1-exp(-2*beta*J);
    spins=ones(m,n);
    %spins=2*round(rand(m,n))-1;
    N=1e4;
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
    for step=1:N
        mark=zeros(m,n);%用于标记一个点是否在集合C中
        l=0;
        queue=zeros(m*n*2,1);
        i=randi(m);
        j=randi(n);
        l=1;
        queue(2*l-1)=i;
        queue(2*l)=j;
        mark(i,j)=1;
        %先生成翻转子集C
        while l~=0
            i=queue(2*l-1);
            j=queue(2*l);
            l=l-1;
            I=i;
            if j==n 
                J=1;
            else
                J=j+1;
            end
            
            if mark(I,J)==0 && spins(i,j)==spins(I,J) && rand()<p
                l=l+1;
                queue(2*l-1)=I;
                queue(2*l)=J;
                mark(I,J)=1;
            end
            
            I=i;
            if j==1
                J=n;
            else
                J=j-1;
            end
            if mark(I,J)==0 && spins(i,j)==spins(I,J) && rand()<p
                l=l+1;
                queue(2*l-1)=I;
                queue(2*l)=J;
                mark(I,J)=1;
            end
            J=j;
            if i==m
                I=1;
            else
                I=i+1;
            end

            if mark(I,J)==0 && spins(i,j)==spins(I,J) && rand()<p
                l=l+1;
                queue(2*l-1)=I;
                queue(2*l)=J;
                mark(I,J)=1;
            end
            
            J=j;
            if i==1
                I=m;
            else
                I=i-1;
            end
            if mark(I,J)==0 && spins(i,j)==spins(I,J) && rand()<p
                l=l+1;
                queue(2*l-1)=I;
                queue(2*l)=J;
                mark(I,J)=1;
            end

            spins(i,j)=spins(i,j)*(-1);
        end
        %下面修正能量。
        for i=1:m
            for j=1:n
                if mark(i,j)==1
                    I=i;
                    if j==n 
                        J=1;
                    else
                        J=j+1;
                    end
            
                    if mark(I,J)==0 
                        H=H-2*spins(i,j)*spins(I,J);
                    end
                    I=i;
                    if j==1
                        J=n;
                    else
                        J=j-1;
                    end
                    if mark(I,J)==0 
                        H=H-2*spins(i,j)*spins(I,J);
                    end

                    J=j;
                    if i==m
                        I=1;
                    else
                        I=i+1;
                    end
                    if mark(I,J)==0 
                        H=H-2*spins(i,j)*spins(I,J);
                    end
                    
                    J=j;
                    if i==1
                        I=m;
                    else
                        I=i-1;
                    end
                    if mark(I,J)==0 
                        H=H-2*spins(i,j)*spins(I,J);
                    end                    
                end
            end
        end        
        Hv(step)=H;
        %draw(spins)
        %bpause(0.1)
    end
    H2=0;
    H1=0;
    
    for i=(N/2+1):N
        H=Hv(i);
        H2=H2+H*H;
        H1=H1+H;
    end
    H2=2*H2/N;
    H1=2*H1/N;
    C=beta*beta*(H2-H1*H1);
    C=C/(m*n);
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
