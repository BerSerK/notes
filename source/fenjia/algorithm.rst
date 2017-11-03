算法
==============================

生成满足正态分布的N维度随机变量
------------------------------------------------------------

算法
````````````````````
设 :math:`N` 维随机变量 :math:`Z` 的每个分量是满足 :math:`\mu=0` , :math:`\sigma=1` 的独立正态分布随机变量. 
则可以由 :math:`x=LZ+R` , :math:`L=chol(\Sigma),\Sigma =LL^T` 生成均值为 :math:`R`, 协方差矩阵为 :math:`\Sigma` 的N维随机变量. 
具体证明可以查看 'Numerical Recipes Chapter 7.4'.
这里chol为 `Cholesky分解 <https://en.wikipedia.org/wiki/Cholesky_decomposition>`_ . 

PS: 这里需要注意的一个问题是生成的随机数列 :math:`Z` 必须是独立的, 这是程序实现过程中很容易犯的一个错误. 

C++程序实现
````````````````````
我利用C++11 的新特性 `生成正态分布随机数列 <http://www.cplusplus.com/reference/random/normal_distribution/>`_ . 
为了使得所生成的 :math:`Z` 相互独立, 我用 :math:`t F(n)` 来做随机数生成器的种子. 这里 :math:`t` 是一个和时间相关的整数,  
而 :math:`F(n)` 是 `斐波那契数列(Fibonacci Number) <https://en.wikipedia.org/wiki/Fibonacci_number>`_ .
显然, 为了每个种子不一样, :math:`F(n)` 必须从 :math:`1,2,3,5..` 开始, 而不是从 :math:`0` 开始. 


各种统计量的计算方法
----------------------------------------
Monte Carlo模拟完成之后, 我们需要计算如下统计量:

  a. 每个基金的 `平均 <https://en.wikipedia.org/wiki/Mean>`_ 第一次下折日;
  b. 第一向上折算日 `频数分布 <https://en.wikipedia.org/wiki/Frequency_distribution>`_ ;
  c. 第一向下折算日频数分布;
  d. 折算日 `截尾均值 <https://en.wikipedia.org/wiki/Truncated_mean>`_ ;
  e. 折算日25% `分位数 <https://en.wikipedia.org/wiki/Quantile>`_ , 50%分位数, 75%分位数, 与90%分位数;
  f. A基金优先份额久期分析;
  g. 计算隐含收益率;

其中前五项 a b c d e 都是常见统计量无需在这里赘述. 



基金优先份额 `久期 <https://en.wikipedia.org/wiki/Bond_duration>`_ 分析
````````````````````````````````````````````````````````````````````````````````````````````````````````````````````````
我们可以通过模拟永续分级基金优先份额现金流实现的金额与日期, 结合 `Macaulay Duration <https://en.wikipedia.org/wiki/Bond_duration#Macaulay_duration>`_ ,
与修正久期( `Modified Duration <https://en.wikipedia.org/wiki/Bond_duration#Modified_duration>`_ )的定义, 得出其修正久期.

.. index:: Macaulay Duration

麦考利久期
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

.. math::
   V=\sum_{i=1}^{n}PV_i

.. math::
   
   MacD = \frac{\sum_{i=1}^{n}t_i\cdot PV_i }{V} = \sum_{i=1}^n t_i \frac{PV_i}{V}

这里:

- :math:`i` 索引现金流,
- :math:`PV_i` 表示现金流现值( `present value <https://en.wikipedia.org/wiki/Present_value>`_ ),
- :math:`t_i` 表示现在起到付款日的时间,
- :math:`V` 是将来所有现金流的现值.

在第二个表达式中的分数部分 :math:`\frac{PV_i}{V}` 全部相加等于 :math:`1.0`, 作为这个加权平均中的权重. 于是这整个表达式就是现金流的一个时间加权平均.

在实际计算中, 我们使用下面这个表达式:

.. math::

   V = \sum_{i=1}^{n}PV_i = \sum_{i=1}^{n} CF_i\cdot e^{-yt_i}

.. math::
   
   MacD = \sum_{i=1}^{n}t_i \frac{CF_i\cdot e^{-yt_i} }{V}

这里:

- :math:`i` 索引现金流,
- :math:`PV_i` 表示第 :math:`i` 次付款的现值,
- :math:`CF_i` 表示第 :math:`i` 次现金流,
- :math:`y` 表示到期收益率(连续复利),
- :math:`t_i` 表示第 :math:`i` 次付款从现在起到付款日的时间, 以年为单位,
- :math:`V` 是将来直到最后到期的所有现金流的总现值.

修正久期
,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

修正久期( `Modified Duration`_ ) 是价格敏感性的一个度量, 定义为价格对收益的百分比导数. 修正久期只有在将债券看做是收益的函数的时候才有效. 我们也可以将其定义为债券的对数导数.

.. math::
   
   ModD= -\frac{1}{V}\cdot \frac{\partial V}{\partial y} = -\frac{\partial \ln{V}}{\partial y}

于是经过简单计算可以得到在连续复利的情况下 :math:`MacD=ModD`.

周期复利
,,,,,,,,,,,,,,,,,,,,,

在金融市场中, 收益往往表现为周期复利(年利率或者半年率), 而不是简单的连续复利. 分级基金A份也通常是以周期复利计算.

.. math::
 
   V(y_k) = \sum_{i=1}^{n}PV_i = \sum_{i=1}^{n}\frac{CF_i}{(1+y_k/k)^{k\cdot t_i}}
   
.. math::

   MacD = \sum_{i=1}^{n} \frac {t_i} {V(y_k)} \cdot \frac{CF_i} {(1+y_k/k)^{k \cdot t_i}} 

为了计算修正久期, 我们将 :math:`V` 对 :math:`y_k` 进行求导.

.. math::

    \frac{\partial V}{\partial y_k} = - \frac{1}{(1+y_k/k)} \cdot \sum_{i=1}^{n} t_i \cdot \frac {CF_i} {(1+y_k/k)^{k \cdot t_i}} = - \frac{MacD \cdot V(y_k)} { (1+y_k/k)} 

整理(两边同时除以 :math:`-V` )得:

.. math::

   \frac{MacD } { (1+y_k/k)} = - \frac{1} {V(y_k)} \cdot \frac{\partial V}{\partial y_k}   \equiv ModD

于是我们得到了, 麦考利久期和修正久期之间的关系:

.. math::
   
   ModD = \frac{MacD}{(1+y_k/k)}

这里:

- :math:`i` 索引现金流,
- :math:`k` 复合利率频率, (1表示年利率, 2表示半年率, 12表示月利率, 52表示周利率, etc.),
- :math:`CF_i` 表示第 :math:`i` 次现金流付款,
- :math:`t_i` 是以年作单位到收到第 :math:`i` 次付款的时间,
- :math:`y_k` 为到期利率,
- :math:`V` 表示所有现金流的现值.

计算隐含收益率&逆推理论价格
````````````````````````````````````````````````````````````

已知交易价格 :math:`P` 与现金流 :math:`CF_i`, 我们可以通过公式 

.. math:: P = \sum_{i=1}^{n}\frac{CF_i}{(1+r)^{t_i}}

来计算隐含收益率 :math:`r`.

而如果用已知收益率去回推理论价格 :math:`P_t`. 我们同样有公式 

.. math:: P_t = \sum_{i=1}^{n}\frac{CF_i}{(1+y_k/k)^{k\cdot t_i}}

这里我们通过Monte Carlo模拟出现金流 :math:`CF_i` 与固定投资利率 :math:`y_k` 就可以用上面的公式计算出理论价格了.
