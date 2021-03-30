import numpy as np
import matplotlib.pyplot as plt

def f (x):
	return 10 * x**2

def grad_descent(lr, x = 5, epohs=20):
	global f
	steps = []
	for i in np.arange(epohs):
		steps.append(x)
		grad = 20*x
		x = x - lr*grad
	return np.array(steps)	

xnew = np.arange(-5, 5, 0.1)
ynew = f(xnew)
x = grad_descent(0.01)

plt.scatter(x, f(x), marker = '*', color = 'r')

plt.plot(xnew, ynew)	
plt.show()