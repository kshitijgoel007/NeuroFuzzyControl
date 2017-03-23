#!/usr/bin/python

import pylab as pl
import numpy as np
f1 = open('./output_data/MSE.txt', 'r')
f2 = open('./output_data/desired.txt', 'r')
f3 = open('./output_data/results.txt', 'r')
f4 = open('./output_data/MSE_test.txt', 'r')

mse = f1.read()
des = f2.read()
res = f3.read()
mse_test = f4.read()

f1.close()
f2.close()
f3.close()
f4.close()

mse = mse.splitlines()
des = des.splitlines()
res = res.splitlines()
mse_test = mse_test.splitlines()

X = []
Y = []
RES = []
DES = []
MSE_TEST = []

for line in mse:
    xy = line.split()
    X.append(float(xy[0]))
    Y.append(float(xy[1]))
for line in res:
    RES.append(float(line.split()[1]))
for line in des:
    DES.append(float(line))
for line in mse_test:
    MSE_TEST.append(float(line.split()[1]))

pl.figure()
pl.xlabel('epochs')
pl.ylabel('MSE')
pl.title('MSE for training data (60% of total data)')
pl.plot(X,Y, label='Training MSE')
pl.plot(X,MSE_TEST, label='Test MSE')
pl.grid()
pl.figure()
pl.xlabel('Years')
pl.ylabel('Scaled Output')
pl.title('Desired and Forward Pass Output on test data (40% of total data)')
pl.plot(RES[187:], label='result')
pl.plot(DES[187:], label='desired')
pl.legend()
pl.grid()
pl.figure()
pl.xlabel('Years')
pl.ylabel('Scaled Output')
pl.title('Desired and Forward Pass Output on training data (to check overfitting)')
pl.plot(RES[0:186], label='result')
pl.plot(DES[0:186], label='desired')
pl.legend()
pl.grid()
pl.show()

# print(type(data))
# data = np.array(data)
# print(data)
# print(type(data))
# # print(data[0])
# `print(data.size())
