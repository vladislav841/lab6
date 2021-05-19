# Лабораторная работа №6. Безусловный экстремум.
<br>Выполнил студент группы 425</br>
<br>Кузнецов Владислав</br>
## Вариант № 22:
Найти точку минимума функции:
<br>![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/1.png)</br>
<br>![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/2.png)</br>
методом наискорейшего спуска. Для одномерной минимизации использовать метод квадратичной ин-
терполяции. Для поиска интервала унимодальности использовать алгоритм скользящего окна.
В окрестности точки минимума построить линии уровня и траекторию поиска (на одном графике).
## Теоретическая часть:
### Метод наискорейшего спуска:
В этом методе ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/3.jpg)выбирается из условия минимума функции f(x) вдоль направления ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/4.jpg), т.е. <br></br>
![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/5.jpg) 
Таким образом, в методе наискорейшего спуска на каждом шаге необходимо решать задачу минимизации функции одной переменной.
Точная нижняя грань функции ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/6.jpg) на полуоси ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/7.jpg) может и не достигаться.
Но даже, если она достигается, точное определение величины ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/7.jpg) как точки глобального на полуоси минимума  функции ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/8.jpg) не всегда возможно.
Поэтому на практике имеет смысл заменить задачу нахождения ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/10.jpg) задачей отыскания минимума минимума ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/9.jpg) на том или ином (достаточно большом) отрезке от 0 до a.
В случае, когда ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/9.jpg) унимодальна на отрезке от 0 до a, для прибилженного решения последней задачи применяют методы одномерного поиска.
### Метод квадратичной интерполяции:
Здесь задаются пробные три пробные точки ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/11.jpg) <br></br>
Для нахождения точки ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/12.jpg) задается шаг h > 0 в положительном направлении от точки ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/13.jpg), т.е ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/14.jpg) и если ![Image alt](https://github.com/vladislav841/lab6/lab6/blob/master/pic/15.jpg), то ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/16.jpg), иначе ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/17.jpg). <br></br>
Вычисляются значения функции в этих точках ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/18.jpg),
строится квадратичный интерполяционный многочлен по трем точкам и находится его точка миимума по формуле
![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/19.jpg).<br></br>
Находится также точка ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/20.jpg).
Если знаменатель в формуле для нахождения минимума квад- ратичного интерполяционного многочлена равен нулю, т.е. все 
три точки лежат на одной прямой рекомендуется выбрать за ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/21.jpg)
и повторить нахождение точки ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/22.jpg). <br></br>
Критерием окончания этого процесса является выполнение условий для заданного ϵ
![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/23.jpg) <br></br>
Если условия окончания не выполняются и ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/24.jpg)
точка ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/13.jpg) заменяется на точку ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/25.jpg), в противном случае точка ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/13.jpg) заменяется на ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/22.jpg).
### Метод скользящего окна:
Для выбранной исходной точки ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/27.jpg) и выбранного окна шириной 2h > 0 около точки ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/27.jpg) проверяется условие унимодальности <br></br>
![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/28.jpg) 
Если условие выполнено, то считается, что интервал унимодальности найден, в противном случае проверяется условие: 
![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/29.jpg) 
Если последнее выполнено, тогда окно сдвигается вправо от точки x на h/2, иными словами точка x изменяется на точку x=x+h/2.
В противном случае окно сдвигается влево от точки x на h/2, иными словами изменяется на x=x-h/2.
Выбор ширины окна определяется эксперементально и целиком зависит от интуиции исследователя.
## Практическая часть:
Программа состоит из  функций. Функция function это функция от 3 переменных,slidingWindow , KvadrInterpolate ,
 dfdxi - производная функции 
 gradient , NormEvklid , functionOneVariable , step3 ,step4 , step5 , Search и методов построения всех необходимых графиков

## Результаты:

В результате работы программы у функции ![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/1.png) <br></br>
Был найден экстремум методами наискорейшего спуска, квадратичной интерполяции, скользящего окна с точность 0.001.
Ниже приведён рисунок с изображением линий уровня анализируемой функции и траектория поиска экстремума. 
![Image alt](https://github.com/vladislav841/lab6/blob/master/pic/graf.png)



