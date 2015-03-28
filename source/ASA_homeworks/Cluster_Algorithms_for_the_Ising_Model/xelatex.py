makefile=open("_build/latex/Makefile","r")
makefiletmp=open("_build/latex/Makefile~","w")

xeCJK="usepackage{xeCJK}\n \\setCJKmainfont[BoldFont=AR PL UKai CN, ItalicFont=AR PL UKai CN]{AR PL UMing CN}\n\\setCJKmonofont[Scale=0.9]{AR PL UKai CN}\n\\setCJKfamilyfont{song}[BoldFont=AR PL UKai CN]{AR PL UMing CN}\n\\setCJKfamilyfont{sf}[BoldFont=AR PL UKai CN]{Droid Sans Fallback}\n\\begin{document}"
texfile=open("_build/latex/ClusterAlgorithmsfortheIsingModel.tex","r")
texfiletmp=open("_build/latex/ClusterAlgorithmsfortheIsingModel.tex~","w")
for l in makefile.readlines():
    l=l.replace('pdflatex','xelatex')
    makefiletmp.write(l)

for l in texfile.readlines():
    l=l.replace("begin{document}",xeCJK)
    texfiletmp.write(l)
import os
os.system("mv _build/latex/Makefile~ _build/latex/Makefile")
os.system("mv _build/latex/ClusterAlgorithmsfortheIsingModel.tex~ _build/latex/ClusterAlgorithmsfortheIsingModel.tex")
