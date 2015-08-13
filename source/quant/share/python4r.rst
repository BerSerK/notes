`Why R data scientists should try out Python ? #rstats #python <http://decisionstats.com/2015/08/11/why-r-data-scientists-should-try-out-python/>`_
======================================================================================================================================================
  
 At the heart of science is an essential balance between two seemingly contradictory attitudes—an openness to new ideas, no matter how bizarre or counterintuitive they may be, and the most ruthless skeptical scrutiny of all ideas, old and new. This is how deep truths are winnowed from deep nonsense.
 — Carl Sagan

An excerpt from my book in progress ( Python for R Users – Wiley 2016)
Why Python for R Users?

To the memory constrained user in R who is neither Hadley Wickham nor Brian Ripley genius like in coding, and who needs a fast open source solution for statistical computing- Python comes with batteries attached.

With Pandas and Seaborn the last excuse of the I can only code for statistics in R and SAS will fall apart. Yes Python is as much open source and free as R. To disavow Python for statistical computing smacks of hypocritical ideology and department level university politics than any basis grounded in statistics.

How is Python different from R?

It's not better , it's not worse . It is just different. While almost the whole of R's ecosystem of packages is dedicated to data analysis , python is much more powerful general purpose language. In that lies both the power and the confusion to the R user coming to Python.
For even a simple function like mean, Python needs to import a package (numpy).  There is no Base , Graphics or Utils that come with Ipython or Python or Cython which immediately helps the new user with functions.

The language syntax is confusing for transition.

In R  the index for an object starts with 1 while in Python the index for an object's first member is 0.
so if::

 > a=c("Ajay","Vijay")
 > a[1]
 [1] "Ajay"
 in R

while in Python it will be::

 In [1]: a=["Ajay","Vijay"]

 In [2]: a[0]
 Out[2]: 'Ajay'

Loading packages in R is done with library("FUNpackage") while in Python it can be anything like
import "FUNPackage" as fun, 

or

.. code-block:: python

 import FUNPackage

or

.. code-block:: python

 import onefunctiononly from FUNPackage

R depends mostly on functions passing parameters and objects within parenthesis, recent brouhaha over magrittr's pipe operator not withstanding. Python mostly passes parameters using the dot notation .
If age is a list of numbers then for finding the mean of the numbers in age::

 mean(age) in R while age.mean() in Python

.

 HELP – when you are searching for help in R or Python.  

In R a single question mark denotes help  as searched from loaded packages while ??keyword would search for that keyword in all the packages of R included in the documentation (some of them are in Github universe.

Those are mostly searched by Google > Stack Overflow > Github>R-bloggers.

 In Python the help for a particular keyword would be keyword.?

Community Python does have a Python Planet but it lacks the appeal of R-Bloggers, and perhaps statistical computing for Python needs a seperate blog aggregator. Also  Pandas doesnot have flashmobs on StackOverflow like R did.
The IDE and GUI in R and Python are very different to R as well.
While R has established and distinct GUI like Deducer ( data visualization) , Rattle ( Data Mining) and R Commander ( extensible GUI for statistics, and others) it has multiple IDE with the current champion the private company established by a Microsoft alumnus, RStudio.

Python has IDE like Spyder and IDLE and a recent fork of Ace Editor called Rodeo ( which thus mimics RStudio 's inspired by Ace) , but none of them come close the market share in the developer world in statistical computing  that RStudio has ( note I am not going to non statistical applications of either r or python in this book).

 Ipython does have a huge appeal but it's not as easy an IDE as RStudio for non hardcore developers.

PURPOSE– Here I am comparing R and Python solely for the monetary rich but idealogically poor field of business analytics which consumes huge data and generates huge savings for businesses in the world as noted by the annual ever increasing of the non open source egalatarian employee friendly company SAS Institute (which is just a pity because I am sure had SAS Institute been founded in 2006 than in 1976 it's incredibly awesome founders would have open sourced atleast a few parts of its rather huge offerings).

 Why should a R user then learn Pandas/ Python?

This is because a professional data scientsist should hedge his career by not depending on just one statistical computing language. The ease at which a person can learn a new language does decrease with age and it's best to base your career on more than R. SAS language did lead the world for four decades but in a fast changing world it is best not to bet your mortgage that R skills are all you need for statistical computing in a multi decade career.

Will this lead to confusion?
images
No. Both R and Python are open source and object oriented languages. Learning both can only help your career in the world of data science and business analytics.
Do you want to be the master of your own destiny or do you want to depend on Hadley Wickham or RStudio or Revolution Analytics (Microsoft) to make tools for you?
Learn Python after you have learnt R and you will have an unbeatable resume.
Why am I writing about Python AFTER writing two books on R?
I come from a very poor country, I think open access to statistical computing can help my people and the world, and I am suspicious of any one that says that one software can solve ALL the problems of business analytics
A few sample workflow in analytics for R users but written in iPython-

- Adult Dataset http://nbviewer.ipython.org/gist/decisionstats/4142e98375445c5e4174
- Diamonds Dataset http://nbviewer.ipython.org/gist/decisionstats/df98ff9df42e7764d600
- Also see this ppt- http://www.slideshare.net/ajayohri/python-for-r-users

