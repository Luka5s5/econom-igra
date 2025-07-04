# Сигма.Экономигра 2021

## Как запустить игру локально?
Данный способ подойдёт для большинства дистрибутивов Linux.
* `git clone https://github.com/Luka5s5/econom-igra.git`
* `sudo apt install -y make g++ gcc build-essential zlib1g-dev libboost-dev libwebsocketpp-dev nlohmann-json3-dev`
* `cd econom-igra`
* `mkdir -p bin`
* `make`
* `./bin/server`

Открыть другой терминал и сделать:
* `cd econom-igra/frontend`
* `python3 -m http.server`

Потом по адресу `localhost:8000` будет доступна админка
Чтобы пользоваться админкой/любыми функциями сайта нужно сначала зайти на страницу `localhost:8000/super-puper-secret.html` -- в бразуере сохранится секретный токен доступа и станут работать все штуки.
