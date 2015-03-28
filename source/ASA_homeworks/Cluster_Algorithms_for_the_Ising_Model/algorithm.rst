************************************************************
基本模型与算法介绍
************************************************************

Ising 模型 与 Potts 模型
============================================================

Ising 模型，是物理学家研究磁性材料的模型，在统计物理中已经被广泛的研究过了。一个相近的模型是 *Potts 模型* 。与Ising模型类似，Potts 模型也是定义在晶格空间 :math:`\mathcal{L}` 上的 :math:`x=(x_l,x\in \mathcal{L})` 。

.. math::

 \mathcal{L}=\{ l=(l_1,l_2)\ for\ l_1,l_2 = 1,\dots,N\}.

与Ising模型不同，在Potts 模型里面每一个 :math:`x_l` 可以取 :math:`q:{1,\dots,q}` 。能量势可以取为：

.. math::

 H(x)=-J\sum_{i\sim j}\delta_{x_ix_j}-\sum_{j}h_j(x_j)

这里 :math:`i\sim j` 表示i和j在晶格空间里面是相邻的。于是我们关心的分布就是Bolzmann分布：

.. math::

 \pi(x) \propto exp\{-\beta H(x)\}

:math:`\beta=(kT)^{-1}` ， :math:`k` 是Bolzmann常数，T是绝对温度。当 :math:`q=2` 时，Potts模型就是Ising模型：

.. math::

 H(x)=-\frac{1}{2}J\sum_{i\sim j}2(\delta_{x_ix_j}-\frac{1}{2})-\sum_{i\sim j}\frac{1}{2}J-\sum_{j}h_j(x_j)

为了简单起见，我们假设 :math:`h_j\equiv 0` 。

关于这个模型的一个重要的问题是相变现象：当温度高的时候，可以观察到所有的spin几乎是独立变化的；而当温度低到一个特定的温度 :math:`c_0` 以后，所有的spin就趋于保持一致。

标准的 Metropolis算法正好方便的应用于模拟这个模型：第一步，随机选一个spin将他的取值 :math:`x_l` 取为 :math:`-x_l` ； 第二步，计算 Metropolis 比例来决定是否接受这个变化。但是当温度接近或者低于 :math:`c_0` 的时候，这个算法变的非常的慢。

算法介绍
=========================

The Swendsen-Wang Algorithm as Data Augmentation
------------------------------------------------------------------------

概念上，我们可以将 Swendsen-wang 算法视为一种“数据增强”（data augmentation scheme）。我们用一个连接变量 :math:`u=(u_{l\sim l'})` 来增强数据。每一个 :math:`u_{l \sim l'}` 在晶格的边界上，取值范围为： :math:`[0,e^{2 \beta J}]` 。

.. math::
 
 \pi(x)& \propto exp\{\beta J \sum_{l\sim l'}x_l x_{l'}\} \\
 &\propto \prod_{l\sim l'}exp\{\beta J(1+ \sum_{l\sim l'}x_l x_{l'})\} \\

注意到 :math:`1+x_l x_{l'}` 等于 0 或者2。所以，如果我们引入辅助变量 :math:`u` 使得：

.. math::

 \pi(x,u) \propto \prod_{l \sim l'} I[0 \leq u_{l,l'} \leq exp{\beta J(1+x_lx_{l'})}],

于是 x 的边界分布就是我们想要的分布。 显然，在这个联合分布中，条件分布 :math:`[u|x]` 是各个基于两个相邻的spin的平均分布的乘积。反过来，给定u，x的条件分布也容易得到：如果 :math:`u_{l,l'}>1` ，则 :math:`x_l=x_{l'}`  ；否则对 :math:`x_l` 没有限制。 于是，u 只有在 :math:`I[u_{l,l'}>1` 时，对 x 起作用。基于u的作用，我们将这些晶格根据相互直接有没有连接来分成组（cluster）。然后，所有属于同一组的 :math:`x_l` 必须保持相同的值。在这样的分组的前提下，没一种情况出现的概率都是相同的。

 所以，我们还可以做另一种数据增强，只用一个 连接变量 :math:`b =(b_{l\sim l'}` ,来表示 :math:`u(l,l')>1` 是否成立。也就是说，我们定义：

.. math::

 b_{l,l'}= I[u_{l,l'}>1]

于是，相应的增强模型是：

.. math::

 \pi(x,b) \propto \prod_{x_l=x_{l'}}\{1+b_{l,l'}(e^{2 \beta J} - 1)\},

且 :math:`b_{l,l'}` 如果 :math:`x_l\neq x_{l'}` 。 spin的分组(clustering)可以通过将连接为1的邻居相连。分组之间的spin方向相互独立。

Swendsen-Wang 算法:

- 对于一个给定的spin情况，以概率 :math:`1-e^{-2\beta J}` 建立每一个相等晶格之间的边界的连接变量 :math:`\langle l,l' \rangle` 取值为1 ，否则取值0。
- 在连接变量 b 前提下，通过 :math:`p(x|b)` 更新 spin变量x ,即在所有可能情况下的平均分布。也就是说，每一个组以概率 0.5 翻转。

The Modification by Wolff
------------------------------------------------------------

Wolff的修正使得算法的效率得到了很大的改善：

Wolff 算法：

- 对于给定的一个情况x，随机选取一个晶格 :math:`x_l` ，然后从一个连接集 :math:`C` 递归的生长：

 - 检查 :math:`C^{old}` 所有未检查的邻居；并且按照 SW算法中的规则建立连接。
 - 将新连接到 :math:`C^{old}` 上的单元添加到 :math:`C^{old}` 中生成 :math:`C^{new}`
 - 停止上诉递归过程直到没有未检查的邻居可以添加。将最后的集合称为 :math:`C`

- 将 集合 C 中的所有元素翻转，（不带随机性）。


Further Generalization
------------------------------------------------------------

Niedermayer 提出允许连接取值不同的邻居。设 :math:`p_a` 为连接相等邻居的概率， :math:`p_b` 为连接相反邻居的概率。生长完一个组 :math:`C` (Cluster)之后，反转整个 :math:`C` 。 选取适当的 :math:`p_a,p_b` 使得：

.. math::

 \frac{1-p_a}{1-p_b}=e^{2\beta J}
