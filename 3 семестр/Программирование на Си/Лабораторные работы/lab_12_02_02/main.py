import tkinter as tk
from tkinter import messagebox as mb
import ctypes


def fibonacci():
    lib = ctypes.CDLL('fibonacci.dll')
    a = []
    _fibonacci = lib.fibonacci
    _fibonacci.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_int)
    try:
        n = int(e0.get())
    except:
        mb.showwarning("Error!", "Error! Input is not correct")
        return
    arr = (ctypes.c_int * n)(*a)
    _fibonacci(arr, n)
    return list(arr)


def arr_filter():
    lib = ctypes.CDLL('fibonacci.dll')

    _arr_filter = lib.copy_arr
    _arr_filter.argtypes = (ctypes.POINTER(ctypes.c_int),
                            ctypes.c_int, ctypes.POINTER(ctypes.c_int))
    _arr_filter.restype = ctypes.c_int

    try:
        a = list(map(int, e1.get().split()))
    except:
        mb.showwarning("Error!", "Error! Input is not correct")
        return

    n_a = len(a)
    arr_a = (ctypes.c_int * n_a)(*a)
    arr_b = (ctypes.c_int * n_a)()
    n_b = _arr_filter(arr_a, n_a, arr_b)
    arr_b = (ctypes.c_int * n_b)()

    _arr_filter(arr_a, n_a, arr_b)
    return list(arr_b)


root = tk.Tk()
root.title('lab_12_02_02')
root.geometry("200x200")
app = tk.Frame(root)
app.grid()

lb0 = tk.Label(app, text='Input array size: ')
lb0.grid(row=0, column=0, sticky=tk.W)

e0 = tk.Entry(app)
e0.grid(row=1, column=0, sticky=tk.W)

but_shift = tk.Button(app, text='Fill array Fibonacci numbers', command=fibonacci)
but_shift.grid(row=2, column=0, sticky=tk.W)

lb2 = tk.Label(app, text='Output Fibonacci array:')
lb2.grid(row=3, column=0, sticky=tk.W)

lb3 = tk.Label(app, text='Input array:')
lb3.grid(row=5, column=0, sticky=tk.W)
e1 = tk.Entry(app)
e1.grid(row=6, column=0, sticky=tk.W)

lb4 = tk.Button(app, text='Copy first entry',
                command=arr_filter)
lb4.grid(row=7, column=0, sticky=tk.W)

lb5 = tk.Label(app, text='Output array:')
lb5.grid(row=8, column=0, sticky=tk.W)

root.mainloop()
