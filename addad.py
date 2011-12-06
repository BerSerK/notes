import os
dirlist=os.listdir('./build/html/')
code='''<script type="text/javascript"><!--
google_ad_client = "ca-pub-7043162859045080";
/* notes */
google_ad_slot = "1612399913";
google_ad_width = 1103;
google_ad_height = 90;
//-->
</script>
<script type="text/javascript"
src="http://pagead2.googlesyndication.com/pagead/show_ads.js">
</script>'''

def ad(f):
    origin=open(f,'r')
    new=open(f+'~','w')
    for l in origin.readlines():
        new.write(l)
        if '<body>' in l:
            new.write(code)
    os.system('mv '+f+'~ '+f)

for f in dirlist:
    if f[-5:] =='.html':
        ad('./build/html/'+f)
