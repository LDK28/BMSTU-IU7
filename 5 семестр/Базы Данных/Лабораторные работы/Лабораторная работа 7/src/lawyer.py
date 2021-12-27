class lawyer():
    # Структура полностью соответствует таблице lawyers.
    id = int()
    name = str()
    email_address = str()
    phone_number = str()
    skill = int()
    office_address = str()
    process_count = int()

    def __init__(self, id, name, email_address, phone_number, skill, office_address, process_count):
        self.id = id
        self.name = name
        self.email_address = email_address
        self.phone_number = phone_number
        self.skill = skill
        self.office_address = office_address
        self.process_count = process_count

    def get(self):
        return {'id': self.id, 'name': self.name, 'email_address': self.email_address,
                'phone_number': self.phone_number, 'skill': self.skill, 'office_address': self.office_address, 'process_count': self.process_count}

    # def __str__(self):
    #     return f"{self.id:<3} {self.name:<40} {self.email_address:<20} {self.phone_number:<12} {self.skill:<3} {self.office_address:<40} {self.process_count:<10}"
    #


def create_lawyers(file_name):
    # Содает коллекцию объектов.
    # Загружая туда данные из файла file_name.
    file = open(file_name, 'r')
    lawyers = list()

    for line in file:
        arr = line.split(',')
        arr[0], arr[4], arr[6] = int(arr[0]), int(arr[4]), int(arr[6])
        lawyers.append(lawyer(*arr).get())

    return lawyers