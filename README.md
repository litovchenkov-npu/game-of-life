Реалізація гри Джона конвея "Життя" мовою C++ з використанням бібліотеки SFML.
Гра відбувається у просторі, розділеному на клітинки, кожна з яких може бути "живою" або "мертвою" і має вісім сусідів. Початковий стан - перше покоління. Дія генетичних законів Конвея визначає долю кожної клітинки:
1. З двома чи трьома живими сусідами жива клітина залишається жити.
2. З одним або нулем живих сусідів жива клітина помирає від "самотності".
3. З чотирма чи більше живими сусідами жива клітина помирає від "перенаселення".
4. У мертвої клітини рівно три живих сусіди призводять до її оживлення.

Елементи управління:
1. Ліва кнопка миші - додати/видалити клітину.
2. Пробіл - увімкнути/вимкнути паузу.
3. C - очистити ігрове поле.
4. R - заповнини ігрове поле випадковими клітинами.
