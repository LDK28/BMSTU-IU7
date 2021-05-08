#   Laboratory work 18

#   Program purposes:
#       Refinement of the roots of the equation

#   Variables' names:
#       A, B - scope of the length
#       h - step
#       eps - inaccuracy
#       count - max number of iterations
#       k - counter of iterations
#       a, b, args, x1 - auxiliary variable 


import numpy as math
from scipy.optimize import bisect
import time
def f(x):
    return math.sin(x)

def f_diff(x):
    return math.cos(x)

def f_diff_x2(x):
    return -math.sin(x)

def mixed_method(a,b):
    if f_diff(a)*f_diff_x2(a) >= 0:
        a = a - (b-a)/(f(b) - f(a))*f(a)
        b = b - f(b)/f_diff(b)
    elif f_diff(a)*f_diff_x2(a) < 0:
        b = b - (a-b)/(f(a) - f(b))*f(b)
        a = a - f(a)/f_diff(a)
    return(a, b)

# Error codes
print('┌──────────────┐')
print('│ Error codes  │')
print('├─────┬────────┴─────────────────────────────────────────┐')
print('│{:^5s}│{:^50s}│'.format('0','No errors'))
print('├─────┼──────────────────────────────────────────────────┤')
print('│{:^5s}│{:^50s}│'.format('101', 'Number of iterations exeeded'))
print('├─────┼──────────────────────────────────────────────────┤')
print('│{:^5s}│{:^50s}│'.format('111', 'Method is not working in this range '\
                                'with this eps'))
print('├─────┼──────────────────────────────────────────────────┤')
print('│{:^5s}│{:^50s}│'.format('121', 'eps is too small'))
print('└─────┴──────────────────────────────────────────────────┘')
print('\n')

# Input
A = float(input('Input start of the length(A): '))
B = float(input('Input end of the length (B): '))
h = float(input('Input the step(h): '))
while A > B or h < 0:
    if A > B:
        print('\n!!A > B!!\nRepeat the action:\n')
    elif h < 0:
        print('\n!!h < 0!!\nRepeat the action:\n')
    A = float(input('Input start of the length(A): '))
    B = float(input('Input end of the length (B): '))
    h = float(input('Input the step(h): '))
eps = float(input('Input eps: '))
count = int(input('Input number of iterations: '))
number = 1
args = math.arange(A, B+h, h)
if args[-1] > B:
    args[-1] = B
x1 = 1000  

# Made mixed method 
print('┌─────────────────────────────────────────────────┐')
print('│                Made mixed method                │')
print('├───────────────┬─────────────────┬───────────────┼──────────────┬────'\
      '────────┬──────────────────────┬────────────┬────────────┐')
print('│ № of the root │ start of length │ end of length │      x       │    '\
      'f(x)    │ number of iterations │    time    │ error code │') 
for i in range(len(args) - 1):
    error = 0
    k = 1
    x = (args[i] +args[i+1])/2
    a, b = args[i],args[i+1]
    if f(args[i])*f(args[i+1]) <= 0:
        if eps < 8.88178e-16:
            error = 121
        else:
            start_timer = time.perf_counter()
            while abs(a - b) > eps:
                a, b = mixed_method(a,b)
                k += 1
                if k > count:
                    error = 101 
                    break
            x = (b + a)/2
            end_timer = time.perf_counter()
        if x > args[i+1] or x < args[i]:
            error = 111
        if error != 0:
            print('├───────────────┼─────────────────┼───────────────┼───────'\
                  '───────┼────────────┼──────────────────────┼────────────┼─'\
                  '───────────┤')
            print('│{:^15d}│{:^17g}│{:^15g}│{:^14s}│{:^12s}│{:^22s}│{:^12.2s}'\
                  '│{:^12g}│'.format(number, args[i], args[i+1], '-', '-',\
                                     '-', '-', error))
            number += 1
        else:
            if abs(x1 - x) > 0.1:
                print('├───────────────┼─────────────────┼───────────────┼───'\
                      '───────────┼────────────┼──────────────────────┼──────'\
                      '──────┼────────────┤')
                print('│{:^15d}│{:^17g}│{:^15g}│{:^14g}│{:^12.0e}│{:^22d}│'\
                      '{:^12.2e}│{:^12g}│'.format(number, args[i], args[i+1],\
                        x, f(x), k-1, end_timer - start_timer, error))
                number += 1
        x1 = x

print('└───────────────┴─────────────────┴───────────────┴──────────────┴────'\
      '────────┴──────────────────────┴────────────┴────────────┘')  


number = 1

# Bisect method from scipy library
print('┌─────────────────────────────────────────────┐')
print('│       Bisect method from scipy library      │')
print('├───────────────┬─────────────────┬───────────┴───┬──────────────┬────'\
      '────────┬──────────────────────┬────────────┬────────────┐')
print('│ № of the root │ start of length │ end of length │      x       │    '\
      'f(x)    │ number of iterations │    time    │ error code │')

for i in range(len(args) - 1):    
    try:
        start_timer = time.perf_counter()
        x, rootRes = bisect(f, args[i], args[i+1], rtol = eps, maxiter = count,\
                                     full_output = True)
        k = rootRes.iterations
        end_timer = time.perf_counter()
        if f(x) == 0:
            k = 1
        print('├───────────────┼─────────────────┼───────────────┼───────'\
              '───────┼────────────┼──────────────────────┼────────────┼─'\
              '───────────┤')
        print('│{:^15d}│{:^17g}│{:^15g}│{:^14.7g}│{:^12.0e}│{:^22d}│'\
              '{:^12.3g}│{:^12s}│'.format(number, args[i], args[i+1],\
                                x, f(x), k, end_timer - start_timer, '0'))
        number += 1
    except Exception as e:
        if str(e) == 'f(a) and f(b) must have different signs':
            continue
        elif str(e) == 'rtol too small (' + str(eps) + ' < 8.88178e-16)':
            error = 121
            print('├───────────────┼─────────────────┼───────────────┼───────'\
                  '───────┼────────────┼──────────────────────┼────────────┼─'\
                  '───────────┤')
            print('│{:^15d}│{:^17g}│{:^15g}│{:^14s}│{:^12s}│{:^22s}│'\
                  '{:^12.2s}│{:^12g}│'.format(number,args[i], args[i+1],\
                                            '-', '-', '-', '-', error))
            number += 1
        elif str(e) == 'Failed to converge after ' + str(count) + ' iterations.':
            error = 101
            print('├───────────────┼─────────────────┼───────────────┼───────'\
                  '───────┼────────────┼──────────────────────┼────────────┼─'\
                  '───────────┤')
            print('│{:^15d}│{:^17g}│{:^15g}│{:^14s}│{:12.0s}│{:^22s}│{:^12.2s}'\
                  '│{:^12g}│'.format(number,args[i], args[i+1], '-', '-', '-',\
                                     '-', error))
            number += 1
            
        
print('└───────────────┴─────────────────┴───────────────┴──────────────┴────'\
      '────────┴──────────────────────┴────────────┴────────────┘')  


