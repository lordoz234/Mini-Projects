from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
import numpy as np

def f(x1, x2):
    return np.sin(x1)**2 + np.sin(x2) ** 2

def grad_descent(lr, num_iter=100, cur_x1=1.5, cur_x2=-1):
    """
    функция, которая реализует градиентный спуск в минимум для функции f от двух переменных. 
        param lr: learning rate алгоритма
        param num_iter: количество итераций градиентного спуска
    """
    global f
    # будем сохранять значения аргументов и значений функции в процессе град. спуска в переменную states
    steps = []
    
    # итерация цикла -- шаг градиентнго спуска
    for iter_num in range(num_iter):
        steps.append([cur_x1, cur_x2, f(cur_x1, cur_x2)])
        
        # чтобы обновить значения cur_x1 и cur_x2, как мы помним с последнего занятия, 
        # нужно найти производные (градиенты) функции f по этим переменным.
        grad_x1 = 2*np.sin(cur_x1)*np.cos(cur_x1)
        grad_x2 = 2*np.sin(cur_x2)*np.cos(cur_x2)
                 
        # после того, как посчитаны производные, можно обновить веса. 
        # не забудьте про lr!
        cur_x1 -= lr*grad_x1
        cur_x2 -= lr*grad_x2
    return np.array(steps)

steps = grad_descent(lr=0.5, num_iter=10)    

path = []

X, Y = np.meshgrid(np.linspace(-3, 3, 100), np.linspace(-3, 3, 100))

fig = plt.figure(figsize=(16, 10))
ax = fig.gca(projection='3d')

ax.plot(xs=steps[:, 0], ys=steps[:, 1], zs=steps[:, 2], marker='*', markersize=20,
                markerfacecolor='y', lw=3, c='black')

ax.plot_surface(X, Y, f(X, Y), cmap=cm.coolwarm)
ax.set_zlim(0, 5)
ax.view_init(elev=60)
plt.show()		