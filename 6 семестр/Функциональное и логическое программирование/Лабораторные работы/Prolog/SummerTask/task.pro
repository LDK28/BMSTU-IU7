domains
	question = symbol.
    question_word = symbol.
    or = symbol.
    tail = simbol.

    or_question = (question, or, question).
    special_question = special_question(question_word, question).
    tail_question = tail_question(question, tail).
	
predicates
	phone_book(phone, name).
	
clauses
	question_type(question):- question.split('Param1', 'Param2', 'Param3').
	phone_book("+10000", "NotMoscow").
	phone_book("+01000", "SPB").
	phone_book("+00100", "Sevastopol").
	phone_book("+00010", "Ufa").
	phone_book("+00001", "Simferopol").
    phone_book(dot, "Simferopol").
	
goal
	phone_book("+10000", Name).

% Классификация вопросов:
% 1. общие (да/нет) -               quest
% 2. разделительные (или) -         quest (or) quest
% 3. спеиальные (что, как, где) -   (what) quest
% 4. хвостовые (,не так ли?) -      quest (is)