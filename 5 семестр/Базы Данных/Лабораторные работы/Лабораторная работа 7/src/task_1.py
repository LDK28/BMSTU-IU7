from py_linq import *

from lawyer import *
from colors import *


def request_1(lawyers):
	# Юристы со скиллом больше 5 отсортированные по имени.
	result = lawyers.where(lambda x: x['skill'] >= 5).order_by(lambda x: x['name']).select(lambda x: {'name': x['name'], 'skill': x['skill']})
	return result


def request_2(lawyers):
	# Количество юристов, со скиллом меньше 5.
	result = lawyers.count(lambda x: x['skill'] < 5)
	return result


def request_3(lawyers):
	# минимальный, максимальный скилл.
	skill = Enumerable([{lawyers.min(lambda x: x['skill']), lawyers.max(lambda x: x['skill'])}])
	# минимальное, минимальное кол-во процессов среди юристов.
	proc_count = Enumerable([{lawyers.min(lambda x: x['process_count']), lawyers.max(lambda x: x['process_count'])}])
	# А теперь объединяем все это.
	result = Enumerable(skill).union(Enumerable(proc_count), lambda x: x)
	
	return result

def request_4(lawyers):
	# Количество юристов по скиллу(группировка).
	result = lawyers.group_by(key_names=['skill'], key=lambda x: x['skill']).select(lambda g: {'skill': g.key.skill, 'count': g.count()})
	return result


def request_5(lawyers):
	# Соединяем юриста и номер документа по id
	docs = Enumerable([{'id': 13, 'doc': 321}, {'id': 24, 'doc': 1234}, {'id': 1, 'doc': 1232}]).order_by(lambda x: x['id'])
	u_d = lawyers.join(docs, lambda o_k: o_k['id'], lambda i_k: i_k['id'])

	for elem in u_d:
		print(elem)

	return u_d

def task_1():
	# Создаем коллекцию.
	lawyers = Enumerable(create_lawyers('data/lawyers.csv'))

	print(GREEN, '\n1.Юристы со скиллом больше 5 отсортированные по имени:\n')
	for elem in request_1(lawyers): 
		print(elem)

	print(YELLOW, f'\n2.Количество юристов, со скиллом меньше 5: {str(request_2(lawyers))}')

	print(BLUE, '\n3.Некоторые характеристики:\n')
	for elem in request_3(lawyers): 
		print(elem)

	print(GREEN, '\n4.Группировка по скиллу:\n')
	for elem in request_4(lawyers): 
		print(elem)

	print(GREEN, '\n5.Соединяем юриста и номер документа по id:\n')
	for elem in request_5(lawyers):
		print(elem)

if __name__ == '__main__':
    task_1()