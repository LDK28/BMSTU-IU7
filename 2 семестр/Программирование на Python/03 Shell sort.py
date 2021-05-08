import time
import random
import numpy as np

import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
from pandas import DataFrame

from tkinter import *
from tkinter import messagebox
from tkinter import ttk


def shellSort(arr):
    start_timer = time.perf_counter()
    r = len(arr) // 2
    while r:
        for i, el in enumerate(arr):
            while i >= r and arr[i - r] > el:
                arr[i] = arr[i - r]
                i -= r
            arr[i] = el
        if r != 1:
            r //= 2
        else:
            r = 0
    end_timer = time.perf_counter()
    return end_timer - start_timer


def MakeTable(table, n1, n2, n3, t1, t2, t3, t4, t5, t6, t7, t8, t9):
    tree = ttk.Treeview(table)

    tree['columns'] = ('1', '2', '3')

    tree.column('#0', width=200)
    tree.column('1', width=100)
    tree.column('2', width=100)
    tree.column('3', width=100)

    tree.heading('#0', text='Type of array\Size of array')
    tree.heading('1', text=str(n1))
    tree.heading('2', text=str(n2))
    tree.heading('3', text=str(n3))

    tree.insert('', '0', text='Sorted array',
                values=([float('{:8.8e}'.format(t1)), float('{:8.8e}'.format(t2)), float('{:8.8e}'.format(t3))]))
    tree.insert('', '1', text='Random array',
                values=([float('{:8.8e}'.format(t4)), float('{:8.8e}'.format(t5)), float('{:8.8e}'.format(t6))]))
    tree.insert('', '2', text='Reversed array',
                values=([float('{:8.8e}'.format(t7)), float('{:8.8e}'.format(t8)), float('{:8.8e}'.format(t9))]))
    tree.pack()


def MakeGraph(Graphic, a, b):
    x = np.linspace(1000, 5500, 10)
    y = np.zeros(10)
    for i in range(10):
        y[i] = shellSort(np.linspace(a, b, x[i]))
    data = {'Size': x, 'Time': y}
    df = DataFrame(data, columns=['Size', 'Time'])
    figure = plt.Figure(figsize=(5, 4))
    ax = figure.add_subplot(111)
    line = FigureCanvasTkAgg(figure, Graphic)
    line.get_tk_widget().pack(side=LEFT, fill=BOTH)
    df = df[['Size', 'Time']].groupby('Size').sum()
    df.plot(kind='line', legend=True, ax=ax, color='g', marker='o', fontsize=10)
    ax.set_title('Time Vs. Size')


def func():
    try:
        n1 = int(WIN1.get())
        n2 = int(WIN2.get())
        n3 = int(WIN3.get())
        a = -100
        b = 100
        # Creation of arrays
        arr_1 = np.linspace(a, b, n1)
        arr_2 = np.linspace(a, b, n2)
        arr_3 = np.linspace(a, b, n3)

        # Sorting & counting time
        t1 = shellSort(arr_1)
        t2 = shellSort(arr_2)
        t3 = shellSort(arr_3)

        t4 = shellSort(np.array([random.random() for i in range(n1)]))
        t5 = shellSort(np.array([random.random() for i in range(n2)]))
        t6 = shellSort(np.array([random.random() for i in range(n3)]))

        t7 = shellSort(arr_1[::-1])
        t8 = shellSort(arr_2[::-1])
        t9 = shellSort(arr_3[::-1])

        # Output
        WindowOut = Tk()
        WindowOut.title('Shell Sort(Output)')
        WindowOut.resizable(height=0, width=0)
        # Table
        table = Frame(WindowOut)
        MakeTable(table, n1, n2, n3, t1, t2, t3, t4, t5, t6, t7, t8, t9)
        table.pack()
        # Graphic
        Graphic = Frame(WindowOut)
        MakeGraph(Graphic, a, b)
        Graphic.pack()

        WindowOut.mainloop()

    except Exception as ex:
        print(ex)
        WIN1.delete(0, END)
        WIN2.delete(0, END)
        WIN3.delete(0, END)
        messagebox.showerror('Error', 'Error')


# Input window
window = Tk()
window.title('Shell Sort(Input)')
window.geometry('445x275')
window['bg'] = 'white'
window.resizable(height=0, width=0)

lbl1 = Label(window, text='Test array:', font=('Calibri', 20, 'bold'), bg='white')
test_array = [43, 54, 45, 435, 0, 6, 254, 6, 23, 1]
lbl2 = Label(window, text='  '.join(map(str, test_array)), font=('Calibri', 16), bg='white', relief='groove', bd=4)
shellSort(test_array)
lbl3 = Label(window, text='Sorted test array:', font=('Calibri', 20, 'bold'), bg='white')
lbl4 = Label(window, text='  '.join(map(str, test_array)), font=('Calibri', 16), bg='white', relief='groove', bd=4)
lbl5 = Label(window, text='Input sizes of arrays:', font=('Calibri', 20, 'bold'), bg='white')
lbl6_1 = Label(window, text='N1 = ', font=('Calibri', 18), bg='white')
lbl6_2 = Label(window, text='N2 = ', font=('Calibri', 18), bg='white')
lbl6_3 = Label(window, text='N3 = ', font=('Calibri', 18), bg='white')

lbl1.grid(column=0, row=0, columnspan=6, sticky=W)
lbl2.grid(column=0, row=1, columnspan=6)
lbl3.grid(column=0, row=2, columnspan=6, sticky=W)
lbl4.grid(column=0, row=3, columnspan=6)
lbl5.grid(column=0, row=4, columnspan=6, sticky=W)
lbl6_1.grid(column=0, row=5, sticky=W)
lbl6_2.grid(column=2, row=5, sticky=W)
lbl6_3.grid(column=4, row=5, sticky=W)

WIN1 = Entry(window, font=("Calibri", 18), justify=RIGHT, width=7, bd=2)
WIN2 = Entry(window, font=("Calibri", 18), justify=RIGHT, width=7, bd=2)
WIN3 = Entry(window, font=("Calibri", 18), justify=RIGHT, width=7, bd=2)

WIN1.grid(column=1, row=5)
WIN2.grid(column=3, row=5)
WIN3.grid(column=5, row=5)

but = Button(window, text='Start', font=("Calibri", 10), command=func, height=2, width=15)
but.grid(column=0, row=7, columnspan=6)

window.mainloop()
