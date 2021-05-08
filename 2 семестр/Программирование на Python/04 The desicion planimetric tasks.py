from tkinter import *
from tkinter import messagebox


def draw_graphic():
    canv.create_line(maxX, maxY * 2, maxX, 0, width=1, arrow=LAST)
    canv.create_line(0, maxY, maxX * 2,  maxY, width=1, arrow=LAST)
    for i in range(-maxX + 50, maxX, 50):
        if i != 0:
            canv.create_text(i + maxX, maxY + 10, text=str(i))
            canv.create_line(i + maxX, maxY, i + maxX, maxY - 5)
    for i in range(-maxY + 50, maxY, 50):
        if i != 0:
            canv.create_text(maxX + 15, i + maxY, text=str(-i))
            canv.create_line(maxX, i + maxY, maxX - 5, i + maxY)


def check_entry(S):
    if S in ['1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '.', '-']:
        return True
    else:
        window.bell()
        return False


def get_point(event):
    point = Tk()
    point.title('Add point')
    point['bg'] = 'white'
    point.resizable(height=0, width=0)

    pointX = Entry(point, font=("Calibri", 14), fg='grey', justify=RIGHT, width=12, bd=2)
    pointX.insert(0, 'Input x:')

    def clear_entryX(event):
        pointX.delete(0, END)
        pointX.config(validate="key", fg='black')

    pointX.bind('<Button>', clear_entryX)
    pointX['validatecommand'] = (pointX.register(check_entry), '%S')
    pointX.grid(row=0)

    pointY = Entry(point, font=("Calibri", 14), fg='grey', justify=RIGHT, width=12, bd=2)
    pointY.insert(0, 'Input y:')

    def clear_entryY(event):
        pointY.delete(0, END)
        pointY.config(validate="key", fg='black')

    pointY.bind('<Button>', clear_entryY)
    pointY['validatecommand'] = (pointY.register(check_entry), '%S')
    pointY.grid(row=1)

    def command(event):
        insert_point(pointX.get(), pointY.get())
        point.destroy()

    point.bind('<Return>', command)
    point.mainloop()


def get_circle(event):
    circle = Tk()
    circle.title('Add circle')
    circle['bg'] = 'white'
    circle.resizable(height=0, width=0)

    centerX = Entry(circle, font=("Calibri", 14), fg='grey', justify=RIGHT, width=12, bd=2)
    centerX.insert(0, 'Input x of center:')

    def clear_entryX(event):
        centerX.delete(0, END)
        centerX.config(validate="key", fg='black')

    centerX.bind('<Button>', clear_entryX)
    centerX['validatecommand'] = (centerX.register(check_entry), '%S')
    centerX.grid(row=0)

    centerY = Entry(circle, font=("Calibri", 14), fg='grey', justify=RIGHT, width=12, bd=2)
    centerY.insert(0, 'Input y of center:')

    def clear_entryY(event):
        centerY.delete(0, END)
        centerY.config(validate="key", fg='black')

    centerY.bind('<Button>', clear_entryY)
    centerY['validatecommand'] = (centerY.register(check_entry), '%S')
    centerY.grid(row=1)

    radius = Entry(circle, font=("Calibri", 14), fg='grey', justify=RIGHT, width=12, bd=2)
    radius.insert(0, 'Input radius:')

    def clear_entryR(event):
        radius.delete(0, END)
        radius.config(validate="key", fg='black')

    radius.bind('<Button>', clear_entryR)
    radius['validatecommand'] = (radius.register(check_entry), '%S')
    radius.grid(row=2)

    def command(event):
        insert_circle(centerX.get(), centerY.get(), radius.get())
        circle.destroy()

    circle.bind('<Return>', command)
    circle.mainloop()


def insert_point(x, y):
    try:
        x = float(x)
        y = float(y)
        points.append([x, y])
        canv.create_oval([x - 2 + maxX, -y - 2 + maxY], [x + 2 + maxX, -y + 2 + maxY], fill='black')
        decision()
    except Exception as ex:
        print(ex)
        messagebox.showerror('Error', 'Missed data')


def insert_circle(x, y, r):
    try:
        x = float(x)
        y = float(y)
        r = float(r)
        if r < 0:
            messagebox.showerror('Error', 'Radius < 0')
            return
        circles.append([x, y, r])
        decision()
    except Exception as ex:
        print(ex)
        messagebox.showerror('Error', 'Missed data')


def draw_elements():
    point = canv.create_text(30, 10, text='add point', font=('Calibri', 10), activefill='blue', fill='gray')
    circle = canv.create_text(30, 30, text='add circle', font=('Calibri', 10), activefill='blue', fill='gray')
    d_point = canv.create_text(33, 50, text='draw point', font=('Calibri', 10), activefill='blue', fill='gray')
    d_circle = canv.create_text(33, 70, text='draw circle', font=('Calibri', 10), activefill='blue', fill='gray')
    clear = canv.create_text(26, 90, text='clear all', font=('Calibri', 10), activefill='blue', fill='gray')
    canv.tag_bind(point, '<Button-1>', get_point)
    canv.tag_bind(circle, '<Button-1>', get_circle)

    def swap_to_point(event):
        global d_r, figure
        d_r = 2
        figure = 'point'

    canv.tag_bind(d_point, '<Button-1>', swap_to_point)

    def swap_to_circle(event):
        global d_r, figure
        get_r = Tk()
        get_r.resizable(height=0, width=0)
        radius = Entry(get_r, font=("Calibri", 14), fg='grey', justify=RIGHT, width=12, bd=2)
        radius.insert(0, 'input radius')

        def clear_entry(event):
            radius.delete(0, END)
            radius.config(validate="key", fg='black')

        radius.bind('<Button>', clear_entry)
        radius['validatecommand'] = (radius.register(check_entry), '%S')
        radius.grid(column=1, row=2)

        def make_r(event):
            global d_r
            d_r = float(radius.get())
            get_r.destroy()

        d_r = get_r.bind('<Return>', make_r)
        figure = 'circle'

    canv.tag_bind(d_circle, '<Button-1>', swap_to_circle)
    canv.tag_bind(clear, '<Button-1>', clear_all)
    global d_r, figure
    d_r = 0
    figure = None
    canv.bind('<Button-1>', draw)


def draw(event):
    if (event.x > 70) or (event.y > 100):
        x = event.x - maxX
        y = -event.y + maxY
        if figure == 'point':
            points.append([x, y])
            canv.create_oval([x - d_r + maxX, -y - d_r + maxY], [x + d_r + maxX, -y + d_r + maxY], fill='black')
        elif figure == 'circle':
            circles.append([x, y, d_r])
            decision()
        else:
            canv.create_oval(0, 0, 0, 0, width=0)
        decision()


def decision():
    global blue_circle
    if len(circles) > 0:
        count = 0
        for i in points:
            if (i[0] - circles[0][0]) ** 2 + (i[1] - circles[0][1]) ** 2 <= circles[0][2] ** 2:
                count += 1
            else:
                count -= 1
        min = count
        for j in circles:
            count = 0
            for i in points:
                if (i[0] - j[0]) ** 2 + (i[1] - j[1]) ** 2 <= j[2] * j[2]:
                    count += 1
                else:
                    count -= 1
            if count <= min:
                min = count
                canv.itemconfig(blue_circle, width=1, outline='black')
                blue_circle = canv.create_oval([j[0] - j[2] + maxX, -j[1] - j[2] + maxY],
                                               [j[0] + j[2] + maxX, -j[1] + j[2] + maxY],
                                               width=2, outline='blue')
                global answer
                answer.config(text=' __ANSWER__\n x: ' + str(j[0]) + '\n y: ' + str(j[1]) + '\n raduius: ' + str(
                    j[2]) + '\n count: ' + str(min), font=('Calibri', 10, 'bold'), fg='green', bg='white')
                answer.grid(column=3, row=0, sticky=W)
            else:
                canv.create_oval([j[0] - j[2] + maxX, -j[1] - j[2] + maxY], [j[0] + j[2] + maxX, -j[1] + j[2] + maxY],
                                 width=1)


def clear_all(event):
    canv.delete("all")
    circles.clear()
    points.clear()
    global answer
    answer.config(text='')
    draw_graphic()
    draw_elements()


if __name__ == '__main__':
    points = []
    circles = []
    maxX = 550
    maxY = 300
    # MAIN PART
    window = Tk()
    window.title('The decision planimetric task')
    window.state('zoomed')
    window['bg'] = 'white'
    answer = Label(window, text='', fg='white', bg='white')

    canv = Canvas(window, width=maxX * 2, height=maxY * 2, bg='white')
    draw_graphic()
    canv.grid(column=0, row=0, columnspan=3, rowspan=5)
    blue_circle = canv.create_oval(0, 0, 0, 0)
    draw_elements()
    window.mainloop()
