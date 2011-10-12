******************************************
A collection of my linux tips
******************************************

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

doxymacs
-----------------------

Active it and set the user email in .emacs::

    (require 'doxymacs)
    (setq-default user-mail-address "...")
    
auto-complete
------------------------

http://cx4a.org/software/auto-complete/#Downloads

TexLive Tips
==================

- Solve::

    Error: Missing language pack for 'Adobe-GB1' mapping

with::

    apt-get install poppler-data

