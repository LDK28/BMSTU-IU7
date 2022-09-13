from telegram import ReplyKeyboardMarkup
from telegram import KeyboardButton

TOKEN = "5436712060:AAFx6kbNWSHeHqxeJX8CMIrZkx6bbkrryAI"
PROXI = "https://telegg.ru/orig/bot"

START_MESSAGE = "Здравствуйте! Вы обратились в бот Главного Юридического Агенства."
HELP_MESSAGE = "Чтобы воспользоваться интерфейсом используйте меню снизу.\n\n" \
               "Контакты: \n" \
               "@DKey28 - разработчик бота\n"
# ADMINS_ID = [735782318, 1021713415, 559633726]
ADMINS_ID = [735782318]


REPLY_MARKUP_START = ReplyKeyboardMarkup(
    keyboard=[
        [KeyboardButton(text="Войти")],
        [KeyboardButton(text="Зарегистрироваться")],
    ],
    resize_keyboard=True,
)

REPLY_MARKUP_MAIN_MENU_LAWYER = ReplyKeyboardMarkup(
    keyboard=[
        [KeyboardButton(text="Список дел")],
        [KeyboardButton(text="Получить все данные по делу")],
        # [KeyboardButton(text="Добавить документ к делу")],
        [KeyboardButton(text="Все близлежащие процессы")],
        [KeyboardButton(text="Свободные дела")],
        [KeyboardButton(text="Взять свободное дело")],
        [KeyboardButton(text="Посмотреть свои данные")],
        [KeyboardButton(text="Выйти")],
    ],
    resize_keyboard=True,
)

REPLY_MARKUP_MAIN_MENU_CUSTOMER = ReplyKeyboardMarkup(
    keyboard=[
        [KeyboardButton(text="Создать дело")],
        [KeyboardButton(text="Получить все данные по делу")],
        # [KeyboardButton(text="Добавить документ к делу")],
        [KeyboardButton(text="Все близлежащие процессы")],
        [KeyboardButton(text="Выйти")],
    ],
    resize_keyboard=True,
)

REPLY_MARKUP_MAIN_MENU_ACCOUNTANT = ReplyKeyboardMarkup(
    keyboard=[
        [KeyboardButton(text="Посмотреть все сделки")],
        [KeyboardButton(text="Добавить сделку")],
        [KeyboardButton(text="Выйти")],
    ],
    resize_keyboard=True,
)
REPLY_MARKUP_MAIN_MENU_ADMIN = ReplyKeyboardMarkup(
    keyboard=[
        [KeyboardButton(text="Добавить пользователя")],
        [KeyboardButton(text="Добавить пользователю права")],
        [KeyboardButton(text="Удалить пользователя")],
        [KeyboardButton(text="Удалить у пользователя права")],
        [KeyboardButton(text="Выйти")],
    ],
    resize_keyboard=True,
)

REPLY_MARKUP_REGISTRATION_CHOOSE_ROLE = ReplyKeyboardMarkup(
    keyboard=[
        [KeyboardButton(text="Юрист")],
        [KeyboardButton(text="Клиент")],
        [KeyboardButton(text="Бухгалтер")]
    ],
    resize_keyboard=True,
)

REPLY_MARKUP_YES_NO = ReplyKeyboardMarkup(
    keyboard=[
        [KeyboardButton(text="Да"), KeyboardButton(text="Нет")],
        [KeyboardButton(text="Вернуться в главное меню...")]
    ],
    resize_keyboard=True
)

REPLY_MARKUP_RETURN = ReplyKeyboardMarkup(
    keyboard=[
        [KeyboardButton(text="Вернуться в главное меню")]
    ],
    resize_keyboard=True
)
