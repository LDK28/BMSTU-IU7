from glob import glob
from mailbox import Mailbox
import config
from telegram import Update
# from telegram import InlineKeyboardButton
# from telegram import InlineKeyboardMarkup
# from telegram import KeyboardButton
# from telegram import ReplyKeyboardMarkup
# from telegram import  ReplyKeyboardRemove

from telegram.ext import Updater
from telegram.ext import MessageHandler
from telegram.ext import Filters
from telegram.ext import CommandHandler
# from telegram.ext import CallbackQueryHandler
from telegram.ext import CallbackContext


from DB import *

# Statuses
ADMIN = 1
LAWYER = 2
CUSTOMER = 3
ACCOUNTANT = 4

ADMIN_GET_USER = 5

MAIN_MENU = 6
LOGIN_ACCOUNTANT_VERIFY = 7
ADD_MONEY = 8

START = 9

username = ''
password = ''

def get_status_reply(status):
    if status == ADMIN: return config.REPLY_MARKUP_MAIN_MENU_ADMIN
    elif status == LAWYER: return config.REPLY_MARKUP_MAIN_MENU_LAWYER
    elif status == ACCOUNTANT: return config.REPLY_MARKUP_MAIN_MENU_ACCOUNTANT
    elif status == CUSTOMER: return config.REPLY_MARKUP_MAIN_MENU_CUSTOMER


def start(update: Update, context: CallbackContext):
    chat_id_cur = update.effective_message.chat_id
    new_user(chat_id_cur)
    context.bot.send_message(
        chat_id=chat_id_cur,
        text=config.START_MESSAGE,
        reply_markup=config.REPLY_MARKUP_START
    )
    set_step(chat_id_cur, START)

def help(update: Update, context: CallbackContext):
    chat_id_cur = update.effective_message.chat_id
    context.bot.send_message(chat_id=chat_id_cur, text=config.HELP_MESSAGE)


def message(update: Update, context: CallbackContext):
    chat_id_cur = update.effective_message.chat_id
    # context.bot.send_message(chat_id=chat_id_cur,text="I'm in reboot")
    
    step = get_step(chat_id_cur)
    message_text = update.message.text

    # if message_text == "Зарегистрироваться":
    #     context.bot.send_message(chat_id=chat_id_cur,
    #                              text="Обратитесь к администратору для получения логина и пароля")
    if message_text == "Войти":
        if get_username(chat_id_cur) != None:
            repl = get_status_reply(get_status(id=chat_id_cur))
            context.bot.send_message(chat_id=chat_id_cur,
                                    text="Добро пожаловать, " + update.effective_user.first_name,
                                    reply_markup=repl)
            set_step(chat_id_cur, MAIN_MENU)
        else:
            context.bot.send_message(chat_id=chat_id_cur,
                                    text="Вы не состоите в бюро. Обратитесь к администратору за более подробной информацией",
                                    reply_markup=config.REPLY_MARKUP_START)
            set_step(chat_id_cur, START)

    elif message_text == 'Добавить сделку':
        context.bot.send_message(chat_id=chat_id_cur,
                text="Введите <имя клинта, имя юриста, сумму>",
                reply_markup=config.REPLY_MARKUP_RETURN)
        set_step(chat_id_cur, ADD_MONEY)
    elif step == ADD_MONEY:
        data = get_username_password(chat_id_cur)
        database = LawyerDB(data[0], data[1])
        context.bot.send_message(chat_id=chat_id_cur,
                text="Сделка успешно добавлена",
                reply_markup=config.REPLY_MARKUP_MAIN_MENU_ACCOUNTANT)
        set_step(chat_id_cur, MAIN_MENU)

    elif message_text == 'Выйти':
        context.bot.send_message(chat_id=chat_id_cur,
                text="Войдите для продолжения",
                reply_markup=config.REPLY_MARKUP_START) 
    elif message_text == 'Вернуться в главное меню':
        repl = get_status_reply(get_status(id=chat_id_cur))
        context.bot.send_message(chat_id=chat_id_cur,
                text="Вы в главном меню",
                reply_markup=repl)
        set_step(MAIN_MENU)
    else: 
        context.bot.send_message(chat_id=chat_id_cur, text="Извините, я вас не понял")

def main():
    updater = Updater(
        token=config.TOKEN,
        # base_url=config.PROXI,
        use_context=True)
    print('Loading...\n')
    print(updater.bot.get_me())

    message_handler = MessageHandler(Filters.all, message)
    star_handler = CommandHandler("start", start)
    help_handler = CommandHandler("help", help)

    updater.dispatcher.add_handler(star_handler)
    updater.dispatcher.add_handler(help_handler)
    updater.dispatcher.add_handler(message_handler)
    updater.start_polling()
    updater.idle()


if __name__ == '__main__':
    main()