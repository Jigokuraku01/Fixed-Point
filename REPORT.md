| Лабораторная работа №1.1     | 24.Б10                    | Архитектура компьютера |
| :--------------------------- | ------------------------- | ---------------------- |
| Числа с фиксированной точкой | Кашенин Андрей Дмитриевич | 2025                   |

## Инструментарий

- CLang 18 версии
- С++ 23 стандарта

## Что реализовано

Была реализована вся логика, указанная в тз, а именно нижеуказанные операции:

- Сложение
- Разность
- Деление
- Умножение

с такими округлениями:

- округление к 0
- Округление к +inf
- Округление к -inf
- Округление к ближайшему чётному

А также перевод и вывод в десятичной форме ровно с 3 знаками после запятой

# Описание

## 0. [main.cpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/main.cpp)

Более подробные описания всех классов и методов ниже. Тут лишь примерные слова о том что они делают.

1. Мне не нравится работать с char\*\*, поэтому я перевожу argv в vector из string.
2. Далее статический метод класса Parser parse_input_query возвращает мне InputQuery, в которой собраны входные данные
3. Создаётся класс ExpressionHolder, цель которого - хранить InputQuery и выполнить операцию в нём.
4. Вызывается метод solve_and_return_ans, который собственно и должен посчитать ответ и вернуть его в виде строки

Важное замечание: Мне показалось более правильным, если при пробрасывании исключения буддут известны как текст ошибки, так и код ошибки, поэтому я написал свой класс MyException.
Ещё одно важное замечание: Я в лабораторной работе везде с int64, чтобы меньше думать о переполнениях

## 1. [My_exception.hpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/include/my_exception.hpp) и [My_exception.cpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/src/my_exception.cpp)

### Назначение

Содержат реализацию класса MyException, которая нужна для хранения сообщения текста ошибки + кода ошибки. Мне показалось что это может быть полезно(хранение кода ошибки), но в итоге я всё равно завершаюсь с кодом 1. Внутри это просто класс с 2 приватными полями: \_code(типа int) и \_error](типа string) и геттерами на их получение.

EXIT_FAILURE это просто define на 1 из cstdlib

## 2. [input_query.hpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/include/input_query.hpp) и [input_query.cpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/src/input_query.cpp)

### Назначение

Содержат основную информацию о входных значениях, а так же класс InputQuery, цель которого просто абсорбировать входные данные. Информация об округлениях и операциях в соответствующих enum классах: PossibleOperations и PossibleRounding. В InputQuery приватные поля и их геттеры на входные данные:

- \_cnt_for_integer(количество битов на целую часть),
- \_cnt_for_fractional(количество битов на целую часть),
- \_first_number(первое по операции число),
- \_second_number(второе число. Если второго по входным данным нет, то 0),
- \_cur_rounding(текущее округление. Тип - PossibleRounding),
- \_cur_operation(текущая операция. Тип - PossibleOperations. Если операции нет, то PossibleOperations::NO_OPER)

Данные при этом тут никак не обрабатываются с точки зрения логики программы(например обрезание входного числа)
В конструкторе класса значения просто присваиваются полям

## 3. [parser.hpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/include/parser.hpp) и [parser.cpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/src/parser.cpp)

### Назначение

Содержат один класс - parser, цель которого из вектора строк получить InputQuery. Для этого в нём есть методы:

- parse_input_query - Собственно он и должен принимать на вход вектор строк и возвращать InputQuery.

```C++
InputQuery parse_input_query(const std::vector<std::string>&& argv);
```

- parse_to_int - этот метод принимает строку и базу СИ, после чего переводит строку в число по данному основанию.

```C++
  std::int64_t parse_to_int(const std::string& inpStr, std::int64_t base)
```

Теперь по реализации:

#### parse_to_int

[.hpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/include/parser.hpp#L11)
[.cpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/src/parser.cpp#L98)

Использует стандартную функцию std::stoul, которая переводит число из строки в uint64 по нужной базе. \

```C++
std::uint64_t pos = 0;
std::uint64_t result = std::stoul(inpStr, &pos, base);
```

Дальше идёт проверка что прочитали всю строку(останавливается на символе, если он не парсится).

#### parse_input_query

[.hpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/include/parser.hpp#L8)
[.cpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/src/parser.cpp#L10)

Этот метод должен только распарсить данные из строковых в InputQuery. Сначала в нём проверка на количество входных данных. \
Дальше инициализация переменных(инициализированные инициализированы не случайно. Это на случай если операции нет. Те которые не будут инициализировать ся точно будут посчитаны далее при любом раскладе). \
Далее я пытаюсь распарсить выражение вида A.B. Нахожу символ '.' в строке, режу по этому символу и отправляю в метод parse_to_int с основанием 10.

Этот блок кода проверяет что точка вообще есть

```C++
if (pos == std::string::npos) {
        throw MyException(EXIT_FAILURE, "invalid input format: " +
                                            integer_and_fractional_cnt);
    }
```

Дальше парсинг просто парсинг.

- Сначала перевод чисел под целую и дробную части
- Потом проверка что код округления - один символ switch/case по этому символу \
  Далее общая часть для входных данных заканчивается и есть if - else, делящий случаи

```С++
if (argv.size() == 3) {
        first_number = parse_to_int(argv[2], 16);
    }
else{
    ...
}
```

Про случай где нет операции всё понятно - просто парсится нужное число. Второе дефолтное 0 и операция дефолтная NO_OPER => получится сконструировать InputQuery. /
Про случай где операция есть просто аналогичный парсингу округления парсинг операции и парсинг 2 чисел. \

После всего этого создаётся InputQuery и возвращается.

## 3. [expression_holder.hpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/include/expression_holder.hpp) и [expression_holder.cpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/src/expression_holder.cpp)

### Назначение

В этих файлах лежит вся непосредственная логика программы. Т.е. то что будет происходить с данными. \

- get_all_ones_at_inp_bit_cnt - Вспомогательная функция, возвращающая число типа std::uint64, у которого на младших inpCnt(входной параметр) битах единицы

```C++
std::uint64_t get_all_ones_at_inp_bit_cnt(std::int64_t inpCnt);
```

- cut_number - принимает число и сколько надо обрезать. Она не просто берёт cnt_bits младших битов, но так же дополняет "обрезанное число" до 64 бит, т.е. множит старший разряд(чтобы было дополнение до 2-x)

```C++
std::int64_t cut_number(std::int64_t inpNumber, std::int64_t cnt_bits);
```

Самый главный класс этой программы: Expression_Holder. Сначала пройдёмся по полям:

- \_act_first_number и \_act_second_number - это обработанные числа, с которыми и будет работать программа. Обработка в себя включает, например, вышеописанное обрезание и дополнение чисел.

```C++
std::int64_t _act_first_number;
std::int64_t _act_second_number;
```

- \_curInpQuery - это просто поле, содержащее пришедшую InputQuery

```C++
InputQuery _curInpQuery;
```

Теперь методы:

- Конструктор(просто принимает InputQuery)
- solve_and_return_ans - как понятно из названия, должен выполнить что нужно и вернуть ответ-строку

```C++
std::string solve_and_return_ans();
```

- use_oper - применяет операцию, если она есть, и возвращает ответ - число

```C++
std::int64_t use_oper();
```

- round_to_dec. Если дробный ответ X, то этот метод должен привести входной аргумент к формату 1000\*X со всеми необходимыми округлениями(1000 \* X по условию целое число)

```C++
std::int64_t round_to_dec(std::int64_t inp_value);
```

- round_to_bin_and_shift - во время лабораторной я довольно часто должен сдвигать число на сколько-то бит вправо и при этом правильно округлять. Это и делает этот метод: сдвигает, округляет и возвращает полученное число

```C++
std::int64_t round_to_bin_and_shift(std::int64_t inpValue, std::int64_t cntOfBits);
```

- divide - как понятно из названия, этот метод делит первое число на второе со всеми необходимыми округлениями и возвращает ответ (Интересный факт, но round_to_bin_and_shift частный случай divide, но я их всё равно разделил т.к. идеологически divide это операция(как + и -), а round_to_bin_and_shift доп. логика программы)

```C++
std::int64_t divide(std::int64_t big_first_numb,
                        std::int64_t big_second_numb, 
                        bool should_shift_numer = true);
```

## Реализация

Теперь пройдёмся по реализации ExpressionHolder и get_all_ones_at_inp_bit_cnt, cut_number(остальные реализации я описал выше, и они и так понятны)

#### 1. get_all_ones_at_inp_bit_cnt

[.hpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/include/expression_holder.hpp#L24)
[.cpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/src/expression_holder.cpp#L164)

Если количество бит на которых должны быть 1 >= 64, можно заметить, что ответ - просто ~0 \
Иначе Можно не боясь переполнения сдвинуть единицу на inpCnt и вычесть единицу

#### 2. cut_number

[.hpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/include/expression_holder.hpp#L25)
[.cpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/src/expression_holder.cpp#L172)

Сначала число обрезается, используя get_all_ones_at_inp_bit_cnt. Обрезается просто через битовое "и".
Потом я хочу дополнить до всего инта(чтобы удобнее работать). В дополнении до 2-х надо просто размножить старший бит. Проверка старшего бита происходит в ифе, и если он 1, то число делает логическое или с единицами от до конца(это просто разность get_all_ones_at_inp_bit_cnt)

```C++
inpNumber =
            static_cast<std::int64_t>(static_cast<std::uint64_t>(inpNumber) |
                                      (get_all_ones_at_inp_bit_cnt(64) -
                                       get_all_ones_at_inp_bit_cnt(cnt_bits)));
```

## 3. [ExpressionHolder](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/include/expression_holder.hpp#L5)

Теперь сам класс ExpressionHolder:

### 1. Конструктор

[.hpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/include/expression_holder.hpp#L7)
[.cpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/src/expression_holder.cpp#L7)

Принимает InputQuery и конструирует приватный \_curInpQuery как копию, при этом \_act_first_number и \_act_second_number конструирует как входные числа из InputQuery, обрезанные функцией cut_number

### 2. solve_and_return_ans

[.hpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/include/expression_holder.hpp#L8)
[.cpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/src/expression_holder.cpp#L17)

Записывает в локальную переменную ans \_act_first_number, если есть операция, применяет её, после чего приводит ans к строке стандартной функцией to_string, ставит где нужно точку и нули и возвращает(подробные пояснения про формат будут в round_to_dec)

```C++
if (_curInpQuery.get_cur_operation() != PossibleOperations::NO_OPER) {
        ans = use_oper();
    }
```

### 3. round_to_dec

[.hpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/include/expression_holder.hpp#L12)
[.cpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/src/expression_holder.cpp#L158)

Как происходит перевод числа. Пусть дробный ответ X. Этой функции приходит число, которое мы храним в памяти в формате X *(2^(...)). Мы знаем что нужно выводить с 3 знаками после запятой => число X*1000 целое. Моя программа умножает входное число на 1000 и уже после этого сдвигает на степень двойки с необходимым округлением. Т.е. мы получаем верно округлённое число, только умноженное на 1000(именно поэтому нужно было в solve_and_return_ans ставить точку и нули в нужном месте).

### 4. round_to_bin_and_shift

[.hpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/include/expression_holder.hpp#L13)
[.cpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/src/expression_holder.cpp#L186)

Как я писал, это частный случай divide, поэтому он просто вызывает divide с нужным делителем. Однако тут могла возникнуть проблема, что нужно сдвинуть слишком большое число(например при умножении двух 32 битных чисел может получиться 64 бита). В divide в обычной ситуации я сдвигаю числитель, чтобы получилась корректная форма(об этом немного дальше). Но иногда, как, например, в этом случае, числитель сдвигать не надо. Мне надо просто поделить число как int на степень двойки. Поэтому флаг, отвечающий за сдвиг, равен false

```C++
std::int64_t ExpressionHolder::round_to_bin_and_shift(std::int64_t inpValue,
                                                      std::int64_t cntOfBits) {
    return divide(inpValue, 1LL << cntOfBits, false);
}
```

### 5. use_oper

[.hpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/include/expression_holder.hpp#L11)
[.cpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/src/expression_holder.cpp#L31)

Тут пригодится то, что я дополнял число до инта. Благодаря этому я могу работать с входными числами как с обычными интами и всё будет корректно. \
В use_oper у меня просто switch case:

1. PLUS - у меня входные числа в десятичной записи совпадают с обрезанными и дополненными => я могу просто сложить и получить корректный числовой ответ
2. MINUS - аналогично плюсу
3. MULTIPLY - можно просто умножить 2 числа, заранее позаботившись о переполнении(перевод в int64), после чего методом round_to_bin_and_shift сдвинуть вправо (Это из тех соображений что (X \* (2 ^ n))) \* (Y \* (2 ^ n)) = (X \* Y) \* (2 ^ 2n) => нужно для корректного ответа сдвинуть на n битов чтобы сохранить корректность формы
4. DIVIDE - вызывается метод divide

После всех операций важно помнить, что ответ мог переполниться => его нужно опять обрезать и только потом возвращать

### 5. divide

[.hpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/include/expression_holder.hpp#L16)
[.cpp](https://github.com/skkv-mathcs/mathcs-ca-25-fixed-point-Jigokuraku01/blob/f2aa0494be6b183f4da5740c34337a1b9a6843cb/src/expression_holder.cpp#L68)

- Сначала проверка что знаменатель не 0
- Потом я привожу дробное число к стандартной форме(знаменатель >= 0, числитель любого знака)
- Потом происходит сдвиг. Он нужен вот для чего: нам нужно поделить число X / Y. При этом нам дан инвариант, что мы храним X \* 2 ^ (...) и Y \* 2 ^ (...). Просто поделив первое число на второе, мы получим X/Y, но утратим инвариант. Сдвиги сократятся. Поэтому я подумал сдвинуть X(никаких переполнений не будет, т.к. количество битов в дробной части <= 31, а у нас свободно для сдвига благодаря int64 ещё 64 бита). \
  Благодаря такому сдвигу я сохраню инвариант и получу валидный ответ \
  Но этот сдвиг не нужно делать при округлении в сдвиге на степень двойки, поэтому я добавил флаг, говорящий нужно ли сделать сдвиг числителя(это костыль чтобы не копипастить код и не было переполнения)

```C++
 big_first_numb <<= _curInpQuery.get_cnt_for_fractional();
```

- Я буду работать с модульной арифметикой. Далее я просто поделил стандартным делением(Но оно с округлением к 0, что важно помнить).\ Буду хранить что в ans - инвариант ответа

```C++
std::int64_t div_tmp_ans = big_first_numb / big_second_numb;
```

- Потом банальная проверка того, что поделилось нацело. Мне приятнее работать когда остаток при делении не равен 0.
- После этого switch case с возможными округлениями:

1. Округление к 0 - это просто стандартное деление.
2. Округление к -inf. Если частное > 0, то оно совпадает с округлением к 0. Если < 0, нужно вычесть единицу(вот тут пригодилось что нам известно что остаток не 0). Только надо отдельно аккуратно посмотреть если частное = 0. Тогда в зависимости от делимого либо 0, либо -1(делимое > 0, делимое < 0)
3. Округление к +inf - зеркальный случай -inf. Если частное < 0, то оно совпадает с округлением к 0. Если > 0, то надо вычесть единицу. В случае если частное = 0 опять надо аккуратно посмотреть. Там либо 0, либо 1(делимое < 0, делимое > 0)
4. Округление к ближайшему чётному. Тут я буду считать модульной арифметикой. mod - остаток по модулю

```C++
std::int64_t mod = big_first_numb - (big_second_numb * div_tmp_ans);
```

Я заранее для удобства сделал

```C++
ans = div_tmp_ans;
```

Для начала я рассматриваю случай когда числитель > 0. Тогда несложно заметить, что \
Если mod \* 2 < big_second_numb, то это совпадает с округлением к 0. \
Если mod \* 2 > big_second_numb, то нужно прибавить единицу \
Если mod \* 2 == big_second_numb, то у меня число между div_tmp_ans и div_tmp_ans + 1 => нужно посмотреть на младший разряд div_tmp_ans и,если он 1, прибавить 1

Случай когда числитель < 0
Знаменатель > 0 и я хочу сравнивать знаменатель и остаток при делении => я завёл abs_mod. Он равен модулю переменной mod

```C++
std::int64_t abs_mod = mod;
if (abs_mod < 0) {
    abs_mod = -abs_mod;
}
```

Дальше абсолютно аналогичные сравнения. \
Если abs_mod \* 2 < big_second_numb, то это совпадает с округлением к 0. \
Если abs_mod \* 2 > big_second_numb, то нужно уже вычесть 1 \
Если abs_mod \* 2 == big_second_numb, то число-ответ между div_tmp_ans - 1 и div_tmp_ans => если младший бит 1, нужно вычесть единицу(т.к. изначально округление - к 0)
