from tkinter import *
from tkinter import messagebox
from math import sin, cos, radians, sqrt
from numpy import arange

maxX = 555
maxY = 390

circle = []
circlePrevious = []

smallCircle = []
smallCirclePrevious = []

arc1 = []
arc1Previous = []
arc2 = []
arc2Previous = []
arcLine1 = [[], []]
arcLine2 = [[], []]

leftLeg = [[], []]
rightLeg = [[], []]

secondLine = [[], []]
hourLine = [[], []]

leftLine = [[], []]
topLine = [[], []]
rightLine = [[], []]
bottomLine = [[], []]


def createStart():
    # Вехняя полуокружность
    for i in range(-50, 51):
        circle.append([i, -sqrt(2500 - (i * i))])
    # Нижняя полуокружность
    for i in range(50, -51, -1):
        circle.append([i, sqrt(2500 - (i * i))])
    # Перенос в центр
    for i in circle:
        i[0] += maxX
        i[1] += maxY
    # Вехняя полуокружность
    for i in arange(-10, 10.25, 0.25):
        smallCircle.append([i, -sqrt(100 - (i * i))])
    # Нижняя полуокружность
    for i in arange(10, -10.25, -0.25):
        smallCircle.append([i, sqrt(100 - (i * i))])
    # Перенос в центр
    for i in smallCircle:
        i[0] += maxX
        i[1] += maxY - 80
    # Дуги эллипсов
    for i in range(-40, 41):
        arc1.append([i, -sqrt(1600 - 0.5 * (i * i))])
        arc2.append([i, -sqrt(1600 - 0.5 * (i * i))])
    # Перенос в центр
    for i in arc1:
        i[0] += maxX
        i[1] += maxY - 30
    for i in arc2:
        i[0] += maxX
        i[1] += maxY - 20
    # Линии, соединяющие дуги
    global arcLine1, arcLine2, leftLeg, rightLeg, secondLine, hourLine, leftLine, rightLine, topLine, bottomLine
    arcLine1 = [[], [arc1[0][0], arc1[0][1], arc2[0][0], arc2[0][1]]]
    arcLine2 = [[], [arc1[-1][0], arc1[-1][1], arc2[-1][0], arc2[-1][1]]]

    leftLeg = [[], [circle[170][0], circle[170][1], maxX - 30, maxY + 70]]
    rightLeg = [[], [circle[130][0], circle[130][1], maxX + 30, maxY + 70]]

    secondLine = [[], [maxX, maxY, maxX, maxY - 30]]
    hourLine = [[], [maxX, maxY, maxX + 20, maxY]]

    leftLine = [[], [maxX - 50, maxY, maxX - 40, maxY]]
    topLine = [[], [maxX, maxY - 50, maxX, maxY - 40]]
    rightLine = [[], [maxX + 40, maxY, maxX + 50, maxY]]
    bottomLine = [[], [maxX, maxY + 40, maxX, maxY + 50]]


def makeAxes():
    # ось у
    canvas.create_line(maxX, maxX * 2, maxX, 0, width=1, fill='light gray', arrow=LAST)
    # ось х
    canvas.create_line(0, maxY, maxX * 2, maxY, width=1, fill='light gray', arrow=LAST)
    # maximum
    canvas.create_text(maxX * 2 - 10, maxY - 10, text=str(maxX), fill='light gray')
    canvas.create_text(maxX + 18, 8, text=str(maxY), fill='light gray')
    # minimum
    canvas.create_text(17, maxY - 10, text=str(-maxX), fill='light gray')
    canvas.create_text(maxX + 18, 2 * maxY - 5, text=str(-maxY), fill='light gray')


def drawElements():
    def getMove():
        x = moveX.get()
        y = moveY.get()
        if x == '' or y == '':
            messagebox.showerror('Ошибка', 'Пропущены данные')
        else:
            try:
                move(float(x), float(y))
            except Exception as ex:
                print(ex)
                messagebox.showerror('Ошибка', 'Некорректные данные')

    def getTurn():
        degree = turnDegree.get()
        x = turnX.get()
        y = turnY.get()
        if x == '' or y == '' or degree == '':
            messagebox.showerror('Ошибка', 'Пропущены данные')
        else:
            try:
                turn(float(degree), float(x) + maxX, float(y) + maxY)
            except Exception as ex:
                print(ex)
                messagebox.showerror('Ошибка', 'Некорректные данные')

    def getScale():
        x = scaleX.get()
        y = scaleY.get()
        kx = scaleKX.get()
        ky = scaleKY.get()
        if x == '' or y == '' or kx == '' or ky == '':
            messagebox.showerror('Ошибка', 'Пропущены данные')
        else:
            try:
                scale(float(x) + maxX, float(y) + maxY, float(kx), float(ky))
            except Exception as ex:
                print(ex)
                messagebox.showerror('Ошибка', 'Некорректные данные')

    makeAxes()

    moveX = Entry(font=("Calibri", 14), justify=RIGHT, width=22, bd=2, validate="key")
    moveX['validatecommand'] = (moveX.register(checkSymbol), '%S')
    moveY = Entry(font=("Calibri", 14), justify=RIGHT, width=22, bd=2, validate="key")
    moveY['validatecommand'] = (moveY.register(checkSymbol), '%S')

    turnDegree = Entry(font=("Calibri", 14), justify=RIGHT, width=22, bd=2, validate="key")
    turnDegree['validatecommand'] = (turnDegree.register(checkSymbol), '%S')
    turnX = Entry(font=("Calibri", 14), justify=RIGHT, width=22, bd=2, validate="key")
    turnX['validatecommand'] = (turnX.register(checkSymbol), '%S')
    turnY = Entry(font=("Calibri", 14), justify=RIGHT, width=22, bd=2, validate="key")
    turnY['validatecommand'] = (turnY.register(checkSymbol), '%S')

    scaleX = Entry(font=("Calibri", 14), justify=RIGHT, width=22, bd=2, validate="key")
    scaleX['validatecommand'] = (scaleX.register(checkSymbol), '%S')
    scaleY = Entry(font=("Calibri", 14), justify=RIGHT, width=22, bd=2, validate="key")
    scaleY['validatecommand'] = (scaleY.register(checkSymbol), '%S')
    scaleKX = Entry(font=("Calibri", 14), justify=RIGHT, width=22, bd=2, validate="key")
    scaleKX['validatecommand'] = (scaleKX.register(checkSymbol), '%S')
    scaleKY = Entry(font=("Calibri", 14), justify=RIGHT, width=22, bd=2, validate="key")
    scaleKY['validatecommand'] = (scaleKY.register(checkSymbol), '%S')

    Label(text='Изменение X:', font=("Calibri", 14)).grid(column=1, row=1)
    Label(text='Изменение Y:', font=("Calibri", 14)).grid(column=1, row=2)
    Label(text='Угол поворота:', font=("Calibri", 14)).grid(column=1, row=4)
    Label(text='Центр X:', font=("Calibri", 14)).grid(column=1, row=5)
    Label(text='Центр Y:', font=("Calibri", 14)).grid(column=1, row=6)
    Label(text='Центр X:', font=("Calibri", 14)).grid(column=1, row=8)
    Label(text='Центр Y:', font=("Calibri", 14)).grid(column=1, row=9)
    Label(text='Изменение X:', font=("Calibri", 14)).grid(column=1, row=10)
    Label(text='Изменение Y:', font=("Calibri", 14)).grid(column=1, row=11)

    addPointButton = Button(window, text="Перенос", width=22, height=1, command=getMove)
    turnButton = Button(window, text="Поворот", width=22, height=1, command=getTurn)
    scaleButton = Button(window, text="Масштабирование", width=22, height=1, command=getScale)
    returnButton = Button(window, text="Предыдущее изображение", width=22, height=1, command=returnArray)
    clearAllButton = Button(window, text="Исходное изображение", width=22, height=1, command=clearAll)

    moveX.grid(column=2, row=1)
    moveY.grid(column=2, row=2)
    addPointButton.grid(column=2, row=3)

    turnDegree.grid(column=2, row=4)
    turnX.grid(column=2, row=5)
    turnY.grid(column=2, row=6)
    turnButton.grid(column=2, row=7)

    scaleX.grid(column=2, row=8)
    scaleY.grid(column=2, row=9)
    scaleKX.grid(column=2, row=10)
    scaleKY.grid(column=2, row=11)
    scaleButton.grid(column=2, row=12)

    returnButton.grid(column=2, row=13)
    clearAllButton.grid(column=2, row=14)


def checkSymbol(symbol):
    if symbol in ['1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '.', '-']:
        return True
    else:
        window.bell()
        return False


def clearAll():
    canvas.delete("all")
    drawElements()

    global leftLeg, rightLeg, secondLine, hourLine, leftLine, topLine, rightLine, bottomLine, arcLine1, arcLine2, circle, circlePrevious, arc1, arc2, arc1Previous, arc2Previous, smallCircle, smallCirclePrevious

    circle = []
    circlePrevious = []
    smallCircle = []
    smallCirclePrevious = []
    arc1 = []
    arc1Previous = []
    arc2 = []
    arc2Previous = []
    arcLine1 = [[], []]
    arcLine2 = [[], []]
    leftLeg = [[], []]
    rightLeg = [[], []]
    secondLine = [[], []]
    hourLine = [[], []]
    leftLine = [[], []]
    topLine = [[], []]
    rightLine = [[], []]
    bottomLine = [[], []]

    createStart()

    drawClock()


def move(deltaX, deltaY):
    moveArray()

    for point in circle:
        point[0] += deltaX
        point[1] += deltaY

    for point in smallCircle:
        point[0] += deltaX
        point[1] += deltaY

    for point in arc1:
        point[0] += deltaX
        point[1] += deltaY

    for point in arc2:
        point[0] += deltaX
        point[1] += deltaY

    arcLine1[1][0] += deltaX
    arcLine1[1][1] += deltaY
    arcLine1[1][2] += deltaX
    arcLine1[1][3] += deltaY

    arcLine2[1][0] += deltaX
    arcLine2[1][1] += deltaY
    arcLine2[1][2] += deltaX
    arcLine2[1][3] += deltaY

    leftLeg[1][0] += deltaX
    leftLeg[1][1] += deltaY
    leftLeg[1][2] += deltaX
    leftLeg[1][3] += deltaY

    rightLeg[1][0] += deltaX
    rightLeg[1][1] += deltaY
    rightLeg[1][2] += deltaX
    rightLeg[1][3] += deltaY

    secondLine[1][0] += deltaX
    secondLine[1][1] += deltaY
    secondLine[1][2] += deltaX
    secondLine[1][3] += deltaY

    hourLine[1][0] += deltaX
    hourLine[1][1] += deltaY
    hourLine[1][2] += deltaX
    hourLine[1][3] += deltaY

    leftLine[1][0] += deltaX
    leftLine[1][1] += deltaY
    leftLine[1][2] += deltaX
    leftLine[1][3] += deltaY

    topLine[1][0] += deltaX
    topLine[1][1] += deltaY
    topLine[1][2] += deltaX
    topLine[1][3] += deltaY

    rightLine[1][0] += deltaX
    rightLine[1][1] += deltaY
    rightLine[1][2] += deltaX
    rightLine[1][3] += deltaY

    bottomLine[1][0] += deltaX
    bottomLine[1][1] += deltaY
    bottomLine[1][2] += deltaX
    bottomLine[1][3] += deltaY

    canvas.delete("all")
    makeAxes()
    drawClock()


def turn(degree, x, y):
    moveArray()
    cosinus = cos(radians(degree))
    sinus = sin(radians(degree))

    for point in circle:
        tempX = point[0]
        point[0] = x + (point[0] - x) * cosinus + (point[1] - y) * sinus
        point[1] = y + (point[1] - y) * cosinus - (tempX - x) * sinus

    for point in smallCircle:
        tempX = point[0]
        point[0] = x + (point[0] - x) * cosinus + (point[1] - y) * sinus
        point[1] = y + (point[1] - y) * cosinus - (tempX - x) * sinus

    for point in arc1:
        tempX = point[0]
        point[0] = x + (point[0] - x) * cosinus + (point[1] - y) * sinus
        point[1] = y + (point[1] - y) * cosinus - (tempX - x) * sinus

    for point in arc2:
        tempX = point[0]
        point[0] = x + (point[0] - x) * cosinus + (point[1] - y) * sinus
        point[1] = y + (point[1] - y) * cosinus - (tempX - x) * sinus

    tempX = arcLine1[1][0]
    arcLine1[1][0] = x + (arcLine1[1][0] - x) * cosinus + (arcLine1[1][1] - y) * sinus
    arcLine1[1][1] = y + (arcLine1[1][1] - y) * cosinus - (tempX - x) * sinus
    tempX = arcLine1[1][2]
    arcLine1[1][2] = x + (arcLine1[1][2] - x) * cosinus + (arcLine1[1][3] - y) * sinus
    arcLine1[1][3] = y + (arcLine1[1][3] - y) * cosinus - (tempX - x) * sinus

    tempX = arcLine2[1][0]
    arcLine2[1][0] = x + (arcLine2[1][0] - x) * cosinus + (arcLine2[1][1] - y) * sinus
    arcLine2[1][1] = y + (arcLine2[1][1] - y) * cosinus - (tempX - x) * sinus
    tempX = arcLine2[1][2]
    arcLine2[1][2] = x + (arcLine2[1][2] - x) * cosinus + (arcLine2[1][3] - y) * sinus
    arcLine2[1][3] = y + (arcLine2[1][3] - y) * cosinus - (tempX - x) * sinus

    tempX = leftLeg[1][0]
    leftLeg[1][0] = x + (leftLeg[1][0] - x) * cosinus + (leftLeg[1][1] - y) * sinus
    leftLeg[1][1] = y + (leftLeg[1][1] - y) * cosinus - (tempX - x) * sinus
    tempX = leftLeg[1][2]
    leftLeg[1][2] = x + (leftLeg[1][2] - x) * cosinus + (leftLeg[1][3] - y) * sinus
    leftLeg[1][3] = y + (leftLeg[1][3] - y) * cosinus - (tempX - x) * sinus

    tempX = rightLeg[1][0]
    rightLeg[1][0] = x + (rightLeg[1][0] - x) * cosinus + (rightLeg[1][1] - y) * sinus
    rightLeg[1][1] = y + (rightLeg[1][1] - y) * cosinus - (tempX - x) * sinus
    tempX = rightLeg[1][2]
    rightLeg[1][2] = x + (rightLeg[1][2] - x) * cosinus + (rightLeg[1][3] - y) * sinus
    rightLeg[1][3] = y + (rightLeg[1][3] - y) * cosinus - (tempX - x) * sinus

    tempX = secondLine[1][0]
    secondLine[1][0] = x + (secondLine[1][0] - x) * cosinus + (secondLine[1][1] - y) * sinus
    secondLine[1][1] = y + (secondLine[1][1] - y) * cosinus - (tempX - x) * sinus
    tempX = secondLine[1][2]
    secondLine[1][2] = x + (secondLine[1][2] - x) * cosinus + (secondLine[1][3] - y) * sinus
    secondLine[1][3] = y + (secondLine[1][3] - y) * cosinus - (tempX - x) * sinus

    tempX = hourLine[1][0]
    hourLine[1][0] = x + (hourLine[1][0] - x) * cosinus + (hourLine[1][1] - y) * sinus
    hourLine[1][1] = y + (hourLine[1][1] - y) * cosinus - (tempX - x) * sinus
    tempX = hourLine[1][2]
    hourLine[1][2] = x + (hourLine[1][2] - x) * cosinus + (hourLine[1][3] - y) * sinus
    hourLine[1][3] = y + (hourLine[1][3] - y) * cosinus - (tempX - x) * sinus

    tempX = leftLine[1][0]
    leftLine[1][0] = x + (leftLine[1][0] - x) * cosinus + (leftLine[1][1] - y) * sinus
    leftLine[1][1] = y + (leftLine[1][1] - y) * cosinus - (tempX - x) * sinus
    tempX = leftLine[1][2]
    leftLine[1][2] = x + (leftLine[1][2] - x) * cosinus + (leftLine[1][3] - y) * sinus
    leftLine[1][3] = y + (leftLine[1][3] - y) * cosinus - (tempX - x) * sinus

    tempX = topLine[1][0]
    topLine[1][0] = x + (topLine[1][0] - x) * cosinus + (topLine[1][1] - y) * sinus
    topLine[1][1] = y + (topLine[1][1] - y) * cosinus - (tempX - x) * sinus
    tempX = topLine[1][2]
    topLine[1][2] = x + (topLine[1][2] - x) * cosinus + (topLine[1][3] - y) * sinus
    topLine[1][3] = y + (topLine[1][3] - y) * cosinus - (tempX - x) * sinus

    tempX = rightLine[1][0]
    rightLine[1][0] = x + (rightLine[1][0] - x) * cosinus + (rightLine[1][1] - y) * sinus
    rightLine[1][1] = y + (rightLine[1][1] - y) * cosinus - (tempX - x) * sinus
    tempX = rightLine[1][2]
    rightLine[1][2] = x + (rightLine[1][2] - x) * cosinus + (rightLine[1][3] - y) * sinus
    rightLine[1][3] = y + (rightLine[1][3] - y) * cosinus - (tempX - x) * sinus

    tempX = bottomLine[1][0]
    bottomLine[1][0] = x + (bottomLine[1][0] - x) * cosinus + (bottomLine[1][1] - y) * sinus
    bottomLine[1][1] = y + (bottomLine[1][1] - y) * cosinus - (tempX - x) * sinus
    tempX = bottomLine[1][2]
    bottomLine[1][2] = x + (bottomLine[1][2] - x) * cosinus + (bottomLine[1][3] - y) * sinus
    bottomLine[1][3] = y + (bottomLine[1][3] - y) * cosinus - (tempX - x) * sinus

    canvas.delete("all")
    makeAxes()
    drawClock()


def scale(x, y, kx, ky):
    moveArray()

    for point in circle:
        point[0] = point[0] * kx + x * (1 - kx)
        point[1] = point[1] * ky + y * (1 - ky)

    for point in smallCircle:
        point[0] = point[0] * kx + x * (1 - kx)
        point[1] = point[1] * ky + y * (1 - ky)

    for point in arc1:
        point[0] = point[0] * kx + x * (1 - kx)
        point[1] = point[1] * ky + y * (1 - ky)

    for point in arc2:
        point[0] = point[0] * kx + x * (1 - kx)
        point[1] = point[1] * ky + y * (1 - ky)

    arcLine1[1][0] = kx * arcLine1[1][0] + x * (1 - kx)
    arcLine1[1][1] = ky * arcLine1[1][1] + y * (1 - ky)
    arcLine1[1][2] = kx * arcLine1[1][2] + x * (1 - kx)
    arcLine1[1][3] = ky * arcLine1[1][3] + y * (1 - ky)

    arcLine2[1][0] = kx * arcLine2[1][0] + x * (1 - kx)
    arcLine2[1][1] = ky * arcLine2[1][1] + y * (1 - ky)
    arcLine2[1][2] = kx * arcLine2[1][2] + x * (1 - kx)
    arcLine2[1][3] = ky * arcLine2[1][3] + y * (1 - ky)

    leftLeg[1][0] = kx * leftLeg[1][0] + x * (1 - kx)
    leftLeg[1][1] = ky * leftLeg[1][1] + y * (1 - ky)
    leftLeg[1][2] = kx * leftLeg[1][2] + x * (1 - kx)
    leftLeg[1][3] = ky * leftLeg[1][3] + y * (1 - ky)

    rightLeg[1][0] = kx * rightLeg[1][0] + x * (1 - kx)
    rightLeg[1][1] = ky * rightLeg[1][1] + y * (1 - ky)
    rightLeg[1][2] = kx * rightLeg[1][2] + x * (1 - kx)
    rightLeg[1][3] = ky * rightLeg[1][3] + y * (1 - ky)

    secondLine[1][0] = kx * secondLine[1][0] + x * (1 - kx)
    secondLine[1][1] = ky * secondLine[1][1] + y * (1 - ky)
    secondLine[1][2] = kx * secondLine[1][2] + x * (1 - kx)
    secondLine[1][3] = ky * secondLine[1][3] + y * (1 - ky)

    hourLine[1][0] = kx * hourLine[1][0] + x * (1 - kx)
    hourLine[1][1] = ky * hourLine[1][1] + y * (1 - ky)
    hourLine[1][2] = kx * hourLine[1][2] + x * (1 - kx)
    hourLine[1][3] = ky * hourLine[1][3] + y * (1 - ky)

    leftLine[1][0] = kx * leftLine[1][0] + x * (1 - kx)
    leftLine[1][1] = ky * leftLine[1][1] + y * (1 - ky)
    leftLine[1][2] = kx * leftLine[1][2] + x * (1 - kx)
    leftLine[1][3] = ky * leftLine[1][3] + y * (1 - ky)

    topLine[1][0] = kx * topLine[1][0] + x * (1 - kx)
    topLine[1][1] = ky * topLine[1][1] + y * (1 - ky)
    topLine[1][2] = kx * topLine[1][2] + x * (1 - kx)
    topLine[1][3] = ky * topLine[1][3] + y * (1 - ky)

    rightLine[1][0] = kx * rightLine[1][0] + x * (1 - kx)
    rightLine[1][1] = ky * rightLine[1][1] + y * (1 - ky)
    rightLine[1][2] = kx * rightLine[1][2] + x * (1 - kx)
    rightLine[1][3] = ky * rightLine[1][3] + y * (1 - ky)

    bottomLine[1][0] = kx * bottomLine[1][0] + x * (1 - kx)
    bottomLine[1][1] = ky * bottomLine[1][1] + y * (1 - ky)
    bottomLine[1][2] = kx * bottomLine[1][2] + x * (1 - kx)
    bottomLine[1][3] = ky * bottomLine[1][3] + y * (1 - ky)

    canvas.delete("all")
    makeAxes()
    drawClock()


def moveArray():
    global circle, circlePrevious, arc1Previous, arc2Previous, arc1, arc2, smallCircle, smallCirclePrevious
    circlePrevious = [i[:] for i in circle]
    arc1Previous = [i[:] for i in arc1]
    arc2Previous = [i[:] for i in arc2]
    smallCirclePrevious = [i[:] for i in smallCircle]
    arcLine1[0] = arcLine1[1][:]
    arcLine2[0] = arcLine2[1][:]
    leftLeg[0] = leftLeg[1][:]
    rightLeg[0] = rightLeg[1][:]
    secondLine[0] = secondLine[1][:]
    hourLine[0] = hourLine[1][:]
    leftLine[0] = leftLine[1][:]
    topLine[0] = topLine[1][:]
    rightLine[0] = rightLine[1][:]
    bottomLine[0] = bottomLine[1][:]


def returnArray():
    global circle, circlePrevious, arc1, arc2, arc1Previous, arc2Previous, smallCircle, smallCirclePrevious
    if not circlePrevious:
        messagebox.showerror('Ошибка', 'Предыдущее состояние отсутствует')
    else:
        circle, circlePrevious = [i[:] for i in circlePrevious], [i[:] for i in circle]
        arc1, arc1Previous = [i[:] for i in arc1Previous], [i[:] for i in arc1]
        arc2, arc2Previous = [i[:] for i in arc2Previous], [i[:] for i in arc2]
        smallCircle, smallCirclePrevious = [i[:] for i in smallCirclePrevious], [i[:] for i in smallCircle]
        arcLine1[1], arcLine1[0] = arcLine1[0][:], arcLine1[1][:]
        arcLine2[1], arcLine2[0] = arcLine2[0][:], arcLine2[1][:]
        leftLeg[1], leftLeg[0] = leftLeg[0][:], leftLeg[1][:]
        rightLeg[1], rightLeg[0] = rightLeg[0][:], rightLeg[1][:]
        secondLine[1], secondLine[0] = secondLine[0][:], secondLine[1][:]
        hourLine[1], hourLine[0] = hourLine[0][:], hourLine[1][:]
        leftLine[1], leftLine[0] = leftLine[0][:], leftLine[1][:]
        topLine[1], topLine[0] = topLine[0][:], topLine[1][:]
        rightLine[1], rightLine[0] = rightLine[0][:], rightLine[1][:]
        bottomLine[1], bottomLine[0] = bottomLine[0][:], bottomLine[1][:]

        canvas.delete("all")
        drawClock()


def drawClock():
    # Ножки
    canvas.create_line(leftLeg[1][0], leftLeg[1][1], leftLeg[1][2], leftLeg[1][3])
    canvas.create_line(rightLeg[1][0], rightLeg[1][1], rightLeg[1][2], rightLeg[1][3])
    # Окружности
    for i in range(len(circle) - 1):
        canvas.create_line(circle[i], circle[i + 1], width=1)
    for i in range(len(smallCircle) - 1):
        canvas.create_line(smallCircle[i], smallCircle[i + 1], width=1)
    # Засечки
    canvas.create_line(leftLine[1][0], leftLine[1][1], leftLine[1][2], leftLine[1][3])
    canvas.create_line(topLine[1][0], topLine[1][1], topLine[1][2], topLine[1][3])
    canvas.create_line(rightLine[1][0], rightLine[1][1], rightLine[1][2], rightLine[1][3])
    canvas.create_line(bottomLine[1][0], bottomLine[1][1], bottomLine[1][2], bottomLine[1][3])

    # Стрелки
    canvas.create_line(secondLine[1][0], secondLine[1][1], secondLine[1][2], secondLine[1][3])
    canvas.create_line(hourLine[1][0], hourLine[1][1], hourLine[1][2], hourLine[1][3])

    # Дуги
    for i in range(len(arc1) - 1):
        canvas.create_line(arc1[i], arc1[i + 1], width=1)
    for i in range(len(arc2) - 1):
        canvas.create_line(arc2[i], arc2[i + 1], width=1)

    canvas.create_line(arcLine1[1][0], arcLine1[1][1], arcLine1[1][2], arcLine1[1][3])
    canvas.create_line(arcLine2[1][0], arcLine2[1][1], arcLine2[1][2], arcLine2[1][3])


if __name__ == '__main__':
    window = Tk()
    window.title('Лабораторная работа 2')
    window.attributes('-fullscreen', True)
    window.resizable(height=0, width=0)
    window['bg'] = 'white'

    canvas = Canvas(window, width=maxX * 2, height=maxY * 2, bg='white')
    canvas.grid(column=0, row=0, columnspan=1, rowspan=15)
    drawElements()
    createStart()
    drawClock()

    window.mainloop()
