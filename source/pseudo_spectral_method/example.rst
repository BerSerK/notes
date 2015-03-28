************************************************************
用伪谱方法 布勒斯基（ Boussinesq ）方程
************************************************************

布勒斯基（ Boussinesq ）方程
==================================================

原始变量形式： :math:`\overrightarrow{u}=(u,v)` 

.. math::

 &\frac{\partial\rho}{\partial t}+\overrightarrow{u}\cdot \nabla \rho = 0\\
 &\frac{\partial u}{\partial t}+\overrightarrow{u}\cdot \nabla \overrightarrow{u} +\nabla p 
 = \left( \begin{array}{c}0\\p\\ \end{array}\right)\\
 &\nabla \cdot \overrightarrow{u} = 0

流函数-涡量形式：

.. math::

 &\frac{\partial\rho}{\partial t}+u\cdot \nabla \rho = 0\\
 &\frac{\partial w}{\partial t}+\overrightarrow{u}\cdot \nabla w 
 = \frac{-\partial{\rho}}{\partial y} \\
 &-\Delta \Phi =w\\
 &w=\frac{\partial u}{\partial y} - \frac{\partial v}{\partial x},u=-\Phi_y,v=\Phi_x


我将对流函数-涡量形式求解。对这个方程组在空间上离散后做傅立叶变换得：

.. math::

   \frac{\partial \hat{\rho}_{jk}}{\partial t} &= \hat{u}_{jk}
   \otimes  i j \hat{\rho}_{jk} + \hat{v}_{jk}
   \otimes  i k \hat{\rho}_{jk}\\
   \frac{\partial \hat{w}_{jk}}{\partial t} &= \hat{u}_{jk}
   \otimes  i j \hat{w}_{jk} + \hat{v}_{jk}
   \otimes  i k \hat{w}_{jk} + i j
   \hat{\rho}_{jk}\\
   \hat{\Phi}_{jk}& = - \frac{\hat{w}_{jk}}{ (-ij)^2 + (-ik)^2 }\\
   \hat{u}_{jk} &= i k \hat{\Phi}_{jk}\\
   \hat{v}_{jk} &= -i j \hat{\Phi}_{jk}\\


来回用傅立叶变换逆变换和傅立叶变换计算卷积，用2/3法则去除折叠（alias）混淆误差。
用4阶Runge-Kutta方法取固定时间步长（ :math:`0.8 \frac{1}{N}` ）迭代求解下一步 :math:`\hat{\rho},\ \hat{w}` 。重复上述步骤。

空间网格为 512 的程序的计算结果：




手工并行化二维FFTW
==================================================

期末复习紧张，刚写了框架没来得及调试，期末之后找时间再弄一下。
