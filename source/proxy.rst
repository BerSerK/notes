.. _proxy:


***************
代理服务
***************


Gappproxy
=============================

这个是搭建在Google App Engine上的一个服务，用于翻墙。
代理地址为:notes.yeshiwei.com:8001

.. _squid:

Squid
=============================

`How to config squid <http://www.linux.gov.cn/netweb/squid.htm>`_
这个代理现在已经关闭不用了。
你的ip如果在我的允许范围内（如果你和我同一个实验室或者一个宿舍就应该可以），那么将你的代理设置为 lab.yeshiwei.com:3129
就可以通过本机的网络上网了。


Goagent
=============================

这个也是搭建在Google App Engine上的服务，可用于访问大部分google的服务。


此代理的端口为3128。在北大校内网，将你的代理设置成lab.yeshiwei.com:3128，
就可以轻松使用google搜索、gmail、Google+, 不用太担心防火长城了。


hosts
=============================

当然许多网站是可以通过改hosts来上其ipv6服务器的。这是我的 `hosts <./_static/hosts>`_ 你可以直接下载覆盖你的hosts文件。如果你的电脑是联通ipv6的话（直接连接北大校园网都是连通ipv6的），加入我这个hosts文件之后可以登录包括facebook，twitter，google，youtube等国外主流网站::
    windows hosts文件的位置是：C:\WINDOWS\system32\drivers\etc\hosts
    linux的是：/etc/hosts

.. _GFW:

关于翻墙
==============================
强烈推荐使用 `google chrome <www.google.com/chrome>`_  浏览器加 `switchy <https://chrome.google.com/webstore/detail/caehdcpeofiiigpdhbabniblemipncjj>`_ 插件来自动切换代理。这是一个 `switchy使用指南 <http://www.laogeng.org/archives/670.html>`_ 。似乎360浏览器自带类似的功能。


在校园网环境下最好的翻墙办法是我上面提到的 `Gappproxy <http://code.google.com/p/gappproxy/>`_ 和 `Goagent <http://code.google.com/p/goagent/>`_ 。可以通过ipv6翻墙。
其中gappproxy甚至可以通过ipv6直接翻过学校网关和GFW两道墙，只要把local client的配置文件中的本地代理（local proxy）设置成ipv6.google.com:80就可以了。而通过goagent可以完美的使用Google+。





比较常规的翻墙办法就是用所谓的zy门了，是轮子的东西，就不做介绍了。

.. .. _winefg:

.. wine a fg
.. ==============================

.. 首先需要安装wine，这个自己搞定我就不赘述了。
   然后到此下载所需文件打包： http://dl.dbank.com/c0izn0jngp
   或者这里也可以下载： ftp://lab.yeshiwei.com/softwares/for_fg.zip
   压缩包内文件列表
   
   
   * MFC42.dll
   * msvcp60.dll
   * riched20.dll
   * riched32.dll
   * simsun.ttc
   * zh.reg
   
   前三个是所需的dll文件拷到/home/用户名/.wine/drive_c/windows/system32/
   将字体文件simsun.ttc拷到/home/用户名/.wine/drive_c/windows/Fonts/
   将zh.reg解压到任意目录，cd到该目录执行

   * regedit zh.reg
   
   这一步是设置字体
   
   这时就可以尝试打开你的fg.exe了，用终端或者是右键使用wine打开都可，如果此时提醒缺少MFC.dll文件，我的解决办法是将此文件直接复制到fg.exe所在的目录下即可解决！（该文件压缩包内有）
