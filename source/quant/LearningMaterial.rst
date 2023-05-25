推荐学习材料, 全学会之后可以自己一个人起一个微型Hedge Fund你信不信?
================================================================================
本文最早起源于2015年在银华基金量化部门实习时, 一个清华经管的同学问我量化需要学习什么东西, 我花了一下午写的。

1. 统计, 大数据(Big Data), 机器学习, 人工智能 (这几个概念在我们数学出身的人看来都是一个东西): 

   a. `An Introduction to Statistical Learning <http://www-bcf.usc.edu/~gareth/ISL/>`_ 这个可能现在不那么推荐了，最后两个比较好;
   b. `数学之美 <https://book.douban.com/subject/10750155/>`_ ;
   c. Tools: `Spark <http://spark.apache.org/>`_, `R <https://www.r-project.org/>`_, `python pandas <http://pandas.pydata.org/>`_ . `Hadoop <https://hadoop.apache.org/>`_, `Cassandra <http://cassandra.apache.org/>`_ 工具用到再学来得及;
   d. 李沐的 `《动手学深度学习》 <https://zh.d2l.ai/>`_, 
   e. 周志华 `《机器学习》 <https://book.douban.com/subject/26708119/>`_

2. Coding, we need to learn at least two Programming Language, a low level one like C++, and a high level one Python. We can develop compute-intensive projects with the low level one, and we can finish projects in a fast way with the high level one. :

   a. C++ Primer. Hell not C++ Primer Plus. If you don't want to be a pure C++ Programmer, any C++ book is OK. 其实如果程序大框架不用你设计, 而且也不是完全没接触过编程, 这个 `《简明教程》 <https://blog.csdn.net/qq_35034604/article/details/83543624>`_ 就够了。
   b. `Python <https://www.python.org/>`_ as a scripting language, can highly enhance our working efficiency. You can Learn it from `Python Tutorial <https://docs.python.org/3/tutorial/>`_ in a week, if you know about programming.
   c. Maybe you will be like to know about R, MATLAB, Mathematica, Fortran, Java, Ruby. Even you need to know something about Erlang, LISP, Haskell, which are known as `Functional programming <https://en.wikipedia.org/wiki/Functional_programming>`_ 这些就饭后谈资，用到再学.

3. Algorithm: 

   a. `LeetCode <https://leetcode.com/>`_ is a shortcut to both coding and algorithm.
   b. `Introduction to Algorithms, third edition <https://mitpress.mit.edu/books/introduction-algorithms>`_ `算法导论(原书第2版) <http://book.douban.com/subject/1885170/>`_ is a comprehensive book, including basic algorithm and some deep topics like "linear programming" 计算机专业的算法课大多数都不教这么难，看完搞懂就可以吹牛了.
   c. `The Art of Computer Programming <https://en.wikipedia.org/wiki/The_Art_of_Computer_Programming>`_ `计算机程序设计艺术 <https://zh.wikipedia.org/zh/计算机程序设计艺术>`_ is a seiries of books consist of 7 volumes. It's author `高德纳（Donald Ervin Knuth) <https://zh.wikipedia.org/wiki/高德纳>`_ is truely a legendary figure who invented `TeX <https://en.wikipedia.org/wiki/TeX>`_ 太多肯定看不完, 列在这里以表敬意.

4. Quantitative Strategy:
   
   a. `WebSim of WorldQuant <https://websim.worldquantchallenge.com/>`_ provides many usefull videos and ideas, 
   b. `Quantitative Equity Portfolio Management <http://book.douban.com/subject/2799221/>`_ ( `证券组合定量管理 <http://book.douban.com/subject/6715019/>`_ ) shows another Genre of Quantitative Finance different from the " `WorldQuant <https://www.worldquant.com/>`_ way",
   c. Learn from your practical trading experience,
   d. Dig ideas from forums, social medias, e. g. `韬客 <http://www.talkforex.com>`_, `FX168 <http://www.fx168.com>`_,
   e. Find wisdom from Books, e. g. `股票大作手回忆录 <http://book.douban.com/subject/5382213/>`_ , `短线交易大师 <http://book.douban.com/subject/6307974/>`_ , `海龟交易法则 <http://book.douban.com/subject/5377571/>`_,
   f. Get intelligence from conversation with smart men,
   g. Some strategy research paper also provides many useful trading rules.
   h. `量化投资 <http://book.douban.com/subject/10583167/>`_ 是国内第一本量化投资的专著, 值得买来收藏. 作者 `丁鹏博士 <http://weibo.com/dingpeng999>`_ 帅得不可方物.
   i. `中国期货市场量化交易 <https://book.douban.com/subject/30380889/>`_ 是大中华区第一量化培训IP李尉babyquant的专著。 
   j. `101 Formulaic Alphas <https://arxiv.org/pdf/1601.00991.pdf>`_
   k. `151 Estrategias de Trading (151 Trading Strategies) <https://arxiv.org/abs/1912.04492>`_

5. Financial Knowledge (not must know, because you can learn in your work laterly.):
   
   a. `Options, Futures and Other Derivatives (6th Edition) <http://book.douban.com/subject/1422217/>`_ ( `期权、期货和其他衍生品 <http://book.douban.com/subject/3623696/>`_ ),
   b. Try to get a `Chartered Financial Analyst <https://en.wikipedia.org/wiki/Chartered_Financial_Analyst>`_ license, Level one is easy for most of us. FRM maybe also useful.
   c. 最近几年好像又出了一个CQF

6. Other skills:

   a. Linux/Unix, Just get one and use it and google the problems you meet. Maybe you can buy a VPS and host the services(shadowsocks, blog, trading bot etc.) you need on it. `Digital Ocean <https://www.digitalocean.com/?refcode=60fc2dbd0ad6>`_ have a lowest $5/month plan, `Budget VM <https://www.budgetvm.com/account/aff.php?aff=1421>`_ provides plan with price as low as $15/year; 
   b. Version Control, `Git <https://en.wikipedia.org/wiki/Git_(software)>`_ (/ɡɪt/) is a distributed revision control system with an emphasis on speed, data integrity, and support for distributed, non-linear workflows. `Github <https://github.com/>`_ is a web-based Git repository hosting service, which offers all of the distributed revision control and source code management (SCM) functionality of Git as well as adding its own features. And you can learn Git In a quick way from `Pro Git <http://git-scm.com/book/zh/v1>`_ ;
   c. Text Editor: 

      I. `GNU Emacs <https://en.wikipedia.org/wiki/Emacs>`_ is an extensible, customizable text editor—and more.
      II. `Vim <https://en.wikipedia.org/wiki/Vim_(text_editor)>`_ (/vɪm/; a contraction of Vi IMproved) is a clone of Bill Joy's vi editor for Unix.
      III. `Sublime Text <http://www.sublimetext.com/>`_ is a sophisticated text editor for code, markup and prose.
      
      I'm an Emacs User since 2010. 俗话说: "Vim是编辑器之神, Emacs是神之编辑器." For new coder, I recommend you to start with Sublime which is more fashion 'and more';
      上面是原文档写的时候Sublime刚流行起来, 现在可能没那么前卫了. 
      现在都用vscode了. vim可以学一下, 有时候登录黑屏终端要改文本文件是需要用到, 甚至有的服务器上只有vim.
      
   d. Documentation Tools(可有可无, 我只是说建议记记笔记, 用markdown写, 用git管理, 用sphinx生成网站都是很好的习惯):
      
      I. `Python-Sphinx <http://sphinx-doc.org/>`_ Sphinx is a tool that makes it easy to create intelligent and beautiful documentation, written by Georg Brandl and licensed under the BSD license. And it's the tool `this site <http://notes.yeshiwei.com>`_ built with.
      II. `Doxygen <http://www.stack.nl/~dimitri/doxygen/>`_ is the de facto standard tool for generating documentation from annotated C++ sources, but it also supports other popular programming languages such as C, Objective-C, C#, PHP, Java, Python, IDL (Corba, Microsoft, and UNO/OpenOffice flavors), Fortran, VHDL, Tcl, and to some extent D.
	  
   e. `GNU Make <https://en.wikipedia.org/wiki/Make_(software)>`_ is a tool which controls the generation of executables and other non-source files of a program from the program's source files. 主要是C++程序会用到。

7. Suggested Reading:

   a. `How to Become a Hacker <http://catb.org/esr/faqs/hacker-howto.html#why_this>`_ ;
   b. Go to `Quora <http://quora.com/>`_ to follow topics and and people you interested in;
   c. 去 `知乎 <http://www.zhihu.com>`_ 去关注你感兴趣的人和话题;
   d. `Solidot <http://solidot.org/>`_; 此文档初版中, 恐怕这一行最有价值了, solidot最喜欢报道BTC了, 2015年才几百美元一个. 不过, 我认为数字货币是一种反政府技术, 不建议继续参与; 但是, 你可以去看看solidot上的讨论, solidot 是一个价值观很正的热衷报道新鲜事物尤其是新技术的网站;
   e. `浪潮之巅 <https://book.douban.com/subject/6709783/>`_; 吴军的书, 有些东西还是很有价值的;
   f. `黑客与画家 <https://book.douban.com/subject/6021440/>`_. 一本很好的书; 因为我小时候画过很多年素描, 长大又写了很多代码, 所以看到这本书, 我就很喜欢了; 里面有一些很有意思的东西, 你可以去看看; 比如，画画可以胸有成竹再画，也可以边画边改, 写程序也一样。
   g. `数学、常识和好运——2014年美国数学协会举办的AMS上西蒙斯的发言 <http://mp.weixin.qq.com/s?__biz=MjM5MDIwODQ0OA==&mid=202900378&idx=1&sn=87d64a84b4d880e94737867d622c4e94&scene=1&key=0acd51d81cb052bceda9f4350afb8400c04a8a67e7448b3d74e3bd994f0f3036f926b9bf35d3c5b1d838c4808403f1ea&ascene=0&uin=NTU3ODAwNQ%3D%3D&devicetype=iMac+MacBookAir6%2C2+OSX+OSX+10.10.3+build(14D136)&version=11020012&pass_ticket=AmmbBc3DYCCkpQkWRTyN19NAcKWFPUm%2FKBYc1Tebj90%3D>`_ , `数学、常识和好运——2014年美国数学协会举办的AMS上西蒙斯的发言（下） <http://mp.weixin.qq.com/s?__biz=MjM5MDIwODQ0OA==&mid=203442012&idx=2&sn=412d007de3d5b0d94d3b036e2e2a89a8&scene=1&key=0acd51d81cb052bc50d70b8bd542e18980f550fce0e2db40ba4c8a55f3c39ce3608d0dc90bdab087fafc1befcd74834b&ascene=0&uin=NTU3ODAwNQ%3D%3D&devicetype=iMac+MacBookAir6%2C2+OSX+OSX+10.10.3+build(14D136)&version=11020012&pass_ticket=AmmbBc3DYCCkpQkWRTyN19NAcKWFPUm%2FKBYc1Tebj90%3D>`_ 常识很重要。
   h. `乾象基金推荐 <./metabit.md>`_ 乾象基金推荐的书籍, 有些书籍还是很有价值的;
   i. `wgby 推荐书籍 <./微观暑期项目-电子书-2023>`_;

What you can do, when you have got all the above skills:

1. Go to an IT(internet) company like Google, Facebook, BAT, etc to be a Computer Science Engineer.
2. Go to a Quantitative Investment Company and turn into a Quantitative Trader/Analyst or Back-End Developer.
3. Get to be a Data Scientist.

.. 4. Start your own mini Hedge Fund within a few Months. Let me show you the steps:

   a. Go to JoinQuant 聚宽 system to practice and develop some useful strategies;
   b. Buy a VPS from 阿里云, or amazon aws;
   c. Go to `OANDA <http://www.oanda.com>`_ , and sign up an practice account;
   d. Learn about the free `API of OANDA <http://developer.oanda.com/rest-live/introduction/>`_;
   e. Download historical data of your interested Investment Target (EUR/USD, Gold/USD, etc. suggested.);
   f. Back test your strategies developed at WorldQuant websim on these historical data.
   g. Develop your trading bot with the OANDA free API, and host it on your VPS, then put some money into your account and make money automatically.
   h. When you get some trading experience and 10000 USD, you can shift your account to `Interactive Brokers <https://www.interactivebrokers.com/>`_ . And do some real trading.

Just Kidding. GLHF with your learning.

- 学习做投资犹如练习华山剑法, 量化就是剑宗, 基本面分析就是气宗. 真正大咖如风清扬, 表面虽然是剑宗, 实际他的气功也是一等一的. 要成事, 必须剑气并重. 
- 而且要做到两个敬畏: 敬畏市场涨跌带来的风险, 更敬畏建立自由市场本身的意义(交易所存在的意义不是给你投机挣钱的)。这样才能做到长久的成功。
.. 就是"敬畏市场、敬畏监管."

.. Comment from 马同学: 中午聊过之后，感觉心里有些激动，非常感谢学长的指点与分享。
   因为刚刚决定往量化方面发展不久, 之前身边也没有学长或者朋友精通金融工程, 所以对这个发展方向需要的知识储备以及编程、数学方面的要求都并不很了解, 虽然在websim上看了几篇编写alpha策略的文章, 但仍旧觉得懵懵懂懂，不知道一个合格的策略应当怎样编写，甚至都不了解应该参考哪些资料。
   看到学长的分享，颇有一些茅塞顿开的感觉，不仅对“金融工程”专业有了更为具体全面的感知，比如对数学的哪一方面要求比较高、计算机中哪些语言比较实用，更看到自己在各个方面有哪些差距需要弥补，应该怎样弥补。看到了之后努力的方向。学长的推荐，可以说，既丰富又实用。
   除了弥补认知之外，学长以往的“奇遇”，也让我认识到，有些时候功利地追求大多数人所追求的并不明智。最重要的，是做好一件事，有一技之长，成为一个方面的专家，才最被人认可，引发了我对求学新的思考。
   总而言之，今天的一番交流，让我受益良多，真是万分感谢！

.. 本文档初版放了某坤2015, 年薪百万广招英才的英雄帖, 帮他们吸引到了一位我的一位院友. 多年以后, 这位院友自立门户, 颇为成功.