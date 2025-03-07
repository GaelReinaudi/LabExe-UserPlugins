/*************************************************************************
Copyright (c) Sergey Bochkanov (ALGLIB project).

>>> SOURCE LICENSE >>>
This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation (www.fsf.org); either version 2 of the
License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

A copy of the GNU General Public License is available at
http://www.fsf.org/licensing/licenses
>>> END OF LICENSE >>>
*************************************************************************/
// #include "StdAfx.h"
#include "optimization.h"

// disable some irrelevant warnings
#if (AE_COMPILER==AE_MSVC)
#pragma warning(disable:4100)
#pragma warning(disable:4127)
#pragma warning(disable:4702)
#pragma warning(disable:4996)
#endif

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS IMPLEMENTATION OF C++ INTERFACE
//
/////////////////////////////////////////////////////////////////////////
namespace alglib
{


/*************************************************************************

*************************************************************************/
_minlbfgsstate_owner::_minlbfgsstate_owner()
{
    p_struct = (alglib_impl::minlbfgsstate*)alglib_impl::ae_malloc(sizeof(alglib_impl::minlbfgsstate), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_minlbfgsstate_init(p_struct, NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_minlbfgsstate_owner::_minlbfgsstate_owner(const _minlbfgsstate_owner &rhs)
{
    p_struct = (alglib_impl::minlbfgsstate*)alglib_impl::ae_malloc(sizeof(alglib_impl::minlbfgsstate), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_minlbfgsstate_init_copy(p_struct, const_cast<alglib_impl::minlbfgsstate*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_minlbfgsstate_owner& _minlbfgsstate_owner::operator=(const _minlbfgsstate_owner &rhs)
{
    if( this==&rhs )
        return *this;
    alglib_impl::_minlbfgsstate_clear(p_struct);
    if( !alglib_impl::_minlbfgsstate_init_copy(p_struct, const_cast<alglib_impl::minlbfgsstate*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
    return *this;
}

_minlbfgsstate_owner::~_minlbfgsstate_owner()
{
    alglib_impl::_minlbfgsstate_clear(p_struct);
    ae_free(p_struct);
}

alglib_impl::minlbfgsstate* _minlbfgsstate_owner::c_ptr()
{
    return p_struct;
}

alglib_impl::minlbfgsstate* _minlbfgsstate_owner::c_ptr() const
{
    return const_cast<alglib_impl::minlbfgsstate*>(p_struct);
}
minlbfgsstate::minlbfgsstate() : _minlbfgsstate_owner() ,needfg(p_struct->needfg),xupdated(p_struct->xupdated),f(p_struct->f),g(&p_struct->g),x(&p_struct->x)
{
}

minlbfgsstate::minlbfgsstate(const minlbfgsstate &rhs):_minlbfgsstate_owner(rhs) ,needfg(p_struct->needfg),xupdated(p_struct->xupdated),f(p_struct->f),g(&p_struct->g),x(&p_struct->x)
{
}

minlbfgsstate& minlbfgsstate::operator=(const minlbfgsstate &rhs)
{
    if( this==&rhs )
        return *this;
    _minlbfgsstate_owner::operator=(rhs);
    return *this;
}

minlbfgsstate::~minlbfgsstate()
{
}


/*************************************************************************

*************************************************************************/
_minlbfgsreport_owner::_minlbfgsreport_owner()
{
    p_struct = (alglib_impl::minlbfgsreport*)alglib_impl::ae_malloc(sizeof(alglib_impl::minlbfgsreport), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_minlbfgsreport_init(p_struct, NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_minlbfgsreport_owner::_minlbfgsreport_owner(const _minlbfgsreport_owner &rhs)
{
    p_struct = (alglib_impl::minlbfgsreport*)alglib_impl::ae_malloc(sizeof(alglib_impl::minlbfgsreport), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_minlbfgsreport_init_copy(p_struct, const_cast<alglib_impl::minlbfgsreport*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_minlbfgsreport_owner& _minlbfgsreport_owner::operator=(const _minlbfgsreport_owner &rhs)
{
    if( this==&rhs )
        return *this;
    alglib_impl::_minlbfgsreport_clear(p_struct);
    if( !alglib_impl::_minlbfgsreport_init_copy(p_struct, const_cast<alglib_impl::minlbfgsreport*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
    return *this;
}

_minlbfgsreport_owner::~_minlbfgsreport_owner()
{
    alglib_impl::_minlbfgsreport_clear(p_struct);
    ae_free(p_struct);
}

alglib_impl::minlbfgsreport* _minlbfgsreport_owner::c_ptr()
{
    return p_struct;
}

alglib_impl::minlbfgsreport* _minlbfgsreport_owner::c_ptr() const
{
    return const_cast<alglib_impl::minlbfgsreport*>(p_struct);
}
minlbfgsreport::minlbfgsreport() : _minlbfgsreport_owner() ,iterationscount(p_struct->iterationscount),nfev(p_struct->nfev),terminationtype(p_struct->terminationtype)
{
}

minlbfgsreport::minlbfgsreport(const minlbfgsreport &rhs):_minlbfgsreport_owner(rhs) ,iterationscount(p_struct->iterationscount),nfev(p_struct->nfev),terminationtype(p_struct->terminationtype)
{
}

minlbfgsreport& minlbfgsreport::operator=(const minlbfgsreport &rhs)
{
    if( this==&rhs )
        return *this;
    _minlbfgsreport_owner::operator=(rhs);
    return *this;
}

minlbfgsreport::~minlbfgsreport()
{
}

/*************************************************************************
        LIMITED MEMORY BFGS METHOD FOR LARGE SCALE OPTIMIZATION

DESCRIPTION:
The subroutine minimizes function F(x) of N arguments by  using  a  quasi-
Newton method (LBFGS scheme) which is optimized to use  a  minimum  amount
of memory.
The subroutine generates the approximation of an inverse Hessian matrix by
using information about the last M steps of the algorithm  (instead of N).
It lessens a required amount of memory from a value  of  order  N^2  to  a
value of order 2*N*M.


REQUIREMENTS:
Algorithm will request following information during its operation:
* function value F and its gradient G (simultaneously) at given point X


USAGE:
1. User initializes algorithm state with MinLBFGSCreate() call
2. User tunes solver parameters with MinLBFGSSetCond() MinLBFGSSetStpMax()
   and other functions
3. User calls MinLBFGSOptimize() function which takes algorithm  state and
   pointer (delegate, etc.) to callback function which calculates F/G.
4. User calls MinLBFGSResults() to get solution
5. Optionally user may call MinLBFGSRestartFrom() to solve another problem
   with same N/M but another starting point and/or another function.
   MinLBFGSRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   problem dimension. N>0
    M       -   number of corrections in the BFGS scheme of Hessian
                approximation update. Recommended value:  3<=M<=7. The smaller
                value causes worse convergence, the bigger will  not  cause  a
                considerably better convergence, but will cause a fall in  the
                performance. M<=N.
    X       -   initial solution approximation, array[0..N-1].


OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state


NOTES:
1. you may tune stopping conditions with MinLBFGSSetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use MinLBFGSSetStpMax() function to bound algorithm's  steps.  However,
   L-BFGS rarely needs such a tuning.


  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minlbfgscreate(const ae_int_t n, const ae_int_t m, const real_1d_array &x, minlbfgsstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlbfgscreate(n, m, const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::minlbfgsstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
        LIMITED MEMORY BFGS METHOD FOR LARGE SCALE OPTIMIZATION

DESCRIPTION:
The subroutine minimizes function F(x) of N arguments by  using  a  quasi-
Newton method (LBFGS scheme) which is optimized to use  a  minimum  amount
of memory.
The subroutine generates the approximation of an inverse Hessian matrix by
using information about the last M steps of the algorithm  (instead of N).
It lessens a required amount of memory from a value  of  order  N^2  to  a
value of order 2*N*M.


REQUIREMENTS:
Algorithm will request following information during its operation:
* function value F and its gradient G (simultaneously) at given point X


USAGE:
1. User initializes algorithm state with MinLBFGSCreate() call
2. User tunes solver parameters with MinLBFGSSetCond() MinLBFGSSetStpMax()
   and other functions
3. User calls MinLBFGSOptimize() function which takes algorithm  state and
   pointer (delegate, etc.) to callback function which calculates F/G.
4. User calls MinLBFGSResults() to get solution
5. Optionally user may call MinLBFGSRestartFrom() to solve another problem
   with same N/M but another starting point and/or another function.
   MinLBFGSRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   problem dimension. N>0
    M       -   number of corrections in the BFGS scheme of Hessian
                approximation update. Recommended value:  3<=M<=7. The smaller
                value causes worse convergence, the bigger will  not  cause  a
                considerably better convergence, but will cause a fall in  the
                performance. M<=N.
    X       -   initial solution approximation, array[0..N-1].


OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state


NOTES:
1. you may tune stopping conditions with MinLBFGSSetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use MinLBFGSSetStpMax() function to bound algorithm's  steps.  However,
   L-BFGS rarely needs such a tuning.


  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minlbfgscreate(const ae_int_t m, const real_1d_array &x, minlbfgsstate &state)
{
    alglib_impl::ae_state _alglib_env_state;    
    ae_int_t n;

    n = x.length();
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlbfgscreate(n, m, const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::minlbfgsstate*>(state.c_ptr()), &_alglib_env_state);

        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This function sets stopping conditions for L-BFGS optimization algorithm.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    EpsG    -   >=0
                The  subroutine  finishes  its  work   if   the  condition
                ||G||<EpsG is satisfied, where ||.|| means Euclidian norm,
                G - gradient.
    EpsF    -   >=0
                The  subroutine  finishes  its work if on k+1-th iteration
                the  condition  |F(k+1)-F(k)|<=EpsF*max{|F(k)|,|F(k+1)|,1}
                is satisfied.
    EpsX    -   >=0
                The subroutine finishes its work if  on  k+1-th  iteration
                the condition |X(k+1)-X(k)| <= EpsX is fulfilled.
    MaxIts  -   maximum number of iterations. If MaxIts=0, the  number  of
                iterations is unlimited.

Passing EpsG=0, EpsF=0, EpsX=0 and MaxIts=0 (simultaneously) will lead to
automatic stopping criterion selection (small EpsX).

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minlbfgssetcond(const minlbfgsstate &state, const double epsg, const double epsf, const double epsx, const ae_int_t maxits)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlbfgssetcond(const_cast<alglib_impl::minlbfgsstate*>(state.c_ptr()), epsg, epsf, epsx, maxits, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This function turns on/off reporting.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    NeedXRep-   whether iteration reports are needed or not

If NeedXRep is True, algorithm will call rep() callback function if  it is
provided to MinLBFGSOptimize().


  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minlbfgssetxrep(const minlbfgsstate &state, const bool needxrep)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlbfgssetxrep(const_cast<alglib_impl::minlbfgsstate*>(state.c_ptr()), needxrep, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This function sets maximum step length

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    StpMax  -   maximum step length, >=0. Set StpMax to 0.0 (default),  if
                you don't want to limit step length.

Use this subroutine when you optimize target function which contains exp()
or  other  fast  growing  functions,  and optimization algorithm makes too
large  steps  which  leads  to overflow. This function allows us to reject
steps  that  are  too  large  (and  therefore  expose  us  to the possible
overflow) without actually calculating function value at the x+stp*d.

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minlbfgssetstpmax(const minlbfgsstate &state, const double stpmax)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlbfgssetstpmax(const_cast<alglib_impl::minlbfgsstate*>(state.c_ptr()), stpmax, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
Modification of the preconditioner:
default preconditioner (simple scaling) is used.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state

After call to this function preconditioner is changed to the default one.

NOTE:  you  can  change  preconditioner  "on  the  fly",  during algorithm
iterations.

  -- ALGLIB --
     Copyright 13.10.2010 by Bochkanov Sergey
*************************************************************************/
void minlbfgssetdefaultpreconditioner(const minlbfgsstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlbfgssetdefaultpreconditioner(const_cast<alglib_impl::minlbfgsstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
Modification of the preconditioner:
Cholesky factorization of approximate Hessian is used.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    P       -   triangular preconditioner, Cholesky factorization of
                the approximate Hessian. array[0..N-1,0..N-1],
                (if larger, only leading N elements are used).
    IsUpper -   whether upper or lower triangle of P is given
                (other triangle is not referenced)

After call to this function preconditioner is changed to P  (P  is  copied
into the internal buffer).

NOTE:  you  can  change  preconditioner  "on  the  fly",  during algorithm
iterations.

NOTE 2:  P  should  be nonsingular. Exception will be thrown otherwise. It
also should be well conditioned, although only strict  non-singularity  is
tested.

  -- ALGLIB --
     Copyright 13.10.2010 by Bochkanov Sergey
*************************************************************************/
void minlbfgssetcholeskypreconditioner(const minlbfgsstate &state, const real_2d_array &p, const bool isupper)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlbfgssetcholeskypreconditioner(const_cast<alglib_impl::minlbfgsstate*>(state.c_ptr()), const_cast<alglib_impl::ae_matrix*>(p.c_ptr()), isupper, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This function provides reverse communication interface
Reverse communication interface is not documented or recommended to use.
See below for functions which provide better documented API
*************************************************************************/
bool minlbfgsiteration(const minlbfgsstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        ae_bool result = alglib_impl::minlbfgsiteration(const_cast<alglib_impl::minlbfgsstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return *(reinterpret_cast<bool*>(&result));
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}


void minlbfgsoptimize(minlbfgsstate &state,
    void (*grad)(const real_1d_array &x, double &func, real_1d_array &grad, void *ptr),
    void  (*rep)(const real_1d_array &x, double func, void *ptr), 
    void *ptr)
{
    alglib_impl::ae_state _alglib_env_state;
    if( grad==NULL )
        throw ap_error("ALGLIB: error in 'minlbfgsoptimize()' (grad is NULL)");
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        while( alglib_impl::minlbfgsiteration(state.c_ptr(), &_alglib_env_state) )
        {
            if( state.needfg )
            {
                grad(state.x, state.f, state.g, ptr);
                continue;
            }
            if( state.xupdated )
            {
                if( rep!=NULL )
                    rep(state.x, state.f, ptr);
                continue;
            }
            throw ap_error("ALGLIB: error in 'minlbfgsoptimize' (some derivatives were not provided?)");
        }
        alglib_impl::ae_state_clear(&_alglib_env_state);
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}



/*************************************************************************
L-BFGS algorithm results

INPUT PARAMETERS:
    State   -   algorithm state

OUTPUT PARAMETERS:
    X       -   array[0..N-1], solution
    Rep     -   optimization report:
                * Rep.TerminationType completetion code:
                    * -2    rounding errors prevent further improvement.
                            X contains best point found.
                    * -1    incorrect parameters were specified
                    *  1    relative function improvement is no more than
                            EpsF.
                    *  2    relative step is no more than EpsX.
                    *  4    gradient norm is no more than EpsG
                    *  5    MaxIts steps was taken
                    *  7    stopping conditions are too stringent,
                            further improvement is impossible
                * Rep.IterationsCount contains iterations count
                * NFEV countains number of function calculations

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minlbfgsresults(const minlbfgsstate &state, real_1d_array &x, minlbfgsreport &rep)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlbfgsresults(const_cast<alglib_impl::minlbfgsstate*>(state.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::minlbfgsreport*>(rep.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
L-BFGS algorithm results

Buffered implementation of MinLBFGSResults which uses pre-allocated buffer
to store X[]. If buffer size is  too  small,  it  resizes  buffer.  It  is
intended to be used in the inner cycles of performance critical algorithms
where array reallocation penalty is too large to be ignored.

  -- ALGLIB --
     Copyright 20.08.2010 by Bochkanov Sergey
*************************************************************************/
void minlbfgsresultsbuf(const minlbfgsstate &state, real_1d_array &x, minlbfgsreport &rep)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlbfgsresultsbuf(const_cast<alglib_impl::minlbfgsstate*>(state.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::minlbfgsreport*>(rep.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This  subroutine restarts LBFGS algorithm from new point. All optimization
parameters are left unchanged.

This  function  allows  to  solve multiple  optimization  problems  (which
must have same number of dimensions) without object reallocation penalty.

INPUT PARAMETERS:
    State   -   structure used to store algorithm state
    X       -   new starting point.

  -- ALGLIB --
     Copyright 30.07.2010 by Bochkanov Sergey
*************************************************************************/
void minlbfgsrestartfrom(const minlbfgsstate &state, const real_1d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlbfgsrestartfrom(const_cast<alglib_impl::minlbfgsstate*>(state.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
Levenberg-Marquardt optimizer.

This structure should be created using one of the MinLMCreate???()
functions. You should not access its fields directly; use ALGLIB functions
to work with it.
*************************************************************************/
_minlmstate_owner::_minlmstate_owner()
{
    p_struct = (alglib_impl::minlmstate*)alglib_impl::ae_malloc(sizeof(alglib_impl::minlmstate), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_minlmstate_init(p_struct, NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_minlmstate_owner::_minlmstate_owner(const _minlmstate_owner &rhs)
{
    p_struct = (alglib_impl::minlmstate*)alglib_impl::ae_malloc(sizeof(alglib_impl::minlmstate), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_minlmstate_init_copy(p_struct, const_cast<alglib_impl::minlmstate*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_minlmstate_owner& _minlmstate_owner::operator=(const _minlmstate_owner &rhs)
{
    if( this==&rhs )
        return *this;
    alglib_impl::_minlmstate_clear(p_struct);
    if( !alglib_impl::_minlmstate_init_copy(p_struct, const_cast<alglib_impl::minlmstate*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
    return *this;
}

_minlmstate_owner::~_minlmstate_owner()
{
    alglib_impl::_minlmstate_clear(p_struct);
    ae_free(p_struct);
}

alglib_impl::minlmstate* _minlmstate_owner::c_ptr()
{
    return p_struct;
}

alglib_impl::minlmstate* _minlmstate_owner::c_ptr() const
{
    return const_cast<alglib_impl::minlmstate*>(p_struct);
}
minlmstate::minlmstate() : _minlmstate_owner() ,needf(p_struct->needf),needfg(p_struct->needfg),needfgh(p_struct->needfgh),needfi(p_struct->needfi),needfij(p_struct->needfij),xupdated(p_struct->xupdated),f(p_struct->f),fi(&p_struct->fi),g(&p_struct->g),h(&p_struct->h),j(&p_struct->j),x(&p_struct->x)
{
}

minlmstate::minlmstate(const minlmstate &rhs):_minlmstate_owner(rhs) ,needf(p_struct->needf),needfg(p_struct->needfg),needfgh(p_struct->needfgh),needfi(p_struct->needfi),needfij(p_struct->needfij),xupdated(p_struct->xupdated),f(p_struct->f),fi(&p_struct->fi),g(&p_struct->g),h(&p_struct->h),j(&p_struct->j),x(&p_struct->x)
{
}

minlmstate& minlmstate::operator=(const minlmstate &rhs)
{
    if( this==&rhs )
        return *this;
    _minlmstate_owner::operator=(rhs);
    return *this;
}

minlmstate::~minlmstate()
{
}


/*************************************************************************
Optimization report, filled by MinLMResults() function

FIELDS:
* TerminationType, completetion code:
    * -9    derivative correctness check failed;
            see Rep.WrongNum, Rep.WrongI, Rep.WrongJ for
            more information.
    *  1    relative function improvement is no more than
            EpsF.
    *  2    relative step is no more than EpsX.
    *  4    gradient is no more than EpsG.
    *  5    MaxIts steps was taken
    *  7    stopping conditions are too stringent,
            further improvement is impossible
* IterationsCount, contains iterations count
* NFunc, number of function calculations
* NJac, number of Jacobi matrix calculations
* NGrad, number of gradient calculations
* NHess, number of Hessian calculations
* NCholesky, number of Cholesky decomposition calculations
*************************************************************************/
_minlmreport_owner::_minlmreport_owner()
{
    p_struct = (alglib_impl::minlmreport*)alglib_impl::ae_malloc(sizeof(alglib_impl::minlmreport), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_minlmreport_init(p_struct, NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_minlmreport_owner::_minlmreport_owner(const _minlmreport_owner &rhs)
{
    p_struct = (alglib_impl::minlmreport*)alglib_impl::ae_malloc(sizeof(alglib_impl::minlmreport), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_minlmreport_init_copy(p_struct, const_cast<alglib_impl::minlmreport*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_minlmreport_owner& _minlmreport_owner::operator=(const _minlmreport_owner &rhs)
{
    if( this==&rhs )
        return *this;
    alglib_impl::_minlmreport_clear(p_struct);
    if( !alglib_impl::_minlmreport_init_copy(p_struct, const_cast<alglib_impl::minlmreport*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
    return *this;
}

_minlmreport_owner::~_minlmreport_owner()
{
    alglib_impl::_minlmreport_clear(p_struct);
    ae_free(p_struct);
}

alglib_impl::minlmreport* _minlmreport_owner::c_ptr()
{
    return p_struct;
}

alglib_impl::minlmreport* _minlmreport_owner::c_ptr() const
{
    return const_cast<alglib_impl::minlmreport*>(p_struct);
}
minlmreport::minlmreport() : _minlmreport_owner() ,iterationscount(p_struct->iterationscount),terminationtype(p_struct->terminationtype),nfunc(p_struct->nfunc),njac(p_struct->njac),ngrad(p_struct->ngrad),nhess(p_struct->nhess),ncholesky(p_struct->ncholesky)
{
}

minlmreport::minlmreport(const minlmreport &rhs):_minlmreport_owner(rhs) ,iterationscount(p_struct->iterationscount),terminationtype(p_struct->terminationtype),nfunc(p_struct->nfunc),njac(p_struct->njac),ngrad(p_struct->ngrad),nhess(p_struct->nhess),ncholesky(p_struct->ncholesky)
{
}

minlmreport& minlmreport::operator=(const minlmreport &rhs)
{
    if( this==&rhs )
        return *this;
    _minlmreport_owner::operator=(rhs);
    return *this;
}

minlmreport::~minlmreport()
{
}

/*************************************************************************
                IMPROVED LEVENBERG-MARQUARDT METHOD FOR
                 NON-LINEAR LEAST SQUARES OPTIMIZATION

DESCRIPTION:
This function is used to find minimum of function which is represented  as
sum of squares:
    F(x) = f[0]^2(x[0],...,x[n-1]) + ... + f[m-1]^2(x[0],...,x[n-1])
using value of function vector f[] and Jacobian of f[].


REQUIREMENTS:
This algorithm will request following information during its operation:

* function vector f[] at given point X
* function vector f[] and Jacobian of f[] (simultaneously) at given point

There are several overloaded versions of  MinLMOptimize()  function  which
correspond  to  different LM-like optimization algorithms provided by this
unit. You should choose version which accepts fvec()  and jac() callbacks.
First  one  is used to calculate f[] at given point, second one calculates
f[] and Jacobian df[i]/dx[j].

You can try to initialize MinLMState structure with VJ  function and  then
use incorrect version  of  MinLMOptimize()  (for  example,  version  which
works  with  general  form function and does not provide Jacobian), but it
will  lead  to  exception  being  thrown  after first attempt to calculate
Jacobian.


USAGE:
1. User initializes algorithm state with MinLMCreateVJ() call
2. User tunes solver parameters with MinLMSetCond(),  MinLMSetStpMax() and
   other functions
3. User calls MinLMOptimize() function which  takes algorithm  state   and
   callback functions.
4. User calls MinLMResults() to get solution
5. Optionally, user may call MinLMRestartFrom() to solve  another  problem
   with same N/M but another starting point and/or another function.
   MinLMRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   dimension, N>1
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size of X
    M       -   number of functions f[i]
    X       -   initial solution, array[0..N-1]

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

NOTES:
1. you may tune stopping conditions with MinLMSetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use MinLMSetStpMax() function to bound algorithm's steps.

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
void minlmcreatevj(const ae_int_t n, const ae_int_t m, const real_1d_array &x, minlmstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlmcreatevj(n, m, const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::minlmstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
                IMPROVED LEVENBERG-MARQUARDT METHOD FOR
                 NON-LINEAR LEAST SQUARES OPTIMIZATION

DESCRIPTION:
This function is used to find minimum of function which is represented  as
sum of squares:
    F(x) = f[0]^2(x[0],...,x[n-1]) + ... + f[m-1]^2(x[0],...,x[n-1])
using value of function vector f[] and Jacobian of f[].


REQUIREMENTS:
This algorithm will request following information during its operation:

* function vector f[] at given point X
* function vector f[] and Jacobian of f[] (simultaneously) at given point

There are several overloaded versions of  MinLMOptimize()  function  which
correspond  to  different LM-like optimization algorithms provided by this
unit. You should choose version which accepts fvec()  and jac() callbacks.
First  one  is used to calculate f[] at given point, second one calculates
f[] and Jacobian df[i]/dx[j].

You can try to initialize MinLMState structure with VJ  function and  then
use incorrect version  of  MinLMOptimize()  (for  example,  version  which
works  with  general  form function and does not provide Jacobian), but it
will  lead  to  exception  being  thrown  after first attempt to calculate
Jacobian.


USAGE:
1. User initializes algorithm state with MinLMCreateVJ() call
2. User tunes solver parameters with MinLMSetCond(),  MinLMSetStpMax() and
   other functions
3. User calls MinLMOptimize() function which  takes algorithm  state   and
   callback functions.
4. User calls MinLMResults() to get solution
5. Optionally, user may call MinLMRestartFrom() to solve  another  problem
   with same N/M but another starting point and/or another function.
   MinLMRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   dimension, N>1
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size of X
    M       -   number of functions f[i]
    X       -   initial solution, array[0..N-1]

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

NOTES:
1. you may tune stopping conditions with MinLMSetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use MinLMSetStpMax() function to bound algorithm's steps.

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
void minlmcreatevj(const ae_int_t m, const real_1d_array &x, minlmstate &state)
{
    alglib_impl::ae_state _alglib_env_state;    
    ae_int_t n;

    n = x.length();
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlmcreatevj(n, m, const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::minlmstate*>(state.c_ptr()), &_alglib_env_state);

        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
                IMPROVED LEVENBERG-MARQUARDT METHOD FOR
                 NON-LINEAR LEAST SQUARES OPTIMIZATION

DESCRIPTION:
This function is used to find minimum of function which is represented  as
sum of squares:
    F(x) = f[0]^2(x[0],...,x[n-1]) + ... + f[m-1]^2(x[0],...,x[n-1])
using value of function vector f[] only. Finite differences  are  used  to
calculate Jacobian.


REQUIREMENTS:
This algorithm will request following information during its operation:
* function vector f[] at given point X

There are several overloaded versions of  MinLMOptimize()  function  which
correspond  to  different LM-like optimization algorithms provided by this
unit. You should choose version which accepts fvec() callback.

You can try to initialize MinLMState structure with VJ  function and  then
use incorrect version  of  MinLMOptimize()  (for  example,  version  which
works with general form function and does not accept function vector), but
it will  lead  to  exception being thrown after first attempt to calculate
Jacobian.


USAGE:
1. User initializes algorithm state with MinLMCreateV() call
2. User tunes solver parameters with MinLMSetCond(),  MinLMSetStpMax() and
   other functions
3. User calls MinLMOptimize() function which  takes algorithm  state   and
   callback functions.
4. User calls MinLMResults() to get solution
5. Optionally, user may call MinLMRestartFrom() to solve  another  problem
   with same N/M but another starting point and/or another function.
   MinLMRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   dimension, N>1
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size of X
    M       -   number of functions f[i]
    X       -   initial solution, array[0..N-1]
    DiffStep-   differentiation step, >0

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

See also MinLMIteration, MinLMResults.

NOTES:
1. you may tune stopping conditions with MinLMSetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use MinLMSetStpMax() function to bound algorithm's steps.

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
void minlmcreatev(const ae_int_t n, const ae_int_t m, const real_1d_array &x, const double diffstep, minlmstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlmcreatev(n, m, const_cast<alglib_impl::ae_vector*>(x.c_ptr()), diffstep, const_cast<alglib_impl::minlmstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
                IMPROVED LEVENBERG-MARQUARDT METHOD FOR
                 NON-LINEAR LEAST SQUARES OPTIMIZATION

DESCRIPTION:
This function is used to find minimum of function which is represented  as
sum of squares:
    F(x) = f[0]^2(x[0],...,x[n-1]) + ... + f[m-1]^2(x[0],...,x[n-1])
using value of function vector f[] only. Finite differences  are  used  to
calculate Jacobian.


REQUIREMENTS:
This algorithm will request following information during its operation:
* function vector f[] at given point X

There are several overloaded versions of  MinLMOptimize()  function  which
correspond  to  different LM-like optimization algorithms provided by this
unit. You should choose version which accepts fvec() callback.

You can try to initialize MinLMState structure with VJ  function and  then
use incorrect version  of  MinLMOptimize()  (for  example,  version  which
works with general form function and does not accept function vector), but
it will  lead  to  exception being thrown after first attempt to calculate
Jacobian.


USAGE:
1. User initializes algorithm state with MinLMCreateV() call
2. User tunes solver parameters with MinLMSetCond(),  MinLMSetStpMax() and
   other functions
3. User calls MinLMOptimize() function which  takes algorithm  state   and
   callback functions.
4. User calls MinLMResults() to get solution
5. Optionally, user may call MinLMRestartFrom() to solve  another  problem
   with same N/M but another starting point and/or another function.
   MinLMRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   dimension, N>1
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size of X
    M       -   number of functions f[i]
    X       -   initial solution, array[0..N-1]
    DiffStep-   differentiation step, >0

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

See also MinLMIteration, MinLMResults.

NOTES:
1. you may tune stopping conditions with MinLMSetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use MinLMSetStpMax() function to bound algorithm's steps.

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
void minlmcreatev(const ae_int_t m, const real_1d_array &x, const double diffstep, minlmstate &state)
{
    alglib_impl::ae_state _alglib_env_state;    
    ae_int_t n;

    n = x.length();
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlmcreatev(n, m, const_cast<alglib_impl::ae_vector*>(x.c_ptr()), diffstep, const_cast<alglib_impl::minlmstate*>(state.c_ptr()), &_alglib_env_state);

        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
    LEVENBERG-MARQUARDT-LIKE METHOD FOR NON-LINEAR OPTIMIZATION

DESCRIPTION:
This  function  is  used  to  find  minimum  of general form (not "sum-of-
-squares") function
    F = F(x[0], ..., x[n-1])
using  its  gradient  and  Hessian.  Levenberg-Marquardt modification with
L-BFGS pre-optimization and internal pre-conditioned  L-BFGS  optimization
after each Levenberg-Marquardt step is used.


REQUIREMENTS:
This algorithm will request following information during its operation:

* function value F at given point X
* F and gradient G (simultaneously) at given point X
* F, G and Hessian H (simultaneously) at given point X

There are several overloaded versions of  MinLMOptimize()  function  which
correspond  to  different LM-like optimization algorithms provided by this
unit. You should choose version which accepts func(),  grad()  and  hess()
function pointers. First pointer is used to calculate F  at  given  point,
second  one  calculates  F(x)  and  grad F(x),  third one calculates F(x),
grad F(x), hess F(x).

You can try to initialize MinLMState structure with FGH-function and  then
use incorrect version of MinLMOptimize() (for example, version which  does
not provide Hessian matrix), but it will lead to  exception  being  thrown
after first attempt to calculate Hessian.


USAGE:
1. User initializes algorithm state with MinLMCreateFGH() call
2. User tunes solver parameters with MinLMSetCond(),  MinLMSetStpMax() and
   other functions
3. User calls MinLMOptimize() function which  takes algorithm  state   and
   pointers (delegates, etc.) to callback functions.
4. User calls MinLMResults() to get solution
5. Optionally, user may call MinLMRestartFrom() to solve  another  problem
   with same N but another starting point and/or another function.
   MinLMRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   dimension, N>1
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size of X
    X       -   initial solution, array[0..N-1]

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

NOTES:
1. you may tune stopping conditions with MinLMSetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use MinLMSetStpMax() function to bound algorithm's steps.

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
void minlmcreatefgh(const ae_int_t n, const real_1d_array &x, minlmstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlmcreatefgh(n, const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::minlmstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
    LEVENBERG-MARQUARDT-LIKE METHOD FOR NON-LINEAR OPTIMIZATION

DESCRIPTION:
This  function  is  used  to  find  minimum  of general form (not "sum-of-
-squares") function
    F = F(x[0], ..., x[n-1])
using  its  gradient  and  Hessian.  Levenberg-Marquardt modification with
L-BFGS pre-optimization and internal pre-conditioned  L-BFGS  optimization
after each Levenberg-Marquardt step is used.


REQUIREMENTS:
This algorithm will request following information during its operation:

* function value F at given point X
* F and gradient G (simultaneously) at given point X
* F, G and Hessian H (simultaneously) at given point X

There are several overloaded versions of  MinLMOptimize()  function  which
correspond  to  different LM-like optimization algorithms provided by this
unit. You should choose version which accepts func(),  grad()  and  hess()
function pointers. First pointer is used to calculate F  at  given  point,
second  one  calculates  F(x)  and  grad F(x),  third one calculates F(x),
grad F(x), hess F(x).

You can try to initialize MinLMState structure with FGH-function and  then
use incorrect version of MinLMOptimize() (for example, version which  does
not provide Hessian matrix), but it will lead to  exception  being  thrown
after first attempt to calculate Hessian.


USAGE:
1. User initializes algorithm state with MinLMCreateFGH() call
2. User tunes solver parameters with MinLMSetCond(),  MinLMSetStpMax() and
   other functions
3. User calls MinLMOptimize() function which  takes algorithm  state   and
   pointers (delegates, etc.) to callback functions.
4. User calls MinLMResults() to get solution
5. Optionally, user may call MinLMRestartFrom() to solve  another  problem
   with same N but another starting point and/or another function.
   MinLMRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   dimension, N>1
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size of X
    X       -   initial solution, array[0..N-1]

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

NOTES:
1. you may tune stopping conditions with MinLMSetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use MinLMSetStpMax() function to bound algorithm's steps.

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
void minlmcreatefgh(const real_1d_array &x, minlmstate &state)
{
    alglib_impl::ae_state _alglib_env_state;    
    ae_int_t n;

    n = x.length();
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlmcreatefgh(n, const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::minlmstate*>(state.c_ptr()), &_alglib_env_state);

        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
                IMPROVED LEVENBERG-MARQUARDT METHOD FOR
                 NON-LINEAR LEAST SQUARES OPTIMIZATION

DESCRIPTION:
This function is used to find minimum of function which is represented  as
sum of squares:
    F(x) = f[0]^2(x[0],...,x[n-1]) + ... + f[m-1]^2(x[0],...,x[n-1])
using:
* value of function vector f[]
* value of Jacobian of f[]
* gradient of merit function F(x)

This function creates optimizer which uses acceleration strategy 2.  Cheap
gradient of merit function (which is twice the product of function  vector
and Jacobian) is used for accelerated iterations (see User Guide for  more
info on this subject).

REQUIREMENTS:
This algorithm will request following information during its operation:

* function vector f[] at given point X
* function vector f[] and Jacobian of f[] (simultaneously) at given point
* gradient of

There are several overloaded versions of  MinLMOptimize()  function  which
correspond  to  different LM-like optimization algorithms provided by this
unit. You should choose version which accepts  fvec(),  jac()  and  grad()
callbacks. First one is used to calculate f[] at given point,  second  one
calculates f[] and Jacobian df[i]/dx[j], last one calculates  gradient  of
merit function F(x).

You can try to initialize MinLMState structure with VJ  function and  then
use incorrect version  of  MinLMOptimize()  (for  example,  version  which
works  with  general  form function and does not provide Jacobian), but it
will  lead  to  exception  being  thrown  after first attempt to calculate
Jacobian.


USAGE:
1. User initializes algorithm state with MinLMCreateVGJ() call
2. User tunes solver parameters with MinLMSetCond(),  MinLMSetStpMax() and
   other functions
3. User calls MinLMOptimize() function which  takes algorithm  state   and
   callback functions.
4. User calls MinLMResults() to get solution
5. Optionally, user may call MinLMRestartFrom() to solve  another  problem
   with same N/M but another starting point and/or another function.
   MinLMRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   dimension, N>1
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size of X
    M       -   number of functions f[i]
    X       -   initial solution, array[0..N-1]

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

NOTES:
1. you may tune stopping conditions with MinLMSetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use MinLMSetStpMax() function to bound algorithm's steps.

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
void minlmcreatevgj(const ae_int_t n, const ae_int_t m, const real_1d_array &x, minlmstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlmcreatevgj(n, m, const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::minlmstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
                IMPROVED LEVENBERG-MARQUARDT METHOD FOR
                 NON-LINEAR LEAST SQUARES OPTIMIZATION

DESCRIPTION:
This function is used to find minimum of function which is represented  as
sum of squares:
    F(x) = f[0]^2(x[0],...,x[n-1]) + ... + f[m-1]^2(x[0],...,x[n-1])
using:
* value of function vector f[]
* value of Jacobian of f[]
* gradient of merit function F(x)

This function creates optimizer which uses acceleration strategy 2.  Cheap
gradient of merit function (which is twice the product of function  vector
and Jacobian) is used for accelerated iterations (see User Guide for  more
info on this subject).

REQUIREMENTS:
This algorithm will request following information during its operation:

* function vector f[] at given point X
* function vector f[] and Jacobian of f[] (simultaneously) at given point
* gradient of

There are several overloaded versions of  MinLMOptimize()  function  which
correspond  to  different LM-like optimization algorithms provided by this
unit. You should choose version which accepts  fvec(),  jac()  and  grad()
callbacks. First one is used to calculate f[] at given point,  second  one
calculates f[] and Jacobian df[i]/dx[j], last one calculates  gradient  of
merit function F(x).

You can try to initialize MinLMState structure with VJ  function and  then
use incorrect version  of  MinLMOptimize()  (for  example,  version  which
works  with  general  form function and does not provide Jacobian), but it
will  lead  to  exception  being  thrown  after first attempt to calculate
Jacobian.


USAGE:
1. User initializes algorithm state with MinLMCreateVGJ() call
2. User tunes solver parameters with MinLMSetCond(),  MinLMSetStpMax() and
   other functions
3. User calls MinLMOptimize() function which  takes algorithm  state   and
   callback functions.
4. User calls MinLMResults() to get solution
5. Optionally, user may call MinLMRestartFrom() to solve  another  problem
   with same N/M but another starting point and/or another function.
   MinLMRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   dimension, N>1
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size of X
    M       -   number of functions f[i]
    X       -   initial solution, array[0..N-1]

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

NOTES:
1. you may tune stopping conditions with MinLMSetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use MinLMSetStpMax() function to bound algorithm's steps.

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
void minlmcreatevgj(const ae_int_t m, const real_1d_array &x, minlmstate &state)
{
    alglib_impl::ae_state _alglib_env_state;    
    ae_int_t n;

    n = x.length();
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlmcreatevgj(n, m, const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::minlmstate*>(state.c_ptr()), &_alglib_env_state);

        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
                   LEVENBERG-MARQUARDT-LIKE METHOD FOR
                  NON-LINEAR LEAST SQUARES OPTIMIZATION

DESCRIPTION:

This function is used to find minimum of function which is represented  as
sum of squares:
    F(x) = f[0]^2(x[0],...,x[n-1]) + ... + f[m-1]^2(x[0],...,x[n-1])
using value of F(), gradient of F(), function vector f[]  and  Jacobian of
f[].

This function is considered obsolete since ALGLIB 3.1.0 and is present for
backward  compatibility  only.  We  recommend to use MinLMCreateVGJ, which
provides similar, but more consistent interface.

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
void minlmcreatefgj(const ae_int_t n, const ae_int_t m, const real_1d_array &x, minlmstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlmcreatefgj(n, m, const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::minlmstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
                   LEVENBERG-MARQUARDT-LIKE METHOD FOR
                  NON-LINEAR LEAST SQUARES OPTIMIZATION

DESCRIPTION:

This function is used to find minimum of function which is represented  as
sum of squares:
    F(x) = f[0]^2(x[0],...,x[n-1]) + ... + f[m-1]^2(x[0],...,x[n-1])
using value of F(), gradient of F(), function vector f[]  and  Jacobian of
f[].

This function is considered obsolete since ALGLIB 3.1.0 and is present for
backward  compatibility  only.  We  recommend to use MinLMCreateVGJ, which
provides similar, but more consistent interface.

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
void minlmcreatefgj(const ae_int_t m, const real_1d_array &x, minlmstate &state)
{
    alglib_impl::ae_state _alglib_env_state;    
    ae_int_t n;

    n = x.length();
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlmcreatefgj(n, m, const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::minlmstate*>(state.c_ptr()), &_alglib_env_state);

        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
    CLASSIC LEVENBERG-MARQUARDT METHOD FOR NON-LINEAR OPTIMIZATION

DESCRIPTION:
This function is used to find minimum of function which is represented  as
sum of squares:
    F(x) = f[0]^2(x[0],...,x[n-1]) + ... + f[m-1]^2(x[0],...,x[n-1])
using  value  of  F(),  function  vector  f[] and Jacobian of f[]. Classic
Levenberg-Marquardt method is used.

This function is considered obsolete since ALGLIB 3.1.0 and is present for
backward  compatibility  only.  We  recommend  to use MinLMCreateVJ, which
provides similar, but more consistent and feature-rich interface.

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
void minlmcreatefj(const ae_int_t n, const ae_int_t m, const real_1d_array &x, minlmstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlmcreatefj(n, m, const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::minlmstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
    CLASSIC LEVENBERG-MARQUARDT METHOD FOR NON-LINEAR OPTIMIZATION

DESCRIPTION:
This function is used to find minimum of function which is represented  as
sum of squares:
    F(x) = f[0]^2(x[0],...,x[n-1]) + ... + f[m-1]^2(x[0],...,x[n-1])
using  value  of  F(),  function  vector  f[] and Jacobian of f[]. Classic
Levenberg-Marquardt method is used.

This function is considered obsolete since ALGLIB 3.1.0 and is present for
backward  compatibility  only.  We  recommend  to use MinLMCreateVJ, which
provides similar, but more consistent and feature-rich interface.

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
void minlmcreatefj(const ae_int_t m, const real_1d_array &x, minlmstate &state)
{
    alglib_impl::ae_state _alglib_env_state;    
    ae_int_t n;

    n = x.length();
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlmcreatefj(n, m, const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::minlmstate*>(state.c_ptr()), &_alglib_env_state);

        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This function sets stopping conditions for Levenberg-Marquardt optimization
algorithm.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    EpsG    -   >=0
                The  subroutine  finishes  its  work   if   the  condition
                ||G||<EpsG is satisfied, where ||.|| means Euclidian norm,
                G - gradient.
    EpsF    -   >=0
                The  subroutine  finishes  its work if on k+1-th iteration
                the  condition  |F(k+1)-F(k)|<=EpsF*max{|F(k)|,|F(k+1)|,1}
                is satisfied.
    EpsX    -   >=0
                The subroutine finishes its work if  on  k+1-th  iteration
                the condition |X(k+1)-X(k)| <= EpsX is fulfilled.
    MaxIts  -   maximum number of iterations. If MaxIts=0, the  number  of
                iterations   is    unlimited.   Only   Levenberg-Marquardt
                iterations  are  counted  (L-BFGS/CG  iterations  are  NOT
                counted because their cost is very low compared to that of
                LM).

Passing EpsG=0, EpsF=0, EpsX=0 and MaxIts=0 (simultaneously) will lead to
automatic stopping criterion selection (small EpsX).

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minlmsetcond(const minlmstate &state, const double epsg, const double epsf, const double epsx, const ae_int_t maxits)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlmsetcond(const_cast<alglib_impl::minlmstate*>(state.c_ptr()), epsg, epsf, epsx, maxits, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This function turns on/off reporting.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    NeedXRep-   whether iteration reports are needed or not

If NeedXRep is True, algorithm will call rep() callback function if  it is
provided to MinLMOptimize(). Both Levenberg-Marquardt and internal  L-BFGS
iterations are reported.

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minlmsetxrep(const minlmstate &state, const bool needxrep)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlmsetxrep(const_cast<alglib_impl::minlmstate*>(state.c_ptr()), needxrep, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This function sets maximum step length

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    StpMax  -   maximum step length, >=0. Set StpMax to 0.0,  if you don't
                want to limit step length.

Use this subroutine when you optimize target function which contains exp()
or  other  fast  growing  functions,  and optimization algorithm makes too
large  steps  which  leads  to overflow. This function allows us to reject
steps  that  are  too  large  (and  therefore  expose  us  to the possible
overflow) without actually calculating function value at the x+stp*d.

NOTE: non-zero StpMax leads to moderate  performance  degradation  because
intermediate  step  of  preconditioned L-BFGS optimization is incompatible
with limits on step size.

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minlmsetstpmax(const minlmstate &state, const double stpmax)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlmsetstpmax(const_cast<alglib_impl::minlmstate*>(state.c_ptr()), stpmax, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This function is used to change acceleration settings

You can choose between three acceleration strategies:
* AccType=0, no acceleration.
* AccType=1, secant updates are used to update quadratic model after  each
  iteration. After fixed number of iterations (or after  model  breakdown)
  we  recalculate  quadratic  model  using  analytic  Jacobian  or  finite
  differences. Number of secant-based iterations depends  on  optimization
  settings: about 3 iterations - when we have analytic Jacobian, up to 2*N
  iterations - when we use finite differences to calculate Jacobian.
* AccType=2, after quadratic model is built and LM step is made, we use it
  as preconditioner for several (5-10) iterations of L-BFGS algorithm.

AccType=1 is recommended when Jacobian  calculation  cost  is  prohibitive
high (several Mx1 function vector calculations  followed  by  several  NxN
Cholesky factorizations are faster than calculation of one M*N  Jacobian).
It should also be used when we have no Jacobian, because finite difference
approximation takes too much time to compute.

AccType=2 is recommended when Jacobian is cheap - much more  cheaper  than
one  Cholesky  factorization.   We   can   reduce   number   of   Cholesky
factorizations at the cost of increased number of  Jacobian  calculations.
Sometimes it helps.

Table below list  optimization  protocols  (XYZ  protocol  corresponds  to
MinLMCreateXYZ) and acceleration types they support (and use by  default).

ACCELERATION TYPES SUPPORTED BY OPTIMIZATION PROTOCOLS:

protocol    0   1   2   comment
V           +   +
VJ          +   +   +
FGH         +       +
VGJ         +   +   +   special protocol, not for widespread use
FJ          +       +   obsolete protocol, not recommended
FGJ         +       +   obsolete protocol, not recommended

DAFAULT VALUES:

protocol    0   1   2   comment
V               x       without acceleration it is so slooooooooow
VJ          x
FGH         x
VGJ                 x   we've implicitly turned (2) by passing gradient
FJ          x           obsolete protocol, not recommended
FGJ                 x   obsolete protocol, not recommended

NOTE: this  function should be called before optimization. Attempt to call
it during algorithm iterations may result in unexpected behavior.

NOTE: attempt to call this function with unsupported protocol/acceleration
combination will result in exception being thrown.

  -- ALGLIB --
     Copyright 14.10.2010 by Bochkanov Sergey
*************************************************************************/
void minlmsetacctype(const minlmstate &state, const ae_int_t acctype)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlmsetacctype(const_cast<alglib_impl::minlmstate*>(state.c_ptr()), acctype, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This function provides reverse communication interface
Reverse communication interface is not documented or recommended to use.
See below for functions which provide better documented API
*************************************************************************/
bool minlmiteration(const minlmstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        ae_bool result = alglib_impl::minlmiteration(const_cast<alglib_impl::minlmstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return *(reinterpret_cast<bool*>(&result));
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}


void minlmoptimize(minlmstate &state,
    void (*fvec)(const real_1d_array &x, real_1d_array &fi, void *ptr),
    void  (*rep)(const real_1d_array &x, double func, void *ptr), 
    void *ptr)
{
    alglib_impl::ae_state _alglib_env_state;
    if( fvec==NULL )
        throw ap_error("ALGLIB: error in 'minlmoptimize()' (fvec is NULL)");
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        while( alglib_impl::minlmiteration(state.c_ptr(), &_alglib_env_state) )
        {
            if( state.needfi )
            {
                fvec(state.x, state.fi, ptr);
                continue;
            }
            if( state.xupdated )
            {
                if( rep!=NULL )
                    rep(state.x, state.f, ptr);
                continue;
            }
            throw ap_error("ALGLIB: error in 'minlmoptimize' (some derivatives were not provided?)");
        }
        alglib_impl::ae_state_clear(&_alglib_env_state);
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}


void minlmoptimize(minlmstate &state,
    void (*fvec)(const real_1d_array &x, real_1d_array &fi, void *ptr),
    void  (*jac)(const real_1d_array &x, real_1d_array &fi, real_2d_array &jac, void *ptr),
    void  (*rep)(const real_1d_array &x, double func, void *ptr), 
    void *ptr)
{
    alglib_impl::ae_state _alglib_env_state;
    if( fvec==NULL )
        throw ap_error("ALGLIB: error in 'minlmoptimize()' (fvec is NULL)");
    if( jac==NULL )
        throw ap_error("ALGLIB: error in 'minlmoptimize()' (jac is NULL)");
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        while( alglib_impl::minlmiteration(state.c_ptr(), &_alglib_env_state) )
        {
            if( state.needfi )
            {
                fvec(state.x, state.fi, ptr);
                continue;
            }
            if( state.needfij )
            {
                jac(state.x, state.fi, state.j, ptr);
                continue;
            }
            if( state.xupdated )
            {
                if( rep!=NULL )
                    rep(state.x, state.f, ptr);
                continue;
            }
            throw ap_error("ALGLIB: error in 'minlmoptimize' (some derivatives were not provided?)");
        }
        alglib_impl::ae_state_clear(&_alglib_env_state);
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}


void minlmoptimize(minlmstate &state,
    void (*func)(const real_1d_array &x, double &func, void *ptr),
    void (*grad)(const real_1d_array &x, double &func, real_1d_array &grad, void *ptr),
    void (*hess)(const real_1d_array &x, double &func, real_1d_array &grad, real_2d_array &hess, void *ptr),
    void  (*rep)(const real_1d_array &x, double func, void *ptr), 
    void *ptr)
{
    alglib_impl::ae_state _alglib_env_state;
    if( func==NULL )
        throw ap_error("ALGLIB: error in 'minlmoptimize()' (func is NULL)");
    if( grad==NULL )
        throw ap_error("ALGLIB: error in 'minlmoptimize()' (grad is NULL)");
    if( hess==NULL )
        throw ap_error("ALGLIB: error in 'minlmoptimize()' (hess is NULL)");
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        while( alglib_impl::minlmiteration(state.c_ptr(), &_alglib_env_state) )
        {
            if( state.needf )
            {
                func(state.x, state.f, ptr);
                continue;
            }
            if( state.needfg )
            {
                grad(state.x, state.f, state.g, ptr);
                continue;
            }
            if( state.needfgh )
            {
                hess(state.x, state.f, state.g, state.h, ptr);
                continue;
            }
            if( state.xupdated )
            {
                if( rep!=NULL )
                    rep(state.x, state.f, ptr);
                continue;
            }
            throw ap_error("ALGLIB: error in 'minlmoptimize' (some derivatives were not provided?)");
        }
        alglib_impl::ae_state_clear(&_alglib_env_state);
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}


void minlmoptimize(minlmstate &state,
    void (*func)(const real_1d_array &x, double &func, void *ptr),
    void  (*jac)(const real_1d_array &x, real_1d_array &fi, real_2d_array &jac, void *ptr),
    void  (*rep)(const real_1d_array &x, double func, void *ptr), 
    void *ptr)
{
    alglib_impl::ae_state _alglib_env_state;
    if( func==NULL )
        throw ap_error("ALGLIB: error in 'minlmoptimize()' (func is NULL)");
    if( jac==NULL )
        throw ap_error("ALGLIB: error in 'minlmoptimize()' (jac is NULL)");
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        while( alglib_impl::minlmiteration(state.c_ptr(), &_alglib_env_state) )
        {
            if( state.needf )
            {
                func(state.x, state.f, ptr);
                continue;
            }
            if( state.needfij )
            {
                jac(state.x, state.fi, state.j, ptr);
                continue;
            }
            if( state.xupdated )
            {
                if( rep!=NULL )
                    rep(state.x, state.f, ptr);
                continue;
            }
            throw ap_error("ALGLIB: error in 'minlmoptimize' (some derivatives were not provided?)");
        }
        alglib_impl::ae_state_clear(&_alglib_env_state);
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}


void minlmoptimize(minlmstate &state,
    void (*func)(const real_1d_array &x, double &func, void *ptr),
    void (*grad)(const real_1d_array &x, double &func, real_1d_array &grad, void *ptr),
    void  (*jac)(const real_1d_array &x, real_1d_array &fi, real_2d_array &jac, void *ptr),
    void  (*rep)(const real_1d_array &x, double func, void *ptr), 
    void *ptr)
{
    alglib_impl::ae_state _alglib_env_state;
    if( func==NULL )
        throw ap_error("ALGLIB: error in 'minlmoptimize()' (func is NULL)");
    if( grad==NULL )
        throw ap_error("ALGLIB: error in 'minlmoptimize()' (grad is NULL)");
    if( jac==NULL )
        throw ap_error("ALGLIB: error in 'minlmoptimize()' (jac is NULL)");
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        while( alglib_impl::minlmiteration(state.c_ptr(), &_alglib_env_state) )
        {
            if( state.needf )
            {
                func(state.x, state.f, ptr);
                continue;
            }
            if( state.needfg )
            {
                grad(state.x, state.f, state.g, ptr);
                continue;
            }
            if( state.needfij )
            {
                jac(state.x, state.fi, state.j, ptr);
                continue;
            }
            if( state.xupdated )
            {
                if( rep!=NULL )
                    rep(state.x, state.f, ptr);
                continue;
            }
            throw ap_error("ALGLIB: error in 'minlmoptimize' (some derivatives were not provided?)");
        }
        alglib_impl::ae_state_clear(&_alglib_env_state);
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}



/*************************************************************************
Levenberg-Marquardt algorithm results

INPUT PARAMETERS:
    State   -   algorithm state

OUTPUT PARAMETERS:
    X       -   array[0..N-1], solution
    Rep     -   optimization report;
                see comments for this structure for more info.

  -- ALGLIB --
     Copyright 10.03.2009 by Bochkanov Sergey
*************************************************************************/
void minlmresults(const minlmstate &state, real_1d_array &x, minlmreport &rep)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlmresults(const_cast<alglib_impl::minlmstate*>(state.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::minlmreport*>(rep.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
Levenberg-Marquardt algorithm results

Buffered implementation of MinLMResults(), which uses pre-allocated buffer
to store X[]. If buffer size is  too  small,  it  resizes  buffer.  It  is
intended to be used in the inner cycles of performance critical algorithms
where array reallocation penalty is too large to be ignored.

  -- ALGLIB --
     Copyright 10.03.2009 by Bochkanov Sergey
*************************************************************************/
void minlmresultsbuf(const minlmstate &state, real_1d_array &x, minlmreport &rep)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlmresultsbuf(const_cast<alglib_impl::minlmstate*>(state.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::minlmreport*>(rep.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This  subroutine  restarts  LM  algorithm from new point. All optimization
parameters are left unchanged.

This  function  allows  to  solve multiple  optimization  problems  (which
must have same number of dimensions) without object reallocation penalty.

INPUT PARAMETERS:
    State   -   structure used for reverse communication previously
                allocated with MinLMCreateXXX call.
    X       -   new starting point.

  -- ALGLIB --
     Copyright 30.07.2010 by Bochkanov Sergey
*************************************************************************/
void minlmrestartfrom(const minlmstate &state, const real_1d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minlmrestartfrom(const_cast<alglib_impl::minlmstate*>(state.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************

*************************************************************************/
_mincgstate_owner::_mincgstate_owner()
{
    p_struct = (alglib_impl::mincgstate*)alglib_impl::ae_malloc(sizeof(alglib_impl::mincgstate), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_mincgstate_init(p_struct, NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_mincgstate_owner::_mincgstate_owner(const _mincgstate_owner &rhs)
{
    p_struct = (alglib_impl::mincgstate*)alglib_impl::ae_malloc(sizeof(alglib_impl::mincgstate), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_mincgstate_init_copy(p_struct, const_cast<alglib_impl::mincgstate*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_mincgstate_owner& _mincgstate_owner::operator=(const _mincgstate_owner &rhs)
{
    if( this==&rhs )
        return *this;
    alglib_impl::_mincgstate_clear(p_struct);
    if( !alglib_impl::_mincgstate_init_copy(p_struct, const_cast<alglib_impl::mincgstate*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
    return *this;
}

_mincgstate_owner::~_mincgstate_owner()
{
    alglib_impl::_mincgstate_clear(p_struct);
    ae_free(p_struct);
}

alglib_impl::mincgstate* _mincgstate_owner::c_ptr()
{
    return p_struct;
}

alglib_impl::mincgstate* _mincgstate_owner::c_ptr() const
{
    return const_cast<alglib_impl::mincgstate*>(p_struct);
}
mincgstate::mincgstate() : _mincgstate_owner() ,needfg(p_struct->needfg),xupdated(p_struct->xupdated),f(p_struct->f),g(&p_struct->g),x(&p_struct->x)
{
}

mincgstate::mincgstate(const mincgstate &rhs):_mincgstate_owner(rhs) ,needfg(p_struct->needfg),xupdated(p_struct->xupdated),f(p_struct->f),g(&p_struct->g),x(&p_struct->x)
{
}

mincgstate& mincgstate::operator=(const mincgstate &rhs)
{
    if( this==&rhs )
        return *this;
    _mincgstate_owner::operator=(rhs);
    return *this;
}

mincgstate::~mincgstate()
{
}


/*************************************************************************

*************************************************************************/
_mincgreport_owner::_mincgreport_owner()
{
    p_struct = (alglib_impl::mincgreport*)alglib_impl::ae_malloc(sizeof(alglib_impl::mincgreport), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_mincgreport_init(p_struct, NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_mincgreport_owner::_mincgreport_owner(const _mincgreport_owner &rhs)
{
    p_struct = (alglib_impl::mincgreport*)alglib_impl::ae_malloc(sizeof(alglib_impl::mincgreport), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_mincgreport_init_copy(p_struct, const_cast<alglib_impl::mincgreport*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_mincgreport_owner& _mincgreport_owner::operator=(const _mincgreport_owner &rhs)
{
    if( this==&rhs )
        return *this;
    alglib_impl::_mincgreport_clear(p_struct);
    if( !alglib_impl::_mincgreport_init_copy(p_struct, const_cast<alglib_impl::mincgreport*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
    return *this;
}

_mincgreport_owner::~_mincgreport_owner()
{
    alglib_impl::_mincgreport_clear(p_struct);
    ae_free(p_struct);
}

alglib_impl::mincgreport* _mincgreport_owner::c_ptr()
{
    return p_struct;
}

alglib_impl::mincgreport* _mincgreport_owner::c_ptr() const
{
    return const_cast<alglib_impl::mincgreport*>(p_struct);
}
mincgreport::mincgreport() : _mincgreport_owner() ,iterationscount(p_struct->iterationscount),nfev(p_struct->nfev),terminationtype(p_struct->terminationtype)
{
}

mincgreport::mincgreport(const mincgreport &rhs):_mincgreport_owner(rhs) ,iterationscount(p_struct->iterationscount),nfev(p_struct->nfev),terminationtype(p_struct->terminationtype)
{
}

mincgreport& mincgreport::operator=(const mincgreport &rhs)
{
    if( this==&rhs )
        return *this;
    _mincgreport_owner::operator=(rhs);
    return *this;
}

mincgreport::~mincgreport()
{
}

/*************************************************************************
        NONLINEAR CONJUGATE GRADIENT METHOD

DESCRIPTION:
The subroutine minimizes function F(x) of N arguments by using one of  the
nonlinear conjugate gradient methods.

These CG methods are globally convergent (even on non-convex functions) as
long as grad(f) is Lipschitz continuous in  a  some  neighborhood  of  the
L = { x : f(x)<=f(x0) }.


REQUIREMENTS:
Algorithm will request following information during its operation:
* function value F and its gradient G (simultaneously) at given point X


USAGE:
1. User initializes algorithm state with MinCGCreate() call
2. User tunes solver parameters with MinCGSetCond(), MinCGSetStpMax() and
   other functions
3. User calls MinCGOptimize() function which takes algorithm  state   and
   pointer (delegate, etc.) to callback function which calculates F/G.
4. User calls MinCGResults() to get solution
5. Optionally, user may call MinCGRestartFrom() to solve another  problem
   with same N but another starting point and/or another function.
   MinCGRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   problem dimension, N>0:
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size of X
    X       -   starting point, array[0..N-1].

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 25.03.2010 by Bochkanov Sergey
*************************************************************************/
void mincgcreate(const ae_int_t n, const real_1d_array &x, mincgstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::mincgcreate(n, const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::mincgstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
        NONLINEAR CONJUGATE GRADIENT METHOD

DESCRIPTION:
The subroutine minimizes function F(x) of N arguments by using one of  the
nonlinear conjugate gradient methods.

These CG methods are globally convergent (even on non-convex functions) as
long as grad(f) is Lipschitz continuous in  a  some  neighborhood  of  the
L = { x : f(x)<=f(x0) }.


REQUIREMENTS:
Algorithm will request following information during its operation:
* function value F and its gradient G (simultaneously) at given point X


USAGE:
1. User initializes algorithm state with MinCGCreate() call
2. User tunes solver parameters with MinCGSetCond(), MinCGSetStpMax() and
   other functions
3. User calls MinCGOptimize() function which takes algorithm  state   and
   pointer (delegate, etc.) to callback function which calculates F/G.
4. User calls MinCGResults() to get solution
5. Optionally, user may call MinCGRestartFrom() to solve another  problem
   with same N but another starting point and/or another function.
   MinCGRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   problem dimension, N>0:
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size of X
    X       -   starting point, array[0..N-1].

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 25.03.2010 by Bochkanov Sergey
*************************************************************************/
void mincgcreate(const real_1d_array &x, mincgstate &state)
{
    alglib_impl::ae_state _alglib_env_state;    
    ae_int_t n;

    n = x.length();
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::mincgcreate(n, const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::mincgstate*>(state.c_ptr()), &_alglib_env_state);

        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This function sets stopping conditions for CG optimization algorithm.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    EpsG    -   >=0
                The  subroutine  finishes  its  work   if   the  condition
                ||G||<EpsG is satisfied, where ||.|| means Euclidian norm,
                G - gradient.
    EpsF    -   >=0
                The  subroutine  finishes  its work if on k+1-th iteration
                the  condition  |F(k+1)-F(k)|<=EpsF*max{|F(k)|,|F(k+1)|,1}
                is satisfied.
    EpsX    -   >=0
                The subroutine finishes its work if  on  k+1-th  iteration
                the condition |X(k+1)-X(k)| <= EpsX is fulfilled.
    MaxIts  -   maximum number of iterations. If MaxIts=0, the  number  of
                iterations is unlimited.

Passing EpsG=0, EpsF=0, EpsX=0 and MaxIts=0 (simultaneously) will lead to
automatic stopping criterion selection (small EpsX).

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void mincgsetcond(const mincgstate &state, const double epsg, const double epsf, const double epsx, const ae_int_t maxits)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::mincgsetcond(const_cast<alglib_impl::mincgstate*>(state.c_ptr()), epsg, epsf, epsx, maxits, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This function turns on/off reporting.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    NeedXRep-   whether iteration reports are needed or not

If NeedXRep is True, algorithm will call rep() callback function if  it is
provided to MinCGOptimize().

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void mincgsetxrep(const mincgstate &state, const bool needxrep)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::mincgsetxrep(const_cast<alglib_impl::mincgstate*>(state.c_ptr()), needxrep, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This function sets CG algorithm.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    CGType  -   algorithm type:
                * -1    automatic selection of the best algorithm
                * 0     DY (Dai and Yuan) algorithm
                * 1     Hybrid DY-HS algorithm

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void mincgsetcgtype(const mincgstate &state, const ae_int_t cgtype)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::mincgsetcgtype(const_cast<alglib_impl::mincgstate*>(state.c_ptr()), cgtype, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This function sets maximum step length

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    StpMax  -   maximum step length, >=0. Set StpMax to 0.0,  if you don't
                want to limit step length.

Use this subroutine when you optimize target function which contains exp()
or  other  fast  growing  functions,  and optimization algorithm makes too
large  steps  which  leads  to overflow. This function allows us to reject
steps  that  are  too  large  (and  therefore  expose  us  to the possible
overflow) without actually calculating function value at the x+stp*d.

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void mincgsetstpmax(const mincgstate &state, const double stpmax)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::mincgsetstpmax(const_cast<alglib_impl::mincgstate*>(state.c_ptr()), stpmax, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This function provides reverse communication interface
Reverse communication interface is not documented or recommended to use.
See below for functions which provide better documented API
*************************************************************************/
bool mincgiteration(const mincgstate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        ae_bool result = alglib_impl::mincgiteration(const_cast<alglib_impl::mincgstate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return *(reinterpret_cast<bool*>(&result));
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}


void mincgoptimize(mincgstate &state,
    void (*grad)(const real_1d_array &x, double &func, real_1d_array &grad, void *ptr),
    void  (*rep)(const real_1d_array &x, double func, void *ptr), 
    void *ptr)
{
    alglib_impl::ae_state _alglib_env_state;
    if( grad==NULL )
        throw ap_error("ALGLIB: error in 'mincgoptimize()' (grad is NULL)");
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        while( alglib_impl::mincgiteration(state.c_ptr(), &_alglib_env_state) )
        {
            if( state.needfg )
            {
                grad(state.x, state.f, state.g, ptr);
                continue;
            }
            if( state.xupdated )
            {
                if( rep!=NULL )
                    rep(state.x, state.f, ptr);
                continue;
            }
            throw ap_error("ALGLIB: error in 'mincgoptimize' (some derivatives were not provided?)");
        }
        alglib_impl::ae_state_clear(&_alglib_env_state);
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}



/*************************************************************************
Conjugate gradient results

INPUT PARAMETERS:
    State   -   algorithm state

OUTPUT PARAMETERS:
    X       -   array[0..N-1], solution
    Rep     -   optimization report:
                * Rep.TerminationType completetion code:
                    * -2    rounding errors prevent further improvement.
                            X contains best point found.
                    * -1    incorrect parameters were specified
                    *  1    relative function improvement is no more than
                            EpsF.
                    *  2    relative step is no more than EpsX.
                    *  4    gradient norm is no more than EpsG
                    *  5    MaxIts steps was taken
                    *  7    stopping conditions are too stringent,
                            further improvement is impossible
                * Rep.IterationsCount contains iterations count
                * NFEV countains number of function calculations

  -- ALGLIB --
     Copyright 20.04.2009 by Bochkanov Sergey
*************************************************************************/
void mincgresults(const mincgstate &state, real_1d_array &x, mincgreport &rep)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::mincgresults(const_cast<alglib_impl::mincgstate*>(state.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::mincgreport*>(rep.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
Conjugate gradient results

Buffered implementation of MinCGResults(), which uses pre-allocated buffer
to store X[]. If buffer size is  too  small,  it  resizes  buffer.  It  is
intended to be used in the inner cycles of performance critical algorithms
where array reallocation penalty is too large to be ignored.

  -- ALGLIB --
     Copyright 20.04.2009 by Bochkanov Sergey
*************************************************************************/
void mincgresultsbuf(const mincgstate &state, real_1d_array &x, mincgreport &rep)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::mincgresultsbuf(const_cast<alglib_impl::mincgstate*>(state.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::mincgreport*>(rep.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This  subroutine  restarts  CG  algorithm from new point. All optimization
parameters are left unchanged.

This  function  allows  to  solve multiple  optimization  problems  (which
must have same number of dimensions) without object reallocation penalty.

INPUT PARAMETERS:
    State   -   structure used to store algorithm state.
    X       -   new starting point.

  -- ALGLIB --
     Copyright 30.07.2010 by Bochkanov Sergey
*************************************************************************/
void mincgrestartfrom(const mincgstate &state, const real_1d_array &x)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::mincgrestartfrom(const_cast<alglib_impl::mincgstate*>(state.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************

*************************************************************************/
_minasastate_owner::_minasastate_owner()
{
    p_struct = (alglib_impl::minasastate*)alglib_impl::ae_malloc(sizeof(alglib_impl::minasastate), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_minasastate_init(p_struct, NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_minasastate_owner::_minasastate_owner(const _minasastate_owner &rhs)
{
    p_struct = (alglib_impl::minasastate*)alglib_impl::ae_malloc(sizeof(alglib_impl::minasastate), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_minasastate_init_copy(p_struct, const_cast<alglib_impl::minasastate*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_minasastate_owner& _minasastate_owner::operator=(const _minasastate_owner &rhs)
{
    if( this==&rhs )
        return *this;
    alglib_impl::_minasastate_clear(p_struct);
    if( !alglib_impl::_minasastate_init_copy(p_struct, const_cast<alglib_impl::minasastate*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
    return *this;
}

_minasastate_owner::~_minasastate_owner()
{
    alglib_impl::_minasastate_clear(p_struct);
    ae_free(p_struct);
}

alglib_impl::minasastate* _minasastate_owner::c_ptr()
{
    return p_struct;
}

alglib_impl::minasastate* _minasastate_owner::c_ptr() const
{
    return const_cast<alglib_impl::minasastate*>(p_struct);
}
minasastate::minasastate() : _minasastate_owner() ,needfg(p_struct->needfg),xupdated(p_struct->xupdated),f(p_struct->f),g(&p_struct->g),x(&p_struct->x)
{
}

minasastate::minasastate(const minasastate &rhs):_minasastate_owner(rhs) ,needfg(p_struct->needfg),xupdated(p_struct->xupdated),f(p_struct->f),g(&p_struct->g),x(&p_struct->x)
{
}

minasastate& minasastate::operator=(const minasastate &rhs)
{
    if( this==&rhs )
        return *this;
    _minasastate_owner::operator=(rhs);
    return *this;
}

minasastate::~minasastate()
{
}


/*************************************************************************

*************************************************************************/
_minasareport_owner::_minasareport_owner()
{
    p_struct = (alglib_impl::minasareport*)alglib_impl::ae_malloc(sizeof(alglib_impl::minasareport), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_minasareport_init(p_struct, NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_minasareport_owner::_minasareport_owner(const _minasareport_owner &rhs)
{
    p_struct = (alglib_impl::minasareport*)alglib_impl::ae_malloc(sizeof(alglib_impl::minasareport), NULL);
    if( p_struct==NULL )
        throw ap_error("ALGLIB: malloc error");
    if( !alglib_impl::_minasareport_init_copy(p_struct, const_cast<alglib_impl::minasareport*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
}

_minasareport_owner& _minasareport_owner::operator=(const _minasareport_owner &rhs)
{
    if( this==&rhs )
        return *this;
    alglib_impl::_minasareport_clear(p_struct);
    if( !alglib_impl::_minasareport_init_copy(p_struct, const_cast<alglib_impl::minasareport*>(rhs.p_struct), NULL, ae_false) )
        throw ap_error("ALGLIB: malloc error");
    return *this;
}

_minasareport_owner::~_minasareport_owner()
{
    alglib_impl::_minasareport_clear(p_struct);
    ae_free(p_struct);
}

alglib_impl::minasareport* _minasareport_owner::c_ptr()
{
    return p_struct;
}

alglib_impl::minasareport* _minasareport_owner::c_ptr() const
{
    return const_cast<alglib_impl::minasareport*>(p_struct);
}
minasareport::minasareport() : _minasareport_owner() ,iterationscount(p_struct->iterationscount),nfev(p_struct->nfev),terminationtype(p_struct->terminationtype),activeconstraints(p_struct->activeconstraints)
{
}

minasareport::minasareport(const minasareport &rhs):_minasareport_owner(rhs) ,iterationscount(p_struct->iterationscount),nfev(p_struct->nfev),terminationtype(p_struct->terminationtype),activeconstraints(p_struct->activeconstraints)
{
}

minasareport& minasareport::operator=(const minasareport &rhs)
{
    if( this==&rhs )
        return *this;
    _minasareport_owner::operator=(rhs);
    return *this;
}

minasareport::~minasareport()
{
}

/*************************************************************************
              NONLINEAR BOUND CONSTRAINED OPTIMIZATION USING
                      MODIFIED ACTIVE SET ALGORITHM
                   WILLIAM W. HAGER AND HONGCHAO ZHANG

DESCRIPTION:
The  subroutine  minimizes  function  F(x)  of  N  arguments  with   bound
constraints: BndL[i] <= x[i] <= BndU[i]

This method is  globally  convergent  as  long  as  grad(f)  is  Lipschitz
continuous on a level set: L = { x : f(x)<=f(x0) }.


REQUIREMENTS:
Algorithm will request following information during its operation:
* function value F and its gradient G (simultaneously) at given point X


USAGE:
1. User initializes algorithm state with MinASACreate() call
2. User tunes solver parameters with MinASASetCond() MinASASetStpMax() and
   other functions
3. User calls MinASAOptimize() function which takes algorithm  state   and
   pointer (delegate, etc.) to callback function which calculates F/G.
4. User calls MinASAResults() to get solution
5. Optionally, user may call MinASARestartFrom() to solve another  problem
   with same N but another starting point and/or another function.
   MinASARestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   problem dimension, N>0:
                * if given, only leading N elements of X are used
                * if not given, automatically determined from sizes of
                  X/BndL/BndU.
    X       -   starting point, array[0..N-1].
    BndL    -   lower bounds, array[0..N-1].
                all elements MUST be specified,  i.e.  all  variables  are
                bounded. However, if some (all) variables  are  unbounded,
                you may specify very small number as bound: -1000,  -1.0E6
                or -1.0E300, or something like that.
    BndU    -   upper bounds, array[0..N-1].
                all elements MUST be specified,  i.e.  all  variables  are
                bounded. However, if some (all) variables  are  unbounded,
                you may specify very large number as bound: +1000,  +1.0E6
                or +1.0E300, or something like that.

OUTPUT PARAMETERS:
    State   -   structure stores algorithm state

NOTES:

1. you may tune stopping conditions with MinASASetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use MinASASetStpMax() function to bound algorithm's steps.
3. this function does NOT support infinite/NaN values in X, BndL, BndU.

  -- ALGLIB --
     Copyright 25.03.2010 by Bochkanov Sergey
*************************************************************************/
void minasacreate(const ae_int_t n, const real_1d_array &x, const real_1d_array &bndl, const real_1d_array &bndu, minasastate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minasacreate(n, const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::ae_vector*>(bndl.c_ptr()), const_cast<alglib_impl::ae_vector*>(bndu.c_ptr()), const_cast<alglib_impl::minasastate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
              NONLINEAR BOUND CONSTRAINED OPTIMIZATION USING
                      MODIFIED ACTIVE SET ALGORITHM
                   WILLIAM W. HAGER AND HONGCHAO ZHANG

DESCRIPTION:
The  subroutine  minimizes  function  F(x)  of  N  arguments  with   bound
constraints: BndL[i] <= x[i] <= BndU[i]

This method is  globally  convergent  as  long  as  grad(f)  is  Lipschitz
continuous on a level set: L = { x : f(x)<=f(x0) }.


REQUIREMENTS:
Algorithm will request following information during its operation:
* function value F and its gradient G (simultaneously) at given point X


USAGE:
1. User initializes algorithm state with MinASACreate() call
2. User tunes solver parameters with MinASASetCond() MinASASetStpMax() and
   other functions
3. User calls MinASAOptimize() function which takes algorithm  state   and
   pointer (delegate, etc.) to callback function which calculates F/G.
4. User calls MinASAResults() to get solution
5. Optionally, user may call MinASARestartFrom() to solve another  problem
   with same N but another starting point and/or another function.
   MinASARestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   problem dimension, N>0:
                * if given, only leading N elements of X are used
                * if not given, automatically determined from sizes of
                  X/BndL/BndU.
    X       -   starting point, array[0..N-1].
    BndL    -   lower bounds, array[0..N-1].
                all elements MUST be specified,  i.e.  all  variables  are
                bounded. However, if some (all) variables  are  unbounded,
                you may specify very small number as bound: -1000,  -1.0E6
                or -1.0E300, or something like that.
    BndU    -   upper bounds, array[0..N-1].
                all elements MUST be specified,  i.e.  all  variables  are
                bounded. However, if some (all) variables  are  unbounded,
                you may specify very large number as bound: +1000,  +1.0E6
                or +1.0E300, or something like that.

OUTPUT PARAMETERS:
    State   -   structure stores algorithm state

NOTES:

1. you may tune stopping conditions with MinASASetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use MinASASetStpMax() function to bound algorithm's steps.
3. this function does NOT support infinite/NaN values in X, BndL, BndU.

  -- ALGLIB --
     Copyright 25.03.2010 by Bochkanov Sergey
*************************************************************************/
void minasacreate(const real_1d_array &x, const real_1d_array &bndl, const real_1d_array &bndu, minasastate &state)
{
    alglib_impl::ae_state _alglib_env_state;    
    ae_int_t n;
    if( (x.length()!=bndl.length()) || (x.length()!=bndu.length()))
        throw ap_error("Error while calling 'minasacreate': looks like one of arguments has wrong size");
    n = x.length();
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minasacreate(n, const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::ae_vector*>(bndl.c_ptr()), const_cast<alglib_impl::ae_vector*>(bndu.c_ptr()), const_cast<alglib_impl::minasastate*>(state.c_ptr()), &_alglib_env_state);

        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This function sets stopping conditions for the ASA optimization algorithm.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    EpsG    -   >=0
                The  subroutine  finishes  its  work   if   the  condition
                ||G||<EpsG is satisfied, where ||.|| means Euclidian norm,
                G - gradient.
    EpsF    -   >=0
                The  subroutine  finishes  its work if on k+1-th iteration
                the  condition  |F(k+1)-F(k)|<=EpsF*max{|F(k)|,|F(k+1)|,1}
                is satisfied.
    EpsX    -   >=0
                The subroutine finishes its work if  on  k+1-th  iteration
                the condition |X(k+1)-X(k)| <= EpsX is fulfilled.
    MaxIts  -   maximum number of iterations. If MaxIts=0, the  number  of
                iterations is unlimited.

Passing EpsG=0, EpsF=0, EpsX=0 and MaxIts=0 (simultaneously) will lead to
automatic stopping criterion selection (small EpsX).

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minasasetcond(const minasastate &state, const double epsg, const double epsf, const double epsx, const ae_int_t maxits)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minasasetcond(const_cast<alglib_impl::minasastate*>(state.c_ptr()), epsg, epsf, epsx, maxits, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This function turns on/off reporting.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    NeedXRep-   whether iteration reports are needed or not

If NeedXRep is True, algorithm will call rep() callback function if  it is
provided to MinASAOptimize().

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minasasetxrep(const minasastate &state, const bool needxrep)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minasasetxrep(const_cast<alglib_impl::minasastate*>(state.c_ptr()), needxrep, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This function sets optimization algorithm.

INPUT PARAMETERS:
    State   -   structure which stores algorithm stat
    UAType  -   algorithm type:
                * -1    automatic selection of the best algorithm
                * 0     DY (Dai and Yuan) algorithm
                * 1     Hybrid DY-HS algorithm

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minasasetalgorithm(const minasastate &state, const ae_int_t algotype)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minasasetalgorithm(const_cast<alglib_impl::minasastate*>(state.c_ptr()), algotype, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This function sets maximum step length

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    StpMax  -   maximum step length, >=0. Set StpMax to 0.0,  if you don't
                want to limit step length (zero by default).

Use this subroutine when you optimize target function which contains exp()
or  other  fast  growing  functions,  and optimization algorithm makes too
large  steps  which  leads  to overflow. This function allows us to reject
steps  that  are  too  large  (and  therefore  expose  us  to the possible
overflow) without actually calculating function value at the x+stp*d.

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minasasetstpmax(const minasastate &state, const double stpmax)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minasasetstpmax(const_cast<alglib_impl::minasastate*>(state.c_ptr()), stpmax, &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This function provides reverse communication interface
Reverse communication interface is not documented or recommended to use.
See below for functions which provide better documented API
*************************************************************************/
bool minasaiteration(const minasastate &state)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        ae_bool result = alglib_impl::minasaiteration(const_cast<alglib_impl::minasastate*>(state.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return *(reinterpret_cast<bool*>(&result));
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}


void minasaoptimize(minasastate &state,
    void (*grad)(const real_1d_array &x, double &func, real_1d_array &grad, void *ptr),
    void  (*rep)(const real_1d_array &x, double func, void *ptr), 
    void *ptr)
{
    alglib_impl::ae_state _alglib_env_state;
    if( grad==NULL )
        throw ap_error("ALGLIB: error in 'minasaoptimize()' (grad is NULL)");
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        while( alglib_impl::minasaiteration(state.c_ptr(), &_alglib_env_state) )
        {
            if( state.needfg )
            {
                grad(state.x, state.f, state.g, ptr);
                continue;
            }
            if( state.xupdated )
            {
                if( rep!=NULL )
                    rep(state.x, state.f, ptr);
                continue;
            }
            throw ap_error("ALGLIB: error in 'minasaoptimize' (some derivatives were not provided?)");
        }
        alglib_impl::ae_state_clear(&_alglib_env_state);
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}



/*************************************************************************
ASA results

INPUT PARAMETERS:
    State   -   algorithm state

OUTPUT PARAMETERS:
    X       -   array[0..N-1], solution
    Rep     -   optimization report:
                * Rep.TerminationType completetion code:
                    * -2    rounding errors prevent further improvement.
                            X contains best point found.
                    * -1    incorrect parameters were specified
                    *  1    relative function improvement is no more than
                            EpsF.
                    *  2    relative step is no more than EpsX.
                    *  4    gradient norm is no more than EpsG
                    *  5    MaxIts steps was taken
                    *  7    stopping conditions are too stringent,
                            further improvement is impossible
                * Rep.IterationsCount contains iterations count
                * NFEV countains number of function calculations
                * ActiveConstraints contains number of active constraints

  -- ALGLIB --
     Copyright 20.03.2009 by Bochkanov Sergey
*************************************************************************/
void minasaresults(const minasastate &state, real_1d_array &x, minasareport &rep)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minasaresults(const_cast<alglib_impl::minasastate*>(state.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::minasareport*>(rep.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
ASA results

Buffered implementation of MinASAResults() which uses pre-allocated buffer
to store X[]. If buffer size is  too  small,  it  resizes  buffer.  It  is
intended to be used in the inner cycles of performance critical algorithms
where array reallocation penalty is too large to be ignored.

  -- ALGLIB --
     Copyright 20.03.2009 by Bochkanov Sergey
*************************************************************************/
void minasaresultsbuf(const minasastate &state, real_1d_array &x, minasareport &rep)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minasaresultsbuf(const_cast<alglib_impl::minasastate*>(state.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::minasareport*>(rep.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}

/*************************************************************************
This  subroutine  restarts  CG  algorithm from new point. All optimization
parameters are left unchanged.

This  function  allows  to  solve multiple  optimization  problems  (which
must have same number of dimensions) without object reallocation penalty.

INPUT PARAMETERS:
    State   -   structure previously allocated with MinCGCreate call.
    X       -   new starting point.
    BndL    -   new lower bounds
    BndU    -   new upper bounds

  -- ALGLIB --
     Copyright 30.07.2010 by Bochkanov Sergey
*************************************************************************/
void minasarestartfrom(const minasastate &state, const real_1d_array &x, const real_1d_array &bndl, const real_1d_array &bndu)
{
    alglib_impl::ae_state _alglib_env_state;
    alglib_impl::ae_state_init(&_alglib_env_state);
    try
    {
        alglib_impl::minasarestartfrom(const_cast<alglib_impl::minasastate*>(state.c_ptr()), const_cast<alglib_impl::ae_vector*>(x.c_ptr()), const_cast<alglib_impl::ae_vector*>(bndl.c_ptr()), const_cast<alglib_impl::ae_vector*>(bndu.c_ptr()), &_alglib_env_state);
        alglib_impl::ae_state_clear(&_alglib_env_state);
        return;
    }
    catch(alglib_impl::ae_error_type)
    {
        throw ap_error(_alglib_env_state.error_msg);
    }
    catch(...)
    {
        throw;
    }
}
}

/////////////////////////////////////////////////////////////////////////
//
// THIS SECTION CONTAINS IMPLEMENTATION OF COMPUTATIONAL CORE
//
/////////////////////////////////////////////////////////////////////////
namespace alglib_impl
{
static void minlbfgs_clearrequestfields(minlbfgsstate* state,
     ae_state *_state);


static ae_int_t minlm_lmmodefj = 0;
static ae_int_t minlm_lmmodefgj = 1;
static ae_int_t minlm_lmmodefgh = 2;
static ae_int_t minlm_lmflagnoprelbfgs = 1;
static ae_int_t minlm_lmflagnointlbfgs = 2;
static ae_int_t minlm_lmprelbfgsm = 5;
static ae_int_t minlm_lmintlbfgsits = 5;
static ae_int_t minlm_lbfgsnorealloc = 1;
static double minlm_lambdaup = 2.0;
static double minlm_lambdadown = 0.33;
static double minlm_suspiciousnu = 16;
static ae_int_t minlm_smallmodelage = 3;
static ae_int_t minlm_additers = 5;
static void minlm_lmprepare(ae_int_t n,
     ae_int_t m,
     ae_bool havegrad,
     minlmstate* state,
     ae_state *_state);
static void minlm_clearrequestfields(minlmstate* state, ae_state *_state);
static ae_bool minlm_increaselambda(double* lambdav,
     double* nu,
     ae_state *_state);
static void minlm_decreaselambda(double* lambdav,
     double* nu,
     ae_state *_state);


static void mincg_clearrequestfields(mincgstate* state, ae_state *_state);


static ae_int_t minasa_n1 = 2;
static ae_int_t minasa_n2 = 2;
static double minasa_stpmin = 1.0E-300;
static double minasa_gpaftol = 0.0001;
static double minasa_gpadecay = 0.5;
static double minasa_asarho = 0.5;
static double minasa_asaboundedantigradnorm(minasastate* state,
     ae_state *_state);
static double minasa_asaginorm(minasastate* state, ae_state *_state);
static double minasa_asad1norm(minasastate* state, ae_state *_state);
static ae_bool minasa_asauisempty(minasastate* state, ae_state *_state);
static void minasa_clearrequestfields(minasastate* state,
     ae_state *_state);





/*************************************************************************
        LIMITED MEMORY BFGS METHOD FOR LARGE SCALE OPTIMIZATION

DESCRIPTION:
The subroutine minimizes function F(x) of N arguments by  using  a  quasi-
Newton method (LBFGS scheme) which is optimized to use  a  minimum  amount
of memory.
The subroutine generates the approximation of an inverse Hessian matrix by
using information about the last M steps of the algorithm  (instead of N).
It lessens a required amount of memory from a value  of  order  N^2  to  a
value of order 2*N*M.


REQUIREMENTS:
Algorithm will request following information during its operation:
* function value F and its gradient G (simultaneously) at given point X


USAGE:
1. User initializes algorithm state with MinLBFGSCreate() call
2. User tunes solver parameters with MinLBFGSSetCond() MinLBFGSSetStpMax()
   and other functions
3. User calls MinLBFGSOptimize() function which takes algorithm  state and
   pointer (delegate, etc.) to callback function which calculates F/G.
4. User calls MinLBFGSResults() to get solution
5. Optionally user may call MinLBFGSRestartFrom() to solve another problem
   with same N/M but another starting point and/or another function.
   MinLBFGSRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   problem dimension. N>0
    M       -   number of corrections in the BFGS scheme of Hessian
                approximation update. Recommended value:  3<=M<=7. The smaller
                value causes worse convergence, the bigger will  not  cause  a
                considerably better convergence, but will cause a fall in  the
                performance. M<=N.
    X       -   initial solution approximation, array[0..N-1].


OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state
    

NOTES:
1. you may tune stopping conditions with MinLBFGSSetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use MinLBFGSSetStpMax() function to bound algorithm's  steps.  However,
   L-BFGS rarely needs such a tuning.


  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minlbfgscreate(ae_int_t n,
     ae_int_t m,
     /* Real    */ ae_vector* x,
     minlbfgsstate* state,
     ae_state *_state)
{

    _minlbfgsstate_clear(state);

    ae_assert(n>=1, "MinLBFGSCreate: N<1!", _state);
    ae_assert(m>=1, "MinLBFGSCreate: M<1", _state);
    ae_assert(m<=n, "MinLBFGSCreate: M>N", _state);
    ae_assert(x->cnt>=n, "MinLBFGSCreate: Length(X)<N!", _state);
    ae_assert(isfinitevector(x, n, _state), "MinLBFGSCreate: X contains infinite or NaN values!", _state);
    minlbfgscreatex(n, m, x, 0, state, _state);
}


/*************************************************************************
This function sets stopping conditions for L-BFGS optimization algorithm.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    EpsG    -   >=0
                The  subroutine  finishes  its  work   if   the  condition
                ||G||<EpsG is satisfied, where ||.|| means Euclidian norm,
                G - gradient.
    EpsF    -   >=0
                The  subroutine  finishes  its work if on k+1-th iteration
                the  condition  |F(k+1)-F(k)|<=EpsF*max{|F(k)|,|F(k+1)|,1}
                is satisfied.
    EpsX    -   >=0
                The subroutine finishes its work if  on  k+1-th  iteration
                the condition |X(k+1)-X(k)| <= EpsX is fulfilled.
    MaxIts  -   maximum number of iterations. If MaxIts=0, the  number  of
                iterations is unlimited.

Passing EpsG=0, EpsF=0, EpsX=0 and MaxIts=0 (simultaneously) will lead to
automatic stopping criterion selection (small EpsX).

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minlbfgssetcond(minlbfgsstate* state,
     double epsg,
     double epsf,
     double epsx,
     ae_int_t maxits,
     ae_state *_state)
{


    ae_assert(ae_isfinite(epsg, _state), "MinLBFGSSetCond: EpsG is not finite number!", _state);
    ae_assert(ae_fp_greater_eq(epsg,0), "MinLBFGSSetCond: negative EpsG!", _state);
    ae_assert(ae_isfinite(epsf, _state), "MinLBFGSSetCond: EpsF is not finite number!", _state);
    ae_assert(ae_fp_greater_eq(epsf,0), "MinLBFGSSetCond: negative EpsF!", _state);
    ae_assert(ae_isfinite(epsx, _state), "MinLBFGSSetCond: EpsX is not finite number!", _state);
    ae_assert(ae_fp_greater_eq(epsx,0), "MinLBFGSSetCond: negative EpsX!", _state);
    ae_assert(maxits>=0, "MinLBFGSSetCond: negative MaxIts!", _state);
    if( ((ae_fp_eq(epsg,0)&&ae_fp_eq(epsf,0))&&ae_fp_eq(epsx,0))&&maxits==0 )
    {
        epsx = 1.0E-6;
    }
    state->epsg = epsg;
    state->epsf = epsf;
    state->epsx = epsx;
    state->maxits = maxits;
}


/*************************************************************************
This function turns on/off reporting.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    NeedXRep-   whether iteration reports are needed or not

If NeedXRep is True, algorithm will call rep() callback function if  it is
provided to MinLBFGSOptimize().


  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minlbfgssetxrep(minlbfgsstate* state,
     ae_bool needxrep,
     ae_state *_state)
{


    state->xrep = needxrep;
}


/*************************************************************************
This function sets maximum step length

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    StpMax  -   maximum step length, >=0. Set StpMax to 0.0 (default),  if
                you don't want to limit step length.

Use this subroutine when you optimize target function which contains exp()
or  other  fast  growing  functions,  and optimization algorithm makes too
large  steps  which  leads  to overflow. This function allows us to reject
steps  that  are  too  large  (and  therefore  expose  us  to the possible
overflow) without actually calculating function value at the x+stp*d.

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minlbfgssetstpmax(minlbfgsstate* state,
     double stpmax,
     ae_state *_state)
{


    ae_assert(ae_isfinite(stpmax, _state), "MinLBFGSSetStpMax: StpMax is not finite!", _state);
    ae_assert(ae_fp_greater_eq(stpmax,0), "MinLBFGSSetStpMax: StpMax<0!", _state);
    state->stpmax = stpmax;
}


/*************************************************************************
Extended subroutine for internal use only.

Accepts additional parameters:

    Flags - additional settings:
            * Flags = 0     means no additional settings
            * Flags = 1     "do not allocate memory". used when solving
                            a many subsequent tasks with  same N/M  values.
                            First  call MUST  be without this flag bit set,
                            subsequent  calls   of   MinLBFGS   with   same
                            MinLBFGSState structure can set Flags to 1.

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minlbfgscreatex(ae_int_t n,
     ae_int_t m,
     /* Real    */ ae_vector* x,
     ae_int_t flags,
     minlbfgsstate* state,
     ae_state *_state)
{
    ae_bool allocatemem;


    ae_assert(n>=1, "MinLBFGS: N too small!", _state);
    ae_assert(m>=1, "MinLBFGS: M too small!", _state);
    ae_assert(m<=n, "MinLBFGS: M too large!", _state);
    
    /*
     * Initialize
     */
    state->n = n;
    state->m = m;
    state->flags = flags;
    allocatemem = flags%2==0;
    flags = flags/2;
    if( allocatemem )
    {
        ae_vector_set_length(&state->rho, m-1+1, _state);
        ae_vector_set_length(&state->theta, m-1+1, _state);
        ae_matrix_set_length(&state->y, m-1+1, n-1+1, _state);
        ae_matrix_set_length(&state->s, m-1+1, n-1+1, _state);
        ae_vector_set_length(&state->d, n-1+1, _state);
        ae_vector_set_length(&state->x, n-1+1, _state);
        ae_vector_set_length(&state->g, n-1+1, _state);
        ae_vector_set_length(&state->work, n-1+1, _state);
    }
    minlbfgssetcond(state, 0, 0, 0, 0, _state);
    minlbfgssetxrep(state, ae_false, _state);
    minlbfgssetstpmax(state, 0, _state);
    minlbfgsrestartfrom(state, x, _state);
    state->prectype = 0;
}


/*************************************************************************
Modification of the preconditioner:
default preconditioner (simple scaling) is used.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state

After call to this function preconditioner is changed to the default one.

NOTE:  you  can  change  preconditioner  "on  the  fly",  during algorithm
iterations.

  -- ALGLIB --
     Copyright 13.10.2010 by Bochkanov Sergey
*************************************************************************/
void minlbfgssetdefaultpreconditioner(minlbfgsstate* state,
     ae_state *_state)
{


    state->prectype = 0;
}


/*************************************************************************
Modification of the preconditioner:
Cholesky factorization of approximate Hessian is used.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    P       -   triangular preconditioner, Cholesky factorization of
                the approximate Hessian. array[0..N-1,0..N-1],
                (if larger, only leading N elements are used).
    IsUpper -   whether upper or lower triangle of P is given
                (other triangle is not referenced)

After call to this function preconditioner is changed to P  (P  is  copied
into the internal buffer).

NOTE:  you  can  change  preconditioner  "on  the  fly",  during algorithm
iterations.

NOTE 2:  P  should  be nonsingular. Exception will be thrown otherwise. It
also should be well conditioned, although only strict  non-singularity  is
tested.

  -- ALGLIB --
     Copyright 13.10.2010 by Bochkanov Sergey
*************************************************************************/
void minlbfgssetcholeskypreconditioner(minlbfgsstate* state,
     /* Real    */ ae_matrix* p,
     ae_bool isupper,
     ae_state *_state)
{
    ae_int_t i;
    double mx;


    ae_assert(isfinitertrmatrix(p, state->n, isupper, _state), "MinLBFGSSetCholeskyPreconditioner: P contains infinite or NAN values!", _state);
    mx = 0;
    for(i=0; i<=state->n-1; i++)
    {
        mx = ae_maxreal(mx, ae_fabs(p->ptr.pp_double[i][i], _state), _state);
    }
    ae_assert(ae_fp_greater(mx,0), "MinLBFGSSetCholeskyPreconditioner: P is strictly singular!", _state);
    if( state->denseh.rows<state->n||state->denseh.cols<state->n )
    {
        ae_matrix_set_length(&state->denseh, state->n, state->n, _state);
    }
    state->prectype = 1;
    if( isupper )
    {
        rmatrixcopy(state->n, state->n, p, 0, 0, &state->denseh, 0, 0, _state);
    }
    else
    {
        rmatrixtranspose(state->n, state->n, p, 0, 0, &state->denseh, 0, 0, _state);
    }
}


/*************************************************************************

  -- ALGLIB --
     Copyright 20.03.2009 by Bochkanov Sergey
*************************************************************************/
ae_bool minlbfgsiteration(minlbfgsstate* state, ae_state *_state)
{
    ae_int_t n;
    ae_int_t m;
    ae_int_t maxits;
    double epsf;
    double epsg;
    double epsx;
    ae_int_t i;
    ae_int_t j;
    ae_int_t ic;
    ae_int_t mcinfo;
    double v;
    double vv;
    ae_bool result;


    
    /*
     * Reverse communication preparations
     * I know it looks ugly, but it works the same way
     * anywhere from C++ to Python.
     *
     * This code initializes locals by:
     * * random values determined during code
     *   generation - on first subroutine call
     * * values from previous call - on subsequent calls
     */
    if( state->rstate.stage>=0 )
    {
        n = state->rstate.ia.ptr.p_int[0];
        m = state->rstate.ia.ptr.p_int[1];
        maxits = state->rstate.ia.ptr.p_int[2];
        i = state->rstate.ia.ptr.p_int[3];
        j = state->rstate.ia.ptr.p_int[4];
        ic = state->rstate.ia.ptr.p_int[5];
        mcinfo = state->rstate.ia.ptr.p_int[6];
        epsf = state->rstate.ra.ptr.p_double[0];
        epsg = state->rstate.ra.ptr.p_double[1];
        epsx = state->rstate.ra.ptr.p_double[2];
        v = state->rstate.ra.ptr.p_double[3];
        vv = state->rstate.ra.ptr.p_double[4];
    }
    else
    {
        n = -983;
        m = -989;
        maxits = -834;
        i = 900;
        j = -287;
        ic = 364;
        mcinfo = 214;
        epsf = -338;
        epsg = -686;
        epsx = 912;
        v = 585;
        vv = 497;
    }
    if( state->rstate.stage==0 )
    {
        goto lbl_0;
    }
    if( state->rstate.stage==1 )
    {
        goto lbl_1;
    }
    if( state->rstate.stage==2 )
    {
        goto lbl_2;
    }
    if( state->rstate.stage==3 )
    {
        goto lbl_3;
    }
    
    /*
     * Routine body
     */
    
    /*
     * Unload frequently used variables from State structure
     * (just for typing convinience)
     */
    n = state->n;
    m = state->m;
    epsg = state->epsg;
    epsf = state->epsf;
    epsx = state->epsx;
    maxits = state->maxits;
    state->repterminationtype = 0;
    state->repiterationscount = 0;
    state->repnfev = 0;
    
    /*
     * Calculate F/G at the initial point
     */
    minlbfgs_clearrequestfields(state, _state);
    state->needfg = ae_true;
    state->rstate.stage = 0;
    goto lbl_rcomm;
lbl_0:
    state->needfg = ae_false;
    if( !state->xrep )
    {
        goto lbl_4;
    }
    minlbfgs_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 1;
    goto lbl_rcomm;
lbl_1:
    state->xupdated = ae_false;
lbl_4:
    state->repnfev = 1;
    state->fold = state->f;
    v = ae_v_dotproduct(&state->g.ptr.p_double[0], 1, &state->g.ptr.p_double[0], 1, ae_v_len(0,n-1));
    v = ae_sqrt(v, _state);
    if( ae_fp_less_eq(v,epsg) )
    {
        state->repterminationtype = 4;
        result = ae_false;
        return result;
    }
    
    /*
     * Choose initial step and direction.
     * Apply preconditioner, if we have something other than default.
     */
    if( ae_fp_eq(state->stpmax,0) )
    {
        state->stp = ae_minreal(1.0/v, 1, _state);
    }
    else
    {
        state->stp = ae_minreal(1.0/v, state->stpmax, _state);
    }
    ae_v_moveneg(&state->d.ptr.p_double[0], 1, &state->g.ptr.p_double[0], 1, ae_v_len(0,n-1));
    if( state->prectype==1 )
    {
        
        /*
         * Cholesky preconditioner is used
         */
        fblscholeskysolve(&state->denseh, 1.0, n, ae_true, &state->d, &state->autobuf, _state);
    }
    
    /*
     * Main cycle
     */
    state->k = 0;
lbl_6:
    if( ae_false )
    {
        goto lbl_7;
    }
    
    /*
     * Main cycle: prepare to 1-D line search
     */
    state->p = state->k%m;
    state->q = ae_minint(state->k, m-1, _state);
    
    /*
     * Store X[k], G[k]
     */
    ae_v_moveneg(&state->s.ptr.pp_double[state->p][0], 1, &state->x.ptr.p_double[0], 1, ae_v_len(0,n-1));
    ae_v_moveneg(&state->y.ptr.pp_double[state->p][0], 1, &state->g.ptr.p_double[0], 1, ae_v_len(0,n-1));
    
    /*
     * Minimize F(x+alpha*d)
     * Calculate S[k], Y[k]
     */
    state->mcstage = 0;
    if( state->k!=0 )
    {
        state->stp = 1.0;
    }
    linminnormalized(&state->d, &state->stp, n, _state);
    mcsrch(n, &state->x, &state->f, &state->g, &state->d, &state->stp, state->stpmax, &mcinfo, &state->nfev, &state->work, &state->lstate, &state->mcstage, _state);
lbl_8:
    if( state->mcstage==0 )
    {
        goto lbl_9;
    }
    minlbfgs_clearrequestfields(state, _state);
    state->needfg = ae_true;
    state->rstate.stage = 2;
    goto lbl_rcomm;
lbl_2:
    state->needfg = ae_false;
    mcsrch(n, &state->x, &state->f, &state->g, &state->d, &state->stp, state->stpmax, &mcinfo, &state->nfev, &state->work, &state->lstate, &state->mcstage, _state);
    goto lbl_8;
lbl_9:
    if( !state->xrep )
    {
        goto lbl_10;
    }
    
    /*
     * report
     */
    minlbfgs_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 3;
    goto lbl_rcomm;
lbl_3:
    state->xupdated = ae_false;
lbl_10:
    state->repnfev = state->repnfev+state->nfev;
    state->repiterationscount = state->repiterationscount+1;
    ae_v_add(&state->s.ptr.pp_double[state->p][0], 1, &state->x.ptr.p_double[0], 1, ae_v_len(0,n-1));
    ae_v_add(&state->y.ptr.pp_double[state->p][0], 1, &state->g.ptr.p_double[0], 1, ae_v_len(0,n-1));
    
    /*
     * Stopping conditions
     */
    if( state->repiterationscount>=maxits&&maxits>0 )
    {
        
        /*
         * Too many iterations
         */
        state->repterminationtype = 5;
        result = ae_false;
        return result;
    }
    v = ae_v_dotproduct(&state->g.ptr.p_double[0], 1, &state->g.ptr.p_double[0], 1, ae_v_len(0,n-1));
    if( ae_fp_less_eq(ae_sqrt(v, _state),epsg) )
    {
        
        /*
         * Gradient is small enough
         */
        state->repterminationtype = 4;
        result = ae_false;
        return result;
    }
    if( ae_fp_less_eq(state->fold-state->f,epsf*ae_maxreal(ae_fabs(state->fold, _state), ae_maxreal(ae_fabs(state->f, _state), 1.0, _state), _state)) )
    {
        
        /*
         * F(k+1)-F(k) is small enough
         */
        state->repterminationtype = 1;
        result = ae_false;
        return result;
    }
    v = ae_v_dotproduct(&state->s.ptr.pp_double[state->p][0], 1, &state->s.ptr.pp_double[state->p][0], 1, ae_v_len(0,n-1));
    if( ae_fp_less_eq(ae_sqrt(v, _state),epsx) )
    {
        
        /*
         * X(k+1)-X(k) is small enough
         */
        state->repterminationtype = 2;
        result = ae_false;
        return result;
    }
    
    /*
     * If Wolfe conditions are satisfied, we can update
     * limited memory model.
     *
     * However, if conditions are not satisfied (NFEV limit is met,
     * function is too wild, ...), we'll skip L-BFGS update
     */
    if( mcinfo!=1 )
    {
        
        /*
         * Skip update.
         *
         * In such cases we'll initialize search direction by
         * antigradient vector, because it  leads to more
         * transparent code with less number of special cases
         */
        state->fold = state->f;
        ae_v_moveneg(&state->d.ptr.p_double[0], 1, &state->g.ptr.p_double[0], 1, ae_v_len(0,n-1));
    }
    else
    {
        
        /*
         * Calculate Rho[k], GammaK
         */
        v = ae_v_dotproduct(&state->y.ptr.pp_double[state->p][0], 1, &state->s.ptr.pp_double[state->p][0], 1, ae_v_len(0,n-1));
        vv = ae_v_dotproduct(&state->y.ptr.pp_double[state->p][0], 1, &state->y.ptr.pp_double[state->p][0], 1, ae_v_len(0,n-1));
        if( ae_fp_eq(v,0)||ae_fp_eq(vv,0) )
        {
            
            /*
             * Rounding errors make further iterations impossible.
             */
            state->repterminationtype = -2;
            result = ae_false;
            return result;
        }
        state->rho.ptr.p_double[state->p] = 1/v;
        state->gammak = v/vv;
        
        /*
         *  Calculate d(k+1) = -H(k+1)*g(k+1)
         *
         *  for I:=K downto K-Q do
         *      V = s(i)^T * work(iteration:I)
         *      theta(i) = V
         *      work(iteration:I+1) = work(iteration:I) - V*Rho(i)*y(i)
         *  work(last iteration) = H0*work(last iteration) - preconditioner
         *  for I:=K-Q to K do
         *      V = y(i)^T*work(iteration:I)
         *      work(iteration:I+1) = work(iteration:I) +(-V+theta(i))*Rho(i)*s(i)
         *
         *  NOW WORK CONTAINS d(k+1)
         */
        ae_v_move(&state->work.ptr.p_double[0], 1, &state->g.ptr.p_double[0], 1, ae_v_len(0,n-1));
        for(i=state->k; i>=state->k-state->q; i--)
        {
            ic = i%m;
            v = ae_v_dotproduct(&state->s.ptr.pp_double[ic][0], 1, &state->work.ptr.p_double[0], 1, ae_v_len(0,n-1));
            state->theta.ptr.p_double[ic] = v;
            vv = v*state->rho.ptr.p_double[ic];
            ae_v_subd(&state->work.ptr.p_double[0], 1, &state->y.ptr.pp_double[ic][0], 1, ae_v_len(0,n-1), vv);
        }
        if( state->prectype==0 )
        {
            
            /*
             * Simple preconditioner is used
             */
            v = state->gammak;
            ae_v_muld(&state->work.ptr.p_double[0], 1, ae_v_len(0,n-1), v);
        }
        if( state->prectype==1 )
        {
            
            /*
             * Cholesky preconditioner is used
             */
            fblscholeskysolve(&state->denseh, 1, n, ae_true, &state->work, &state->autobuf, _state);
        }
        for(i=state->k-state->q; i<=state->k; i++)
        {
            ic = i%m;
            v = ae_v_dotproduct(&state->y.ptr.pp_double[ic][0], 1, &state->work.ptr.p_double[0], 1, ae_v_len(0,n-1));
            vv = state->rho.ptr.p_double[ic]*(-v+state->theta.ptr.p_double[ic]);
            ae_v_addd(&state->work.ptr.p_double[0], 1, &state->s.ptr.pp_double[ic][0], 1, ae_v_len(0,n-1), vv);
        }
        ae_v_moveneg(&state->d.ptr.p_double[0], 1, &state->work.ptr.p_double[0], 1, ae_v_len(0,n-1));
        
        /*
         * Next step
         */
        state->fold = state->f;
        state->k = state->k+1;
    }
    goto lbl_6;
lbl_7:
    result = ae_false;
    return result;
    
    /*
     * Saving state
     */
lbl_rcomm:
    result = ae_true;
    state->rstate.ia.ptr.p_int[0] = n;
    state->rstate.ia.ptr.p_int[1] = m;
    state->rstate.ia.ptr.p_int[2] = maxits;
    state->rstate.ia.ptr.p_int[3] = i;
    state->rstate.ia.ptr.p_int[4] = j;
    state->rstate.ia.ptr.p_int[5] = ic;
    state->rstate.ia.ptr.p_int[6] = mcinfo;
    state->rstate.ra.ptr.p_double[0] = epsf;
    state->rstate.ra.ptr.p_double[1] = epsg;
    state->rstate.ra.ptr.p_double[2] = epsx;
    state->rstate.ra.ptr.p_double[3] = v;
    state->rstate.ra.ptr.p_double[4] = vv;
    return result;
}


/*************************************************************************
L-BFGS algorithm results

INPUT PARAMETERS:
    State   -   algorithm state

OUTPUT PARAMETERS:
    X       -   array[0..N-1], solution
    Rep     -   optimization report:
                * Rep.TerminationType completetion code:
                    * -2    rounding errors prevent further improvement.
                            X contains best point found.
                    * -1    incorrect parameters were specified
                    *  1    relative function improvement is no more than
                            EpsF.
                    *  2    relative step is no more than EpsX.
                    *  4    gradient norm is no more than EpsG
                    *  5    MaxIts steps was taken
                    *  7    stopping conditions are too stringent,
                            further improvement is impossible
                * Rep.IterationsCount contains iterations count
                * NFEV countains number of function calculations

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minlbfgsresults(minlbfgsstate* state,
     /* Real    */ ae_vector* x,
     minlbfgsreport* rep,
     ae_state *_state)
{

    ae_vector_clear(x);
    _minlbfgsreport_clear(rep);

    minlbfgsresultsbuf(state, x, rep, _state);
}


/*************************************************************************
L-BFGS algorithm results

Buffered implementation of MinLBFGSResults which uses pre-allocated buffer
to store X[]. If buffer size is  too  small,  it  resizes  buffer.  It  is
intended to be used in the inner cycles of performance critical algorithms
where array reallocation penalty is too large to be ignored.

  -- ALGLIB --
     Copyright 20.08.2010 by Bochkanov Sergey
*************************************************************************/
void minlbfgsresultsbuf(minlbfgsstate* state,
     /* Real    */ ae_vector* x,
     minlbfgsreport* rep,
     ae_state *_state)
{


    if( x->cnt<state->n )
    {
        ae_vector_set_length(x, state->n, _state);
    }
    ae_v_move(&x->ptr.p_double[0], 1, &state->x.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    rep->iterationscount = state->repiterationscount;
    rep->nfev = state->repnfev;
    rep->terminationtype = state->repterminationtype;
}


/*************************************************************************
This  subroutine restarts LBFGS algorithm from new point. All optimization
parameters are left unchanged.

This  function  allows  to  solve multiple  optimization  problems  (which
must have same number of dimensions) without object reallocation penalty.

INPUT PARAMETERS:
    State   -   structure used to store algorithm state
    X       -   new starting point.

  -- ALGLIB --
     Copyright 30.07.2010 by Bochkanov Sergey
*************************************************************************/
void minlbfgsrestartfrom(minlbfgsstate* state,
     /* Real    */ ae_vector* x,
     ae_state *_state)
{


    ae_assert(x->cnt>=state->n, "MinLBFGSRestartFrom: Length(X)<N!", _state);
    ae_assert(isfinitevector(x, state->n, _state), "MinLBFGSRestartFrom: X contains infinite or NaN values!", _state);
    ae_v_move(&state->x.ptr.p_double[0], 1, &x->ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    ae_vector_set_length(&state->rstate.ia, 6+1, _state);
    ae_vector_set_length(&state->rstate.ra, 4+1, _state);
    state->rstate.stage = -1;
    minlbfgs_clearrequestfields(state, _state);
}


/*************************************************************************
Clears request fileds (to be sure that we don't forgot to clear something)
*************************************************************************/
static void minlbfgs_clearrequestfields(minlbfgsstate* state,
     ae_state *_state)
{


    state->needfg = ae_false;
    state->xupdated = ae_false;
}


ae_bool _minlbfgsstate_init(minlbfgsstate* p, ae_state *_state, ae_bool make_automatic)
{
    if( !ae_vector_init(&p->rho, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_matrix_init(&p->y, 0, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_matrix_init(&p->s, 0, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->theta, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->d, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->work, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_matrix_init(&p->denseh, 0, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->autobuf, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->x, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->g, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !_rcommstate_init(&p->rstate, _state, make_automatic) )
        return ae_false;
    if( !_linminstate_init(&p->lstate, _state, make_automatic) )
        return ae_false;
    return ae_true;
}


ae_bool _minlbfgsstate_init_copy(minlbfgsstate* dst, minlbfgsstate* src, ae_state *_state, ae_bool make_automatic)
{
    dst->n = src->n;
    dst->m = src->m;
    dst->epsg = src->epsg;
    dst->epsf = src->epsf;
    dst->epsx = src->epsx;
    dst->maxits = src->maxits;
    dst->flags = src->flags;
    dst->xrep = src->xrep;
    dst->stpmax = src->stpmax;
    dst->nfev = src->nfev;
    dst->mcstage = src->mcstage;
    dst->k = src->k;
    dst->q = src->q;
    dst->p = src->p;
    if( !ae_vector_init_copy(&dst->rho, &src->rho, _state, make_automatic) )
        return ae_false;
    if( !ae_matrix_init_copy(&dst->y, &src->y, _state, make_automatic) )
        return ae_false;
    if( !ae_matrix_init_copy(&dst->s, &src->s, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->theta, &src->theta, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->d, &src->d, _state, make_automatic) )
        return ae_false;
    dst->stp = src->stp;
    if( !ae_vector_init_copy(&dst->work, &src->work, _state, make_automatic) )
        return ae_false;
    dst->fold = src->fold;
    dst->prectype = src->prectype;
    dst->gammak = src->gammak;
    if( !ae_matrix_init_copy(&dst->denseh, &src->denseh, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->autobuf, &src->autobuf, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->x, &src->x, _state, make_automatic) )
        return ae_false;
    dst->f = src->f;
    if( !ae_vector_init_copy(&dst->g, &src->g, _state, make_automatic) )
        return ae_false;
    dst->needfg = src->needfg;
    dst->xupdated = src->xupdated;
    if( !_rcommstate_init_copy(&dst->rstate, &src->rstate, _state, make_automatic) )
        return ae_false;
    dst->repiterationscount = src->repiterationscount;
    dst->repnfev = src->repnfev;
    dst->repterminationtype = src->repterminationtype;
    if( !_linminstate_init_copy(&dst->lstate, &src->lstate, _state, make_automatic) )
        return ae_false;
    return ae_true;
}


void _minlbfgsstate_clear(minlbfgsstate* p)
{
    ae_vector_clear(&p->rho);
    ae_matrix_clear(&p->y);
    ae_matrix_clear(&p->s);
    ae_vector_clear(&p->theta);
    ae_vector_clear(&p->d);
    ae_vector_clear(&p->work);
    ae_matrix_clear(&p->denseh);
    ae_vector_clear(&p->autobuf);
    ae_vector_clear(&p->x);
    ae_vector_clear(&p->g);
    _rcommstate_clear(&p->rstate);
    _linminstate_clear(&p->lstate);
}


ae_bool _minlbfgsreport_init(minlbfgsreport* p, ae_state *_state, ae_bool make_automatic)
{
    return ae_true;
}


ae_bool _minlbfgsreport_init_copy(minlbfgsreport* dst, minlbfgsreport* src, ae_state *_state, ae_bool make_automatic)
{
    dst->iterationscount = src->iterationscount;
    dst->nfev = src->nfev;
    dst->terminationtype = src->terminationtype;
    return ae_true;
}


void _minlbfgsreport_clear(minlbfgsreport* p)
{
}




/*************************************************************************
                IMPROVED LEVENBERG-MARQUARDT METHOD FOR
                 NON-LINEAR LEAST SQUARES OPTIMIZATION

DESCRIPTION:
This function is used to find minimum of function which is represented  as
sum of squares:
    F(x) = f[0]^2(x[0],...,x[n-1]) + ... + f[m-1]^2(x[0],...,x[n-1])
using value of function vector f[] and Jacobian of f[].


REQUIREMENTS:
This algorithm will request following information during its operation:

* function vector f[] at given point X
* function vector f[] and Jacobian of f[] (simultaneously) at given point

There are several overloaded versions of  MinLMOptimize()  function  which
correspond  to  different LM-like optimization algorithms provided by this
unit. You should choose version which accepts fvec()  and jac() callbacks.
First  one  is used to calculate f[] at given point, second one calculates
f[] and Jacobian df[i]/dx[j].

You can try to initialize MinLMState structure with VJ  function and  then
use incorrect version  of  MinLMOptimize()  (for  example,  version  which
works  with  general  form function and does not provide Jacobian), but it
will  lead  to  exception  being  thrown  after first attempt to calculate
Jacobian.


USAGE:
1. User initializes algorithm state with MinLMCreateVJ() call
2. User tunes solver parameters with MinLMSetCond(),  MinLMSetStpMax() and
   other functions
3. User calls MinLMOptimize() function which  takes algorithm  state   and
   callback functions.
4. User calls MinLMResults() to get solution
5. Optionally, user may call MinLMRestartFrom() to solve  another  problem
   with same N/M but another starting point and/or another function.
   MinLMRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   dimension, N>1
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size of X
    M       -   number of functions f[i]
    X       -   initial solution, array[0..N-1]

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

NOTES:
1. you may tune stopping conditions with MinLMSetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use MinLMSetStpMax() function to bound algorithm's steps.

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
void minlmcreatevj(ae_int_t n,
     ae_int_t m,
     /* Real    */ ae_vector* x,
     minlmstate* state,
     ae_state *_state)
{

    _minlmstate_clear(state);

    ae_assert(n>=1, "MinLMCreateVJ: N<1!", _state);
    ae_assert(m>=1, "MinLMCreateVJ: M<1!", _state);
    ae_assert(x->cnt>=n, "MinLMCreateVJ: Length(X)<N!", _state);
    ae_assert(isfinitevector(x, n, _state), "MinLMCreateVJ: X contains infinite or NaN values!", _state);
    
    /*
     * initialize, check parameters
     */
    state->n = n;
    state->m = m;
    state->algomode = 1;
    state->hasf = ae_false;
    state->hasfi = ae_true;
    state->hasg = ae_false;
    
    /*
     * second stage of initialization
     */
    minlm_lmprepare(n, m, ae_false, state, _state);
    minlmsetacctype(state, 0, _state);
    minlmsetcond(state, 0, 0, 0, 0, _state);
    minlmsetxrep(state, ae_false, _state);
    minlmsetstpmax(state, 0, _state);
    minlmrestartfrom(state, x, _state);
}


/*************************************************************************
                IMPROVED LEVENBERG-MARQUARDT METHOD FOR
                 NON-LINEAR LEAST SQUARES OPTIMIZATION

DESCRIPTION:
This function is used to find minimum of function which is represented  as
sum of squares:
    F(x) = f[0]^2(x[0],...,x[n-1]) + ... + f[m-1]^2(x[0],...,x[n-1])
using value of function vector f[] only. Finite differences  are  used  to
calculate Jacobian.


REQUIREMENTS:
This algorithm will request following information during its operation:
* function vector f[] at given point X

There are several overloaded versions of  MinLMOptimize()  function  which
correspond  to  different LM-like optimization algorithms provided by this
unit. You should choose version which accepts fvec() callback.

You can try to initialize MinLMState structure with VJ  function and  then
use incorrect version  of  MinLMOptimize()  (for  example,  version  which
works with general form function and does not accept function vector), but
it will  lead  to  exception being thrown after first attempt to calculate
Jacobian.


USAGE:
1. User initializes algorithm state with MinLMCreateV() call
2. User tunes solver parameters with MinLMSetCond(),  MinLMSetStpMax() and
   other functions
3. User calls MinLMOptimize() function which  takes algorithm  state   and
   callback functions.
4. User calls MinLMResults() to get solution
5. Optionally, user may call MinLMRestartFrom() to solve  another  problem
   with same N/M but another starting point and/or another function.
   MinLMRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   dimension, N>1
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size of X
    M       -   number of functions f[i]
    X       -   initial solution, array[0..N-1]
    DiffStep-   differentiation step, >0

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

See also MinLMIteration, MinLMResults.

NOTES:
1. you may tune stopping conditions with MinLMSetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use MinLMSetStpMax() function to bound algorithm's steps.

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
void minlmcreatev(ae_int_t n,
     ae_int_t m,
     /* Real    */ ae_vector* x,
     double diffstep,
     minlmstate* state,
     ae_state *_state)
{

    _minlmstate_clear(state);

    ae_assert(ae_isfinite(diffstep, _state), "MinLMCreateV: DiffStep is not finite!", _state);
    ae_assert(ae_fp_greater(diffstep,0), "MinLMCreateV: DiffStep<=0!", _state);
    ae_assert(n>=1, "MinLMCreateV: N<1!", _state);
    ae_assert(m>=1, "MinLMCreateV: M<1!", _state);
    ae_assert(x->cnt>=n, "MinLMCreateV: Length(X)<N!", _state);
    ae_assert(isfinitevector(x, n, _state), "MinLMCreateV: X contains infinite or NaN values!", _state);
    
    /*
     * initialize
     */
    state->n = n;
    state->m = m;
    state->algomode = 0;
    state->hasf = ae_false;
    state->hasfi = ae_true;
    state->hasg = ae_false;
    state->diffstep = diffstep;
    
    /*
     * second stage of initialization
     */
    minlm_lmprepare(n, m, ae_false, state, _state);
    minlmsetacctype(state, 1, _state);
    minlmsetcond(state, 0, 0, 0, 0, _state);
    minlmsetxrep(state, ae_false, _state);
    minlmsetstpmax(state, 0, _state);
    minlmrestartfrom(state, x, _state);
}


/*************************************************************************
    LEVENBERG-MARQUARDT-LIKE METHOD FOR NON-LINEAR OPTIMIZATION

DESCRIPTION:
This  function  is  used  to  find  minimum  of general form (not "sum-of-
-squares") function
    F = F(x[0], ..., x[n-1])
using  its  gradient  and  Hessian.  Levenberg-Marquardt modification with
L-BFGS pre-optimization and internal pre-conditioned  L-BFGS  optimization
after each Levenberg-Marquardt step is used.


REQUIREMENTS:
This algorithm will request following information during its operation:

* function value F at given point X
* F and gradient G (simultaneously) at given point X
* F, G and Hessian H (simultaneously) at given point X

There are several overloaded versions of  MinLMOptimize()  function  which
correspond  to  different LM-like optimization algorithms provided by this
unit. You should choose version which accepts func(),  grad()  and  hess()
function pointers. First pointer is used to calculate F  at  given  point,
second  one  calculates  F(x)  and  grad F(x),  third one calculates F(x),
grad F(x), hess F(x).

You can try to initialize MinLMState structure with FGH-function and  then
use incorrect version of MinLMOptimize() (for example, version which  does
not provide Hessian matrix), but it will lead to  exception  being  thrown
after first attempt to calculate Hessian.


USAGE:
1. User initializes algorithm state with MinLMCreateFGH() call
2. User tunes solver parameters with MinLMSetCond(),  MinLMSetStpMax() and
   other functions
3. User calls MinLMOptimize() function which  takes algorithm  state   and
   pointers (delegates, etc.) to callback functions.
4. User calls MinLMResults() to get solution
5. Optionally, user may call MinLMRestartFrom() to solve  another  problem
   with same N but another starting point and/or another function.
   MinLMRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   dimension, N>1
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size of X
    X       -   initial solution, array[0..N-1]

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

NOTES:
1. you may tune stopping conditions with MinLMSetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use MinLMSetStpMax() function to bound algorithm's steps.

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
void minlmcreatefgh(ae_int_t n,
     /* Real    */ ae_vector* x,
     minlmstate* state,
     ae_state *_state)
{

    _minlmstate_clear(state);

    ae_assert(n>=1, "MinLMCreateFGH: N<1!", _state);
    ae_assert(x->cnt>=n, "MinLMCreateFGH: Length(X)<N!", _state);
    ae_assert(isfinitevector(x, n, _state), "MinLMCreateFGH: X contains infinite or NaN values!", _state);
    
    /*
     * initialize
     */
    state->n = n;
    state->m = 0;
    state->algomode = 2;
    state->hasf = ae_true;
    state->hasfi = ae_false;
    state->hasg = ae_true;
    
    /*
     * init2
     */
    minlm_lmprepare(n, 0, ae_true, state, _state);
    minlmsetacctype(state, 2, _state);
    minlmsetcond(state, 0, 0, 0, 0, _state);
    minlmsetxrep(state, ae_false, _state);
    minlmsetstpmax(state, 0, _state);
    minlmrestartfrom(state, x, _state);
}


/*************************************************************************
                IMPROVED LEVENBERG-MARQUARDT METHOD FOR
                 NON-LINEAR LEAST SQUARES OPTIMIZATION

DESCRIPTION:
This function is used to find minimum of function which is represented  as
sum of squares:
    F(x) = f[0]^2(x[0],...,x[n-1]) + ... + f[m-1]^2(x[0],...,x[n-1])
using:
* value of function vector f[]
* value of Jacobian of f[]
* gradient of merit function F(x)

This function creates optimizer which uses acceleration strategy 2.  Cheap
gradient of merit function (which is twice the product of function  vector
and Jacobian) is used for accelerated iterations (see User Guide for  more
info on this subject).

REQUIREMENTS:
This algorithm will request following information during its operation:

* function vector f[] at given point X
* function vector f[] and Jacobian of f[] (simultaneously) at given point
* gradient of

There are several overloaded versions of  MinLMOptimize()  function  which
correspond  to  different LM-like optimization algorithms provided by this
unit. You should choose version which accepts  fvec(),  jac()  and  grad()
callbacks. First one is used to calculate f[] at given point,  second  one
calculates f[] and Jacobian df[i]/dx[j], last one calculates  gradient  of
merit function F(x).

You can try to initialize MinLMState structure with VJ  function and  then
use incorrect version  of  MinLMOptimize()  (for  example,  version  which
works  with  general  form function and does not provide Jacobian), but it
will  lead  to  exception  being  thrown  after first attempt to calculate
Jacobian.


USAGE:
1. User initializes algorithm state with MinLMCreateVGJ() call
2. User tunes solver parameters with MinLMSetCond(),  MinLMSetStpMax() and
   other functions
3. User calls MinLMOptimize() function which  takes algorithm  state   and
   callback functions.
4. User calls MinLMResults() to get solution
5. Optionally, user may call MinLMRestartFrom() to solve  another  problem
   with same N/M but another starting point and/or another function.
   MinLMRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   dimension, N>1
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size of X
    M       -   number of functions f[i]
    X       -   initial solution, array[0..N-1]

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

NOTES:
1. you may tune stopping conditions with MinLMSetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use MinLMSetStpMax() function to bound algorithm's steps.

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
void minlmcreatevgj(ae_int_t n,
     ae_int_t m,
     /* Real    */ ae_vector* x,
     minlmstate* state,
     ae_state *_state)
{

    _minlmstate_clear(state);

    ae_assert(n>=1, "MinLMCreateVGJ: N<1!", _state);
    ae_assert(m>=1, "MinLMCreateVGJ: M<1!", _state);
    ae_assert(x->cnt>=n, "MinLMCreateVGJ: Length(X)<N!", _state);
    ae_assert(isfinitevector(x, n, _state), "MinLMCreateVGJ: X contains infinite or NaN values!", _state);
    
    /*
     * initialize, check parameters
     */
    state->n = n;
    state->m = m;
    state->algomode = 1;
    state->hasf = ae_false;
    state->hasfi = ae_true;
    state->hasg = ae_false;
    
    /*
     * second stage of initialization
     */
    minlm_lmprepare(n, m, ae_false, state, _state);
    minlmsetacctype(state, 2, _state);
    minlmsetcond(state, 0, 0, 0, 0, _state);
    minlmsetxrep(state, ae_false, _state);
    minlmsetstpmax(state, 0, _state);
    minlmrestartfrom(state, x, _state);
}


/*************************************************************************
                   LEVENBERG-MARQUARDT-LIKE METHOD FOR
                  NON-LINEAR LEAST SQUARES OPTIMIZATION

DESCRIPTION:

This function is used to find minimum of function which is represented  as
sum of squares:
    F(x) = f[0]^2(x[0],...,x[n-1]) + ... + f[m-1]^2(x[0],...,x[n-1])
using value of F(), gradient of F(), function vector f[]  and  Jacobian of
f[].

This function is considered obsolete since ALGLIB 3.1.0 and is present for
backward  compatibility  only.  We  recommend to use MinLMCreateVGJ, which
provides similar, but more consistent interface.

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
void minlmcreatefgj(ae_int_t n,
     ae_int_t m,
     /* Real    */ ae_vector* x,
     minlmstate* state,
     ae_state *_state)
{

    _minlmstate_clear(state);

    ae_assert(n>=1, "MinLMCreateFGJ: N<1!", _state);
    ae_assert(m>=1, "MinLMCreateFGJ: M<1!", _state);
    ae_assert(x->cnt>=n, "MinLMCreateFGJ: Length(X)<N!", _state);
    ae_assert(isfinitevector(x, n, _state), "MinLMCreateFGJ: X contains infinite or NaN values!", _state);
    
    /*
     * initialize
     */
    state->n = n;
    state->m = m;
    state->algomode = 1;
    state->hasf = ae_true;
    state->hasfi = ae_false;
    state->hasg = ae_true;
    
    /*
     * init2
     */
    minlm_lmprepare(n, m, ae_true, state, _state);
    minlmsetacctype(state, 2, _state);
    minlmsetcond(state, 0, 0, 0, 0, _state);
    minlmsetxrep(state, ae_false, _state);
    minlmsetstpmax(state, 0, _state);
    minlmrestartfrom(state, x, _state);
}


/*************************************************************************
    CLASSIC LEVENBERG-MARQUARDT METHOD FOR NON-LINEAR OPTIMIZATION

DESCRIPTION:
This function is used to find minimum of function which is represented  as
sum of squares:
    F(x) = f[0]^2(x[0],...,x[n-1]) + ... + f[m-1]^2(x[0],...,x[n-1])
using  value  of  F(),  function  vector  f[] and Jacobian of f[]. Classic
Levenberg-Marquardt method is used.

This function is considered obsolete since ALGLIB 3.1.0 and is present for
backward  compatibility  only.  We  recommend  to use MinLMCreateVJ, which
provides similar, but more consistent and feature-rich interface.

  -- ALGLIB --
     Copyright 30.03.2009 by Bochkanov Sergey
*************************************************************************/
void minlmcreatefj(ae_int_t n,
     ae_int_t m,
     /* Real    */ ae_vector* x,
     minlmstate* state,
     ae_state *_state)
{

    _minlmstate_clear(state);

    ae_assert(n>=1, "MinLMCreateFJ: N<1!", _state);
    ae_assert(m>=1, "MinLMCreateFJ: M<1!", _state);
    ae_assert(x->cnt>=n, "MinLMCreateFJ: Length(X)<N!", _state);
    ae_assert(isfinitevector(x, n, _state), "MinLMCreateFJ: X contains infinite or NaN values!", _state);
    
    /*
     * initialize
     */
    state->n = n;
    state->m = m;
    state->algomode = 1;
    state->hasf = ae_true;
    state->hasfi = ae_false;
    state->hasg = ae_false;
    
    /*
     * init 2
     */
    minlm_lmprepare(n, m, ae_true, state, _state);
    minlmsetacctype(state, 0, _state);
    minlmsetcond(state, 0, 0, 0, 0, _state);
    minlmsetxrep(state, ae_false, _state);
    minlmsetstpmax(state, 0, _state);
    minlmrestartfrom(state, x, _state);
}


/*************************************************************************
This function sets stopping conditions for Levenberg-Marquardt optimization
algorithm.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    EpsG    -   >=0
                The  subroutine  finishes  its  work   if   the  condition
                ||G||<EpsG is satisfied, where ||.|| means Euclidian norm,
                G - gradient.
    EpsF    -   >=0
                The  subroutine  finishes  its work if on k+1-th iteration
                the  condition  |F(k+1)-F(k)|<=EpsF*max{|F(k)|,|F(k+1)|,1}
                is satisfied.
    EpsX    -   >=0
                The subroutine finishes its work if  on  k+1-th  iteration
                the condition |X(k+1)-X(k)| <= EpsX is fulfilled.
    MaxIts  -   maximum number of iterations. If MaxIts=0, the  number  of
                iterations   is    unlimited.   Only   Levenberg-Marquardt
                iterations  are  counted  (L-BFGS/CG  iterations  are  NOT
                counted because their cost is very low compared to that of
                LM).

Passing EpsG=0, EpsF=0, EpsX=0 and MaxIts=0 (simultaneously) will lead to
automatic stopping criterion selection (small EpsX).

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minlmsetcond(minlmstate* state,
     double epsg,
     double epsf,
     double epsx,
     ae_int_t maxits,
     ae_state *_state)
{


    ae_assert(ae_isfinite(epsg, _state), "MinLMSetCond: EpsG is not finite number!", _state);
    ae_assert(ae_fp_greater_eq(epsg,0), "MinLMSetCond: negative EpsG!", _state);
    ae_assert(ae_isfinite(epsf, _state), "MinLMSetCond: EpsF is not finite number!", _state);
    ae_assert(ae_fp_greater_eq(epsf,0), "MinLMSetCond: negative EpsF!", _state);
    ae_assert(ae_isfinite(epsx, _state), "MinLMSetCond: EpsX is not finite number!", _state);
    ae_assert(ae_fp_greater_eq(epsx,0), "MinLMSetCond: negative EpsX!", _state);
    ae_assert(maxits>=0, "MinLMSetCond: negative MaxIts!", _state);
    if( ((ae_fp_eq(epsg,0)&&ae_fp_eq(epsf,0))&&ae_fp_eq(epsx,0))&&maxits==0 )
    {
        epsx = 1.0E-6;
    }
    state->epsg = epsg;
    state->epsf = epsf;
    state->epsx = epsx;
    state->maxits = maxits;
}


/*************************************************************************
This function turns on/off reporting.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    NeedXRep-   whether iteration reports are needed or not

If NeedXRep is True, algorithm will call rep() callback function if  it is
provided to MinLMOptimize(). Both Levenberg-Marquardt and internal  L-BFGS
iterations are reported.

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minlmsetxrep(minlmstate* state, ae_bool needxrep, ae_state *_state)
{


    state->xrep = needxrep;
}


/*************************************************************************
This function sets maximum step length

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    StpMax  -   maximum step length, >=0. Set StpMax to 0.0,  if you don't
                want to limit step length.

Use this subroutine when you optimize target function which contains exp()
or  other  fast  growing  functions,  and optimization algorithm makes too
large  steps  which  leads  to overflow. This function allows us to reject
steps  that  are  too  large  (and  therefore  expose  us  to the possible
overflow) without actually calculating function value at the x+stp*d.

NOTE: non-zero StpMax leads to moderate  performance  degradation  because
intermediate  step  of  preconditioned L-BFGS optimization is incompatible
with limits on step size.

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minlmsetstpmax(minlmstate* state, double stpmax, ae_state *_state)
{


    ae_assert(ae_isfinite(stpmax, _state), "MinLMSetStpMax: StpMax is not finite!", _state);
    ae_assert(ae_fp_greater_eq(stpmax,0), "MinLMSetStpMax: StpMax<0!", _state);
    state->stpmax = stpmax;
}


/*************************************************************************
This function is used to change acceleration settings

You can choose between three acceleration strategies:
* AccType=0, no acceleration.
* AccType=1, secant updates are used to update quadratic model after  each
  iteration. After fixed number of iterations (or after  model  breakdown)
  we  recalculate  quadratic  model  using  analytic  Jacobian  or  finite
  differences. Number of secant-based iterations depends  on  optimization
  settings: about 3 iterations - when we have analytic Jacobian, up to 2*N
  iterations - when we use finite differences to calculate Jacobian.
* AccType=2, after quadratic model is built and LM step is made, we use it
  as preconditioner for several (5-10) iterations of L-BFGS algorithm.

AccType=1 is recommended when Jacobian  calculation  cost  is  prohibitive
high (several Mx1 function vector calculations  followed  by  several  NxN
Cholesky factorizations are faster than calculation of one M*N  Jacobian).
It should also be used when we have no Jacobian, because finite difference
approximation takes too much time to compute.

AccType=2 is recommended when Jacobian is cheap - much more  cheaper  than
one  Cholesky  factorization.   We   can   reduce   number   of   Cholesky
factorizations at the cost of increased number of  Jacobian  calculations.
Sometimes it helps.

Table below list  optimization  protocols  (XYZ  protocol  corresponds  to
MinLMCreateXYZ) and acceleration types they support (and use by  default).

ACCELERATION TYPES SUPPORTED BY OPTIMIZATION PROTOCOLS:

protocol    0   1   2   comment
V           +   +
VJ          +   +   +
FGH         +       +
VGJ         +   +   +   special protocol, not for widespread use
FJ          +       +   obsolete protocol, not recommended
FGJ         +       +   obsolete protocol, not recommended

DAFAULT VALUES:

protocol    0   1   2   comment
V               x       without acceleration it is so slooooooooow
VJ          x
FGH         x
VGJ                 x   we've implicitly turned (2) by passing gradient
FJ          x           obsolete protocol, not recommended
FGJ                 x   obsolete protocol, not recommended

NOTE: this  function should be called before optimization. Attempt to call
it during algorithm iterations may result in unexpected behavior.

NOTE: attempt to call this function with unsupported protocol/acceleration
combination will result in exception being thrown.

  -- ALGLIB --
     Copyright 14.10.2010 by Bochkanov Sergey
*************************************************************************/
void minlmsetacctype(minlmstate* state,
     ae_int_t acctype,
     ae_state *_state)
{


    ae_assert((acctype==0||acctype==1)||acctype==2, "MinLMSetAccType: incorrect AccType!", _state);
    if( acctype==0 )
    {
        state->maxmodelage = 0;
        state->makeadditers = ae_false;
        return;
    }
    if( acctype==1 )
    {
        ae_assert(state->hasfi, "MinLMSetAccType: AccType=1 is incompatible with current protocol!", _state);
        if( state->algomode==0 )
        {
            state->maxmodelage = 2*state->n;
        }
        else
        {
            state->maxmodelage = minlm_smallmodelage;
        }
        state->makeadditers = ae_false;
        return;
    }
    if( acctype==2 )
    {
        ae_assert(state->algomode==1||state->algomode==2, "MinLMSetAccType: AccType=2 is incompatible with current protocol!", _state);
        state->maxmodelage = 0;
        state->makeadditers = ae_true;
        return;
    }
}


/*************************************************************************
NOTES:

1. Depending on function used to create state  structure,  this  algorithm
   may accept Jacobian and/or Hessian and/or gradient.  According  to  the
   said above, there ase several versions of this function,  which  accept
   different sets of callbacks.

   This flexibility opens way to subtle errors - you may create state with
   MinLMCreateFGH() (optimization using Hessian), but call function  which
   does not accept Hessian. So when algorithm will request Hessian,  there
   will be no callback to call. In this case exception will be thrown.

   Be careful to avoid such errors because there is no way to find them at
   compile time - you can see them at runtime only.

  -- ALGLIB --
     Copyright 10.03.2009 by Bochkanov Sergey
*************************************************************************/
ae_bool minlmiteration(minlmstate* state, ae_state *_state)
{
    ae_int_t n;
    ae_int_t m;
    ae_bool bflag;
    ae_int_t iflag;
    double v;
    double s;
    double t;
    ae_int_t i;
    ae_int_t k;
    ae_bool result;


    
    /*
     * Reverse communication preparations
     * I know it looks ugly, but it works the same way
     * anywhere from C++ to Python.
     *
     * This code initializes locals by:
     * * random values determined during code
     *   generation - on first subroutine call
     * * values from previous call - on subsequent calls
     */
    if( state->rstate.stage>=0 )
    {
        n = state->rstate.ia.ptr.p_int[0];
        m = state->rstate.ia.ptr.p_int[1];
        iflag = state->rstate.ia.ptr.p_int[2];
        i = state->rstate.ia.ptr.p_int[3];
        k = state->rstate.ia.ptr.p_int[4];
        bflag = state->rstate.ba.ptr.p_bool[0];
        v = state->rstate.ra.ptr.p_double[0];
        s = state->rstate.ra.ptr.p_double[1];
        t = state->rstate.ra.ptr.p_double[2];
    }
    else
    {
        n = -983;
        m = -989;
        iflag = -834;
        i = 900;
        k = -287;
        bflag = ae_false;
        v = 214;
        s = -338;
        t = -686;
    }
    if( state->rstate.stage==0 )
    {
        goto lbl_0;
    }
    if( state->rstate.stage==1 )
    {
        goto lbl_1;
    }
    if( state->rstate.stage==2 )
    {
        goto lbl_2;
    }
    if( state->rstate.stage==3 )
    {
        goto lbl_3;
    }
    if( state->rstate.stage==4 )
    {
        goto lbl_4;
    }
    if( state->rstate.stage==5 )
    {
        goto lbl_5;
    }
    if( state->rstate.stage==6 )
    {
        goto lbl_6;
    }
    if( state->rstate.stage==7 )
    {
        goto lbl_7;
    }
    if( state->rstate.stage==8 )
    {
        goto lbl_8;
    }
    if( state->rstate.stage==9 )
    {
        goto lbl_9;
    }
    if( state->rstate.stage==10 )
    {
        goto lbl_10;
    }
    if( state->rstate.stage==11 )
    {
        goto lbl_11;
    }
    if( state->rstate.stage==12 )
    {
        goto lbl_12;
    }
    if( state->rstate.stage==13 )
    {
        goto lbl_13;
    }
    if( state->rstate.stage==14 )
    {
        goto lbl_14;
    }
    if( state->rstate.stage==15 )
    {
        goto lbl_15;
    }
    if( state->rstate.stage==16 )
    {
        goto lbl_16;
    }
    if( state->rstate.stage==17 )
    {
        goto lbl_17;
    }
    
    /*
     * Routine body
     */
    
    /*
     * prepare
     */
    n = state->n;
    m = state->m;
    state->repiterationscount = 0;
    state->repterminationtype = 0;
    state->repnfunc = 0;
    state->repnjac = 0;
    state->repngrad = 0;
    state->repnhess = 0;
    state->repncholesky = 0;
    
    /*
     * Initial report of current point
     *
     * Note 1: we rewrite State.X twice because
     * user may accidentally change it after first call.
     *
     * Note 2: we set NeedF or NeedFI depending on what
     * information about function we have.
     */
    if( !state->xrep )
    {
        goto lbl_18;
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->xbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
    minlm_clearrequestfields(state, _state);
    if( !state->hasf )
    {
        goto lbl_20;
    }
    state->needf = ae_true;
    state->rstate.stage = 0;
    goto lbl_rcomm;
lbl_0:
    state->needf = ae_false;
    goto lbl_21;
lbl_20:
    ae_assert(state->hasfi, "MinLM: internal error 2!", _state);
    state->needfi = ae_true;
    state->rstate.stage = 1;
    goto lbl_rcomm;
lbl_1:
    state->needfi = ae_false;
    v = ae_v_dotproduct(&state->fi.ptr.p_double[0], 1, &state->fi.ptr.p_double[0], 1, ae_v_len(0,m-1));
    state->f = v;
lbl_21:
    state->repnfunc = state->repnfunc+1;
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->xbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
    minlm_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 2;
    goto lbl_rcomm;
lbl_2:
    state->xupdated = ae_false;
lbl_18:
    
    /*
     * Prepare control variables
     */
    state->nu = 1;
    state->lambdav = -ae_maxrealnumber;
    state->modelage = state->maxmodelage+1;
    state->deltaxready = ae_false;
    state->deltafready = ae_false;
    
    /*
     * Main cycle.
     *
     * We move through it until either:
     * * one of the stopping conditions is met
     * * we decide that stopping conditions are too stringent
     *   and break from cycle
     *
     */
lbl_22:
    if( ae_false )
    {
        goto lbl_23;
    }
    
    /*
     * First, we have to prepare quadratic model for our function.
     * We use BFlag to ensure that model is prepared;
     * if it is false at the end of this block, something went wrong.
     *
     * We may either calculate brand new model or update old one.
     *
     * Before this block we have:
     * * State.XBase            - current position.
     * * State.DeltaX           - if DeltaXReady is True
     * * State.DeltaF           - if DeltaFReady is True
     *
     * After this block is over, we will have:
     * * State.XBase            - base point (unchanged)
     * * State.FBase            - F(XBase)
     * * State.GBase            - linear term
     * * State.QuadraticModel   - quadratic term
     * * State.LambdaV          - current estimate for lambda
     *
     * We also clear DeltaXReady/DeltaFReady flags
     * after initialization is done.
     */
    bflag = ae_false;
    if( !(state->algomode==0||state->algomode==1) )
    {
        goto lbl_24;
    }
    
    /*
     * Calculate f[] and Jacobian
     */
    if( !(state->modelage>state->maxmodelage||!(state->deltaxready&&state->deltafready)) )
    {
        goto lbl_26;
    }
    
    /*
     * Refresh model (using either finite differences or analytic Jacobian)
     */
    if( state->algomode!=0 )
    {
        goto lbl_28;
    }
    
    /*
     * Optimization using F values only.
     * Use finite differences to estimate Jacobian.
     */
    ae_assert(state->hasfi, "MinLMIteration: internal error when estimating Jacobian (no f[])", _state);
    k = 0;
lbl_30:
    if( k>n-1 )
    {
        goto lbl_32;
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->xbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
    state->x.ptr.p_double[k] = state->x.ptr.p_double[k]-state->diffstep;
    minlm_clearrequestfields(state, _state);
    state->needfi = ae_true;
    state->rstate.stage = 3;
    goto lbl_rcomm;
lbl_3:
    state->repnfunc = state->repnfunc+1;
    ae_v_move(&state->fm1.ptr.p_double[0], 1, &state->fi.ptr.p_double[0], 1, ae_v_len(0,m-1));
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->xbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
    state->x.ptr.p_double[k] = state->x.ptr.p_double[k]+state->diffstep;
    minlm_clearrequestfields(state, _state);
    state->needfi = ae_true;
    state->rstate.stage = 4;
    goto lbl_rcomm;
lbl_4:
    state->repnfunc = state->repnfunc+1;
    ae_v_move(&state->fp1.ptr.p_double[0], 1, &state->fi.ptr.p_double[0], 1, ae_v_len(0,m-1));
    v = 1/(2*state->diffstep);
    ae_v_moved(&state->j.ptr.pp_double[0][k], state->j.stride, &state->fp1.ptr.p_double[0], 1, ae_v_len(0,m-1), v);
    ae_v_subd(&state->j.ptr.pp_double[0][k], state->j.stride, &state->fm1.ptr.p_double[0], 1, ae_v_len(0,m-1), v);
    k = k+1;
    goto lbl_30;
lbl_32:
    
    /*
     * Calculate F(XBase)
     */
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->xbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
    minlm_clearrequestfields(state, _state);
    state->needfi = ae_true;
    state->rstate.stage = 5;
    goto lbl_rcomm;
lbl_5:
    state->needfi = ae_false;
    state->repnfunc = state->repnfunc+1;
    state->repnjac = state->repnjac+1;
    
    /*
     * New model
     */
    state->modelage = 0;
    goto lbl_29;
lbl_28:
    
    /*
     * Obtain f[] and Jacobian
     */
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->xbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
    minlm_clearrequestfields(state, _state);
    state->needfij = ae_true;
    state->rstate.stage = 6;
    goto lbl_rcomm;
lbl_6:
    state->needfij = ae_false;
    state->repnfunc = state->repnfunc+1;
    state->repnjac = state->repnjac+1;
    
    /*
     * New model
     */
    state->modelage = 0;
lbl_29:
    goto lbl_27;
lbl_26:
    
    /*
     * State.J contains Jacobian or its current approximation;
     * refresh it using secant updates:
     *
     * f(x0+dx) = f(x0) + J*dx,
     * J_new = J_old + u*h'
     * h = x_new-x_old
     * u = (f_new - f_old - J_old*h)/(h'h)
     *
     * We can explicitly generate h and u, but it is
     * preferential to do in-place calculations. Only
     * I-th row of J_old is needed to calculate u[I],
     * so we can update J row by row in one pass.
     *
     * NOTE: we expect that State.XBase contains new point,
     * State.FBase contains old point, State.DeltaX and
     * State.DeltaY contain updates from last step.
     */
    ae_assert(state->deltaxready&&state->deltafready, "MinLMIteration: uninitialized DeltaX/DeltaF", _state);
    t = ae_v_dotproduct(&state->deltax.ptr.p_double[0], 1, &state->deltax.ptr.p_double[0], 1, ae_v_len(0,n-1));
    ae_assert(ae_fp_neq(t,0), "MinLM: internal error (T=0)", _state);
    for(i=0; i<=m-1; i++)
    {
        v = ae_v_dotproduct(&state->j.ptr.pp_double[i][0], 1, &state->deltax.ptr.p_double[0], 1, ae_v_len(0,n-1));
        v = (state->deltaf.ptr.p_double[i]-v)/t;
        ae_v_addd(&state->j.ptr.pp_double[i][0], 1, &state->deltax.ptr.p_double[0], 1, ae_v_len(0,n-1), v);
    }
    ae_v_move(&state->fi.ptr.p_double[0], 1, &state->fibase.ptr.p_double[0], 1, ae_v_len(0,m-1));
    ae_v_add(&state->fi.ptr.p_double[0], 1, &state->deltaf.ptr.p_double[0], 1, ae_v_len(0,m-1));
    
    /*
     * Increase model age
     */
    state->modelage = state->modelage+1;
lbl_27:
    
    /*
     * Generate quadratic model:
     *     f(xbase+dx) =
     *       = (f0 + J*dx)'(f0 + J*dx)
     *       = f0^2 + dx'J'f0 + f0*J*dx + dx'J'J*dx
     *       = f0^2 + 2*f0*J*dx + dx'J'J*dx
     *
     * Note that we calculate 2*(J'J) instead of J'J because
     * our quadratic model is based on Tailor decomposition,
     * i.e. it has 0.5 before quadratic term.
     */
    rmatrixgemm(n, n, m, 2.0, &state->j, 0, 0, 1, &state->j, 0, 0, 0, 0.0, &state->quadraticmodel, 0, 0, _state);
    rmatrixmv(n, m, &state->j, 0, 0, 1, &state->fi, 0, &state->gbase, 0, _state);
    ae_v_muld(&state->gbase.ptr.p_double[0], 1, ae_v_len(0,n-1), 2);
    v = ae_v_dotproduct(&state->fi.ptr.p_double[0], 1, &state->fi.ptr.p_double[0], 1, ae_v_len(0,m-1));
    state->fbase = v;
    ae_v_move(&state->fibase.ptr.p_double[0], 1, &state->fi.ptr.p_double[0], 1, ae_v_len(0,m-1));
    
    /*
     * set control variables
     */
    bflag = ae_true;
lbl_24:
    if( state->algomode!=2 )
    {
        goto lbl_33;
    }
    ae_assert(!state->hasfi, "MinLMIteration: internal error (HasFI is True in Hessian-based mode)", _state);
    
    /*
     * Obtain F, G, H
     */
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->xbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
    minlm_clearrequestfields(state, _state);
    state->needfgh = ae_true;
    state->rstate.stage = 7;
    goto lbl_rcomm;
lbl_7:
    state->needfgh = ae_false;
    state->repnfunc = state->repnfunc+1;
    state->repngrad = state->repngrad+1;
    state->repnhess = state->repnhess+1;
    rmatrixcopy(n, n, &state->h, 0, 0, &state->quadraticmodel, 0, 0, _state);
    ae_v_move(&state->gbase.ptr.p_double[0], 1, &state->g.ptr.p_double[0], 1, ae_v_len(0,n-1));
    state->fbase = state->f;
    
    /*
     * set control variables
     */
    bflag = ae_true;
    state->modelage = 0;
lbl_33:
    ae_assert(bflag, "MinLM: internal integrity check failed!", _state);
    state->deltaxready = ae_false;
    state->deltafready = ae_false;
    
    /*
     * If Lambda is not initialized, initialize it using quadratic model
     */
    if( ae_fp_less(state->lambdav,0) )
    {
        state->lambdav = 0;
        for(i=0; i<=n-1; i++)
        {
            state->lambdav = ae_maxreal(state->lambdav, ae_fabs(state->quadraticmodel.ptr.pp_double[i][i], _state), _state);
        }
        state->lambdav = 0.001*state->lambdav;
        if( ae_fp_eq(state->lambdav,0) )
        {
            state->lambdav = 1;
        }
    }
    
    /*
     * Test stopping conditions for function gradient
     */
    v = ae_v_dotproduct(&state->gbase.ptr.p_double[0], 1, &state->gbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
    v = ae_sqrt(v, _state);
    if( ae_fp_greater(v,state->epsg) )
    {
        goto lbl_35;
    }
    if( state->modelage!=0 )
    {
        goto lbl_37;
    }
    
    /*
     * Model is fresh, we can rely on it and terminate algorithm
     */
    state->repterminationtype = 4;
    if( !state->xrep )
    {
        goto lbl_39;
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->xbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
    state->f = state->fbase;
    minlm_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 8;
    goto lbl_rcomm;
lbl_8:
    state->xupdated = ae_false;
lbl_39:
    result = ae_false;
    return result;
    goto lbl_38;
lbl_37:
    
    /*
     * Model is not fresh, we should refresh it and test
     * conditions once more
     */
    state->modelage = state->maxmodelage+1;
    goto lbl_22;
lbl_38:
lbl_35:
    
    /*
     * Find value of Levenberg-Marquardt damping parameter which:
     * * leads to positive definite damped model
     * * within bounds specified by StpMax
     * * generates step which decreases function value
     *
     * After this block IFlag is set to:
     * * -2, if model update is needed (either Lambda growth is too large
     *       or step is too short, but we can't rely on model and stop iterations)
     * * -1, if model is fresh, Lambda have grown too large, termination is needed
     * *  0, if everything is OK, continue iterations
     *
     * State.Nu can have any value on enter, but after exit it is set to 1.0
     */
    iflag = -99;
lbl_41:
    if( ae_false )
    {
        goto lbl_42;
    }
    
    /*
     * Do we need model update?
     */
    if( state->modelage>0&&ae_fp_greater_eq(state->nu,minlm_suspiciousnu) )
    {
        iflag = -2;
        goto lbl_42;
    }
    
    /*
     * DampedModel = QuadraticModel+lambda*I
     */
    rmatrixcopy(n, n, &state->quadraticmodel, 0, 0, &state->dampedmodel, 0, 0, _state);
    for(i=0; i<=n-1; i++)
    {
        state->dampedmodel.ptr.pp_double[i][i] = state->dampedmodel.ptr.pp_double[i][i]+state->lambdav;
    }
    
    /*
     * 1. try to solve (RawModel+Lambda*I)*dx = -g.
     *    increase lambda if left part is not positive definite.
     * 2. bound step by StpMax
     *    increase lambda if step is larger than StpMax
     *
     * We use BFlag variable to indicate that we have to increase Lambda.
     * If it is False, we will try to increase Lambda and move to new iteration.
     */
    bflag = ae_true;
    state->repncholesky = state->repncholesky+1;
    if( spdmatrixcholeskyrec(&state->dampedmodel, 0, n, ae_true, &state->choleskybuf, _state) )
    {
        ae_v_moveneg(&state->xdir.ptr.p_double[0], 1, &state->gbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
        fblscholeskysolve(&state->dampedmodel, 1.0, n, ae_true, &state->xdir, &state->choleskybuf, _state);
        v = ae_v_dotproduct(&state->xdir.ptr.p_double[0], 1, &state->xdir.ptr.p_double[0], 1, ae_v_len(0,n-1));
        if( ae_isfinite(v, _state) )
        {
            v = ae_sqrt(v, _state);
            if( ae_fp_greater(state->stpmax,0)&&ae_fp_greater(v,state->stpmax) )
            {
                bflag = ae_false;
            }
        }
        else
        {
            bflag = ae_false;
        }
    }
    else
    {
        bflag = ae_false;
    }
    if( !bflag )
    {
        
        /*
         * Solution failed:
         * try to increase lambda to make matrix positive definite and continue.
         */
        if( !minlm_increaselambda(&state->lambdav, &state->nu, _state) )
        {
            iflag = -1;
            goto lbl_42;
        }
        goto lbl_41;
    }
    
    /*
     * Step in State.XDir and it is bounded by StpMax.
     *
     * We should check stopping conditions on step size here.
     * DeltaX, which is used for secant updates, is initialized here.
     *
     * This code is a bit tricky because sometimes XDir<>0, but
     * it is so small that XDir+XBase==XBase (in finite precision
     * arithmetics). So we set DeltaX to XBase, then
     * add XDir, and then subtract XBase to get exact value of
     * DeltaX.
     *
     * Step length is estimated using DeltaX.
     *
     * NOTE: stopping conditions are tested
     * for fresh models only (ModelAge=0)
     */
    ae_v_move(&state->deltax.ptr.p_double[0], 1, &state->xbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
    ae_v_add(&state->deltax.ptr.p_double[0], 1, &state->xdir.ptr.p_double[0], 1, ae_v_len(0,n-1));
    ae_v_sub(&state->deltax.ptr.p_double[0], 1, &state->xbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
    state->deltaxready = ae_true;
    v = ae_v_dotproduct(&state->deltax.ptr.p_double[0], 1, &state->deltax.ptr.p_double[0], 1, ae_v_len(0,n-1));
    v = ae_sqrt(v, _state);
    if( ae_fp_greater(v,state->epsx) )
    {
        goto lbl_43;
    }
    if( state->modelage!=0 )
    {
        goto lbl_45;
    }
    
    /*
     * Step is too short, model is fresh and we can rely on it.
     * Terminating.
     */
    state->repterminationtype = 2;
    if( !state->xrep )
    {
        goto lbl_47;
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->xbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
    state->f = state->fbase;
    minlm_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 9;
    goto lbl_rcomm;
lbl_9:
    state->xupdated = ae_false;
lbl_47:
    result = ae_false;
    return result;
    goto lbl_46;
lbl_45:
    
    /*
     * Step is suspiciously short, but model is not fresh
     * and we can't rely on it.
     */
    iflag = -2;
    goto lbl_42;
lbl_46:
lbl_43:
    
    /*
     * Let's evaluate new step:
     * a) if we have Fi vector, we evaluate it using rcomm, and
     *    then we manually calculate State.F as sum of squares of Fi[]
     * b) if we have F value, we just evaluate it through rcomm interface
     *
     * We prefer (a) because we may need Fi vector for additional
     * iterations
     */
    ae_assert(state->hasfi||state->hasf, "MinLM: internal error 2!", _state);
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->xbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
    ae_v_add(&state->x.ptr.p_double[0], 1, &state->xdir.ptr.p_double[0], 1, ae_v_len(0,n-1));
    minlm_clearrequestfields(state, _state);
    if( !state->hasfi )
    {
        goto lbl_49;
    }
    state->needfi = ae_true;
    state->rstate.stage = 10;
    goto lbl_rcomm;
lbl_10:
    state->needfi = ae_false;
    v = ae_v_dotproduct(&state->fi.ptr.p_double[0], 1, &state->fi.ptr.p_double[0], 1, ae_v_len(0,m-1));
    state->f = v;
    ae_v_move(&state->deltaf.ptr.p_double[0], 1, &state->fi.ptr.p_double[0], 1, ae_v_len(0,m-1));
    ae_v_sub(&state->deltaf.ptr.p_double[0], 1, &state->fibase.ptr.p_double[0], 1, ae_v_len(0,m-1));
    state->deltafready = ae_true;
    goto lbl_50;
lbl_49:
    state->needf = ae_true;
    state->rstate.stage = 11;
    goto lbl_rcomm;
lbl_11:
    state->needf = ae_false;
lbl_50:
    state->repnfunc = state->repnfunc+1;
    if( ae_fp_greater_eq(state->f,state->fbase) )
    {
        
        /*
         * Increase lambda and continue
         */
        if( !minlm_increaselambda(&state->lambdav, &state->nu, _state) )
        {
            iflag = -1;
            goto lbl_42;
        }
        goto lbl_41;
    }
    
    /*
     * We've found our step!
     */
    iflag = 0;
    goto lbl_42;
    goto lbl_41;
lbl_42:
    state->nu = 1;
    ae_assert(iflag>=-2&&iflag<=0, "MinLM: internal integrity check failed!", _state);
    if( iflag==-2 )
    {
        state->modelage = state->maxmodelage+1;
        goto lbl_22;
    }
    if( iflag==-1 )
    {
        goto lbl_23;
    }
    
    /*
     * Levenberg-Marquardt step is ready.
     * Compare predicted vs. actual decrease and decide what to do with lambda.
     *
     * NOTE: we expect that State.DeltaX contains direction of step,
     * State.F contains function value at new point.
     */
    ae_assert(state->deltaxready, "MinLM: deltaX is not ready", _state);
    t = 0;
    for(i=0; i<=n-1; i++)
    {
        v = ae_v_dotproduct(&state->quadraticmodel.ptr.pp_double[i][0], 1, &state->deltax.ptr.p_double[0], 1, ae_v_len(0,n-1));
        t = t+state->deltax.ptr.p_double[i]*state->gbase.ptr.p_double[i]+0.5*state->deltax.ptr.p_double[i]*v;
    }
    state->predicteddecrease = -t;
    state->actualdecrease = -(state->f-state->fbase);
    if( ae_fp_less_eq(state->predicteddecrease,0) )
    {
        goto lbl_23;
    }
    v = state->actualdecrease/state->predicteddecrease;
    if( ae_fp_greater_eq(v,0.1) )
    {
        goto lbl_51;
    }
    if( minlm_increaselambda(&state->lambdav, &state->nu, _state) )
    {
        goto lbl_53;
    }
    
    /*
     * Lambda is too large, we have to break iterations.
     */
    state->repterminationtype = 7;
    if( !state->xrep )
    {
        goto lbl_55;
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->xbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
    state->f = state->fbase;
    minlm_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 12;
    goto lbl_rcomm;
lbl_12:
    state->xupdated = ae_false;
lbl_55:
    result = ae_false;
    return result;
lbl_53:
lbl_51:
    if( ae_fp_greater(v,0.5) )
    {
        minlm_decreaselambda(&state->lambdav, &state->nu, _state);
    }
    
    /*
     * Accept step, report it and
     * test stopping conditions on iterations count and function decrease.
     *
     * NOTE: we expect that State.DeltaX contains direction of step,
     * State.F contains function value at new point.
     *
     * NOTE2: we should update XBase ONLY. In the beginning of the next
     * iteration we expect that State.FIBase is NOT updated and
     * contains old value of a function vector.
     */
    ae_v_add(&state->xbase.ptr.p_double[0], 1, &state->deltax.ptr.p_double[0], 1, ae_v_len(0,n-1));
    if( !state->xrep )
    {
        goto lbl_57;
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->xbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
    minlm_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 13;
    goto lbl_rcomm;
lbl_13:
    state->xupdated = ae_false;
lbl_57:
    state->repiterationscount = state->repiterationscount+1;
    if( state->repiterationscount>=state->maxits&&state->maxits>0 )
    {
        state->repterminationtype = 5;
    }
    if( state->modelage==0 )
    {
        if( ae_fp_less_eq(ae_fabs(state->f-state->fbase, _state),state->epsf*ae_maxreal(1, ae_maxreal(ae_fabs(state->f, _state), ae_fabs(state->fbase, _state), _state), _state)) )
        {
            state->repterminationtype = 1;
        }
    }
    if( state->repterminationtype<=0 )
    {
        goto lbl_59;
    }
    if( !state->xrep )
    {
        goto lbl_61;
    }
    
    /*
     * Report: XBase contains new point, F contains function value at new point
     */
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->xbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
    minlm_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 14;
    goto lbl_rcomm;
lbl_14:
    state->xupdated = ae_false;
lbl_61:
    result = ae_false;
    return result;
lbl_59:
    state->modelage = state->modelage+1;
    
    /*
     * Additional iterations for unconstrained problems:
     * preconditioned L-BFGS is used.
     *
     * NOTE: additional iterations are incompatible with secant updates
     * because they invalidate
     */
    if( !(ae_fp_eq(state->stpmax,0)&&state->makeadditers) )
    {
        goto lbl_63;
    }
    ae_assert(state->hasg||state->m!=0, "MinLM: no grad or Jacobian for additional iterations", _state);
    
    /*
     * Make preconditioned iterations
     */
    minlbfgssetcholeskypreconditioner(&state->internalstate, &state->dampedmodel, ae_true, _state);
    minlbfgsrestartfrom(&state->internalstate, &state->xbase, _state);
lbl_65:
    if( !minlbfgsiteration(&state->internalstate, _state) )
    {
        goto lbl_66;
    }
    if( !state->internalstate.needfg )
    {
        goto lbl_67;
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->internalstate.x.ptr.p_double[0], 1, ae_v_len(0,n-1));
    minlm_clearrequestfields(state, _state);
    if( !state->hasg )
    {
        goto lbl_69;
    }
    state->needfg = ae_true;
    state->rstate.stage = 15;
    goto lbl_rcomm;
lbl_15:
    state->needfg = ae_false;
    state->repngrad = state->repngrad+1;
    ae_v_move(&state->internalstate.g.ptr.p_double[0], 1, &state->g.ptr.p_double[0], 1, ae_v_len(0,n-1));
    state->internalstate.f = state->f;
    goto lbl_70;
lbl_69:
    state->needfij = ae_true;
    state->rstate.stage = 16;
    goto lbl_rcomm;
lbl_16:
    state->needfij = ae_false;
    state->repnfunc = state->repnfunc+1;
    state->repnjac = state->repnjac+1;
    for(i=0; i<=n-1; i++)
    {
        state->internalstate.g.ptr.p_double[i] = 0;
    }
    for(i=0; i<=m-1; i++)
    {
        v = 2*state->fi.ptr.p_double[i];
        ae_v_addd(&state->internalstate.g.ptr.p_double[0], 1, &state->j.ptr.pp_double[i][0], 1, ae_v_len(0,n-1), v);
        state->internalstate.f = state->internalstate.f+ae_sqr(state->fi.ptr.p_double[i], _state);
    }
lbl_70:
lbl_67:
    goto lbl_65;
lbl_66:
    minlbfgsresultsbuf(&state->internalstate, &state->xbase, &state->internalrep, _state);
    
    /*
     * Invalidate DeltaX/DeltaF (control variables used for integrity checks)
     */
    state->deltaxready = ae_false;
    state->deltafready = ae_false;
lbl_63:
    goto lbl_22;
lbl_23:
    
    /*
     * Lambda is too large, we have to break iterations.
     */
    state->repterminationtype = 7;
    if( !state->xrep )
    {
        goto lbl_71;
    }
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->xbase.ptr.p_double[0], 1, ae_v_len(0,n-1));
    state->f = state->fbase;
    minlm_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 17;
    goto lbl_rcomm;
lbl_17:
    state->xupdated = ae_false;
lbl_71:
    result = ae_false;
    return result;
    
    /*
     * Saving state
     */
lbl_rcomm:
    result = ae_true;
    state->rstate.ia.ptr.p_int[0] = n;
    state->rstate.ia.ptr.p_int[1] = m;
    state->rstate.ia.ptr.p_int[2] = iflag;
    state->rstate.ia.ptr.p_int[3] = i;
    state->rstate.ia.ptr.p_int[4] = k;
    state->rstate.ba.ptr.p_bool[0] = bflag;
    state->rstate.ra.ptr.p_double[0] = v;
    state->rstate.ra.ptr.p_double[1] = s;
    state->rstate.ra.ptr.p_double[2] = t;
    return result;
}


/*************************************************************************
Levenberg-Marquardt algorithm results

INPUT PARAMETERS:
    State   -   algorithm state

OUTPUT PARAMETERS:
    X       -   array[0..N-1], solution
    Rep     -   optimization report;
                see comments for this structure for more info.

  -- ALGLIB --
     Copyright 10.03.2009 by Bochkanov Sergey
*************************************************************************/
void minlmresults(minlmstate* state,
     /* Real    */ ae_vector* x,
     minlmreport* rep,
     ae_state *_state)
{

    ae_vector_clear(x);
    _minlmreport_clear(rep);

    minlmresultsbuf(state, x, rep, _state);
}


/*************************************************************************
Levenberg-Marquardt algorithm results

Buffered implementation of MinLMResults(), which uses pre-allocated buffer
to store X[]. If buffer size is  too  small,  it  resizes  buffer.  It  is
intended to be used in the inner cycles of performance critical algorithms
where array reallocation penalty is too large to be ignored.

  -- ALGLIB --
     Copyright 10.03.2009 by Bochkanov Sergey
*************************************************************************/
void minlmresultsbuf(minlmstate* state,
     /* Real    */ ae_vector* x,
     minlmreport* rep,
     ae_state *_state)
{


    if( x->cnt<state->n )
    {
        ae_vector_set_length(x, state->n, _state);
    }
    ae_v_move(&x->ptr.p_double[0], 1, &state->x.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    rep->iterationscount = state->repiterationscount;
    rep->terminationtype = state->repterminationtype;
    rep->nfunc = state->repnfunc;
    rep->njac = state->repnjac;
    rep->ngrad = state->repngrad;
    rep->nhess = state->repnhess;
    rep->ncholesky = state->repncholesky;
}


/*************************************************************************
This  subroutine  restarts  LM  algorithm from new point. All optimization
parameters are left unchanged.

This  function  allows  to  solve multiple  optimization  problems  (which
must have same number of dimensions) without object reallocation penalty.

INPUT PARAMETERS:
    State   -   structure used for reverse communication previously
                allocated with MinLMCreateXXX call.
    X       -   new starting point.

  -- ALGLIB --
     Copyright 30.07.2010 by Bochkanov Sergey
*************************************************************************/
void minlmrestartfrom(minlmstate* state,
     /* Real    */ ae_vector* x,
     ae_state *_state)
{


    ae_assert(x->cnt>=state->n, "MinLMRestartFrom: Length(X)<N!", _state);
    ae_assert(isfinitevector(x, state->n, _state), "MinLMRestartFrom: X contains infinite or NaN values!", _state);
    ae_v_move(&state->xbase.ptr.p_double[0], 1, &x->ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    ae_vector_set_length(&state->rstate.ia, 4+1, _state);
    ae_vector_set_length(&state->rstate.ba, 0+1, _state);
    ae_vector_set_length(&state->rstate.ra, 2+1, _state);
    state->rstate.stage = -1;
    minlm_clearrequestfields(state, _state);
}


/*************************************************************************
Prepare internal structures (except for RComm).

Note: M must be zero for FGH mode, non-zero for V/VJ/FJ/FGJ mode.
*************************************************************************/
static void minlm_lmprepare(ae_int_t n,
     ae_int_t m,
     ae_bool havegrad,
     minlmstate* state,
     ae_state *_state)
{
    ae_int_t i;


    if( n<=0||m<0 )
    {
        return;
    }
    if( havegrad )
    {
        ae_vector_set_length(&state->g, n, _state);
    }
    if( m!=0 )
    {
        ae_matrix_set_length(&state->j, m, n, _state);
        ae_vector_set_length(&state->fi, m, _state);
        ae_vector_set_length(&state->fibase, m, _state);
        ae_vector_set_length(&state->deltaf, m, _state);
        ae_vector_set_length(&state->fm2, m, _state);
        ae_vector_set_length(&state->fm1, m, _state);
        ae_vector_set_length(&state->fp2, m, _state);
        ae_vector_set_length(&state->fp1, m, _state);
    }
    else
    {
        ae_matrix_set_length(&state->h, n, n, _state);
    }
    ae_vector_set_length(&state->x, n, _state);
    ae_vector_set_length(&state->deltax, n, _state);
    ae_matrix_set_length(&state->quadraticmodel, n, n, _state);
    ae_matrix_set_length(&state->dampedmodel, n, n, _state);
    ae_vector_set_length(&state->xbase, n, _state);
    ae_vector_set_length(&state->gbase, n, _state);
    ae_vector_set_length(&state->xdir, n, _state);
    
    /*
     * prepare internal L-BFGS
     */
    for(i=0; i<=n-1; i++)
    {
        state->x.ptr.p_double[i] = 0;
    }
    minlbfgscreate(n, ae_minint(minlm_additers, n, _state), &state->x, &state->internalstate, _state);
    minlbfgssetcond(&state->internalstate, 0.0, 0.0, 0.0, ae_minint(minlm_additers, n, _state), _state);
}


/*************************************************************************
Clears request fileds (to be sure that we don't forgot to clear something)
*************************************************************************/
static void minlm_clearrequestfields(minlmstate* state, ae_state *_state)
{


    state->needf = ae_false;
    state->needfg = ae_false;
    state->needfgh = ae_false;
    state->needfij = ae_false;
    state->needfi = ae_false;
    state->xupdated = ae_false;
}


/*************************************************************************
Increases lambda, returns False when there is a danger of overflow
*************************************************************************/
static ae_bool minlm_increaselambda(double* lambdav,
     double* nu,
     ae_state *_state)
{
    double lnlambda;
    double lnnu;
    double lnlambdaup;
    double lnmax;
    ae_bool result;


    result = ae_false;
    lnlambda = ae_log(*lambdav, _state);
    lnlambdaup = ae_log(minlm_lambdaup, _state);
    lnnu = ae_log(*nu, _state);
    lnmax = ae_log(ae_maxrealnumber, _state);
    if( ae_fp_greater(lnlambda+lnlambdaup+lnnu,0.25*lnmax) )
    {
        return result;
    }
    if( ae_fp_greater(lnnu+ae_log(2, _state),lnmax) )
    {
        return result;
    }
    *lambdav = *lambdav*minlm_lambdaup*(*nu);
    *nu = *nu*2;
    result = ae_true;
    return result;
}


/*************************************************************************
Decreases lambda, but leaves it unchanged when there is danger of underflow.
*************************************************************************/
static void minlm_decreaselambda(double* lambdav,
     double* nu,
     ae_state *_state)
{


    *nu = 1;
    if( ae_fp_less(ae_log(*lambdav, _state)+ae_log(minlm_lambdadown, _state),ae_log(ae_minrealnumber, _state)) )
    {
        *lambdav = ae_minrealnumber;
    }
    else
    {
        *lambdav = *lambdav*minlm_lambdadown;
    }
}


ae_bool _minlmstate_init(minlmstate* p, ae_state *_state, ae_bool make_automatic)
{
    if( !ae_vector_init(&p->x, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->fi, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_matrix_init(&p->j, 0, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_matrix_init(&p->h, 0, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->g, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->xbase, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->fibase, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->gbase, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_matrix_init(&p->quadraticmodel, 0, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_matrix_init(&p->dampedmodel, 0, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->xdir, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->deltax, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->deltaf, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !_rcommstate_init(&p->rstate, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->choleskybuf, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->fm2, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->fm1, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->fp2, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->fp1, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !_minlbfgsstate_init(&p->internalstate, _state, make_automatic) )
        return ae_false;
    if( !_minlbfgsreport_init(&p->internalrep, _state, make_automatic) )
        return ae_false;
    return ae_true;
}


ae_bool _minlmstate_init_copy(minlmstate* dst, minlmstate* src, ae_state *_state, ae_bool make_automatic)
{
    dst->n = src->n;
    dst->m = src->m;
    dst->diffstep = src->diffstep;
    dst->epsg = src->epsg;
    dst->epsf = src->epsf;
    dst->epsx = src->epsx;
    dst->maxits = src->maxits;
    dst->xrep = src->xrep;
    dst->stpmax = src->stpmax;
    dst->maxmodelage = src->maxmodelage;
    dst->makeadditers = src->makeadditers;
    if( !ae_vector_init_copy(&dst->x, &src->x, _state, make_automatic) )
        return ae_false;
    dst->f = src->f;
    if( !ae_vector_init_copy(&dst->fi, &src->fi, _state, make_automatic) )
        return ae_false;
    if( !ae_matrix_init_copy(&dst->j, &src->j, _state, make_automatic) )
        return ae_false;
    if( !ae_matrix_init_copy(&dst->h, &src->h, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->g, &src->g, _state, make_automatic) )
        return ae_false;
    dst->needf = src->needf;
    dst->needfg = src->needfg;
    dst->needfgh = src->needfgh;
    dst->needfij = src->needfij;
    dst->needfi = src->needfi;
    dst->xupdated = src->xupdated;
    dst->algomode = src->algomode;
    dst->hasf = src->hasf;
    dst->hasfi = src->hasfi;
    dst->hasg = src->hasg;
    if( !ae_vector_init_copy(&dst->xbase, &src->xbase, _state, make_automatic) )
        return ae_false;
    dst->fbase = src->fbase;
    if( !ae_vector_init_copy(&dst->fibase, &src->fibase, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->gbase, &src->gbase, _state, make_automatic) )
        return ae_false;
    if( !ae_matrix_init_copy(&dst->quadraticmodel, &src->quadraticmodel, _state, make_automatic) )
        return ae_false;
    dst->lambdav = src->lambdav;
    dst->nu = src->nu;
    if( !ae_matrix_init_copy(&dst->dampedmodel, &src->dampedmodel, _state, make_automatic) )
        return ae_false;
    dst->modelage = src->modelage;
    if( !ae_vector_init_copy(&dst->xdir, &src->xdir, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->deltax, &src->deltax, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->deltaf, &src->deltaf, _state, make_automatic) )
        return ae_false;
    dst->deltaxready = src->deltaxready;
    dst->deltafready = src->deltafready;
    dst->repiterationscount = src->repiterationscount;
    dst->repterminationtype = src->repterminationtype;
    dst->repnfunc = src->repnfunc;
    dst->repnjac = src->repnjac;
    dst->repngrad = src->repngrad;
    dst->repnhess = src->repnhess;
    dst->repncholesky = src->repncholesky;
    if( !_rcommstate_init_copy(&dst->rstate, &src->rstate, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->choleskybuf, &src->choleskybuf, _state, make_automatic) )
        return ae_false;
    dst->actualdecrease = src->actualdecrease;
    dst->predicteddecrease = src->predicteddecrease;
    if( !ae_vector_init_copy(&dst->fm2, &src->fm2, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->fm1, &src->fm1, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->fp2, &src->fp2, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->fp1, &src->fp1, _state, make_automatic) )
        return ae_false;
    if( !_minlbfgsstate_init_copy(&dst->internalstate, &src->internalstate, _state, make_automatic) )
        return ae_false;
    if( !_minlbfgsreport_init_copy(&dst->internalrep, &src->internalrep, _state, make_automatic) )
        return ae_false;
    return ae_true;
}


void _minlmstate_clear(minlmstate* p)
{
    ae_vector_clear(&p->x);
    ae_vector_clear(&p->fi);
    ae_matrix_clear(&p->j);
    ae_matrix_clear(&p->h);
    ae_vector_clear(&p->g);
    ae_vector_clear(&p->xbase);
    ae_vector_clear(&p->fibase);
    ae_vector_clear(&p->gbase);
    ae_matrix_clear(&p->quadraticmodel);
    ae_matrix_clear(&p->dampedmodel);
    ae_vector_clear(&p->xdir);
    ae_vector_clear(&p->deltax);
    ae_vector_clear(&p->deltaf);
    _rcommstate_clear(&p->rstate);
    ae_vector_clear(&p->choleskybuf);
    ae_vector_clear(&p->fm2);
    ae_vector_clear(&p->fm1);
    ae_vector_clear(&p->fp2);
    ae_vector_clear(&p->fp1);
    _minlbfgsstate_clear(&p->internalstate);
    _minlbfgsreport_clear(&p->internalrep);
}


ae_bool _minlmreport_init(minlmreport* p, ae_state *_state, ae_bool make_automatic)
{
    return ae_true;
}


ae_bool _minlmreport_init_copy(minlmreport* dst, minlmreport* src, ae_state *_state, ae_bool make_automatic)
{
    dst->iterationscount = src->iterationscount;
    dst->terminationtype = src->terminationtype;
    dst->nfunc = src->nfunc;
    dst->njac = src->njac;
    dst->ngrad = src->ngrad;
    dst->nhess = src->nhess;
    dst->ncholesky = src->ncholesky;
    return ae_true;
}


void _minlmreport_clear(minlmreport* p)
{
}




/*************************************************************************
        NONLINEAR CONJUGATE GRADIENT METHOD

DESCRIPTION:
The subroutine minimizes function F(x) of N arguments by using one of  the
nonlinear conjugate gradient methods.

These CG methods are globally convergent (even on non-convex functions) as
long as grad(f) is Lipschitz continuous in  a  some  neighborhood  of  the
L = { x : f(x)<=f(x0) }.


REQUIREMENTS:
Algorithm will request following information during its operation:
* function value F and its gradient G (simultaneously) at given point X


USAGE:
1. User initializes algorithm state with MinCGCreate() call
2. User tunes solver parameters with MinCGSetCond(), MinCGSetStpMax() and
   other functions
3. User calls MinCGOptimize() function which takes algorithm  state   and
   pointer (delegate, etc.) to callback function which calculates F/G.
4. User calls MinCGResults() to get solution
5. Optionally, user may call MinCGRestartFrom() to solve another  problem
   with same N but another starting point and/or another function.
   MinCGRestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   problem dimension, N>0:
                * if given, only leading N elements of X are used
                * if not given, automatically determined from size of X
    X       -   starting point, array[0..N-1].

OUTPUT PARAMETERS:
    State   -   structure which stores algorithm state

  -- ALGLIB --
     Copyright 25.03.2010 by Bochkanov Sergey
*************************************************************************/
void mincgcreate(ae_int_t n,
     /* Real    */ ae_vector* x,
     mincgstate* state,
     ae_state *_state)
{

    _mincgstate_clear(state);

    ae_assert(n>=1, "MinCGCreate: N too small!", _state);
    ae_assert(x->cnt>=n, "MinCGCreate: Length(X)<N!", _state);
    ae_assert(isfinitevector(x, n, _state), "MinCGCreate: X contains infinite or NaN values!", _state);
    
    /*
     * Initialize
     */
    state->n = n;
    mincgsetcond(state, 0, 0, 0, 0, _state);
    mincgsetxrep(state, ae_false, _state);
    mincgsetstpmax(state, 0, _state);
    mincgsetcgtype(state, -1, _state);
    ae_vector_set_length(&state->xk, n, _state);
    ae_vector_set_length(&state->dk, n, _state);
    ae_vector_set_length(&state->xn, n, _state);
    ae_vector_set_length(&state->dn, n, _state);
    ae_vector_set_length(&state->x, n, _state);
    ae_vector_set_length(&state->d, n, _state);
    ae_vector_set_length(&state->g, n, _state);
    ae_vector_set_length(&state->work, n, _state);
    ae_vector_set_length(&state->yk, n, _state);
    mincgrestartfrom(state, x, _state);
}


/*************************************************************************
This function sets stopping conditions for CG optimization algorithm.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    EpsG    -   >=0
                The  subroutine  finishes  its  work   if   the  condition
                ||G||<EpsG is satisfied, where ||.|| means Euclidian norm,
                G - gradient.
    EpsF    -   >=0
                The  subroutine  finishes  its work if on k+1-th iteration
                the  condition  |F(k+1)-F(k)|<=EpsF*max{|F(k)|,|F(k+1)|,1}
                is satisfied.
    EpsX    -   >=0
                The subroutine finishes its work if  on  k+1-th  iteration
                the condition |X(k+1)-X(k)| <= EpsX is fulfilled.
    MaxIts  -   maximum number of iterations. If MaxIts=0, the  number  of
                iterations is unlimited.

Passing EpsG=0, EpsF=0, EpsX=0 and MaxIts=0 (simultaneously) will lead to
automatic stopping criterion selection (small EpsX).

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void mincgsetcond(mincgstate* state,
     double epsg,
     double epsf,
     double epsx,
     ae_int_t maxits,
     ae_state *_state)
{


    ae_assert(ae_isfinite(epsg, _state), "MinCGSetCond: EpsG is not finite number!", _state);
    ae_assert(ae_fp_greater_eq(epsg,0), "MinCGSetCond: negative EpsG!", _state);
    ae_assert(ae_isfinite(epsf, _state), "MinCGSetCond: EpsF is not finite number!", _state);
    ae_assert(ae_fp_greater_eq(epsf,0), "MinCGSetCond: negative EpsF!", _state);
    ae_assert(ae_isfinite(epsx, _state), "MinCGSetCond: EpsX is not finite number!", _state);
    ae_assert(ae_fp_greater_eq(epsx,0), "MinCGSetCond: negative EpsX!", _state);
    ae_assert(maxits>=0, "MinCGSetCond: negative MaxIts!", _state);
    if( ((ae_fp_eq(epsg,0)&&ae_fp_eq(epsf,0))&&ae_fp_eq(epsx,0))&&maxits==0 )
    {
        epsx = 1.0E-6;
    }
    state->epsg = epsg;
    state->epsf = epsf;
    state->epsx = epsx;
    state->maxits = maxits;
}


/*************************************************************************
This function turns on/off reporting.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    NeedXRep-   whether iteration reports are needed or not

If NeedXRep is True, algorithm will call rep() callback function if  it is
provided to MinCGOptimize().

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void mincgsetxrep(mincgstate* state, ae_bool needxrep, ae_state *_state)
{


    state->xrep = needxrep;
}


/*************************************************************************
This function sets CG algorithm.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    CGType  -   algorithm type:
                * -1    automatic selection of the best algorithm
                * 0     DY (Dai and Yuan) algorithm
                * 1     Hybrid DY-HS algorithm

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void mincgsetcgtype(mincgstate* state, ae_int_t cgtype, ae_state *_state)
{


    ae_assert(cgtype>=-1&&cgtype<=1, "MinCGSetCGType: incorrect CGType!", _state);
    if( cgtype==-1 )
    {
        cgtype = 1;
    }
    state->cgtype = cgtype;
}


/*************************************************************************
This function sets maximum step length

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    StpMax  -   maximum step length, >=0. Set StpMax to 0.0,  if you don't
                want to limit step length.

Use this subroutine when you optimize target function which contains exp()
or  other  fast  growing  functions,  and optimization algorithm makes too
large  steps  which  leads  to overflow. This function allows us to reject
steps  that  are  too  large  (and  therefore  expose  us  to the possible
overflow) without actually calculating function value at the x+stp*d.

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void mincgsetstpmax(mincgstate* state, double stpmax, ae_state *_state)
{


    ae_assert(ae_isfinite(stpmax, _state), "MinCGSetStpMax: StpMax is not finite!", _state);
    ae_assert(ae_fp_greater_eq(stpmax,0), "MinCGSetStpMax: StpMax<0!", _state);
    state->stpmax = stpmax;
}


/*************************************************************************

  -- ALGLIB --
     Copyright 20.04.2009 by Bochkanov Sergey
*************************************************************************/
ae_bool mincgiteration(mincgstate* state, ae_state *_state)
{
    ae_int_t n;
    ae_int_t i;
    double betak;
    double v;
    double vv;
    ae_int_t mcinfo;
    ae_bool result;


    
    /*
     * Reverse communication preparations
     * I know it looks ugly, but it works the same way
     * anywhere from C++ to Python.
     *
     * This code initializes locals by:
     * * random values determined during code
     *   generation - on first subroutine call
     * * values from previous call - on subsequent calls
     */
    if( state->rstate.stage>=0 )
    {
        n = state->rstate.ia.ptr.p_int[0];
        i = state->rstate.ia.ptr.p_int[1];
        mcinfo = state->rstate.ia.ptr.p_int[2];
        betak = state->rstate.ra.ptr.p_double[0];
        v = state->rstate.ra.ptr.p_double[1];
        vv = state->rstate.ra.ptr.p_double[2];
    }
    else
    {
        n = -983;
        i = -989;
        mcinfo = -834;
        betak = 900;
        v = -287;
        vv = 364;
    }
    if( state->rstate.stage==0 )
    {
        goto lbl_0;
    }
    if( state->rstate.stage==1 )
    {
        goto lbl_1;
    }
    if( state->rstate.stage==2 )
    {
        goto lbl_2;
    }
    if( state->rstate.stage==3 )
    {
        goto lbl_3;
    }
    
    /*
     * Routine body
     */
    
    /*
     * Prepare
     */
    n = state->n;
    state->repterminationtype = 0;
    state->repiterationscount = 0;
    state->repnfev = 0;
    state->debugrestartscount = 0;
    
    /*
     * Calculate F/G, initialize algorithm
     */
    mincg_clearrequestfields(state, _state);
    state->needfg = ae_true;
    state->rstate.stage = 0;
    goto lbl_rcomm;
lbl_0:
    state->needfg = ae_false;
    if( !state->xrep )
    {
        goto lbl_4;
    }
    mincg_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 1;
    goto lbl_rcomm;
lbl_1:
    state->xupdated = ae_false;
lbl_4:
    v = ae_v_dotproduct(&state->g.ptr.p_double[0], 1, &state->g.ptr.p_double[0], 1, ae_v_len(0,n-1));
    v = ae_sqrt(v, _state);
    if( ae_fp_eq(v,0) )
    {
        state->repterminationtype = 4;
        result = ae_false;
        return result;
    }
    state->repnfev = 1;
    state->k = 0;
    state->fold = state->f;
    ae_v_move(&state->xk.ptr.p_double[0], 1, &state->x.ptr.p_double[0], 1, ae_v_len(0,n-1));
    ae_v_moveneg(&state->dk.ptr.p_double[0], 1, &state->g.ptr.p_double[0], 1, ae_v_len(0,n-1));
    
    /*
     * Main cycle
     */
lbl_6:
    if( ae_false )
    {
        goto lbl_7;
    }
    
    /*
     * Store G[k] for later calculation of Y[k]
     */
    ae_v_moveneg(&state->yk.ptr.p_double[0], 1, &state->g.ptr.p_double[0], 1, ae_v_len(0,n-1));
    
    /*
     * Calculate X(k+1): minimize F(x+alpha*d)
     */
    ae_v_move(&state->d.ptr.p_double[0], 1, &state->dk.ptr.p_double[0], 1, ae_v_len(0,n-1));
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->xk.ptr.p_double[0], 1, ae_v_len(0,n-1));
    state->mcstage = 0;
    state->stp = 1.0;
    linminnormalized(&state->d, &state->stp, n, _state);
    if( ae_fp_neq(state->laststep,0) )
    {
        state->stp = state->laststep;
    }
    mcsrch(n, &state->x, &state->f, &state->g, &state->d, &state->stp, state->stpmax, &mcinfo, &state->nfev, &state->work, &state->lstate, &state->mcstage, _state);
lbl_8:
    if( state->mcstage==0 )
    {
        goto lbl_9;
    }
    mincg_clearrequestfields(state, _state);
    state->needfg = ae_true;
    state->rstate.stage = 2;
    goto lbl_rcomm;
lbl_2:
    state->needfg = ae_false;
    mcsrch(n, &state->x, &state->f, &state->g, &state->d, &state->stp, state->stpmax, &mcinfo, &state->nfev, &state->work, &state->lstate, &state->mcstage, _state);
    goto lbl_8;
lbl_9:
    if( !state->xrep )
    {
        goto lbl_10;
    }
    mincg_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 3;
    goto lbl_rcomm;
lbl_3:
    state->xupdated = ae_false;
lbl_10:
    ae_v_move(&state->xn.ptr.p_double[0], 1, &state->x.ptr.p_double[0], 1, ae_v_len(0,n-1));
    if( mcinfo==1 )
    {
        
        /*
         * Standard Wolfe conditions hold
         * Calculate Y[K] and BetaK
         */
        ae_v_add(&state->yk.ptr.p_double[0], 1, &state->g.ptr.p_double[0], 1, ae_v_len(0,n-1));
        vv = ae_v_dotproduct(&state->yk.ptr.p_double[0], 1, &state->dk.ptr.p_double[0], 1, ae_v_len(0,n-1));
        v = ae_v_dotproduct(&state->g.ptr.p_double[0], 1, &state->g.ptr.p_double[0], 1, ae_v_len(0,n-1));
        state->betady = v/vv;
        v = ae_v_dotproduct(&state->g.ptr.p_double[0], 1, &state->yk.ptr.p_double[0], 1, ae_v_len(0,n-1));
        state->betahs = v/vv;
        if( state->cgtype==0 )
        {
            betak = state->betady;
        }
        if( state->cgtype==1 )
        {
            betak = ae_maxreal(0, ae_minreal(state->betady, state->betahs, _state), _state);
        }
    }
    else
    {
        
        /*
         * Something is wrong (may be function is too wild or too flat).
         *
         * We'll set BetaK=0, which will restart CG algorithm.
         * We can stop later (during normal checks) if stopping conditions are met.
         */
        betak = 0;
        state->debugrestartscount = state->debugrestartscount+1;
    }
    
    /*
     * Calculate D(k+1)
     */
    ae_v_moveneg(&state->dn.ptr.p_double[0], 1, &state->g.ptr.p_double[0], 1, ae_v_len(0,n-1));
    ae_v_addd(&state->dn.ptr.p_double[0], 1, &state->dk.ptr.p_double[0], 1, ae_v_len(0,n-1), betak);
    
    /*
     * Update info about step length
     */
    v = ae_v_dotproduct(&state->d.ptr.p_double[0], 1, &state->d.ptr.p_double[0], 1, ae_v_len(0,n-1));
    state->laststep = ae_sqrt(v, _state)*state->stp;
    
    /*
     * Update information and Hessian.
     * Check stopping conditions.
     */
    state->repnfev = state->repnfev+state->nfev;
    state->repiterationscount = state->repiterationscount+1;
    if( state->repiterationscount>=state->maxits&&state->maxits>0 )
    {
        
        /*
         * Too many iterations
         */
        state->repterminationtype = 5;
        result = ae_false;
        return result;
    }
    v = ae_v_dotproduct(&state->g.ptr.p_double[0], 1, &state->g.ptr.p_double[0], 1, ae_v_len(0,n-1));
    if( ae_fp_less_eq(ae_sqrt(v, _state),state->epsg) )
    {
        
        /*
         * Gradient is small enough
         */
        state->repterminationtype = 4;
        result = ae_false;
        return result;
    }
    if( ae_fp_less_eq(state->fold-state->f,state->epsf*ae_maxreal(ae_fabs(state->fold, _state), ae_maxreal(ae_fabs(state->f, _state), 1.0, _state), _state)) )
    {
        
        /*
         * F(k+1)-F(k) is small enough
         */
        state->repterminationtype = 1;
        result = ae_false;
        return result;
    }
    if( ae_fp_less_eq(state->laststep,state->epsx) )
    {
        
        /*
         * X(k+1)-X(k) is small enough
         */
        state->repterminationtype = 2;
        result = ae_false;
        return result;
    }
    
    /*
     * Shift Xk/Dk, update other information
     */
    ae_v_move(&state->xk.ptr.p_double[0], 1, &state->xn.ptr.p_double[0], 1, ae_v_len(0,n-1));
    ae_v_move(&state->dk.ptr.p_double[0], 1, &state->dn.ptr.p_double[0], 1, ae_v_len(0,n-1));
    state->fold = state->f;
    state->k = state->k+1;
    goto lbl_6;
lbl_7:
    result = ae_false;
    return result;
    
    /*
     * Saving state
     */
lbl_rcomm:
    result = ae_true;
    state->rstate.ia.ptr.p_int[0] = n;
    state->rstate.ia.ptr.p_int[1] = i;
    state->rstate.ia.ptr.p_int[2] = mcinfo;
    state->rstate.ra.ptr.p_double[0] = betak;
    state->rstate.ra.ptr.p_double[1] = v;
    state->rstate.ra.ptr.p_double[2] = vv;
    return result;
}


/*************************************************************************
Conjugate gradient results

INPUT PARAMETERS:
    State   -   algorithm state

OUTPUT PARAMETERS:
    X       -   array[0..N-1], solution
    Rep     -   optimization report:
                * Rep.TerminationType completetion code:
                    * -2    rounding errors prevent further improvement.
                            X contains best point found.
                    * -1    incorrect parameters were specified
                    *  1    relative function improvement is no more than
                            EpsF.
                    *  2    relative step is no more than EpsX.
                    *  4    gradient norm is no more than EpsG
                    *  5    MaxIts steps was taken
                    *  7    stopping conditions are too stringent,
                            further improvement is impossible
                * Rep.IterationsCount contains iterations count
                * NFEV countains number of function calculations

  -- ALGLIB --
     Copyright 20.04.2009 by Bochkanov Sergey
*************************************************************************/
void mincgresults(mincgstate* state,
     /* Real    */ ae_vector* x,
     mincgreport* rep,
     ae_state *_state)
{

    ae_vector_clear(x);
    _mincgreport_clear(rep);

    mincgresultsbuf(state, x, rep, _state);
}


/*************************************************************************
Conjugate gradient results

Buffered implementation of MinCGResults(), which uses pre-allocated buffer
to store X[]. If buffer size is  too  small,  it  resizes  buffer.  It  is
intended to be used in the inner cycles of performance critical algorithms
where array reallocation penalty is too large to be ignored.

  -- ALGLIB --
     Copyright 20.04.2009 by Bochkanov Sergey
*************************************************************************/
void mincgresultsbuf(mincgstate* state,
     /* Real    */ ae_vector* x,
     mincgreport* rep,
     ae_state *_state)
{


    if( x->cnt<state->n )
    {
        ae_vector_set_length(x, state->n, _state);
    }
    ae_v_move(&x->ptr.p_double[0], 1, &state->xn.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    rep->iterationscount = state->repiterationscount;
    rep->nfev = state->repnfev;
    rep->terminationtype = state->repterminationtype;
}


/*************************************************************************
This  subroutine  restarts  CG  algorithm from new point. All optimization
parameters are left unchanged.

This  function  allows  to  solve multiple  optimization  problems  (which
must have same number of dimensions) without object reallocation penalty.

INPUT PARAMETERS:
    State   -   structure used to store algorithm state.
    X       -   new starting point.

  -- ALGLIB --
     Copyright 30.07.2010 by Bochkanov Sergey
*************************************************************************/
void mincgrestartfrom(mincgstate* state,
     /* Real    */ ae_vector* x,
     ae_state *_state)
{


    ae_assert(x->cnt>=state->n, "MinCGRestartFrom: Length(X)<N!", _state);
    ae_assert(isfinitevector(x, state->n, _state), "MinCGCreate: X contains infinite or NaN values!", _state);
    ae_v_move(&state->x.ptr.p_double[0], 1, &x->ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    state->laststep = 0;
    ae_vector_set_length(&state->rstate.ia, 2+1, _state);
    ae_vector_set_length(&state->rstate.ra, 2+1, _state);
    state->rstate.stage = -1;
    mincg_clearrequestfields(state, _state);
}


/*************************************************************************
Clears request fileds (to be sure that we don't forgot to clear something)
*************************************************************************/
static void mincg_clearrequestfields(mincgstate* state, ae_state *_state)
{


    state->needfg = ae_false;
    state->xupdated = ae_false;
}


ae_bool _mincgstate_init(mincgstate* p, ae_state *_state, ae_bool make_automatic)
{
    if( !ae_vector_init(&p->xk, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->dk, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->xn, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->dn, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->d, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->work, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->yk, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->x, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->g, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !_rcommstate_init(&p->rstate, _state, make_automatic) )
        return ae_false;
    if( !_linminstate_init(&p->lstate, _state, make_automatic) )
        return ae_false;
    return ae_true;
}


ae_bool _mincgstate_init_copy(mincgstate* dst, mincgstate* src, ae_state *_state, ae_bool make_automatic)
{
    dst->n = src->n;
    dst->epsg = src->epsg;
    dst->epsf = src->epsf;
    dst->epsx = src->epsx;
    dst->maxits = src->maxits;
    dst->stpmax = src->stpmax;
    dst->xrep = src->xrep;
    dst->cgtype = src->cgtype;
    dst->nfev = src->nfev;
    dst->mcstage = src->mcstage;
    dst->k = src->k;
    if( !ae_vector_init_copy(&dst->xk, &src->xk, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->dk, &src->dk, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->xn, &src->xn, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->dn, &src->dn, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->d, &src->d, _state, make_automatic) )
        return ae_false;
    dst->fold = src->fold;
    dst->stp = src->stp;
    if( !ae_vector_init_copy(&dst->work, &src->work, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->yk, &src->yk, _state, make_automatic) )
        return ae_false;
    dst->laststep = src->laststep;
    if( !ae_vector_init_copy(&dst->x, &src->x, _state, make_automatic) )
        return ae_false;
    dst->f = src->f;
    if( !ae_vector_init_copy(&dst->g, &src->g, _state, make_automatic) )
        return ae_false;
    dst->needfg = src->needfg;
    dst->xupdated = src->xupdated;
    if( !_rcommstate_init_copy(&dst->rstate, &src->rstate, _state, make_automatic) )
        return ae_false;
    dst->repiterationscount = src->repiterationscount;
    dst->repnfev = src->repnfev;
    dst->repterminationtype = src->repterminationtype;
    dst->debugrestartscount = src->debugrestartscount;
    if( !_linminstate_init_copy(&dst->lstate, &src->lstate, _state, make_automatic) )
        return ae_false;
    dst->betahs = src->betahs;
    dst->betady = src->betady;
    return ae_true;
}


void _mincgstate_clear(mincgstate* p)
{
    ae_vector_clear(&p->xk);
    ae_vector_clear(&p->dk);
    ae_vector_clear(&p->xn);
    ae_vector_clear(&p->dn);
    ae_vector_clear(&p->d);
    ae_vector_clear(&p->work);
    ae_vector_clear(&p->yk);
    ae_vector_clear(&p->x);
    ae_vector_clear(&p->g);
    _rcommstate_clear(&p->rstate);
    _linminstate_clear(&p->lstate);
}


ae_bool _mincgreport_init(mincgreport* p, ae_state *_state, ae_bool make_automatic)
{
    return ae_true;
}


ae_bool _mincgreport_init_copy(mincgreport* dst, mincgreport* src, ae_state *_state, ae_bool make_automatic)
{
    dst->iterationscount = src->iterationscount;
    dst->nfev = src->nfev;
    dst->terminationtype = src->terminationtype;
    return ae_true;
}


void _mincgreport_clear(mincgreport* p)
{
}




/*************************************************************************
              NONLINEAR BOUND CONSTRAINED OPTIMIZATION USING
                      MODIFIED ACTIVE SET ALGORITHM
                   WILLIAM W. HAGER AND HONGCHAO ZHANG

DESCRIPTION:
The  subroutine  minimizes  function  F(x)  of  N  arguments  with   bound
constraints: BndL[i] <= x[i] <= BndU[i]

This method is  globally  convergent  as  long  as  grad(f)  is  Lipschitz
continuous on a level set: L = { x : f(x)<=f(x0) }.


REQUIREMENTS:
Algorithm will request following information during its operation:
* function value F and its gradient G (simultaneously) at given point X


USAGE:
1. User initializes algorithm state with MinASACreate() call
2. User tunes solver parameters with MinASASetCond() MinASASetStpMax() and
   other functions
3. User calls MinASAOptimize() function which takes algorithm  state   and
   pointer (delegate, etc.) to callback function which calculates F/G.
4. User calls MinASAResults() to get solution
5. Optionally, user may call MinASARestartFrom() to solve another  problem
   with same N but another starting point and/or another function.
   MinASARestartFrom() allows to reuse already initialized structure.


INPUT PARAMETERS:
    N       -   problem dimension, N>0:
                * if given, only leading N elements of X are used
                * if not given, automatically determined from sizes of
                  X/BndL/BndU.
    X       -   starting point, array[0..N-1].
    BndL    -   lower bounds, array[0..N-1].
                all elements MUST be specified,  i.e.  all  variables  are
                bounded. However, if some (all) variables  are  unbounded,
                you may specify very small number as bound: -1000,  -1.0E6
                or -1.0E300, or something like that.
    BndU    -   upper bounds, array[0..N-1].
                all elements MUST be specified,  i.e.  all  variables  are
                bounded. However, if some (all) variables  are  unbounded,
                you may specify very large number as bound: +1000,  +1.0E6
                or +1.0E300, or something like that.

OUTPUT PARAMETERS:
    State   -   structure stores algorithm state

NOTES:

1. you may tune stopping conditions with MinASASetCond() function
2. if target function contains exp() or other fast growing functions,  and
   optimization algorithm makes too large steps which leads  to  overflow,
   use MinASASetStpMax() function to bound algorithm's steps.
3. this function does NOT support infinite/NaN values in X, BndL, BndU.

  -- ALGLIB --
     Copyright 25.03.2010 by Bochkanov Sergey
*************************************************************************/
void minasacreate(ae_int_t n,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* bndl,
     /* Real    */ ae_vector* bndu,
     minasastate* state,
     ae_state *_state)
{
    ae_int_t i;

    _minasastate_clear(state);

    ae_assert(n>=1, "MinASA: N too small!", _state);
    ae_assert(x->cnt>=n, "MinCGCreate: Length(X)<N!", _state);
    ae_assert(isfinitevector(x, n, _state), "MinCGCreate: X contains infinite or NaN values!", _state);
    ae_assert(bndl->cnt>=n, "MinCGCreate: Length(BndL)<N!", _state);
    ae_assert(isfinitevector(bndl, n, _state), "MinCGCreate: BndL contains infinite or NaN values!", _state);
    ae_assert(bndu->cnt>=n, "MinCGCreate: Length(BndU)<N!", _state);
    ae_assert(isfinitevector(bndu, n, _state), "MinCGCreate: BndU contains infinite or NaN values!", _state);
    for(i=0; i<=n-1; i++)
    {
        ae_assert(ae_fp_less_eq(bndl->ptr.p_double[i],bndu->ptr.p_double[i]), "MinASA: inconsistent bounds!", _state);
        ae_assert(ae_fp_less_eq(bndl->ptr.p_double[i],x->ptr.p_double[i]), "MinASA: infeasible X!", _state);
        ae_assert(ae_fp_less_eq(x->ptr.p_double[i],bndu->ptr.p_double[i]), "MinASA: infeasible X!", _state);
    }
    
    /*
     * Initialize
     */
    state->n = n;
    minasasetcond(state, 0, 0, 0, 0, _state);
    minasasetxrep(state, ae_false, _state);
    minasasetstpmax(state, 0, _state);
    minasasetalgorithm(state, -1, _state);
    ae_vector_set_length(&state->bndl, n, _state);
    ae_vector_set_length(&state->bndu, n, _state);
    ae_vector_set_length(&state->ak, n, _state);
    ae_vector_set_length(&state->xk, n, _state);
    ae_vector_set_length(&state->dk, n, _state);
    ae_vector_set_length(&state->an, n, _state);
    ae_vector_set_length(&state->xn, n, _state);
    ae_vector_set_length(&state->dn, n, _state);
    ae_vector_set_length(&state->x, n, _state);
    ae_vector_set_length(&state->d, n, _state);
    ae_vector_set_length(&state->g, n, _state);
    ae_vector_set_length(&state->gc, n, _state);
    ae_vector_set_length(&state->work, n, _state);
    ae_vector_set_length(&state->yk, n, _state);
    minasarestartfrom(state, x, bndl, bndu, _state);
}


/*************************************************************************
This function sets stopping conditions for the ASA optimization algorithm.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    EpsG    -   >=0
                The  subroutine  finishes  its  work   if   the  condition
                ||G||<EpsG is satisfied, where ||.|| means Euclidian norm,
                G - gradient.
    EpsF    -   >=0
                The  subroutine  finishes  its work if on k+1-th iteration
                the  condition  |F(k+1)-F(k)|<=EpsF*max{|F(k)|,|F(k+1)|,1}
                is satisfied.
    EpsX    -   >=0
                The subroutine finishes its work if  on  k+1-th  iteration
                the condition |X(k+1)-X(k)| <= EpsX is fulfilled.
    MaxIts  -   maximum number of iterations. If MaxIts=0, the  number  of
                iterations is unlimited.

Passing EpsG=0, EpsF=0, EpsX=0 and MaxIts=0 (simultaneously) will lead to
automatic stopping criterion selection (small EpsX).

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minasasetcond(minasastate* state,
     double epsg,
     double epsf,
     double epsx,
     ae_int_t maxits,
     ae_state *_state)
{


    ae_assert(ae_isfinite(epsg, _state), "MinASASetCond: EpsG is not finite number!", _state);
    ae_assert(ae_fp_greater_eq(epsg,0), "MinASASetCond: negative EpsG!", _state);
    ae_assert(ae_isfinite(epsf, _state), "MinASASetCond: EpsF is not finite number!", _state);
    ae_assert(ae_fp_greater_eq(epsf,0), "MinASASetCond: negative EpsF!", _state);
    ae_assert(ae_isfinite(epsx, _state), "MinASASetCond: EpsX is not finite number!", _state);
    ae_assert(ae_fp_greater_eq(epsx,0), "MinASASetCond: negative EpsX!", _state);
    ae_assert(maxits>=0, "MinASASetCond: negative MaxIts!", _state);
    if( ((ae_fp_eq(epsg,0)&&ae_fp_eq(epsf,0))&&ae_fp_eq(epsx,0))&&maxits==0 )
    {
        epsx = 1.0E-6;
    }
    state->epsg = epsg;
    state->epsf = epsf;
    state->epsx = epsx;
    state->maxits = maxits;
}


/*************************************************************************
This function turns on/off reporting.

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    NeedXRep-   whether iteration reports are needed or not

If NeedXRep is True, algorithm will call rep() callback function if  it is
provided to MinASAOptimize().

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minasasetxrep(minasastate* state, ae_bool needxrep, ae_state *_state)
{


    state->xrep = needxrep;
}


/*************************************************************************
This function sets optimization algorithm.

INPUT PARAMETERS:
    State   -   structure which stores algorithm stat
    UAType  -   algorithm type:
                * -1    automatic selection of the best algorithm
                * 0     DY (Dai and Yuan) algorithm
                * 1     Hybrid DY-HS algorithm

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minasasetalgorithm(minasastate* state,
     ae_int_t algotype,
     ae_state *_state)
{


    ae_assert(algotype>=-1&&algotype<=1, "MinASASetAlgorithm: incorrect AlgoType!", _state);
    if( algotype==-1 )
    {
        algotype = 1;
    }
    state->cgtype = algotype;
}


/*************************************************************************
This function sets maximum step length

INPUT PARAMETERS:
    State   -   structure which stores algorithm state
    StpMax  -   maximum step length, >=0. Set StpMax to 0.0,  if you don't
                want to limit step length (zero by default).

Use this subroutine when you optimize target function which contains exp()
or  other  fast  growing  functions,  and optimization algorithm makes too
large  steps  which  leads  to overflow. This function allows us to reject
steps  that  are  too  large  (and  therefore  expose  us  to the possible
overflow) without actually calculating function value at the x+stp*d.

  -- ALGLIB --
     Copyright 02.04.2010 by Bochkanov Sergey
*************************************************************************/
void minasasetstpmax(minasastate* state, double stpmax, ae_state *_state)
{


    ae_assert(ae_isfinite(stpmax, _state), "MinASASetStpMax: StpMax is not finite!", _state);
    ae_assert(ae_fp_greater_eq(stpmax,0), "MinASASetStpMax: StpMax<0!", _state);
    state->stpmax = stpmax;
}


/*************************************************************************

  -- ALGLIB --
     Copyright 20.03.2009 by Bochkanov Sergey
*************************************************************************/
ae_bool minasaiteration(minasastate* state, ae_state *_state)
{
    ae_int_t n;
    ae_int_t i;
    double betak;
    double v;
    double vv;
    ae_int_t mcinfo;
    ae_bool b;
    ae_bool stepfound;
    ae_int_t diffcnt;
    ae_bool result;


    
    /*
     * Reverse communication preparations
     * I know it looks ugly, but it works the same way
     * anywhere from C++ to Python.
     *
     * This code initializes locals by:
     * * random values determined during code
     *   generation - on first subroutine call
     * * values from previous call - on subsequent calls
     */
    if( state->rstate.stage>=0 )
    {
        n = state->rstate.ia.ptr.p_int[0];
        i = state->rstate.ia.ptr.p_int[1];
        mcinfo = state->rstate.ia.ptr.p_int[2];
        diffcnt = state->rstate.ia.ptr.p_int[3];
        b = state->rstate.ba.ptr.p_bool[0];
        stepfound = state->rstate.ba.ptr.p_bool[1];
        betak = state->rstate.ra.ptr.p_double[0];
        v = state->rstate.ra.ptr.p_double[1];
        vv = state->rstate.ra.ptr.p_double[2];
    }
    else
    {
        n = -983;
        i = -989;
        mcinfo = -834;
        diffcnt = 900;
        b = ae_true;
        stepfound = ae_false;
        betak = 214;
        v = -338;
        vv = -686;
    }
    if( state->rstate.stage==0 )
    {
        goto lbl_0;
    }
    if( state->rstate.stage==1 )
    {
        goto lbl_1;
    }
    if( state->rstate.stage==2 )
    {
        goto lbl_2;
    }
    if( state->rstate.stage==3 )
    {
        goto lbl_3;
    }
    if( state->rstate.stage==4 )
    {
        goto lbl_4;
    }
    if( state->rstate.stage==5 )
    {
        goto lbl_5;
    }
    if( state->rstate.stage==6 )
    {
        goto lbl_6;
    }
    if( state->rstate.stage==7 )
    {
        goto lbl_7;
    }
    if( state->rstate.stage==8 )
    {
        goto lbl_8;
    }
    if( state->rstate.stage==9 )
    {
        goto lbl_9;
    }
    if( state->rstate.stage==10 )
    {
        goto lbl_10;
    }
    if( state->rstate.stage==11 )
    {
        goto lbl_11;
    }
    if( state->rstate.stage==12 )
    {
        goto lbl_12;
    }
    if( state->rstate.stage==13 )
    {
        goto lbl_13;
    }
    if( state->rstate.stage==14 )
    {
        goto lbl_14;
    }
    
    /*
     * Routine body
     */
    
    /*
     * Prepare
     */
    n = state->n;
    state->repterminationtype = 0;
    state->repiterationscount = 0;
    state->repnfev = 0;
    state->debugrestartscount = 0;
    state->cgtype = 1;
    ae_v_move(&state->xk.ptr.p_double[0], 1, &state->x.ptr.p_double[0], 1, ae_v_len(0,n-1));
    for(i=0; i<=n-1; i++)
    {
        if( ae_fp_eq(state->xk.ptr.p_double[i],state->bndl.ptr.p_double[i])||ae_fp_eq(state->xk.ptr.p_double[i],state->bndu.ptr.p_double[i]) )
        {
            state->ak.ptr.p_double[i] = 0;
        }
        else
        {
            state->ak.ptr.p_double[i] = 1;
        }
    }
    state->mu = 0.1;
    state->curalgo = 0;
    
    /*
     * Calculate F/G, initialize algorithm
     */
    minasa_clearrequestfields(state, _state);
    state->needfg = ae_true;
    state->rstate.stage = 0;
    goto lbl_rcomm;
lbl_0:
    state->needfg = ae_false;
    if( !state->xrep )
    {
        goto lbl_15;
    }
    
    /*
     * progress report
     */
    minasa_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 1;
    goto lbl_rcomm;
lbl_1:
    state->xupdated = ae_false;
lbl_15:
    if( ae_fp_less_eq(minasa_asaboundedantigradnorm(state, _state),state->epsg) )
    {
        state->repterminationtype = 4;
        result = ae_false;
        return result;
    }
    state->repnfev = state->repnfev+1;
    
    /*
     * Main cycle
     *
     * At the beginning of new iteration:
     * * CurAlgo stores current algorithm selector
     * * State.XK, State.F and State.G store current X/F/G
     * * State.AK stores current set of active constraints
     */
lbl_17:
    if( ae_false )
    {
        goto lbl_18;
    }
    
    /*
     * GPA algorithm
     */
    if( state->curalgo!=0 )
    {
        goto lbl_19;
    }
    state->k = 0;
    state->acount = 0;
lbl_21:
    if( ae_false )
    {
        goto lbl_22;
    }
    
    /*
     * Determine Dk = proj(xk - gk)-xk
     */
    for(i=0; i<=n-1; i++)
    {
        state->d.ptr.p_double[i] = boundval(state->xk.ptr.p_double[i]-state->g.ptr.p_double[i], state->bndl.ptr.p_double[i], state->bndu.ptr.p_double[i], _state)-state->xk.ptr.p_double[i];
    }
    
    /*
     * Armijo line search.
     * * exact search with alpha=1 is tried first,
     *   'exact' means that we evaluate f() EXACTLY at
     *   bound(x-g,bndl,bndu), without intermediate floating
     *   point operations.
     * * alpha<1 are tried if explicit search wasn't successful
     * Result is placed into XN.
     *
     * Two types of search are needed because we can't
     * just use second type with alpha=1 because in finite
     * precision arithmetics (x1-x0)+x0 may differ from x1.
     * So while x1 is correctly bounded (it lie EXACTLY on
     * boundary, if it is active), (x1-x0)+x0 may be
     * not bounded.
     */
    v = ae_v_dotproduct(&state->d.ptr.p_double[0], 1, &state->g.ptr.p_double[0], 1, ae_v_len(0,n-1));
    state->dginit = v;
    state->finit = state->f;
    if( !(ae_fp_less_eq(minasa_asad1norm(state, _state),state->stpmax)||ae_fp_eq(state->stpmax,0)) )
    {
        goto lbl_23;
    }
    
    /*
     * Try alpha=1 step first
     */
    for(i=0; i<=n-1; i++)
    {
        state->x.ptr.p_double[i] = boundval(state->xk.ptr.p_double[i]-state->g.ptr.p_double[i], state->bndl.ptr.p_double[i], state->bndu.ptr.p_double[i], _state);
    }
    minasa_clearrequestfields(state, _state);
    state->needfg = ae_true;
    state->rstate.stage = 2;
    goto lbl_rcomm;
lbl_2:
    state->needfg = ae_false;
    state->repnfev = state->repnfev+1;
    stepfound = ae_fp_less_eq(state->f,state->finit+minasa_gpaftol*state->dginit);
    goto lbl_24;
lbl_23:
    stepfound = ae_false;
lbl_24:
    if( !stepfound )
    {
        goto lbl_25;
    }
    
    /*
     * we are at the boundary(ies)
     */
    ae_v_move(&state->xn.ptr.p_double[0], 1, &state->x.ptr.p_double[0], 1, ae_v_len(0,n-1));
    state->stp = 1;
    goto lbl_26;
lbl_25:
    
    /*
     * alpha=1 is too large, try smaller values
     */
    state->stp = 1;
    linminnormalized(&state->d, &state->stp, n, _state);
    state->dginit = state->dginit/state->stp;
    state->stp = minasa_gpadecay*state->stp;
    if( ae_fp_greater(state->stpmax,0) )
    {
        state->stp = ae_minreal(state->stp, state->stpmax, _state);
    }
lbl_27:
    if( ae_false )
    {
        goto lbl_28;
    }
    v = state->stp;
    ae_v_move(&state->x.ptr.p_double[0], 1, &state->xk.ptr.p_double[0], 1, ae_v_len(0,n-1));
    ae_v_addd(&state->x.ptr.p_double[0], 1, &state->d.ptr.p_double[0], 1, ae_v_len(0,n-1), v);
    minasa_clearrequestfields(state, _state);
    state->needfg = ae_true;
    state->rstate.stage = 3;
    goto lbl_rcomm;
lbl_3:
    state->needfg = ae_false;
    state->repnfev = state->repnfev+1;
    if( ae_fp_less_eq(state->stp,minasa_stpmin) )
    {
        goto lbl_28;
    }
    if( ae_fp_less_eq(state->f,state->finit+state->stp*minasa_gpaftol*state->dginit) )
    {
        goto lbl_28;
    }
    state->stp = state->stp*minasa_gpadecay;
    goto lbl_27;
lbl_28:
    ae_v_move(&state->xn.ptr.p_double[0], 1, &state->x.ptr.p_double[0], 1, ae_v_len(0,n-1));
lbl_26:
    state->repiterationscount = state->repiterationscount+1;
    if( !state->xrep )
    {
        goto lbl_29;
    }
    
    /*
     * progress report
     */
    minasa_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 4;
    goto lbl_rcomm;
lbl_4:
    state->xupdated = ae_false;
lbl_29:
    
    /*
     * Calculate new set of active constraints.
     * Reset counter if active set was changed.
     * Prepare for the new iteration
     */
    for(i=0; i<=n-1; i++)
    {
        if( ae_fp_eq(state->xn.ptr.p_double[i],state->bndl.ptr.p_double[i])||ae_fp_eq(state->xn.ptr.p_double[i],state->bndu.ptr.p_double[i]) )
        {
            state->an.ptr.p_double[i] = 0;
        }
        else
        {
            state->an.ptr.p_double[i] = 1;
        }
    }
    for(i=0; i<=n-1; i++)
    {
        if( ae_fp_neq(state->ak.ptr.p_double[i],state->an.ptr.p_double[i]) )
        {
            state->acount = -1;
            break;
        }
    }
    state->acount = state->acount+1;
    ae_v_move(&state->xk.ptr.p_double[0], 1, &state->xn.ptr.p_double[0], 1, ae_v_len(0,n-1));
    ae_v_move(&state->ak.ptr.p_double[0], 1, &state->an.ptr.p_double[0], 1, ae_v_len(0,n-1));
    
    /*
     * Stopping conditions
     */
    if( !(state->repiterationscount>=state->maxits&&state->maxits>0) )
    {
        goto lbl_31;
    }
    
    /*
     * Too many iterations
     */
    state->repterminationtype = 5;
    if( !state->xrep )
    {
        goto lbl_33;
    }
    minasa_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 5;
    goto lbl_rcomm;
lbl_5:
    state->xupdated = ae_false;
lbl_33:
    result = ae_false;
    return result;
lbl_31:
    if( ae_fp_greater(minasa_asaboundedantigradnorm(state, _state),state->epsg) )
    {
        goto lbl_35;
    }
    
    /*
     * Gradient is small enough
     */
    state->repterminationtype = 4;
    if( !state->xrep )
    {
        goto lbl_37;
    }
    minasa_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 6;
    goto lbl_rcomm;
lbl_6:
    state->xupdated = ae_false;
lbl_37:
    result = ae_false;
    return result;
lbl_35:
    v = ae_v_dotproduct(&state->d.ptr.p_double[0], 1, &state->d.ptr.p_double[0], 1, ae_v_len(0,n-1));
    if( ae_fp_greater(ae_sqrt(v, _state)*state->stp,state->epsx) )
    {
        goto lbl_39;
    }
    
    /*
     * Step size is too small, no further improvement is
     * possible
     */
    state->repterminationtype = 2;
    if( !state->xrep )
    {
        goto lbl_41;
    }
    minasa_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 7;
    goto lbl_rcomm;
lbl_7:
    state->xupdated = ae_false;
lbl_41:
    result = ae_false;
    return result;
lbl_39:
    if( ae_fp_greater(state->finit-state->f,state->epsf*ae_maxreal(ae_fabs(state->finit, _state), ae_maxreal(ae_fabs(state->f, _state), 1.0, _state), _state)) )
    {
        goto lbl_43;
    }
    
    /*
     * F(k+1)-F(k) is small enough
     */
    state->repterminationtype = 1;
    if( !state->xrep )
    {
        goto lbl_45;
    }
    minasa_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 8;
    goto lbl_rcomm;
lbl_8:
    state->xupdated = ae_false;
lbl_45:
    result = ae_false;
    return result;
lbl_43:
    
    /*
     * Decide - should we switch algorithm or not
     */
    if( minasa_asauisempty(state, _state) )
    {
        if( ae_fp_greater_eq(minasa_asaginorm(state, _state),state->mu*minasa_asad1norm(state, _state)) )
        {
            state->curalgo = 1;
            goto lbl_22;
        }
        else
        {
            state->mu = state->mu*minasa_asarho;
        }
    }
    else
    {
        if( state->acount==minasa_n1 )
        {
            if( ae_fp_greater_eq(minasa_asaginorm(state, _state),state->mu*minasa_asad1norm(state, _state)) )
            {
                state->curalgo = 1;
                goto lbl_22;
            }
        }
    }
    
    /*
     * Next iteration
     */
    state->k = state->k+1;
    goto lbl_21;
lbl_22:
lbl_19:
    
    /*
     * CG algorithm
     */
    if( state->curalgo!=1 )
    {
        goto lbl_47;
    }
    
    /*
     * first, check that there are non-active constraints.
     * move to GPA algorithm, if all constraints are active
     */
    b = ae_true;
    for(i=0; i<=n-1; i++)
    {
        if( ae_fp_neq(state->ak.ptr.p_double[i],0) )
        {
            b = ae_false;
            break;
        }
    }
    if( b )
    {
        state->curalgo = 0;
        goto lbl_17;
    }
    
    /*
     * CG iterations
     */
    state->fold = state->f;
    ae_v_move(&state->xk.ptr.p_double[0], 1, &state->x.ptr.p_double[0], 1, ae_v_len(0,n-1));
    for(i=0; i<=n-1; i++)
    {
        state->dk.ptr.p_double[i] = -state->g.ptr.p_double[i]*state->ak.ptr.p_double[i];
        state->gc.ptr.p_double[i] = state->g.ptr.p_double[i]*state->ak.ptr.p_double[i];
    }
lbl_49:
    if( ae_false )
    {
        goto lbl_50;
    }
    
    /*
     * Store G[k] for later calculation of Y[k]
     */
    for(i=0; i<=n-1; i++)
    {
        state->yk.ptr.p_double[i] = -state->gc.ptr.p_double[i];
    }
    
    /*
     * Make a CG step in direction given by DK[]:
     * * calculate step. Step projection into feasible set
     *   is used. It has several benefits: a) step may be
     *   found with usual line search, b) multiple constraints
     *   may be activated with one step, c) activated constraints
     *   are detected in a natural way - just compare x[i] with
     *   bounds
     * * update active set, set B to True, if there
     *   were changes in the set.
     */
    ae_v_move(&state->d.ptr.p_double[0], 1, &state->dk.ptr.p_double[0], 1, ae_v_len(0,n-1));
    ae_v_move(&state->xn.ptr.p_double[0], 1, &state->xk.ptr.p_double[0], 1, ae_v_len(0,n-1));
    state->mcstage = 0;
    state->stp = 1;
    linminnormalized(&state->d, &state->stp, n, _state);
    if( ae_fp_neq(state->laststep,0) )
    {
        state->stp = state->laststep;
    }
    mcsrch(n, &state->xn, &state->f, &state->gc, &state->d, &state->stp, state->stpmax, &mcinfo, &state->nfev, &state->work, &state->lstate, &state->mcstage, _state);
lbl_51:
    if( state->mcstage==0 )
    {
        goto lbl_52;
    }
    
    /*
     * preprocess data: bound State.XN so it belongs to the
     * feasible set and store it in the State.X
     */
    for(i=0; i<=n-1; i++)
    {
        state->x.ptr.p_double[i] = boundval(state->xn.ptr.p_double[i], state->bndl.ptr.p_double[i], state->bndu.ptr.p_double[i], _state);
    }
    
    /*
     * RComm
     */
    minasa_clearrequestfields(state, _state);
    state->needfg = ae_true;
    state->rstate.stage = 9;
    goto lbl_rcomm;
lbl_9:
    state->needfg = ae_false;
    
    /*
     * postprocess data: zero components of G corresponding to
     * the active constraints
     */
    for(i=0; i<=n-1; i++)
    {
        if( ae_fp_eq(state->x.ptr.p_double[i],state->bndl.ptr.p_double[i])||ae_fp_eq(state->x.ptr.p_double[i],state->bndu.ptr.p_double[i]) )
        {
            state->gc.ptr.p_double[i] = 0;
        }
        else
        {
            state->gc.ptr.p_double[i] = state->g.ptr.p_double[i];
        }
    }
    mcsrch(n, &state->xn, &state->f, &state->gc, &state->d, &state->stp, state->stpmax, &mcinfo, &state->nfev, &state->work, &state->lstate, &state->mcstage, _state);
    goto lbl_51;
lbl_52:
    diffcnt = 0;
    for(i=0; i<=n-1; i++)
    {
        
        /*
         * XN contains unprojected result, project it,
         * save copy to X (will be used for progress reporting)
         */
        state->xn.ptr.p_double[i] = boundval(state->xn.ptr.p_double[i], state->bndl.ptr.p_double[i], state->bndu.ptr.p_double[i], _state);
        
        /*
         * update active set
         */
        if( ae_fp_eq(state->xn.ptr.p_double[i],state->bndl.ptr.p_double[i])||ae_fp_eq(state->xn.ptr.p_double[i],state->bndu.ptr.p_double[i]) )
        {
            state->an.ptr.p_double[i] = 0;
        }
        else
        {
            state->an.ptr.p_double[i] = 1;
        }
        if( ae_fp_neq(state->an.ptr.p_double[i],state->ak.ptr.p_double[i]) )
        {
            diffcnt = diffcnt+1;
        }
        state->ak.ptr.p_double[i] = state->an.ptr.p_double[i];
    }
    ae_v_move(&state->xk.ptr.p_double[0], 1, &state->xn.ptr.p_double[0], 1, ae_v_len(0,n-1));
    state->repnfev = state->repnfev+state->nfev;
    state->repiterationscount = state->repiterationscount+1;
    if( !state->xrep )
    {
        goto lbl_53;
    }
    
    /*
     * progress report
     */
    minasa_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 10;
    goto lbl_rcomm;
lbl_10:
    state->xupdated = ae_false;
lbl_53:
    
    /*
     * Update info about step length
     */
    v = ae_v_dotproduct(&state->d.ptr.p_double[0], 1, &state->d.ptr.p_double[0], 1, ae_v_len(0,n-1));
    state->laststep = ae_sqrt(v, _state)*state->stp;
    
    /*
     * Check stopping conditions.
     */
    if( ae_fp_greater(minasa_asaboundedantigradnorm(state, _state),state->epsg) )
    {
        goto lbl_55;
    }
    
    /*
     * Gradient is small enough
     */
    state->repterminationtype = 4;
    if( !state->xrep )
    {
        goto lbl_57;
    }
    minasa_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 11;
    goto lbl_rcomm;
lbl_11:
    state->xupdated = ae_false;
lbl_57:
    result = ae_false;
    return result;
lbl_55:
    if( !(state->repiterationscount>=state->maxits&&state->maxits>0) )
    {
        goto lbl_59;
    }
    
    /*
     * Too many iterations
     */
    state->repterminationtype = 5;
    if( !state->xrep )
    {
        goto lbl_61;
    }
    minasa_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 12;
    goto lbl_rcomm;
lbl_12:
    state->xupdated = ae_false;
lbl_61:
    result = ae_false;
    return result;
lbl_59:
    if( !(ae_fp_greater_eq(minasa_asaginorm(state, _state),state->mu*minasa_asad1norm(state, _state))&&diffcnt==0) )
    {
        goto lbl_63;
    }
    
    /*
     * These conditions (EpsF/EpsX) are explicitly or implicitly
     * related to the current step size and influenced
     * by changes in the active constraints.
     *
     * For these reasons they are checked only when we don't
     * want to 'unstick' at the end of the iteration and there
     * were no changes in the active set.
     *
     * NOTE: consition |G|>=Mu*|D1| must be exactly opposite
     * to the condition used to switch back to GPA. At least
     * one inequality must be strict, otherwise infinite cycle
     * may occur when |G|=Mu*|D1| (we DON'T test stopping
     * conditions and we DON'T switch to GPA, so we cycle
     * indefinitely).
     */
    if( ae_fp_greater(state->fold-state->f,state->epsf*ae_maxreal(ae_fabs(state->fold, _state), ae_maxreal(ae_fabs(state->f, _state), 1.0, _state), _state)) )
    {
        goto lbl_65;
    }
    
    /*
     * F(k+1)-F(k) is small enough
     */
    state->repterminationtype = 1;
    if( !state->xrep )
    {
        goto lbl_67;
    }
    minasa_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 13;
    goto lbl_rcomm;
lbl_13:
    state->xupdated = ae_false;
lbl_67:
    result = ae_false;
    return result;
lbl_65:
    if( ae_fp_greater(state->laststep,state->epsx) )
    {
        goto lbl_69;
    }
    
    /*
     * X(k+1)-X(k) is small enough
     */
    state->repterminationtype = 2;
    if( !state->xrep )
    {
        goto lbl_71;
    }
    minasa_clearrequestfields(state, _state);
    state->xupdated = ae_true;
    state->rstate.stage = 14;
    goto lbl_rcomm;
lbl_14:
    state->xupdated = ae_false;
lbl_71:
    result = ae_false;
    return result;
lbl_69:
lbl_63:
    
    /*
     * Check conditions for switching
     */
    if( ae_fp_less(minasa_asaginorm(state, _state),state->mu*minasa_asad1norm(state, _state)) )
    {
        state->curalgo = 0;
        goto lbl_50;
    }
    if( diffcnt>0 )
    {
        if( minasa_asauisempty(state, _state)||diffcnt>=minasa_n2 )
        {
            state->curalgo = 1;
        }
        else
        {
            state->curalgo = 0;
        }
        goto lbl_50;
    }
    
    /*
     * Calculate D(k+1)
     *
     * Line search may result in:
     * * maximum feasible step being taken (already processed)
     * * point satisfying Wolfe conditions
     * * some kind of error (CG is restarted by assigning 0.0 to Beta)
     */
    if( mcinfo==1 )
    {
        
        /*
         * Standard Wolfe conditions are satisfied:
         * * calculate Y[K] and BetaK
         */
        ae_v_add(&state->yk.ptr.p_double[0], 1, &state->gc.ptr.p_double[0], 1, ae_v_len(0,n-1));
        vv = ae_v_dotproduct(&state->yk.ptr.p_double[0], 1, &state->dk.ptr.p_double[0], 1, ae_v_len(0,n-1));
        v = ae_v_dotproduct(&state->gc.ptr.p_double[0], 1, &state->gc.ptr.p_double[0], 1, ae_v_len(0,n-1));
        state->betady = v/vv;
        v = ae_v_dotproduct(&state->gc.ptr.p_double[0], 1, &state->yk.ptr.p_double[0], 1, ae_v_len(0,n-1));
        state->betahs = v/vv;
        if( state->cgtype==0 )
        {
            betak = state->betady;
        }
        if( state->cgtype==1 )
        {
            betak = ae_maxreal(0, ae_minreal(state->betady, state->betahs, _state), _state);
        }
    }
    else
    {
        
        /*
         * Something is wrong (may be function is too wild or too flat).
         *
         * We'll set BetaK=0, which will restart CG algorithm.
         * We can stop later (during normal checks) if stopping conditions are met.
         */
        betak = 0;
        state->debugrestartscount = state->debugrestartscount+1;
    }
    ae_v_moveneg(&state->dn.ptr.p_double[0], 1, &state->gc.ptr.p_double[0], 1, ae_v_len(0,n-1));
    ae_v_addd(&state->dn.ptr.p_double[0], 1, &state->dk.ptr.p_double[0], 1, ae_v_len(0,n-1), betak);
    ae_v_move(&state->dk.ptr.p_double[0], 1, &state->dn.ptr.p_double[0], 1, ae_v_len(0,n-1));
    
    /*
     * update other information
     */
    state->fold = state->f;
    state->k = state->k+1;
    goto lbl_49;
lbl_50:
lbl_47:
    goto lbl_17;
lbl_18:
    result = ae_false;
    return result;
    
    /*
     * Saving state
     */
lbl_rcomm:
    result = ae_true;
    state->rstate.ia.ptr.p_int[0] = n;
    state->rstate.ia.ptr.p_int[1] = i;
    state->rstate.ia.ptr.p_int[2] = mcinfo;
    state->rstate.ia.ptr.p_int[3] = diffcnt;
    state->rstate.ba.ptr.p_bool[0] = b;
    state->rstate.ba.ptr.p_bool[1] = stepfound;
    state->rstate.ra.ptr.p_double[0] = betak;
    state->rstate.ra.ptr.p_double[1] = v;
    state->rstate.ra.ptr.p_double[2] = vv;
    return result;
}


/*************************************************************************
ASA results

INPUT PARAMETERS:
    State   -   algorithm state

OUTPUT PARAMETERS:
    X       -   array[0..N-1], solution
    Rep     -   optimization report:
                * Rep.TerminationType completetion code:
                    * -2    rounding errors prevent further improvement.
                            X contains best point found.
                    * -1    incorrect parameters were specified
                    *  1    relative function improvement is no more than
                            EpsF.
                    *  2    relative step is no more than EpsX.
                    *  4    gradient norm is no more than EpsG
                    *  5    MaxIts steps was taken
                    *  7    stopping conditions are too stringent,
                            further improvement is impossible
                * Rep.IterationsCount contains iterations count
                * NFEV countains number of function calculations
                * ActiveConstraints contains number of active constraints

  -- ALGLIB --
     Copyright 20.03.2009 by Bochkanov Sergey
*************************************************************************/
void minasaresults(minasastate* state,
     /* Real    */ ae_vector* x,
     minasareport* rep,
     ae_state *_state)
{

    ae_vector_clear(x);
    _minasareport_clear(rep);

    minasaresultsbuf(state, x, rep, _state);
}


/*************************************************************************
ASA results

Buffered implementation of MinASAResults() which uses pre-allocated buffer
to store X[]. If buffer size is  too  small,  it  resizes  buffer.  It  is
intended to be used in the inner cycles of performance critical algorithms
where array reallocation penalty is too large to be ignored.

  -- ALGLIB --
     Copyright 20.03.2009 by Bochkanov Sergey
*************************************************************************/
void minasaresultsbuf(minasastate* state,
     /* Real    */ ae_vector* x,
     minasareport* rep,
     ae_state *_state)
{
    ae_int_t i;


    if( x->cnt<state->n )
    {
        ae_vector_set_length(x, state->n, _state);
    }
    ae_v_move(&x->ptr.p_double[0], 1, &state->x.ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    rep->iterationscount = state->repiterationscount;
    rep->nfev = state->repnfev;
    rep->terminationtype = state->repterminationtype;
    rep->activeconstraints = 0;
    for(i=0; i<=state->n-1; i++)
    {
        if( ae_fp_eq(state->ak.ptr.p_double[i],0) )
        {
            rep->activeconstraints = rep->activeconstraints+1;
        }
    }
}


/*************************************************************************
This  subroutine  restarts  CG  algorithm from new point. All optimization
parameters are left unchanged.

This  function  allows  to  solve multiple  optimization  problems  (which
must have same number of dimensions) without object reallocation penalty.

INPUT PARAMETERS:
    State   -   structure previously allocated with MinCGCreate call.
    X       -   new starting point.
    BndL    -   new lower bounds
    BndU    -   new upper bounds

  -- ALGLIB --
     Copyright 30.07.2010 by Bochkanov Sergey
*************************************************************************/
void minasarestartfrom(minasastate* state,
     /* Real    */ ae_vector* x,
     /* Real    */ ae_vector* bndl,
     /* Real    */ ae_vector* bndu,
     ae_state *_state)
{


    ae_assert(x->cnt>=state->n, "MinASARestartFrom: Length(X)<N!", _state);
    ae_assert(isfinitevector(x, state->n, _state), "MinASARestartFrom: X contains infinite or NaN values!", _state);
    ae_assert(bndl->cnt>=state->n, "MinASARestartFrom: Length(BndL)<N!", _state);
    ae_assert(isfinitevector(bndl, state->n, _state), "MinASARestartFrom: BndL contains infinite or NaN values!", _state);
    ae_assert(bndu->cnt>=state->n, "MinASARestartFrom: Length(BndU)<N!", _state);
    ae_assert(isfinitevector(bndu, state->n, _state), "MinASARestartFrom: BndU contains infinite or NaN values!", _state);
    ae_v_move(&state->x.ptr.p_double[0], 1, &x->ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    ae_v_move(&state->bndl.ptr.p_double[0], 1, &bndl->ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    ae_v_move(&state->bndu.ptr.p_double[0], 1, &bndu->ptr.p_double[0], 1, ae_v_len(0,state->n-1));
    state->laststep = 0;
    ae_vector_set_length(&state->rstate.ia, 3+1, _state);
    ae_vector_set_length(&state->rstate.ba, 1+1, _state);
    ae_vector_set_length(&state->rstate.ra, 2+1, _state);
    state->rstate.stage = -1;
    minasa_clearrequestfields(state, _state);
}


/*************************************************************************
Returns norm of bounded anti-gradient.

Bounded antigradient is a vector obtained from  anti-gradient  by  zeroing
components which point outwards:
    result = norm(v)
    v[i]=0     if ((-g[i]<0)and(x[i]=bndl[i])) or
                  ((-g[i]>0)and(x[i]=bndu[i]))
    v[i]=-g[i] otherwise

This function may be used to check a stopping criterion.

  -- ALGLIB --
     Copyright 20.03.2009 by Bochkanov Sergey
*************************************************************************/
static double minasa_asaboundedantigradnorm(minasastate* state,
     ae_state *_state)
{
    ae_int_t i;
    double v;
    double result;


    result = 0;
    for(i=0; i<=state->n-1; i++)
    {
        v = -state->g.ptr.p_double[i];
        if( ae_fp_eq(state->x.ptr.p_double[i],state->bndl.ptr.p_double[i])&&ae_fp_less(-state->g.ptr.p_double[i],0) )
        {
            v = 0;
        }
        if( ae_fp_eq(state->x.ptr.p_double[i],state->bndu.ptr.p_double[i])&&ae_fp_greater(-state->g.ptr.p_double[i],0) )
        {
            v = 0;
        }
        result = result+ae_sqr(v, _state);
    }
    result = ae_sqrt(result, _state);
    return result;
}


/*************************************************************************
Returns norm of GI(x).

GI(x) is  a  gradient  vector  whose  components  associated  with  active
constraints are zeroed. It  differs  from  bounded  anti-gradient  because
components  of   GI(x)   are   zeroed  independently  of  sign(g[i]),  and
anti-gradient's components are zeroed with respect to both constraint  and
sign.

  -- ALGLIB --
     Copyright 20.03.2009 by Bochkanov Sergey
*************************************************************************/
static double minasa_asaginorm(minasastate* state, ae_state *_state)
{
    ae_int_t i;
    double result;


    result = 0;
    for(i=0; i<=state->n-1; i++)
    {
        if( ae_fp_neq(state->x.ptr.p_double[i],state->bndl.ptr.p_double[i])&&ae_fp_neq(state->x.ptr.p_double[i],state->bndu.ptr.p_double[i]) )
        {
            result = result+ae_sqr(state->g.ptr.p_double[i], _state);
        }
    }
    result = ae_sqrt(result, _state);
    return result;
}


/*************************************************************************
Returns norm(D1(State.X))

For a meaning of D1 see 'NEW ACTIVE SET ALGORITHM FOR BOX CONSTRAINED
OPTIMIZATION' by WILLIAM W. HAGER AND HONGCHAO ZHANG.

  -- ALGLIB --
     Copyright 20.03.2009 by Bochkanov Sergey
*************************************************************************/
static double minasa_asad1norm(minasastate* state, ae_state *_state)
{
    ae_int_t i;
    double result;


    result = 0;
    for(i=0; i<=state->n-1; i++)
    {
        result = result+ae_sqr(boundval(state->x.ptr.p_double[i]-state->g.ptr.p_double[i], state->bndl.ptr.p_double[i], state->bndu.ptr.p_double[i], _state)-state->x.ptr.p_double[i], _state);
    }
    result = ae_sqrt(result, _state);
    return result;
}


/*************************************************************************
Returns True, if U set is empty.

* State.X is used as point,
* State.G - as gradient,
* D is calculated within function (because State.D may have different
  meaning depending on current optimization algorithm)

For a meaning of U see 'NEW ACTIVE SET ALGORITHM FOR BOX CONSTRAINED
OPTIMIZATION' by WILLIAM W. HAGER AND HONGCHAO ZHANG.

  -- ALGLIB --
     Copyright 20.03.2009 by Bochkanov Sergey
*************************************************************************/
static ae_bool minasa_asauisempty(minasastate* state, ae_state *_state)
{
    ae_int_t i;
    double d;
    double d2;
    double d32;
    ae_bool result;


    d = minasa_asad1norm(state, _state);
    d2 = ae_sqrt(d, _state);
    d32 = d*d2;
    result = ae_true;
    for(i=0; i<=state->n-1; i++)
    {
        if( ae_fp_greater_eq(ae_fabs(state->g.ptr.p_double[i], _state),d2)&&ae_fp_greater_eq(ae_minreal(state->x.ptr.p_double[i]-state->bndl.ptr.p_double[i], state->bndu.ptr.p_double[i]-state->x.ptr.p_double[i], _state),d32) )
        {
            result = ae_false;
            return result;
        }
    }
    return result;
}


/*************************************************************************
Clears request fileds (to be sure that we don't forgot to clear something)
*************************************************************************/
static void minasa_clearrequestfields(minasastate* state,
     ae_state *_state)
{


    state->needfg = ae_false;
    state->xupdated = ae_false;
}


ae_bool _minasastate_init(minasastate* p, ae_state *_state, ae_bool make_automatic)
{
    if( !ae_vector_init(&p->bndl, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->bndu, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->ak, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->xk, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->dk, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->an, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->xn, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->dn, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->d, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->work, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->yk, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->gc, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->x, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init(&p->g, 0, DT_REAL, _state, make_automatic) )
        return ae_false;
    if( !_rcommstate_init(&p->rstate, _state, make_automatic) )
        return ae_false;
    if( !_linminstate_init(&p->lstate, _state, make_automatic) )
        return ae_false;
    return ae_true;
}


ae_bool _minasastate_init_copy(minasastate* dst, minasastate* src, ae_state *_state, ae_bool make_automatic)
{
    dst->n = src->n;
    dst->epsg = src->epsg;
    dst->epsf = src->epsf;
    dst->epsx = src->epsx;
    dst->maxits = src->maxits;
    dst->xrep = src->xrep;
    dst->stpmax = src->stpmax;
    dst->cgtype = src->cgtype;
    dst->k = src->k;
    dst->nfev = src->nfev;
    dst->mcstage = src->mcstage;
    if( !ae_vector_init_copy(&dst->bndl, &src->bndl, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->bndu, &src->bndu, _state, make_automatic) )
        return ae_false;
    dst->curalgo = src->curalgo;
    dst->acount = src->acount;
    dst->mu = src->mu;
    dst->finit = src->finit;
    dst->dginit = src->dginit;
    if( !ae_vector_init_copy(&dst->ak, &src->ak, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->xk, &src->xk, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->dk, &src->dk, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->an, &src->an, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->xn, &src->xn, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->dn, &src->dn, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->d, &src->d, _state, make_automatic) )
        return ae_false;
    dst->fold = src->fold;
    dst->stp = src->stp;
    if( !ae_vector_init_copy(&dst->work, &src->work, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->yk, &src->yk, _state, make_automatic) )
        return ae_false;
    if( !ae_vector_init_copy(&dst->gc, &src->gc, _state, make_automatic) )
        return ae_false;
    dst->laststep = src->laststep;
    if( !ae_vector_init_copy(&dst->x, &src->x, _state, make_automatic) )
        return ae_false;
    dst->f = src->f;
    if( !ae_vector_init_copy(&dst->g, &src->g, _state, make_automatic) )
        return ae_false;
    dst->needfg = src->needfg;
    dst->xupdated = src->xupdated;
    if( !_rcommstate_init_copy(&dst->rstate, &src->rstate, _state, make_automatic) )
        return ae_false;
    dst->repiterationscount = src->repiterationscount;
    dst->repnfev = src->repnfev;
    dst->repterminationtype = src->repterminationtype;
    dst->debugrestartscount = src->debugrestartscount;
    if( !_linminstate_init_copy(&dst->lstate, &src->lstate, _state, make_automatic) )
        return ae_false;
    dst->betahs = src->betahs;
    dst->betady = src->betady;
    return ae_true;
}


void _minasastate_clear(minasastate* p)
{
    ae_vector_clear(&p->bndl);
    ae_vector_clear(&p->bndu);
    ae_vector_clear(&p->ak);
    ae_vector_clear(&p->xk);
    ae_vector_clear(&p->dk);
    ae_vector_clear(&p->an);
    ae_vector_clear(&p->xn);
    ae_vector_clear(&p->dn);
    ae_vector_clear(&p->d);
    ae_vector_clear(&p->work);
    ae_vector_clear(&p->yk);
    ae_vector_clear(&p->gc);
    ae_vector_clear(&p->x);
    ae_vector_clear(&p->g);
    _rcommstate_clear(&p->rstate);
    _linminstate_clear(&p->lstate);
}


ae_bool _minasareport_init(minasareport* p, ae_state *_state, ae_bool make_automatic)
{
    return ae_true;
}


ae_bool _minasareport_init_copy(minasareport* dst, minasareport* src, ae_state *_state, ae_bool make_automatic)
{
    dst->iterationscount = src->iterationscount;
    dst->nfev = src->nfev;
    dst->terminationtype = src->terminationtype;
    dst->activeconstraints = src->activeconstraints;
    return ae_true;
}


void _minasareport_clear(minasareport* p)
{
}



}

