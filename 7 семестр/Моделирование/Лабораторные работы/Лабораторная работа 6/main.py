from random import random
import tkinter as tk
from tkinter import ttk
import random

MINVALUE_GEN = 1
MAXVALUE_GEN = 10000
MAXVALUE_LESS = MAXVALUE_GEN  # // 10
unit_of_time = 0.01
COLOR = '#ffffff'
MAX_SIZE = 10
WIDGET_WIDTH_1 = 30
WIDGET_WIDTH = 25


class UniformDistribution:
    def __init__(self, a: float, b: float):
        self.a = a
        self.b = b

    def generate(self):
        return self.a + (self.b - self.a) * random.random()


class Generator:
    def __init__(self, generator, count):
        self._generator = generator
        self.receivers = []
        self.num_requests = count
        self.next = 0

    def next_time(self):
        return self._generator.generate()

    def generate_request(self):
        self.num_requests -= 1
        receiver_min = self.receivers[0]
        min = self.receivers[0].current_queue_size
        for receiver in self.receivers:
            if receiver.current_queue_size < min:
                min = receiver.current_queue_size
                receiver_min = receiver
        receiver_min.receive_request()
        return receiver_min


class Processor(Generator):
    def __init__(self, generator, max_queue=-1):
        self._generator = generator
        self.current_queue_size = 0
        self.max_queue_size = max_queue
        self.max_size = 0
        self.processed_requests = 0
        self.received_requests = 0
        self.next = 0
        self.receivers = []

    def process_request(self):
        if self.current_queue_size > 0:
            self.processed_requests += 1
            self.current_queue_size -= 1

        if len(self.receivers) != 0:
            receiver_min = self.receivers[0]
            min = self.receivers[0].current_queue_size
            for receiver in self.receivers:
                if receiver.current_queue_size < min:
                    min = receiver.current_queue_size
                    receiver_min = receiver
            receiver_min.receive_request()
            receiver_min.next = self.next + receiver_min.next_time()

    def receive_request(self):
        self.current_queue_size += 1
        self.received_requests += 1
        if self.max_size < self.current_queue_size:
            self.max_size = self.current_queue_size
        return True

    def next_time(self):
        return self._generator.generate()


class Modeller:
    def __init__(self, generator, operators, computers):
        self._generator = generator
        self._operators = operators
        self._computers = computers

    def event_mode(self):
        refusals = 0
        processed = 0
        generated_requests = self._generator.num_requests
        generator = self._generator

        generator.next = generator.next_time()
        self._operators[0].next = self._operators[0].next_time()

        blocks = [
                     generator
                 ] + self._computers + self._operators

        num_requests = generator.num_requests
        count = 0
        while count < num_requests:
            current_time = generator.next
            for block in blocks:
                if 0 < block.next < current_time:
                    current_time = block.next

            for block in blocks:
                if current_time == block.next:
                    if not isinstance(block, Processor):
                        next_generator = generator.generate_request()
                        if next_generator is not None:
                            next_generator.next = \
                                current_time + next_generator.next_time()
                            processed += 1
                        else:
                            refusals += 1
                        generator.next = current_time + generator.next_time()
                    else:
                        block.process_request()
                        if block.current_queue_size == 0:
                            block.next = 0
                        else:
                            block.next = current_time + block.next_time()
            count = 0
            for oper in self._computers:
                count += oper.processed_requests

        max_queue = []
        for oper in self._operators:
            max_queue.append(oper.max_size)
        for oper in self._computers:
            max_queue.append(oper.max_size)
        processed_arr = []
        for oper in self._operators:
            processed_arr.append(oper.processed_requests)
        for oper in self._computers:
            processed_arr.append(oper.processed_requests)
        return {"max_queue": max_queue,
                'time': current_time,
                "processed": count,
                "proc_arr": processed_arr,
                "pribilo": processed
                }


class FrameBlock:
    def __init__(self, master, text, row, column, rowspan=1, columnspan=1, def_from=1, def_to=1):
        self.frame_1 = tk.LabelFrame(master, bg=COLOR, text=text, width=90, height=100)
        self.lab2 = tk.Label(self.frame_1, bg=COLOR, width=WIDGET_WIDTH_1//2, text='от:')
        self.lab3 = tk.Label(self.frame_1, bg=COLOR, width=WIDGET_WIDTH_1//2, text='до:')
        self.from_ = ttk.Combobox(self.frame_1, width=WIDGET_WIDTH_1 // 2,
                                  values=[i for i in range(1, MAX_SIZE*10 + 1)],
                                  state='readonly')
        self.to_ = ttk.Combobox(self.frame_1, width=WIDGET_WIDTH_1 // 2,
                                values=[i for i in range(1, MAX_SIZE*10 + 1)],
                                state='readonly')

        self.from_.bind("<FocusIn>", self.defocus)
        self.from_.set(def_from)
        self.to_.bind("<FocusIn>", self.defocus)
        self.to_.set(def_to)

        self.frame_1.grid(row=row, column=column, rowspan=rowspan, columnspan=columnspan, padx=5, pady=5)

        self.lab2.grid(row=0, column=0, padx=5, pady=5)
        self.lab3.grid(row=1, column=0, padx=5, pady=5)
        self.from_.grid(row=0, column=1, padx=5, pady=5)
        self.to_.grid(row=1, column=1, padx=5, pady=5)

    def get_info(self):
        return int(self.from_.get()), int(self.to_.get())

    @staticmethod
    def defocus(event):
        event.widget.master.focus_set()


class Block:
    def __init__(self, master):

        self.frame = tk.LabelFrame(master, bg=COLOR, text='Ввод данных', width=400, height=450)

        self.calculate_result_btn = tk.Button(self.frame, text="Вычислить", width=WIDGET_WIDTH,
                                              bg=COLOR, command=self.solve)

        self.generator_info = FrameBlock(self.frame, 'Время поступления клиентов', 0, 0, 1, 2, 2, 6)
        self.operator_1 = FrameBlock(self.frame, 'Время работы упаковщика', 1, 0, 1, 2, 5, 15)
        self.processor_1 = FrameBlock(self.frame, 'время работы фасовщика', 2, 0, 1, 2, 3, 9)

        self.count_req_lab = tk.Label(self.frame, bg=COLOR, width=WIDGET_WIDTH_1//2, text='Количество заявок:')
        self.count_req = ttk.Combobox(self.frame, width=WIDGET_WIDTH_1//2,
                                      values=[i for i in range(100, 10001, 100)],
                                      state='readonly')
        self.count_req.bind("<FocusIn>", self.defocus)
        self.count_req.set(300)
        self.count_req_lab.grid(row=6, column=0, columnspan=1)
        self.count_req.grid(row=6, column=1)

        self.result_frame = tk.LabelFrame(master, bg=COLOR, text='Результат', width=650, height=200)
        self.result_frame.grid_propagate(False)

        self.res_label = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH, text='Объект')
        self.res_label.grid(row=0, column=0, )

        self.res_label = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH, text='Максимальная очередь')
        self.res_label.grid(row=0, column=1,)
        self.res_label = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH, text='Обработано')
        self.res_label.grid(row=0, column=2, )

        self.res_label1 = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH-4, text='Упаковщик 1')
        self.res_label1.grid(row=1, column=0, )
        self.res_label2 = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH-4, text='Упаковщик 2')
        self.res_label2.grid(row=2, column=0, )
        self.res_label3 = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH - 4, text='Упаковщик 3')
        self.res_label3.grid(row=3, column=0, )
        self.res_label5 = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH - 4, text='Упаковщик 4')
        self.res_label5.grid(row=4, column=0, )
        self.res_label4 = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH + 5, text='Фасовщик 1')
        self.res_label4.grid(row=5, column=0, )
        self.res_label4 = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH + 5, text='Фасовщик 2')
        self.res_label4.grid(row=6, column=0, )
        self.res_label4 = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH + 5, text='Фасовщик 3')
        self.res_label4.grid(row=7, column=0, )

        self.step_label_res1 = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH - 15, text='')
        self.step_label_res1.grid(row=1, column=1)
        self.step_label_res2 = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH - 15, text='')
        self.step_label_res2.grid(row=2, column=1)

        self.step_label_res3 = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH - 15, text='')
        self.step_label_res3.grid(row=3, column=1)
        self.step_label_res4 = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH - 15, text='')
        self.step_label_res4.grid(row=4, column=1)
        self.step_label_res5 = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH - 15, text='')
        self.step_label_res5.grid(row=5, column=1)
        self.step_label_res6 = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH - 15, text='')
        self.step_label_res6.grid(row=6, column=1)
        self.step_label_res7 = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH - 15, text='')
        self.step_label_res7.grid(row=7, column=1)

        self.step_label_res1_ = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH - 15, text='')
        self.step_label_res1_.grid(row=1, column=2)
        self.step_label_res2_ = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH - 15, text='')
        self.step_label_res2_.grid(row=2, column=2)

        self.step_label_res3_ = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH - 15, text='')
        self.step_label_res3_.grid(row=3, column=2)
        self.step_label_res4_ = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH - 15, text='')
        self.step_label_res4_.grid(row=4, column=2)
        self.step_label_res5_ = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH - 15, text='')
        self.step_label_res5_.grid(row=5, column=2)

        self.step_label_res6_ = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH - 15,
                                         text='')
        self.step_label_res6_.grid(row=6, column=2)

        self.step_label_res7_ = tk.Label(self.result_frame, bg=COLOR, width=WIDGET_WIDTH - 15,
                                         text='')
        self.step_label_res7_.grid(row=7, column=2)

        self.calculate_result_btn.grid(row=8, column=0, columnspan=2,  pady=5)

    @staticmethod
    def defocus(event):
        event.widget.master.focus_set()

    def make_view(self):
        # self.frame.grid(row=row, column=column)
        self.frame.pack()
        # self.listbox_frame.grid(row=3, column=0, columnspan=10)
        self.result_frame.pack(pady=5)

    def solve(self):
        clients_number = int(self.count_req.get())

        generator = Generator(
            UniformDistribution(*self.generator_info.get_info()),
            clients_number,
        )

        operators = [
            Processor(
                UniformDistribution(*self.operator_1.get_info())
            ),
            Processor(
                UniformDistribution(*self.operator_1.get_info())
            ),
            Processor(
                UniformDistribution(*self.operator_1.get_info())
            ),
            Processor(
                UniformDistribution(*self.operator_1.get_info())
            ),
        ]

        computers = [
            Processor(UniformDistribution(*self.processor_1.get_info()), ),
            Processor(UniformDistribution(*self.processor_1.get_info()), ),
            Processor(UniformDistribution(*self.processor_1.get_info()), ),
        ]

        generator.receivers = operators.copy()
        operators[0].receivers = computers
        operators[1].receivers = computers
        operators[2].receivers = computers
        operators[3].receivers = computers

        model = Modeller(generator, operators, computers)
        result = model.event_mode()

        self.step_label_res1['text'] = str(result['max_queue'][0])
        self.step_label_res2['text'] = str(result['max_queue'][1])
        self.step_label_res3['text'] = str(result['max_queue'][2])
        self.step_label_res4['text'] = str(result['max_queue'][3])
        self.step_label_res5['text'] = str(result['max_queue'][4])
        self.step_label_res6['text'] = str(result['max_queue'][5])
        self.step_label_res7['text'] = str(result['max_queue'][6])

        self.step_label_res1_['text'] = str(result['proc_arr'][0])
        self.step_label_res2_['text'] = str(result['proc_arr'][1])
        self.step_label_res3_['text'] = str(result['proc_arr'][2])
        self.step_label_res4_['text'] = str(result['proc_arr'][3])
        self.step_label_res5_['text'] = str(result['proc_arr'][4])
        self.step_label_res6_['text'] = str(result['proc_arr'][5])
        self.step_label_res7_['text'] = str(result['proc_arr'][6])


root = tk.Tk()
root['bg'] = COLOR
root.geometry('880x650')

first_block = Block(root)
first_block.make_view()
root.mainloop()
