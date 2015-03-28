#log# Automatic Logger file. *** THIS MUST BE THE FIRST LINE ***
#log# DO NOT CHANGE THIS LINE OR THE TWO BELOW
#log# opts = Struct({'__allownew': True, 'logfile': 'ipython_log.py'})
#log# args = []
#log# It is safe to make manual edits below here.
#log#-----------------------------------------------------------------------
_ip.magic("logstart ")

from scipy import *
a=zeros(1000)
a[:100]=1
b=fft(a)
b
plot(abs(b))
from pylab import *
plot(abs(b))
show()
show()
show()
show()
show()
show()
exit()
