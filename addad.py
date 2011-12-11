import os
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

code1='''<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-27650007-1']);
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>'''

def ad(f):
    origin=open(f,'r')
    new=open(f+'~','w')
    input=origin.readlines()
    for i in range(len(input)):
	l=input[i]
        new.write(l)
        if '<body>' in l and  i+1<len(input) and 'script' not in input[i+1]:
            new.write(code)
	if i+1<len(input) and '</head>' in input[i+1] and '</script>' not in l:
	    new.write(code1) 
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

