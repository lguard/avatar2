from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import sys
x =[0,0,0,1]
y =[0,1,0,0]
z =[0,0,1,0]
import csv
with open(sys.argv[1]) as csvfile:
    spamreader = csv.reader(csvfile, delimiter=',', quotechar='|')
    for row in spamreader:
        x.append(float(row[0]))
        y.append(float(row[1]))
        z.append(float(row[2]))


fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')





ax.scatter(x, y, z, c='r', marker='o')

ax.set_xlabel('X Label')
ax.set_ylabel('Y Label')
ax.set_zlabel('Z Label')

plt.show()
