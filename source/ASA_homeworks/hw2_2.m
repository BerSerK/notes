function ans=hw2_2()
for i = 1:10
    res(i)=estimate();
end
ans = mean(res);

end

function ans=estimate()
syms x;
f = sin(pi*x);
I = int(f,0,1);
N = [4,8,16,32,64,128,256,512]*10;
for i = 1:8
    res(i)=I-mc(N(i),f,x);
end
res=abs(double(res));
ans=polyfit(log(N),log(res),1);
ans = -ans(1);
end

function ans=mc(n,f,x)

ans = mean(subs(f,x,rand(n,1)));
end
