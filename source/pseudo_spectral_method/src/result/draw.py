import matplotlib
import numpy as np
import os

from matplotlib import cm
import matplotlib.mlab as mlab
import matplotlib.pyplot as plt

fig = plt.figure()

def diff(filea,fileb):
    A=np.loadtxt(filea)
    B=np.loadtxt(fileb)    
    Z=A-B
    dx=2*np.pi/Z.shape[0]
    X=np.arange(0,2*np.pi,dx)
    dy=2*np.pi/Z.shape[1]
    Y=np.arange(0,2*np.pi,dy)
    
    X,Y=np.meshgrid(X,Y)
    #V=np.arange(0,10,1.2);
    CS = plt.contour(X, Y, Z)
    plt.clabel(CS, inline=1, fontsize=10)  
    plt.title(filea+" diff with "+fileb)
    plt.show()
    plt.clf()

    
def draw_contour(filename):
    #print "drawing from "+filename
    Z=np.loadtxt(filename)
    #Z = Z.transpose()
    dx=2*np.pi/Z.shape[0]
    X=np.arange(0,2*np.pi,dx)
    dy=2*np.pi/Z.shape[1]
    Y=np.arange(0,2*np.pi,dy)
    
    X,Y=np.meshgrid(X,Y)
    #V=np.arange(0,10,1.2);
    CS = plt.contour(X, Y, Z)
    plt.clabel(CS, inline=1, fontsize=10)  
    plt.title(filename)
    fig.savefig(filename+".png")
    plt.clf()

def draw_contourf(filename):
    #print "drawing from "+filename
    Z=np.loadtxt(filename)
    #Z = Z.transpose()
    dx=2*np.pi/Z.shape[0]
    X=np.arange(0,2*np.pi,dx)
    dy=2*np.pi/Z.shape[1]
    Y=np.arange(0,2*np.pi,dy)
    
    X,Y=np.meshgrid(X,Y)
    #V=np.arange(0,10,1.2);
    CS = plt.contourf(X, Y, Z)
    plt.title(filename)
    fig.savefig(filename+".png")
    plt.clf()

def show_file(filename):
    #print "drawing from "+filename

    Z=np.loadtxt(filename)
    #Z = Z.transpose()
    dx=2*np.pi/Z.shape[0]
    X=np.arange(0,2*np.pi,dx)
    dy=2*np.pi/Z.shape[1]
    Y=np.arange(0,2*np.pi,dy)
    
    X,Y=np.meshgrid(X,Y)

    CS = plt.contour(X, Y, Z)
    plt.clabel(CS, inline=1, fontsize=10)  
    plt.title(filename)
    fig.savefig(filename+".png")
    plt.show()
    plt.clf()

def show_contourf(filename):
    #print "drawing from "+filename

    Z = np.loadtxt(filename)
    #Z = Z.transpose()
    dx=2*np.pi/Z.shape[0]
    X=np.arange(0,2*np.pi,dx)
    dy=2*np.pi/Z.shape[1]
    Y=np.arange(0,2*np.pi,dy)
    
    X,Y=np.meshgrid(X,Y)
    CS = plt.contourf(X, Y, Z)
    plt.title(filename)
    fig.savefig(filename+".png")
    plt.show()
    plt.clf()


def scp_and_draw(filename):
    os.system("scp alex@jl217ws.3322.org:/home/alex/spectral/src/result/"+filename+" .")
    draw_contourf(filename)

def scp_and_show(filename):
    os.system("scp alex@jl217ws.3322.org:/home/alex/spectral/src/result/"+filename+" .")
    show_file(filename)


files = ["0.txt"]

'''files=["rhoft.txt","rho1.txt","rho2.txt","rho.txt"]
,"u.txt","v.txt"]
'''
def make_movie(name):
    os.system("mencoder 'mf://*.png' -mf type=png:fps=5 -ovc lavc -lavcopts vcodec=wmv2 -oac copy -o "+name+".avi")

if __name__ =="__main__":
    for i in range(0,2020,10):
        scp_and_draw(str(i).zfill(6)+".txt")
        print i
    make_movie("512grid_with0.8time_step")



    
