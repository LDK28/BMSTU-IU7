#   Laboratory work 1 "Correction of roots"

#   Program purposes:
#       Refinement of the roots of the equation

#   Variables' names:
#       A, B - scope of the length
#       h - step
#       eps - inaccuracy
#       count - max number of iterations
#       k - counter of iterations
#       a, b, args, x1 - auxiliary variable 

import numpy as np
import matplotlib.pyplot as plt
from tkinter import *
from tkinter import ttk
from tkinter import messagebox
import time
from scipy.optimize import bisect



def f(x):
    return np.sin(x)

def f_diff(x):
    return np.cos(x)

def f_diff_x2(x):
    return np.sin(-x)

def mixed_method(a,b):
    if f_diff(a)*f_diff_x2(a) >= 0:
        a = a - (b-a)/(f(b) - f(a))*f(a)
        b = b - f(b)/f_diff(b)
    elif f_diff(a)*f_diff_x2(a) < 0:
        b = b - (a-b)/(f(a) - f(b))*f(b)
        a = a - f(a)/f_diff(a)        
    return(a, b)

def error_codes(window_out):
    tree0=ttk.Treeview(window_out)

    tree0['columns'] = ('1', '2')
    tree0.column('#0', width=100)
    tree0.column('1', width=50)
    tree0.column('2', width=400)
    
    tree0.heading('#0', text='Error codes')
    tree0.heading('1', text='№')
    tree0.heading('2', text='Problem')

    tree0.insert('', 'end', text='', values=(['0', 'No errors']))
    tree0.insert('', 'end', text='', values=(['101', 'Number of iterations ex'\
                                              'eeded']))
    tree0.insert('', 'end', text='', values=(['111', 'Method is not working '\
                                              'in this range '\
                                'with this eps']))
    tree0.insert('', 'end', text='', values=(['121', 'eps is too small']))

    tree0.pack()


def graphic(a, b, roots):
    x = np.linspace(a, b, 3000)
    y = f(x)
    plt.xlabel('─────────────────────────────────────────────────────────>X')
    plt.ylabel('──────────────────────────────────────────>Y')
    plt.plot(x, y, 'g')
    plt.grid()
    yroots = [0]*len(roots)
    plt.scatter(roots,yroots,color='blue')
    miny=min(y)
    maxy=max(y)
    tmax=True
    tmin=True
    for i in range(len(y)):
        if y[i]-miny<=0.00001 and tmin==True:
            plt.scatter(x[i],y[i],color='r')
            tmin=False
            tmax=True
        if maxy-y[i]<=0.00001 and tmax==True:
            plt.scatter(x[i],y[i],color='r')
            tmin=True
            tmax=False
    plt.legend(("graf","roots","min and max"))
    plt.show()


def output(A, B, h, eps, count):
    out = Tk()
    out.title('Output')
    window_out = Frame(out)
    error_codes(window_out)
    made_method(window_out, A, B, h, eps, count)
    roots = bisect_method_from_scipy(window_out, A, B, h, eps, count)
    window_out.pack(side=TOP)
    return roots

    

def made_method(window_out, A, B, h, eps, count):

    tree = ttk.Treeview(window_out)
    
    tree['columns'] = ('1', '2', '3', '4', '5', '6', '7', '8')
    tree.column('#0', width=200)
    tree.column('1', width=50)
    tree.column('2', width=100)
    tree.column('3', width=100)
    tree.column('4', width=100)
    tree.column('5', width=100)
    tree.column('6', width=100)
    tree.column('7', width=100)
    tree.column('8', width=100)

    tree.heading('#0', text='Made mixed method')
    tree.heading('1', text='№')
    tree.heading('2', text='start of length')
    tree.heading('3', text='end of length')
    tree.heading('4', text='x')
    tree.heading('5', text='f(x)')
    tree.heading('6', text='iterations')
    tree.heading('7', text='time')
    tree.heading('8', text='error code')

    
    number = 1
    args = np.arange(A, B+h, h)
    if args[-1] > B:
        args[-1] = B
    x1 = 1000 
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
            if error != 0 and args[i] != 0:
                tree.insert('', 'end', text='', values=([number, int(args[i]),\
                                    int(args[i+1]), '-', '-', '-', '-', error]))
                number += 1
            else:
                if abs(x1 - x) > 0.001 and args[i] != 0:
                    tree.insert('', 'end', text='', values=([number, int(args[i]), \
                            int(args[i+1]), float('{:8.6e}'.format(x)), \
                            float('{:8.0e}'.format(f(x))), k-1, \
                            float('{:8.2e}'.format(end_timer - start_timer)), error]))
                    number += 1
            x1 = x



    tree.pack()


def bisect_method_from_scipy(window_out, A, B, h, eps, count):
    tree1 = ttk.Treeview(window_out)
    
    tree1['columns'] = ('1', '2', '3', '4', '5', '6', '7', '8')
    tree1.column('#0', width=200)
    tree1.column('1', width=50)
    tree1.column('2', width=100)
    tree1.column('3', width=100)
    tree1.column('4', width=100)
    tree1.column('5', width=100)
    tree1.column('6', width=100)
    tree1.column('7', width=100)
    tree1.column('8', width=100)
    
    tree1.heading('#0', text='Bisect method from scipy library')
    tree1.heading('1', text='№')
    tree1.heading('2', text='start of length')
    tree1.heading('3', text='end of length')
    tree1.heading('4', text='x')
    tree1.heading('5', text='f(x)')
    tree1.heading('6', text='iterations')
    tree1.heading('7', text='time')
    tree1.heading('8', text='error code')

    args = np.arange(A, B+h, h)
    if args[-1] > B:
        args[-1] = B
    number = 1
    roots = []
    x1 = 1000

    for i in range(len(args) - 1):
        error = 0
        try:
            start_timer = time.perf_counter()
            x, rootRes = bisect(f, args[i], args[i+1], rtol = eps, maxiter = count,\
                                     full_output = True)
            k = rootRes.iterations
            end_timer = time.perf_counter()
            if f(x) == 0:
                k = 1
            roots.append(x)
            if x1 != x:
                tree1.insert('', 'end', text='', values=([number, int(args[i]), \
                            int(args[i+1]), float('{:8.6e}'.format(x)), \
                            float('{:8.0e}'.format(f(x))), k, \
                            float('{:8.2e}'.format(end_timer - start_timer)), error]))
                number += 1
            x1 = x
        except Exception as e:
            if str(e) == 'f(a) and f(b) must have different signs':
                continue
            elif str(e) == 'rtol too small (' + str(eps) + ' < 8.88178e-16)':
                error = 121
                tree1.insert('', 'end', text='', values=([number, int(args[i]),\
                                int(args[i+1]), '-', '-', '-', '-', error]))
                number += 1
            elif str(e) == 'Failed to converge after ' + str(count) + ' iterations.':
                error = 101
                tree1.insert('', 'end', text='', values=([number, int(args[i]),\
                                int(args[i+1]), '-', '-', '-', '-', error]))
                number += 1

    tree1.pack(side=BOTTOM)
    return(roots)
    
    
def clicked():
    try:
        A = float('{}'.format(field_A.get()))
        B = float('{}'.format(field_B.get()))
        h = float('{}'.format(field_h.get()))
        eps = float('{}'.format(field_eps.get()))
        count = int('{}'.format(field_count.get()))
        if B < A or h == 0 or eps == 0 or abs(B-A) < abs(h):
            messagebox.showwarning('INCORRECT DATA', 'OK')
        else:
            roots = output(A, B, h, eps, count)
            print('output was made')
            graphic(A, B, roots)
            print('graphic was  made')
    except:
        messagebox.showwarning('ERROR', 'OK')



window = Tk()
window.title('Correction of roots')
window.geometry('400x200')

lbl = Label(window, text='Input of Data', font=('Times New Roman', 12))
lbl.grid(column=1, row=0, sticky=W)

lbl_A = Label(window, text='Input start of the length(A):', font=('Times New Roman', 12))  
lbl_A.grid(column=0, row=1, sticky=W)
field_A = Entry(window, width=15)
field_A.grid(column=1, row=1, sticky=W)

lbl_B = Label(window, text='Input end of the length (B):', font=('Times New Roman', 12))  
lbl_B.grid(column=0, row=2, sticky=W)
field_B = Entry(window, width=15)
field_B.grid(column=1, row=2, sticky=W)

lbl_h = Label(window, text='Input the step(h):', font=('Times New Roman', 12))  
lbl_h.grid(column=0, row=3, sticky=W)
field_h = Entry(window, width=15)
field_h.grid(column=1, row=3, sticky=W)

lbl_eps = Label(window, text='Input the inaccuracy(eps):', font=('Times New Roman', 12))  
lbl_eps.grid(column=0, row=4, sticky=W)
field_eps = Entry(window, width=15)
field_eps.grid(column=1, row=4, sticky=W)

lbl_count = Label(window, text='Input the maximum of itterations(count):',\
                  font=('Times New Roman', 12))  
lbl_count.grid(column=0, row=5, sticky=W)
field_count = Entry(window, width=15)
field_count.grid(column=1, row=5, sticky=W)

lbl_t = Label(window, text='Function:', font=('Times New Roman', 12))
lbl_t.grid(column=0, row=7, sticky=W)

lbl_F = Label(window, text='sin(x)', font=('Times New Roman', 12))
lbl_F.grid(column=1, row=7, sticky=W)

btn = Button(window, text='Input', command=clicked, width=12)
btn.grid(column=1, row=6, sticky=W)

window.mainloop()
