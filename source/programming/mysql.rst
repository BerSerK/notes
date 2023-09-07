MySQL 使用笔记
======================

- 导出数据到文件

.. code-block:: bash

    mysqldump -hlocalhost -uroot -P3306 -p6NbAFQBE btmox>./btmox.sql

- 恢复

.. code-block:: bash

    mysql -uroot-P3306 -p6NbAFQBE btmox< ./btmox-data.sql

- 导入另一个数据库，登录之后先建立一个数据库，再 use 这个数据库，再 source 这个文件.

.. code-block:: bash

    mysql -uroot -p6NbAFQBE
    mysql> create database btmox;
    mysql> use btmox;
    mysql> source ./btmox.sql