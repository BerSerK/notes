import os
code='''<script data-ad-client="ca-pub-7043162859045080" async src="https://pagead2.googlesyndication.com/pagead/js/adsbygoogle.js"></script>'''


def ad(f):
	origin=open(f,'r')
	new=open(f+'~','w')
	input=origin.readlines()
	for i in range(len(input)):
		l=input[i]
		new.write(l)
		if '<head>' in l and  i+1<len(input) and 'pagead' not in input[i+1]:
			new.write(code)
	os.system('mv '+f+'~ '+f)
def checkpath(path):
    if os.path.isdir(path):
        dirlist=os.listdir(path)
        for i in dirlist:
            checkpath(path+'/'+i)
    else:
        if path[-5:] =='.html':
            ad(path)

checkpath('./build/html/')

