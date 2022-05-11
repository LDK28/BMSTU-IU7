domains
	lname, phone, city, street = symbol.
	building, apartment = integer.
	model, color, bank, account = symbol.
	price, amount = integer.
	address = address(city, street, building, apartment).

predicates
	phone_book(lname, phone, address).
	car(lname, model, color, price).
	investors(lname, bank, account, amount).
	car_by_lname(phone, lname, model, price).
	address_and_bank(lname, city, street, bank, phone).
	
clauses
	phone_book("Winter", "+123", address("Moscow", "Postal", 1, 2)).
	phone_book("Spring", "+111", address("Spb", "Somestrt", 2, 4)).
	phone_book("Summer", "+345", address("Sevastopol", "Anotherstrt", 4, 8)).
	phone_book("Autumn", "+333", address("Moscow", "Postal", 8, 16)).
	
	car("Winter", "IDK", red, 200000).
	car("Winter", "SmallOne", black, 150).
	car("Summer", "Apple", green, 1000000).
	
	investors("Winter", "RNCB", private, 999999999).
	investors("Autumn", "Sberbank", public, 10).
	investors("Autumn", "Raiffeisen", public, 10000).
	
	car_by_lname(Phone, Lname, Model, Price) :- 
		phone_book(Lname, Phone, _), 
		car(Lname, Model, _, Price). 
	address_and_bank(Lname, City, Street, Bank, Phone) :- 
		phone_book(Lname, Phone, address(City, Street, _, _)),
		investors(Lname, Bank, _, _).
		
	
goal
	% 1.a find by phone number
	%car_by_lname("+123", Last_name, Model, Price).
	%car_by_lname("+333", Last_name, Model, Price).
	%car_by_lname("+000", Last_name, Model, Price).
	
	% 1.b find car model using 1.a
	%car_by_lname("+123", _, Model, _).
	%car_by_lname("+333", _, Model, _).
	%car_by_lname("+000", _, Model, _).
	
	% 2
	%address_and_bank("Winter", "Moscow", Street, Bank, Phone).
	%address_and_bank("Autumn", "Moscow", Street, Bank, Phone).
	%address_and_bank("Spring", "SPB", Street, Bank, Phone).
