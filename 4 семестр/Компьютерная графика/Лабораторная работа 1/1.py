from tkinter import *
from tkinter import messagebox
from tkinter.ttk import Treeview, Style
from math import pi

maxX = 600
maxY = 360
points = []


def drawBasics():
    canvas.create_line(5, maxY * 2, 5, 0, width=1, arrow=LAST)
    canvas.create_line(5, maxY * 2, maxX * 2, maxY * 2, width=1, arrow=LAST)


def drawElements():
    addPointButton = Button(window, text="Добавить точку", width=22, height=1, command=getPoint)
    editPointButton = Button(window, text="Изменить точку", width=22, height=1, command=editPoint)
    deletePointButton = Button(window, text="Удалить точку", width=22, height=1, command=deletePoint)
    clearAllButton = Button(window, text="Очистить всё", width=22, height=1, command=clearAll)

    addPointButton.grid(column=1, row=1)
    editPointButton.grid(column=1, row=2)
    deletePointButton.grid(column=1, row=3)
    clearAllButton.grid(column=1, row=4)


def editPoint():
    try:
        index = int(table.item(table.selection()[0], option="values")[0]) - 1
        point = Tk()
        point.title('Изменить точку')
        point['bg'] = 'white'
        point.resizable(height=0, width=0)

        pointX = Entry(point, font=("Calibri", 14), justify=RIGHT, width=12, bd=2)
        pointX.insert(0, points[index][0])

        pointX['validatecommand'] = (pointX.register(checkSymbol), '%S')
        pointX.grid(row=0)

        pointY = Entry(point, font=("Calibri", 14), justify=RIGHT, width=12, bd=2)
        pointY.insert(0, points[index][1])

        pointY['validatecommand'] = (pointY.register(checkSymbol), '%S')
        pointY.grid(row=1)

        def command(event):
            points[index][0], points[index][1] = float(pointX.get()), float(pointY.get())
            point.destroy()
            table.delete(*table.get_children())
            for i in range(len(points)):
                points[i][2] = i + 1
                table.insert("", END, values=(points[i][2], points[i][0], points[i][1]))
            decision()

        point.bind('<Return>', command)

        point.mainloop()

    except Exception as ex:
        print(ex)
        messagebox.showerror('Ошибка', 'Точка не выбрана')


def getPoint():
    point = Tk()
    point.title('Добавить точку')
    point['bg'] = 'white'
    point.resizable(height=0, width=0)

    pointX = Entry(point, font=("Calibri", 14), fg='grey', justify=RIGHT, width=12, bd=2)
    pointX.insert(0, 'Координата x:')

    def clearFieldX(event):
        pointX.delete(0, END)
        pointX.config(validate="key", fg='black')

    pointX.bind('<Button>', clearFieldX)
    pointX['validatecommand'] = (pointX.register(checkSymbol), '%S')
    pointX.grid(row=0)

    pointY = Entry(point, font=("Calibri", 14), fg='grey', justify=RIGHT, width=12, bd=2)
    pointY.insert(0, 'Координата y:')

    def clearFieldY(event):
        pointY.delete(0, END)
        pointY.config(validate="key", fg='black')

    pointY.bind('<Button>', clearFieldY)
    pointY['validatecommand'] = (pointY.register(checkSymbol), '%S')
    pointY.grid(row=1)

    def command(event):
        insertPoint(pointX.get(), pointY.get(), len(points) + 1)
        point.destroy()

    point.bind('<Return>', command)

    point.mainloop()


def checkSymbol(symbol):
    if symbol in ['1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '.', '-']:
        return True
    else:
        window.bell()
        return False


def insertPoint(x, y, num):
    try:
        x = float(x)
        y = float(y)
        points.append([x, y, num])
        table.insert("", END, values=(num, x, y))
        decision()
    except Exception as ex:
        print(ex)
        messagebox.showerror('Ошибка', 'Неверноый ввод')


def deletePoint():
    try:
        index = int(table.item(table.selection()[0], option="values")[0])
        table.delete(table.selection()[0])
        points.pop(index - 1)
        table.delete(*table.get_children())
        for i in range(len(points)):
            points[i][2] = i + 1
            table.insert("", END, values=(points[i][2], points[i][0], points[i][1]))
        decision()
    except Exception as ex:
        print(ex)
        if str(ex) == "pop from empty list":
            messagebox.showerror('Ошибка', 'Список точек пуст')
        elif str(ex) == 'tuple index out of range':
            messagebox.showerror('Ошибка', 'Точка не выбрана')


def decision():
    canvas.delete("all")
    drawBasics()
    drawElements()
    if len(points) > 2:
        a, b, c = triangleSizes(points[0], points[1], points[2])
        answer = 0
        if a + b > c + 0.00000001 and a + c > b + 0.00000001 and b + c > a + 0.00000001:
            answer = triangleArea(a, b, c) - circleArea(a, b, c)
        answerPoints = [0, 1, 2]
        for i in range(len(points) - 2):
            for j in range(i + 1, len(points) - 1, 1):
                for k in range(j + 1, len(points), 1):
                    a, b, c = triangleSizes(points[i], points[j], points[k])
                    if a + b > c + 0.00000001 and a + c > b + 0.00000001 and b + c > a + 0.00000001:
                        dif = triangleArea(a, b, c) - circleArea(a, b, c)
                        if dif < answer and dif != 0:
                            answer = dif
                            answerPoints = [i, j, k]
                        elif answer == 0:
                            answer = dif
                            answerPoints = [i, j, k]
        if answer == 0:
            answerText.config(text='Все точки лежат\nна одной прямой\nили в одной точке')
        else:
            answerText.config(text='№ ' + str(points[answerPoints[0]][2]) + '\nx = ' + str(
                points[answerPoints[0]][0]) + '; y = ' + str(points[answerPoints[0]][1]) + '\n№ ' + str(
                points[answerPoints[1]][2]) + '\nx = ' + str(points[answerPoints[1]][0]) + '; y = ' + str(
                points[answerPoints[1]][1]) + '\n№ ' + str(points[answerPoints[2]][2]) + '\nx = ' + str(
                points[answerPoints[2]][0]) + '; y = ' + str(points[answerPoints[2]][1]) + '\nS = ' + str(answer))
            drawTriangle(answerPoints[0], answerPoints[1], answerPoints[2])
    else:
        answerText.config(text='Недостаточно\nточек')


def circleArea(a, b, c):
    p = (a + b + c) / 2
    r = (((p - a) * (p - b) * (p - c)) / p) ** 0.5
    return pi * r ** 2


def triangleArea(a, b, c):
    p = (a + b + c) / 2
    return (p * (p - a) * (p - b) * (p - c)) ** 0.5


def triangleSizes(point1, point2, point3):
    a = ((point1[0] - point2[0]) ** 2 + (point1[1] - point2[1]) ** 2) ** 0.5
    b = ((point2[0] - point3[0]) ** 2 + (point2[1] - point3[1]) ** 2) ** 0.5
    c = ((point3[0] - point1[0]) ** 2 + (point3[1] - point1[1]) ** 2) ** 0.5
    return a, b, c


def drawTriangle(i, j, k):
    canvas.delete("all")
    drawBasics()
    drawElements()
    x1, y1, x2, y2, x3, y3 = points[i][0], points[i][1], points[j][0], points[j][1], points[k][0], points[k][1]
    while float(canvas.cget('width')) + 25 > (max(x1, x2, x3) - min(x1, x2, x3)):
        x1 *= 1.1
        y1 *= 1.1
        x2 *= 1.1
        y2 *= 1.1
        x3 *= 1.1
        y3 *= 1.1
    while float(canvas.cget('width')) - 25 < (max(x1, x2, x3) - min(x1, x2, x3)):
        x1 /= 1.1
        y1 /= 1.1
        x2 /= 1.1
        y2 /= 1.1
        x3 /= 1.1
        y3 /= 1.1
    while float(canvas.cget('height')) - 25 < (max(y1, y2, y3) - min(y1, y2, y3)):
        x1 /= 1.1
        y1 /= 1.1
        x2 /= 1.1
        y2 /= 1.1
        x3 /= 1.1
        y3 /= 1.1
    x1, y1, x2, y2, x3, y3 = moveTriangle(x1, y1, x2, y2, x3, y3)
    x1 += 20
    x2 += 20
    x3 += 20
    y1 += 20
    y2 += 20
    y3 += 20

    canvas.create_polygon(x1, -y1 + 2 * maxY, x2, -y2 + 2 * maxY, x3, -y3 + 2 * maxY, fill='', outline='blue')

    a, b, c = triangleSizes([x1, y1], [x2, y2], [x3, y3])
    p = (a + b + c) / 2
    S = 0.5 * abs(((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1)))
    r = S / p
    x0 = (x1 * b + x2 * c + x3 * a) / (a + b + c)
    y0 = (y1 * b + y2 * c + y3 * a) / (a + b + c)
    canvas.create_oval(x0 - r, -y0 + 2 * maxY - r, x0 + r, -y0 + 2 * maxY + r, fill='', outline='red')

    deltaX, deltaY = numberPosition(x0, y0, x1, y1)
    canvas.create_oval(x1 - 3, -y1 + 2 * maxY - 3, x1 + 3, -y1 + 2 * maxY + 3, fill='blue')
    canvas.create_text(x1 + deltaX, -y1 + 2 * maxY - deltaY, text=str(i + 1))

    deltaX, deltaY = numberPosition(x0, y0, x2, y2)
    canvas.create_oval(x2 - 3, -y2 + 2 * maxY - 3, x2 + 3, -y2 + 2 * maxY + 3, fill='blue')
    canvas.create_text(x2 + deltaX, -y2 + 2 * maxY - deltaY, text=str(j + 1))

    deltaX, deltaY = numberPosition(x0, y0, x3, y3)
    canvas.create_oval(x3 - 3, -y3 + 2 * maxY - 3, x3 + 3, -y3 + 2 * maxY + 3, fill='blue')
    canvas.create_text(x3 + deltaX, -y3 + 2 * maxY - deltaY, text=str(k + 1))


# передвигает изображение в первую четверть
def moveTriangle(x1, y1, x2, y2, x3, y3):
    difX = min(x1, x2, x3)
    difY = min(y1, y2, y3)
    x1 -= difX
    x2 -= difX
    x3 -= difX
    y1 -= difY
    y2 -= difY
    y3 -= difY
    return x1, y1, x2, y2, x3, y3


def numberPosition(x0, y0, xp, yp):
    if x0 < xp and y0 < yp:
        return 7, 7
    elif x0 > xp and y0 > yp:
        return -7, -7
    elif x0 < xp and y0 > yp:
        return 7, -7
    elif x0 > xp and y0 < yp:
        return -7, 7


def clearAll():
    canvas.delete("all")
    points.clear()
    table.delete(*table.get_children())
    drawBasics()
    drawElements()
    answerText.config(text='---')


if __name__ == '__main__':
    window = Tk()
    window.title('Лабораторная работа 1')
    window.resizable(width=False, height=False)
    window.attributes('-fullscreen', True)
    window['bg'] = 'white'

    canvas = Canvas(window, width=maxX * 2, height=maxY * 2, bg='white')
    canvas.grid(column=0, row=0, columnspan=1, rowspan=7)

    table = Treeview(window, show="headings", columns=("#1", "#2", "#3"), height=20)
    table.column("#1", width=65)
    table.column("#2", width=65)
    table.column("#3", width=65)
    table.heading("#1", text="№")
    table.heading("#2", text="x")
    table.heading("#3", text="y")
    table.grid(column=1, row=0, rowspan=1, columnspan=1)

    answerLabel = Label(window, width=10, font=('Courier New', 20, 'bold'), text='ОТВЕТ')
    answerLabel.grid(column=1, row=5, rowspan=1, columnspan=1)
    answerText = Label(window, width=25, font=('Courier New', 12, 'bold'), text='---')
    answerText.grid(column=1, row=6, rowspan=1, columnspan=1)

    drawBasics()
    drawElements()

    window.mainloop()
