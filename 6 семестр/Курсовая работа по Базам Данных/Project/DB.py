from asyncio.windows_events import NULL
from select import select
from PostgresClient import PostgresClient

class LawyerDB:
    def __init__(self, user, password) -> None:
        
        self.database = PostgresClient(user, password, 'localhost', '5432', 'lab_1')

    def check_lawyer_by_id(self, id):
        if self.database.select_from_table(table_name="lawyers", fields=["id"], where_field="id", where_value=id) == []:
            return False
        else:
            return True

    def check_customer_by_id(self, id):
        if self.database.select_from_table(table_name="customers", fields=["id"], where_field="id", where_value=id) == []:
            return False
        else:
            return True

    def check_admin_by_id(self, id):
        if self.database.select_from_table(table_name="admins", fields=["id"], where_field="id", where_value=id) == []:
            return False
        else:
            return True

    def get_accountant_password(self, id):
        return self.database.select_from_table(table_name="accountants", where_field="id", where_value=id, fields=["password"])[0][0]

    def add_accountant(self, _id, _name):
        self.database.insert_into_table(table_name="accountants", id=_id, name=_name)
            
    def set_accountant_password(self, _id, _password):
        self.database.update_table(table_name="accountants", where_field="id", where_value=_id, passward=_password)


def set_step(id, step_id):
    database = PostgresClient('postgres', '281001', 'localhost', '5432', 'lab_1')
    database.update_table(table_name="steps", where_field="id", where_value=id, step=step_id)


def get_step(id):
    database = PostgresClient('postgres', '281001', 'localhost', '5432', 'lab_1')
    return database.select_from_table(table_name="steps", where_field="id", where_value=id, fields=["step"])[0][0]

def set_status(id, status_id):
    database = PostgresClient('postgres', '281001', 'localhost', '5432', 'lab_1')
    database.update_table(table_name="steps", where_field="id", where_value=id, status=status_id)

def get_status(id: int):
    database = PostgresClient('postgres', '281001', 'localhost', '5432', 'lab_1')
    return database.select_from_table(table_name="steps", where_field="id", where_value=id, fields=["status"])[0][0]

# def get_status(username: str):
#     database = PostgresClient('postgres', '281001', 'localhost', '5432', 'lab_1')
#     return database.select_from_table(table_name="steps", where_field="username", where_value='\'' + username + '\'', fields=["status"])[0][0]

def get_username(id):
    database = PostgresClient('postgres', '281001', 'localhost', '5432', 'lab_1')
    return database.select_from_table(table_name="steps", where_field="id", where_value=id, fields=["username"])[0][0]

def get_username_password(id):
    database = PostgresClient('postgres', '281001', 'localhost', '5432', 'lab_1')
    return database.select_from_table(table_name="steps", where_field="id", where_value=id, fields=["username, password"])[0]


def new_user(id):
    database = PostgresClient('postgres', '281001', 'localhost', '5432', 'lab_1')
    database.insert_into_table(table_name="steps", id=id)