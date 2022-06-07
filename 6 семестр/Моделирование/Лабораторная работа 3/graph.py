import matplotlib.pyplot as plt
import numpy as np


file = open("res.txt", "r")



dist = file.readline().split()

file_line = True

arrs = []

while file_line:
    file_line = file.readline()

    if file_line:
        arrs.append(list(map(float, file_line.split())))


file.close()


arrs = np.array(arrs)
arrs = np.transpose(arrs)

arrs = [list(i) for i in arrs]


labels = ["up", "u"]

for i in range(len(labels)):
    plt.plot(arrs[0], arrs[i+1], label = labels[i])



    
plt.xlabel("Z")
plt.ylabel("u")
plt.legend()

plt.show()

plt.plot(arrs[0], arrs[3], label = "F")
plt.xlabel("Z")
plt.ylabel("F")

plt.show()


plt.plot(arrs[0], arrs[4], label = "F'")
#plt.legend()
plt.xlabel("Z")
plt.ylabel("divF")

plt.show()

file_names = ["../k0.txt", "../p.txt", "../R.txt", "../T0.txt", "../Tw.txt"]
labels = ["u0(k0)", "u0(p)", "u0(R0)", "u0(T0)", "u0(Tw)"]

for i in range(len(file_names)):
    file = open("../" + file_names[i])

    dist = file.readline().split()

    file_line = True

    arrs = []

    while file_line:
        file_line = file.readline()

        if file_line:
            arrs.append(list(map(float, file_line.split())))


    file.close()


    arrs = np.array(arrs)
    arrs = np.transpose(arrs)

    arrs = [list(i) for i in arrs]

    plt.subplot(2, 3, i + 1)
    plt.plot(arrs[0], arrs[1], label = labels[i])
    plt.legend()

plt.show()


