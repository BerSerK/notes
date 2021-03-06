.. _sphinx:

******************************
用python的Sphinx工具整理笔记
******************************

.. _introduction:

sphinx介绍
====================

rst（reStructuredText）标记语言
--------------------------------------------------

使用sphinx必须得会用`rst <http://docutils.sourceforge.net/docs/user/rst/quickref.html>`_ 标记语言写文本。
这个可以通过这个文档在半个小时内基本上手： http://docutils.sourceforge.net/docs/user/rst/quickref.html

sphinx
--------------------------------------------------
然后通过 http://sphinx.pocoo.org/ 可以了解sphinx的使用细节。


Using xelatex in Sphinx
===============================

add the script in the root directory::

 from conf import latex_documents
 
 from tempfile import mkstemp
 from shutil import move
 from os import remove, close
 
 def replace(file, pattern, subst):
     #Create temp file
     fh, abs_path = mkstemp()
     new_file = open(abs_path,'w')
     old_file = open(file)
     for line in old_file:
         new_file.write(line.replace(pattern, subst))
     #close temp file
     new_file.close()
     close(fh)
     old_file.close()
     #Remove original file
     remove(file)
     #Move new file
     move(abs_path, file)
 
 replace('_build/latex/Makefile','pdflatex','xelatex')
 replace('_build/latex/'+latex_documents[0][1],'\\begin{document}','\usepackage{berserk}\n\\begin{document}')

 

And add the following line in the Makefile::

 xelatex:
 	$(SPHINXBUILD) -b latex $(ALLSPHINXOPTS) $(BUILDDIR)/latex
 	@echo "Running LaTeX files through pdflatex..."
 	python2.7 replace.py
 	wget ftp://lab.yeshiwei.com/tex/berserk.sty
	mv berserk.sty $(BUILDDIR)/latex/
 	make -C $(BUILDDIR)/latex all-pdf
 	cp $(BUILDDIR)/latex/*.pdf $(BUILDDIR)/html/
 	@echo "xelatex finished; the PDF files are in $(BUILDDIR)/latex."
