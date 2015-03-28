N=100;
R=10;
T=R/N:R/N:R;
T=T;
C=zeros(1,N);
U=zeros(1,N);

for i=1:N
    i
    [C(i),U(i)] = metropolis(50,50,T(i));
end

subplot(2,1,1)
plot(T,C,'o')
title('T-C')
subplot(2,1,2)
plot(T,U,'o')
title('T-U')

saveas(gcf,'metropolis1e6.png','png')

