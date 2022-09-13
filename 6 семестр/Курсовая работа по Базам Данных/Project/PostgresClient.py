import psycopg2

class PostgresClient:
    def __init__(self, user, password, host, port, database):
            """Подключаемся к БД и сохраняем курсор соединения"""
            self.connection = psycopg2.connect(user=user,
                                                password=password,  # Your PostgreSQL passward
                                                host=host,  # Your DB host
                                                port=port,  # Your PostgreSQL port
                                                database=database)
            self.cursor = self.connection.cursor()

    # SELSECT field FROM table
    def select_from_table(self, table_name, 
                                table_name_join=None, 
                                join_field_1=None, 
                                join_field_2=None, 
                                order_by = None,
                                where_field=None,
                                where_value=None,
                                fields = ["id"]):
        request = "SELECT "
        for field in fields:
            request += field + ", "
        request = request[:-2] + " FROM " + table_name

        if table_name_join != None:
            request += " JOIN " + table_name_join + " ON " + table_name + "." + join_field_1 + " = " + table_name_join + "." + join_field_2

        if where_field != None and where_value != None:
            request += " WHERE " + where_field + " = " + str(where_value)

        if order_by != None:
            request += " ORDER BY " + table_name + "." + order_by

        print(request)

        with self.connection:
            self.cursor.execute(request)
            return self.cursor.fetchall()
    
    def insert_into_table(self, table_name, 
                                where_field=None,
                                where_value=None,
                                **kwargs):
        request = "INSERT INTO " + table_name
        fields = " ("
        values = " ("
        for field, value in kwargs.items():
            fields += str(field) + ", "
            values += str(value) + ", "
        fields = fields[:-2] + ")"
        values = values[:-2] + ")"

        if where_field != None and where_value != None:
            request += " WHERE " + where_field + " = " + str(where_value)

        request = request + fields + " VALUES " + values

        print(request)

        with self.connection:
            self.cursor.execute(request)


    def update_table(self, table_name, 
                            where_field=None,
                            where_value=None,
                            **kwargs):
        request = "UPDATE " + table_name + " SET "
        for field, value in kwargs.items():
            request += str(field) + " = " + str(value) + ", "
        request = request[:-2] 

        if where_field != None and where_value != None:
            request += " WHERE " +str(where_field) + " = " + str(where_value)

        print(request)

        with self.connection:
            self.cursor.execute(request)


    def delete_from_table(self, table_name, 
                            where_field,
                            where_value):
        request = "DELETE FROM " + table_name
        request += " WHERE " + str(where_field) + " = " + str(where_value)

        print(request)

        with self.connection:
            self.cursor.execute(request)
