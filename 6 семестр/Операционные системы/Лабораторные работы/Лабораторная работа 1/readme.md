Сборка:

```bash
gcc -pthread main.c -o app.out
```

Запуск:

```bash
sudo ./app.out
```

Вывод id демона:

```bash
cat /var/run/daemon.pid
```

Вывод списка процессов:

```bash
ps -ajx
```

Вывод log файла:

```bash
cat /var/log/syslog
```
