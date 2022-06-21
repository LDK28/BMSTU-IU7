import matplotlib.pyplot as plt
import math
import pylab
from matplotlib import ticker

### PARAMS
R0 = 0.35
Tw = 2e3
T0 = 1e4
k0 = 3.5e-9
c = 3e10
p = 4
RUN_STEP = 1e-2
SH_STEP = 0.1

F0 = 0
Z0 = 0

Z1 = 1

### FUNCS
def T(z):
    return (Tw - T0) * pow(z, p) + T0

def k(z):
    tmp = (T(z) / 300) ** 6
    return k0 * tmp

def up(z):
    return (3.084 * 1e-4) / (math.exp(47990 / T(z)) - 1)

def f_du(z, u, f):
    return -f * 3. * k(z) * R0 / c


def f_df(z, u, f):
    if z == 0.0:
        return R0 * c * k(z) * (up(z) - u) / 2.0
    return R0 * c * k(z) * (up(z) - u) - f / z

def runge(u0, f_du, f_df):
    h = RUN_STEP
    tmp = h / 2
    z = Z0
    u = u0
    f = F0
    u_vec = [u]
    f_vec = [f]
    z_vec = [z]
    while (z <= Z1):
        k1 = h * f_du (z, u, f)
        q1 = h * f_df(z, u, f)

        k2 = h * f_du (z + tmp, u + k1 / 2., f + q1 / 2.)
        q2 = h * f_df(z + tmp, u + k1 / 2., f + q1 / 2.)

        k3 = h * f_du (z + tmp, u + k2 / 2., f + q2 / 2.)
        q3 = h * f_df(z + tmp, u + k2 / 2., f + q2 / 2.)

        k4 = h * f_du(z + h, u + k3, f + q3)
        q4 = h * f_df(z + h, u + k3, f + q3)

        u += (k1 + 2 * k2 + 2 * k3 + k4) / 6
        u_vec.append(u)
        f += (q1 + 2. * q2 + 2. * q3 + q4) / 6
        f_vec.append(f)

        z += h
        z_vec.append(z)
    return (u_vec, f_vec, z_vec)

def sign(n):
    if n < 0:
        return -1
    else:
        return 1


def half_division_method(left, right, func, grad):
    mid = (left + right) / 2
    if abs(left - right) < 1e-8:
        return mid
    test = func(mid)
    if grad:
        if test > 0:
            return half_division_method(left, mid, func, grad)
        elif test < 0:
            return half_division_method(mid, right, func, grad)
    else:
        if test < 0:
            return half_division_method(left, mid, func, grad)
        elif test > 0:
            return half_division_method(mid, right, func, grad)
    return mid

def __shooting(u0):
    return runge(u0, f_du, f_df)

def _shooting(u0):
    arr = __shooting(u0)
    u1 = arr[0][len(arr[0]) - 1]
    f1 = arr[1][len(arr[1]) - 1]
    return f1 - 0.393 * c * u1

def shooting():
    h = SH_STEP
    ksi = 0
    z0 = Z0
    u0 = ksi * up(z0)
    
    sign0 = sign(_shooting(u0))
    sig = sign0
    
    while sig == sign0:
        ksi += h
        u0 = ksi * up(z0)
        sig = sign(_shooting(u0))

    ksi -= h
    u0_left = ksi * up(z0)
    u0_right = u0
    if sign0 == -1:
        u0 = half_division_method(u0_left, u0_right, _shooting, True)
    else:
        u0 = half_division_method(u0_left, u0_right, _shooting, False)
    
    return u0
def trace_R0(init, end):
    step = (end - init) / 100
    global R0
    R0 = init
    val = []
    us = []
    for _ in range (100):
        val.append(R0)
        u0 = shooting()
        us.append(u0)
        R0 += step
    return (val, us)

def trace_Tw(init, end):
    step = (end - init) / 100
    global Tw
    Tw = init
    val = []
    us = []
    for _ in range (100):
        val.append(Tw)
        u0 = shooting()
        us.append(u0)
        Tw += step
    return (val, us)

def trace_T0(init, end):
    step = (end - init) / 100
    global T0
    T0 = init
    val = []
    us = []
    for _ in range (100):
        val.append(T0)
        u0 = shooting()
        us.append(u0)
        T0 += step
    return (val, us)

def trace_k0(init, end):
    step = (end - init) / 100
    global k0
    k0 = init
    val = []
    us = []
    for _ in range (100):
        val.append(k0)
        u0 = shooting()
        us.append(u0)
        k0 += step
    return (val, us)

def trace_p(init, end):
    step = (end - init) / 4
    global p
    p = init
    val = []
    us = []
    for _ in range (4):
        val.append(p)
        u0 = shooting()
        us.append(u0)
        p += step
    return (val, us)
def main():
    u0 = shooting()
    u, f, z = __shooting(u0)
    up_v = []
    for zi in z:
        up_v.append(up(zi))
    formatter = ticker.ScalarFormatter(useMathText=True)
    formatter.set_scientific(True) 
    formatter.set_powerlimits((-1, 1)) 

    pylab.figure(1)
    ax1 = pylab.subplot(1, 2, 1)
    pylab.plot(z, f, label = "f(z)")
    pylab.legend()

    ax2 = pylab.subplot(1, 2, 2)
    pylab.plot(z, u, label = "u(z)")
    pylab.plot(z, up_v, label = "up(z)")
    pylab.legend()

    ax2.yaxis.set_major_formatter(formatter)
    plt.sca(ax1)
    ax1.yaxis.set_major_formatter(formatter)
    pylab.show()

   
    pylab.figure(2)

    val, us = trace_R0(0, 100)
    global R0
    R0 = 0.35
    pylab.subplot(2, 3, 1)
    pylab.plot(us, val, label = "R(u0)")
    pylab.legend()

    val, us = trace_Tw(1950, 2050)
    global Tw
    Tw = 2e3
    pylab.subplot(2, 3, 2)
    pylab.plot(us, val, label = "Tw(u0)")
    pylab.legend()

    val, us = trace_k0(0.00079, 0.00081)
    global k0
    k0 = 8e-4
    pylab.subplot(2, 3, 3)
    pylab.plot(us, val, label = "k0(u0)")
    pylab.legend()

    val, us = trace_T0(9950, 10050)
    global T0
    T0 = 1e4
    pylab.subplot(2, 3, 4)
    pylab.plot(us, val, label = "T0(u0)")
    pylab.legend()

    val, us = trace_p(1, 5)
    global p
    p = 4
    pylab.subplot(2, 3, 5)
    pylab.plot(us, val, label = "p(u0)")
    pylab.legend()

    pylab.show()

main()
