# Laboratory work 2 "Calculator"

# Program purposes:
#       Make calculator which translate from 9 number system to 10


from tkinter import *
from tkinter import ttk
from tkinter import messagebox
from tkinter import Menu


def info():
    info = Tk()
    info.title('info')
    info.geometry('350x100')
    info['bg'] = 'white'
    info.resizable(height=0, width=0)
    text1_1 = Label(info, text='Program version:', bg='white', \
                    font=('Times New Roman', 12))
    text1_2 = Label(info, text='Programmer:', bg='white', \
                    font=('Times New Roman', 12))
    text1_3 = Label(info, text='Directors:', bg='white', \
                    font=('Times New Roman', 12))
    text2_1 = Label(info, text='1.0', bg='white', \
                    font=('Times New Roman', 12))
    text2_2 = Label(info, text='Dmitry Kostev', bg='white', \
                    font=('Times New Roman', 12))
    text2_3 = Label(info, text='Borisov Stanislav & Kuznetsova Olga', \
                    bg='white', font=('Times New Roman', 12))
    text1_1.grid(column=0, row=0, sticky=W)
    text1_2.grid(column=0, row=1, sticky=W)
    text1_3.grid(column=0, row=2, sticky=W)
    text2_1.grid(column=1, row=0, sticky=E)
    text2_2.grid(column=1, row=1, sticky=E)
    text2_3.grid(column=1, row=2, sticky=E)
    info.mainloop()


back = []


def story():
    story = Tk()
    story.title('story')
    story.geometry('400x400')
    story['bg'] = 'white'
    story.resizable(height=0, width=0)
    if len(back):
        s = ''
    else:
        s = 'no story'
    for i in range(len(back) - 1, -1, -1):
        s += '# ' + back[i] + '\n'
    text = Label(story, text=s, bg='white', font=('Times New Roman', 12))
    text.grid(column=0, row=0, sticky=W)
    story.mainloop()


def insert_num(x):
    WIN.insert(END, x)


def insert_point():
    s = WIN.get()
    l = len(s)
    if l:
        check = True
        for i in range(l):
            if s[i] == '.':
                check = False
        if s == '-':
            check = False
        if check:
            WIN.insert(END, '.')


def insert_minus():
    if len(WIN.get()) == 0:
        WIN.insert(END, '-')


def CE():
    WIN.delete(0, END)


def C():
    length = len(WIN.get())
    WIN.delete(length - 1, length)


def nine_to_ten():
    # Get and check number from Entry
    s = WIN.get()
    if len(s) == 0:
        return 1
    minus = False
    if s[0] == '-':
        s = s[1:]
        minus = True
    if s[-1] == '.':
        s = s[:len(s) - 1]
    for i in range(len(s)):
        if (s[i] not in '012345678.'):
            WIN.delete(0, END)
            messagebox.showwarning('Error', 'Error')
            return 1
    if minus:
        back.append('-' + s)
    else:
        back.append(s)
    try:
        pos_point = s.index('.')
        int_part = s[:pos_point]
        fractional_part = s[pos_point + 1:len(s)]
    except:
        int_part = s
        fractional_part = ''

    ten_num = 0
    k = 0
    if len(int_part) > 0:
        int_part = int(int_part)
        while (int_part > 0):
            ten_num += (int_part % 10) * 9 ** k
            int_part //= 10
            k += 1
    if len(fractional_part) > 0:
        k = -1
        fractional_part = int(fractional_part[::-1])
        while (fractional_part > 0):
            ten_num += (fractional_part % 10) * 9 ** k
            fractional_part //= 10
            k -= 1
    if minus:
        ten_num = '-' + str(ten_num)
    else:
        ten_num = str(ten_num)
    WIN.delete(0, END)
    WIN.insert(END, ten_num)


def ten_to_nine():
    # Get and check number from Entry
    s = WIN.get()
    if len(s) == 0:
        return 1
    minus = False
    if s[0] == '-':
        s = s[1:]
        minus = True
    if s[-1] == '.':
        s = s[:len(s) - 1]
    for i in range(len(s)):
        if (s[i] not in '0123456789.'):
            WIN.delete(0, END)
            messagebox.showwarning('Error', 'Error')
            return 1
    if minus:
        back.append('-' + s)
    else:
        back.append(s)
    try:
        pos_point = s.index('.')
        int_part = s[:pos_point]
        fractional_part = s[pos_point + 1:len(s)]
    except:
        int_part = s
        fractional_part = ''

    nine_num = ''

    # Integer part
    if len(int_part) > 0:
        int_part = int(int_part)
        while int_part >= 9:
            nine_num = str(int_part % 9) + nine_num
            int_part //= 9
        nine_num = str(int_part) + nine_num
    # Fractional pert
    if len(fractional_part) > 0:
        nine_num = nine_num + '.'
        fractional_part = int(fractional_part) / 10 ** len(fractional_part)
        c = 0
        while (c < 8) and (fractional_part != 0):
            fractional_part *= 9
            nine_num = nine_num + str(int(fractional_part))
            fractional_part -= int(fractional_part)
            c += 1
    if minus:
        nine_num = '-' + str(nine_num)

    WIN.delete(0, END)
    WIN.insert(END, nine_num)


tap = -1


def last():
    global tap
    if len(back) > 0:
        if abs(tap) == len(back) + 1:
            tap = -1
        WIN.delete(0, END)
        WIN.insert(END, back[tap])
        tap -= 1


window = Tk()
window.title('Calculator')
window.iconbitmap \
    (r'C:\Users\1\AppData\Local\Programs\Python\Python37-32\DLLs\calc.ico')
window.geometry('320x520')
window['bg'] = 'white'
window.resizable(height=0, width=0)

menu = Menu(window)
menu.add_cascade(label='story', command=story)
menu.add_cascade(label='info', command=info)
window.config(menu=menu)

WIN = Entry(window, font=("Times New Roman", 20), justify=RIGHT, bd=15, \
            width=18)
WIN.focus()
WIN.grid(column=0, row=0, columnspan=4, sticky=NSEW)

# Commands
CE = Button(window, text='CE', bg='grey', fg='white', command=CE, \
            height=5, width=10)
CE.grid(column=0, row=1, sticky=W)

C = Button(window, text='C', bg='grey', fg='white', command=C, \
           height=5, width=10)
C.grid(column=1, row=1, sticky=W)

Back = Button(window, text='Back', bg='grey', fg='white', command=lambda: \
    last(), height=5, width=10)
Back.grid(column=2, row=1, sticky=W)

# Buttons for numbers
SEVEN = Button(window, text='7', command=lambda: insert_num('7'), \
               height=5, width=10)
SEVEN.grid(column=0, row=2, sticky=W)
EIGHT = Button(window, text='8', command=lambda: insert_num('8'), \
               height=5, width=10)
EIGHT.grid(column=1, row=2, sticky=W)
NINE = Button(window, text='9', command=lambda: insert_num('9'), \
              height=5, width=10)
NINE.grid(column=2, row=2, sticky=W)

FOUR = Button(window, text='4', command=lambda: insert_num('4'), \
              height=5, width=10)
FOUR.grid(column=0, row=3, sticky=W)
FIVE = Button(window, text='5', command=lambda: insert_num('5'), \
              height=5, width=10)
FIVE.grid(column=1, row=3, sticky=W)
SIX = Button(window, text='6', command=lambda: insert_num('6'), \
             height=5, width=10)
SIX.grid(column=2, row=3, sticky=W)

ONE = Button(window, text='1', command=lambda: insert_num('1'), \
             height=5, width=10)
ONE.grid(column=0, row=4, sticky=W)
TWO = Button(window, text='2', command=lambda: insert_num('2'), \
             height=5, width=10)
TWO.grid(column=1, row=4, sticky=W)
THREE = Button(window, text='3', command=lambda: insert_num('3'), \
               height=5, width=10)
THREE.grid(column=2, row=4, sticky=W)

ZERO = Button(window, text='0', command=lambda: insert_num('0'), \
              height=5, width=10)
ZERO.grid(column=0, row=5, sticky=W)

POINT = Button(window, text='.', command=lambda: insert_point(), \
               height=5, width=10)
POINT.grid(column=1, row=5, sticky=W)

MINUS = Button(window, text='-', command=insert_minus, height=5, \
               width=10)
MINUS.grid(column=2, row=5, sticky=W)

NOT_BUT = Button(window, state=DISABLED, height=5, width=10)
NOT_BUT.grid(column=3, row=5, sticky=W)

# Commands
NINEtoTEN = Button(window, text='9 >> 10', command=nine_to_ten, \
                   bg='orange', activebackground='yellow', height=11, width=10)
NINEtoTEN.grid(column=3, row=1, rowspan=2, sticky=W)

TENtoNINE = Button(window, text='10 >> 9', command=ten_to_nine, \
                   bg='orange', activebackground='yellow', height=11, width=10)
TENtoNINE.grid(column=3, row=3, rowspan=2, sticky=W)

window.mainloop()
