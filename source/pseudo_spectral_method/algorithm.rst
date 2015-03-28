*******************************************
Pseudo Spectral Method 算法说明
*******************************************


Introducing remarks
==================================================

- the pseudo-spectral(PS) methods are methods to solve partial differential equantions(PDE)
- they originate roughly in 1970
- the PS methods have successfully been applied to 

 - fluid dynamics(turbulence modeling, weather predictions)
 - non-linear waves
 - seismic modeling
 - MHD
 - ...


Basic principles of the pseudo-spectral method
==================================================

- the 'pseudo-spectral' in the method refers to the spatial part of a PDE
- example: a apatial PDE:

.. math::

 L u(x)=s(x), x\in V \\
 b.c.:f(u(y))=0, y\in \partial V

L: a spatial differential operator(e.g. :math:`L=\partial_{xx}+\partial_{yy}` , etc. )

- wanted: numerical solution :math:`u^N(x)` such that the residual R:

.. math::
 
 R(x):=Lu^N(x)-s(x)

is small-but how do we difine the smallness?

- general procedure:
 
1. choose a finite set of trial functions(expansion functions) :math:`\phi_j,j=0,\dots , N-1` and expand :math:`u^N` in these functions

.. math::

 u^N(x)=\sum_{j=0}^{N-1}\hat{u_j}\phi_j(x)

2. choose a set of test functions :math:`\chi_n,n=0,1,2,\dots, N-1` and demand that

.. math::

 (\chi_n,R)=0 \ \ for\ n=0,1\dots N-1 (scalar product)

- 'spectral methods' means that the trial functions :math:`\phi_n` form a basis for a certain space of global, smooth functions (e.g. Fourier polynomials)(global: extending over the whole spatial domain of interest)
- there are various spectral methods, classified according to the *test functions* :math:`\chi_n` :

 Galerkin method, tau method, collocation or pseudo-spectral method

- collocation or pseudo-spectral method:

.. math::
 
 \chi_n(x) = \delta(x-x_n),

where the :math:`x_n (n=0,1,\dots,N-1)` are special points, the collocation points

- the smallness condition for the residual  becomes:

.. math::

 \sum_{j=0}^{N-1}\hat{u_j}L\phi_j(x_n)-s(x_n)=0, n = 0,,1,2,\dots,N-1

N equations to determine the unknown N coeffients :math:`\hat{u_j}`

- remark: the solution at the collocation points is exact, in between them we interpolate the solution

- what trial functions to choose?

 1. periodic b.c.: trigonometric functions (Fourier series)
 2. non-periodic b.c.: orthogonal polynomials(main candidate: Chebyshev polynomials)

Pseudo-spectral methods and Fourier transforms
==================================================

Comparison to analytical Fourier method
--------------------------------------------------

- in 

.. math::

 Lu(x)=s(x),\ \ x\in V\\
 b.c.:f(u(y))=0,\ y\in \partial V

assume 1-D, and e.g. :math:`L=partial_{zz}` , :math:`\partial_{zz}u=s(x)`

- Fourier transform:

.. math::

 (-ik_z)^2\hat{u}(k_z)=\hat{s}(k_z)

- in principle, we want to do this numerically, but we have to make sure about a few points...

pseudo-spectral method, the Fourier case
--------------------------------------------------

- the aim is to find the expansion coefficients :math:`\hat{u}_j` such that the residual

.. math::

 \sum_{j=0}^{N-1} \hat{u}_j L \phi_j(x_n)-s(x_n)=0,\ n=0,1,2,\dots,N-1

or

.. math::

  \sum_{j=0}^{N-1} \hat{u}_j L e^{-ik_jx_n}-s(x_n)=0,\ n=0,1,2,\dots,N-1

vanishes. If L is linear, then :math:`Le^{-ik_jx_n}=h(k_j)e^{-ik_jx_n}`

.. math::

  \sum_{j=0}^{N-1} \hat{u}_j h(k_j)e^{-ik_jx_n}-s(x_n)=0,\ n=0,1,2,\dots,N-1

the 'trick' is to choose (turning now to 1D for simplicity)

.. math::

 x_n=n\Delta, n=0,1,2,\dots N-1

and 

.. math::

 k_j= 2\pi j/(N \Delta), j=-N/2,\dots,N/2\\
 \Delta:\textrm{spatial resotuion}

- :math:`z_n` and :math:`k_j` are equi-spaced, and the condition on the residual becomces:

.. math::

  \sum_{j=0}^{N-1} \hat{u}_j h(k_j)e^{-i2\pi j n/N}-s(x_n)=0,\ n=0,1,2,\dots,N-1


- we define the discrete Foureier Transform DFT as

.. math::
 
 \hat{u}_j=\frac{1}{\sqrt{N}} \sum_{n=0}^{N-1}u_ne^{2 \pi i nj/N}

- with :math:`u_n=u(x_n)` , and the inverse :math:`DFT^{-1}` as

.. math::

 u_n=\frac{1}{\sqrt{N}} \sum_{n=-N/2}^{N/2}\hat{u}_je^{-2 \pi i nj/N}

- it can be shown that with the specific choice of :math:`k_j` and :math:`x_n`

.. math::

 \frac{1}{\sqrt{N}} \sum_{n=0}^{N-1}e^{2\pi i j'/N}e^{-2 \pi i n j/N}=\delta(j-j')

[algebraic proof, using :math:`\sum_{n=0}^{N-1}q^n=(1-q^N)/(1-q)` ]

so that

.. math::

 u=DFT^{-1}(DFT(u))

(but just and only at the collocation points, actually :math:`u_n=DFT^{-1}(DFT(u_n))` )

- then the condition on the residual

.. math::

 \sum_{j=0}^{N-1} \hat{u}_j h(k_j)e^{-i2\pi j n/N}-s(x_n)=0,\ n=0,1,2,\dots,N-1

can thus, using the DFT, be written as:

.. math::

 DFT^{-1}[\hat{u}_j h(k_j)](x_n)-s(x_n)=0

and, on applying DFT,

.. math::

 \hat{u}_j h(k_j)(x_n)-DFT[s(x_n)](k_j)=0

-> we can maipulate our equations numerically with the DFT analogously as we do treat equations analytically with the Fourier transform

Remark:
 - :math:`x_n` and :math:`k_j` are equi-spaced only for trigonometric polynomials, every set of expansion functions has its own characteristic distribution of collocation points-equi-distribution is an exception (Chebychev, Legendre polynomials etc)
 - the sets {:math:`u_n`} and {:math:`u_j^*`} are completely equivalent, they contain the same information


Time-dependent problems
==================================================

- example: diffusion equation in 1D:

.. math::

 \partial_tu=v\partial_{zz}u\\
 u(z,0)=u_0(z)

- we consider the euqation only at the collocation points :math:`z_n=n\Delta,n=0,1,\dots,N-1` writing symbolically

.. math::

 \partial_tu_n=v\partial_{zz}u_n\\
 u(z_n,0)=u_0(z_n)

apply a spatial DFT:

.. math::

 \partial_t\hat{u}_j=-v4\pi^2(j/N)^2\hat{u}_j\\
 \hat{u}(k_j,0)=\hat{u_0}(k_j)

where :math:`j=-N/2,\dots,N/2`

we have a set of N ODEs
the temporal integration is done in Fourier space

Temporal integration
--------------------------------------------------

- The idea is to move the initial condition to Fourier space, and to do the temporal integration in Fourier space, since there we have ODEs
- since we ahve a set of ODEs, in principle every numerical scheme for integrating ODEs can be applied
- often good is Runge-Kutta 4th order, adaptive step-size
- 4th order RK:

.. math::

 du/dt&=F(u,t) \ \ \ (u has N components)\\
 u^{n+1}&=u^n+1/6(r_1+2r_2+2r_3+r_4)\\
 r_1&=\Delta t F(u^n,t_n)\\
 r_2&=\Delta t F(u^n+1/2r_1,t_n+1/2\Delta t)\\
 r_3&=\Delta t F(u^n+1/2r_2,t_n+1/2\Delta t)\\
 r_4&=\Delta t F(u^n+r_3,t_n+\Delta t)\\

- adaptive step-size:(for efficiency of the code)

advance :math:`\Delta t` , and also :math:`\Delta t/2+\Delta t/2`,compare the results with prescribed accuracy, depending on the result make :math:`\Delta t` smaller or larger.

how to treat non-linearities
==================================================

- assume there is a term :math:`\rho(z)u(z)` in the original PDE
- we are working in F-space, using DFT, so at a given time we have available :math:`\rho^*_j` and :math:`u^*_j` 
- :math:`\rho u` corresponds to a convolution in F-space, but convolutions are expensive(CPU time) and must be avoided (~:math:`N^2` )
- the procedure to calculate :math:`(\rho u)^*_j` is as follow(~ :math:`N log_2N` ):

 1. given at time t are :math:`\rho^*_j` and :math:`u^*_j` 
 2. calculate :math:`\rho_n=DFT^{-1}(\rho^*_j)` and :math:`u_n=DFT^{-1}(u^*_j)`
 3. multiply and store :math:`w_n=\rho_nu_n`
 4. move :math:`w_n` to F-space, :math:`w^*_k=DFT(w_n)`
 5. use :math:`w^*_j\ for \ (\rho u)^*_j`

Aliasing--de-aliansing
==================================================

- the Foureier modes used are:

.. math::

 e^{ik_jz_n}\\
 \textrm{with wave-vectors} k_j=2\pi j/N \Delta, j=-N/2,\dots, N/2\\
 \textrm{ and grid-points} z_n=n\Delta, n=0,1,\dots,N-1,\\
 \textrm{i.e. the modes are } e^{2 \pi i j n/N}

- at the grid points :math:`x_n,e^{2\pi i n j /N}` equals:

.. math::

 e^{2 \pi i(j+lN)n/Nf}, l=\dots,-2,-1,0,1,2,\dots

this implies that modes with:

.. math::

 k=2\pi (j+lN)/(N\Delta )

contribute to the DFT as if they had

.. math::

 k=2\pi j /N \Delta

i.e. high k modes alias/bias the amplitude a lower k modes!

- example: for :math:`\Delta =1,N=8` , our wave vectors are

.. math::

 k_j=-\pi,-3\pi/4,\dots,-\pi/4,0,\pi/4,\dots,3\pi/4,\pi

now e.g. to :math:`k=\pi/4` also the modes :math:`k=9\pi/4,17\pi/4 \dots` etc. contribute! i.e. modes outside the k-range we model bias the modeled k-range

example: grid of N=8 points, :math:`\Delta =1` :

:math:`sin(z \pi/4)` and :math:`sin(z 9 \pi/4)` appear as being the same function when sampled.

First consequence of the aliasing effect:

prescribed functions such as initial conditions :math:`u(z,t=0)` or source functions :math:`s(z,t)` are best provided as superpositions fo the explicitly available modes,

.. math::

 u(z_n,t=0)=\sum_j u^*_{0,j}e^{2 \pi i j n/N}

Aliasing and nonlinearities
--------------------------------------------------

- assume we have a non-linear term :math:`\rho u` in our PDE, and 

.. math::

 \rho(z)=sin(k_1z),u(z)=sin(k_2z),

with :math:`k_1,k_2` form our set of available wave-vectors :math:`k_j`

- now

.. math::

 \rho u ~ -cos[(k_1+k_2)z]+cos[(k_2-k_1)z],

and :math:`k_1+k_2` may lie outside our range of k's,
and the available Foureier amplitudes might get aliased!

- :math:`k_1+k_2` outside range if :math:`k_1+k_2>\pi` and the amplitude appears wrongly in the range of ks at :math:`k_1+k_2-2\pi(l=-1,j_1+j_2-N)` the DFT is aliased

De-aliasing
--------------------------------------------------

- several methods exist to prevent aliasing:

 zero-padding(3/2-rule), truncating(2/3-rule), phase shift

- we apply 2/3-rule:

 - simple to apply
 - low cost in computing time

- Basic idea:

 set part of the amplitudes to zero always prior to (non-linear) multiplications:

 full index range of k-vectors: :math:`[-N/2,N/2]`
 -> keep the sub-range :math:`[-K,K]` free of aliasing
 method: set Fourier amplitudes :math:`u^*_j=0\ in \ [-N/2,-K]\ and \ [N/2, K]`

- why does this work?  and how to choose K?
- let j and s be in :math:`[0,K]` 
- if :math:`j+s>N/2` (outside range), then the amplitude corresponding to j+s will be aliased to j+s-N
- we demand that :math:`j+s-N<-K` (in the not used part of the spectrum), the largest j, s in the range are :math:`j=s=K; j+s-N<=2K-N` i.e. :math:`K<N/3`

- we set :math:`K=N/3=(2/3)N/2`: '2/3-rule`
- for :math:`j.s` in :math:`j+s>N/2` the amplitude is aliased to :math:`j+s-N`, which may lie in :math:`[-K,0]` , but we do not have to care, the amplitudes at j and s are set to zero-> the range :math:`[-K,K]` is free of aliasing.

non-linearities, de-aliased
--------------------------------------------------

- assume you need to evaluate :math:`DFT(\rho_iu_i)` , having given the Fourier transforms :math:`\rho_j^*` and :math:`u_j^*` :

.. math::

 &\rho_j^*,u_j^* \\
 \rightarrow & \rho_j^*,u_j^*=0\ for\ j>(2/3)N/2 \\
 \rightarrow &(DFT^{-1}) \rho_n , u_n \\
 \rightarrow &w_n=\rho_n u_n \\
 \rightarrow &(\rho_ju_j)^*=w^*

Stability and convergence
--------------------------------------------------

- ... theory on stability on convergence ...
- reproduce analytically known cases
- reproduce results of others, or results derived in different ways
- test the individual sub-tasks the code performs
- monitor conserved quantities (if there are any)
- apply fantasy and pysical intuition to the concrete problem you study, try to be as critical as you can against your results

Concluding remarks
==================================================

Positive properties of the pseudo-spectral(PS) method
----------------------------------------------------------------------

- for analytic functions (solutions), the errors decay exponentially with N, i.e. very fast
- non-smoothness of even discontinuities in coeficients ro the solutions seem note to cause problems
- often, less grid points are needed with the PS method than with finite difference methods to achieve the same accuracy(computing time and memory!)

Negative properties of the pseudo-spectral method
----------------------------------------------------------------------

- certain boundary condition s may cause difficulties
- irregular domains(simulation boxes) can be difficult or impossible to implement
- strong shocks can cause problems
- local grid refinement (for cases where it is needed) seems not possible, so-far

References
==================================================

.. [1] Here is a nice `tutorial <_static/pseudo-spectral_2.pdf>`_
.. [2] `Wikipedia page for pseudo spectral method <http://en.wikipedia.org/wiki/Pseudo-spectral_method>`_
.. [3] Press, WH; Teukolsky, SA; Vetterling, WT; Flannery, BP (2007). "Section 20.7. Spectral Methods". `Numerical Recipes: The Art of Scientific Computing (3rd ed.) <ftp://lab.yeshiwei.com/Ebooks/Programming/Numerical_Recipes__The_Art_of_Scientific_Computing__Third_Edition.pdf>`_ . New York: Cambridge University Press. ISBN 978-0-521-88068-8.
