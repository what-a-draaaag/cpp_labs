1. Для получения ошибки multiple definition можно объявить в каком-нибудь из файлов функцию с именем уже существующей, например, добавить в файл main.c такую строку:

	double doComputation(int a, double b);


2. Для получения ошибки undefined reference должна произойти ситуация, когда компилятор не нашел определения функции. Чтобы получилась эта ошибка, можно удалить один из файлов util.c, io.c, algorithm.c.