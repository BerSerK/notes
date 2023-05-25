Books from metabit's recommenddation
========================================

Part 1
---------------

1. [Probability and Statistics](./metabit1/Morris%20H%20DeGroot_%20Mark%20J%20Schervish-Probability%20and%20statistics-Pearson%20Education%20%20(2012).pdf)
    - 作者：Morris H. Degroot & Mark J. Schervish
    - 推荐等级：入门级
    - 推荐理由：这本书是一本经典且基础的概率统计类教材，是很多大学本科统计类入门级课程。概率论与基础的统计知识非常全面且扎实，教材从概率出发，对于条件概率、随机变量&分布、期望、特殊分布、大随机样本、估计、样本估计量的分布、假-设检验等均有详细的描述与讲解，配合详实的例题，读完之后一定会受益匪浅。

2. [An Introduction to Statistical Learning](./metabit1/ISLRv2_website.pdf)
    - 作者：Trevor Hastie, Robert Tibshirani, Gareth James and Daniela Witten
    - 推荐等级：入门级
    - 推荐理由：这本书俗称ISL，是Stanford University的三个统计学大佬之二的Trevor Hastie以及Robert Tibshirani合著的一本关于statistical learning的入门级读物。
    从简单易于理解的linear regression开始，再讲到常见的linear classification方法，再上升到非线性的polynomial regression/tree-based method/SVM，最后也简单介绍了一些unsupervised learning的方法。
    在系统性介绍了各种statistical learning后，本书还非常详细地描述了statistical learning的函数拟合本质，以及如何应对learning最大的问题之一：bias-variance tradeoff，深入浅出地介绍了大部分常见的learning method，可以在量化策略中大量应用。
3. [The Elements of Statistical Learning](./metabit1/ESLII.pdf)
    - 作者：Trevor Hastie, Robert Tibshirani and Jerome Friedman
    - 推荐等级：进阶级
    - 推荐理由：这本书俗称ESL，是Stanford University的三个统计学大佬三人一起合著的“终身心血”。
    与上述的ISL相比，整体难度比较高，全书更偏向于statistical learning theory，相比ISL书中包含更多严谨的数学证明，需要读者有相对深入的数学知识（比如证明中会涉及到Hilbert space等）。
    相对ISL，ESL在书中也会额外增加一些内容，比如说generalized additive model/boosting/neural network/graphical models等。

4. [Analysis of Financial Time Series](./metabit1/analysis-of-financial-time-series-copy-2ffgm3v.pdf)
    - 作者：Ruey S. Tsay
    - 推荐等级：进阶级
    - 推荐理由：虽然都是讲时间序列，但是本书相较于下面两本，把做数据分析的目的做了更清晰的阐释，即，通过对过去金融危机期间的数据分析，来避免未来可能发生的金融危机，因为这些危机事件之间并不是完全独立的，所以具备分析价值。
    本书先简明扼要地讲述了时间序列分析的理论基础，再援引了大量金融世界中的概念与实例，深入浅出地将金融实践与数学理论结合在一起，是严谨又实用的分析、能解决一系列的现实问题。
    下面两本基本上都属于time series analysis/stochastic process的经典教材，内容上和 Analysis of Financial Time Series有一些重合，因此作为选读。

5. [Time Series Analysis and Its Applications](./metabit1/)   
    - 作者：Robert H. Shumway & David S. Stoffer
    - 推荐等级：选读
    - 推荐理由：本书全面且精细地讲解了在时间序列处理中，time domain和frequency domain两方面常见的分析方法。作者从时间序列本身的特征讲起，介绍了autocorrelation/stationary等基础概念，并从此讲解了ARIMA以及spectral analysis的基础应用；随后书中也提到了GARCH/threshold theory等，继而介绍了在物理、材料等领域有诸多应用的state space model。
    本书比较适合有一定统计基础的同学作为时间序列建模的入门读物，书中有一定的范例，同时书中把理论证明和正文分开展示，在阅读时也不用过于纠结繁琐的理论证明。

6. [Markov Chains](./metabit1/MarkovChains.pdf)
    - 作者：Pierre Bremaud
    - 推荐等级：选读
    - 推荐理由：如果是为了准备quant trading公司的技术面试，那么必不可少的一项技能就是在统计方面对于马尔科夫链（Markov chain）的理解了。
    本书从经典的离散马尔科夫链开始，介绍了transition matrix/first-step analysis等基础概念，并由此延展到马尔科夫链的convergence以及Martingale的介绍；后续在书中也介绍了经典的蒙特卡洛（Monte Carlo）方法，从Gibbs sampling讲到了马尔科夫链和蒙特卡洛结合的经典方法MCMC。
    本书中有不少证明，所需的数理统计知识较多，比较合适统计背景的同学阅读。

7. [Convex Optimization](./metabit1/bv_cvxbook.pdf)
    - 作者：Stephen Boyd
    - 推荐等级：选读
    - 推荐理由：这本书围绕最优问题的基本方法之一凸优化（Convex optimization），先指出了其在数学领域的应用需求是与日俱增，尤其是对于攻读EE/CS方向的毕业生，关于凸优化的掌握会给他们带来不小好处。其次，本书通过几种主流的算法，阐述了凸优化在研究问题的具象化表达和在建模上的应用。
    量化策略的很多环节都会或多或少应用到一些特定约束下的优化问题，本书便是一本非常不错的convex optimization教材，从理论/应用/优化算法三个大方面详细描述了convex optimization有关内容。
    在理论方面，本书从convex set/function开始，到定义何为一个convex optimization问题，再到何为Lagrangian duality以及KKT condition，铺垫了优化问题中的理论基础;
    在简单介绍convex optimization在概率统计/数据拟合等领域的应用之后，本书教学了常见的解决convex optimization问题的数值方法，包括可以简单得到理论最优解的quadratic optimization，以及如何应用Newton’s method以及interior-point method去解决更复杂、有更多类型约束的优化问题。
    总的来说，是一本非常不错的optimization algorithm教材。本书的受众并不指一般的研究员、科学家和工程师（比如：在数学优化，或者更广泛地说，计算数学方面的研究者）；相反地，主要受众是在计算机科学、经济学、金融学、统计学、数据挖掘等多方面进行科学研究的用户。

想要成为一名quant researcher，前提是必须拥有强大的数学背景（通常具备数学，物理学或工程学学位）。


Part 2
-----------------

1. Inside the Black Box: A Simple Guide to Quantitative and High Frequency Trading (中文翻译《打开量化投资的黑箱》)
    - 作者：Rishi K. Narang
    - 推荐等级：入门级
    - 推荐理由：大名鼎鼎的“打开量化交易的黑箱”，作者站在非技术研究的角度，介绍了量化策略从数据到因子到风险控制到投资组合再到下单执行的全流程，深入浅出地介绍了“高深莫测”的量化交易到底是什么。如果有一些同学在考虑是否有能力加入或者是否适合加入量化交易这个领域，那么相信这本书会令你茅塞顿开。

2. [Quantitative Trading](./metabit2/epchan.pdf)
    - 作者：Ernest Chan
    - 推荐等级：入门级
    - 推荐理由：非常general地介绍了什么叫做quantitative trading，阐释了量化策略是什么，量化策略由哪些模块所构成，什么是交易系统，以及基础的动量策略与反转策略的区别和联系；书中配有大量的MATLAB代码辅助配合读者的理解与练习，是一本初学者也能看懂的量化交易入门级读物。

3. [Finding Alphas](./metabit2/WorldQuant_FindingAlphas.pdf)
    - 作者：Igor Tulchinsky et al.
    - 推荐等级：入门级
    - 推荐理由：大名鼎鼎的Worldquant公司，描述了他们是如何寻找市场中的“alpha”的一些例子，以及该公司用于alpha research的方法论，比较适合刚接触量化交易的小伙伴们去熟悉“因子”这个概念。

4. [Hands-on Machine Learning for Algorithmic Trading](./metabit2/Machine_Learning_for_Algorithmic_Trading_Predictive.pdf)
    - 作者：Stefan Jansen
    - 推荐等级：入门级
    - 推荐理由：是一本比较全面的关于全链路机器学习在量化交易中应用的教材，从市场数据的获取与处理，另类数据的分类与质量检查，到因子研究、交易信号生成以及策略评价体系都有详尽的介绍；书中配有大量的以Python为基础的范例代码，书中靠后的章节还介绍了近些年火热的、对于文本类数据的处理，适合同时想学习量化交易以及机器学习的读者。

5. [Algorithmic Trading and DMA: An introduction to direct access trading strategies](./metabit2/Algorithmic-Trading-and-Direct-Market-Access.pdf)
    - 作者：Barry Johonson
    - 推荐等级：进阶级
    - 推荐理由：介绍了常见的金融市场微观结构，包含交易订单种类、交易成本模型等；同时讲解了常见的下单算法以及下单执行的知识点，比较适合感兴趣高频交易的读者。

6. [Statistical Arbitrage Algorithmic Trading Insights and Techniques (Wiley Finance)](./metabit2/Statistical%20Arbitrage%20Algorithmic%20Trading%20Insights%20and%20Techniques%20(Wiley%20Finance).pdf)
    - 作者：Andrew Pole
    - 推荐等级：选读
    - 推荐理由：本书作者从自身视角出发，介绍了基础的统计套利知识：什么是反转理论、如何理解以及分解一只股票的价格变化、“75分位”理论以及如何利用该理论设计统计套利策略等。本书的数理统计内容相对较少，更多是包含了一些作者的经验以及对于市场的理解，比较适合想要获得统计套利基础知识的读者。