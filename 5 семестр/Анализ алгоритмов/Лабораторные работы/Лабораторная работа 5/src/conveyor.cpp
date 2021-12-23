#include "conveyor.h"


void Conveyor::run_parallel(size_t cars_cnt)
{
    for (size_t i = 0; i < cars_cnt; i++)
    {
        std::shared_ptr<Car> new_car(new Car);
        cars.push_back(new_car);
        q1.push(new_car);
    }

    this->threads[0] = std::thread(&Conveyor::create_carcass, this);
    this->threads[1] = std::thread(&Conveyor::create_engine, this);
    this->threads[2] = std::thread(&Conveyor::create_wheels, this);

    for (int i = 0; i < THRD_CNT; i++)
    {
        this->threads[i].join();
    }
}

void print_my(size_t task, size_t part, size_t ms, tm tmm)
{
    std::printf("Task №%u | Part%u | Start | %02u:%02u:%02u.%3u\n", 
                task,
                part,
                tmm.tm_hour, 
                tmm.tm_min, 
                tmm.tm_sec, 
                static_cast<unsigned>(ms / milliseconds(1).count()));
}

void Conveyor::run_linear(size_t cars_cnt) 
{
    for (size_t i = 0; i < cars_cnt; i++)
    {
        std::shared_ptr<Car> new_car(new Car);
        cars.push_back(new_car);
        q1.push(new_car);
    }

    // Переменные для логгирования 
    tm start_1;
    size_t str1;
    tm stop_1;
    size_t stp1;
    
    tm start_2;
    size_t str2;
    tm stop_2;
    size_t stp2;

    tm start_3;
    size_t str3;
    tm stop_3;
    size_t stp3;


    for (size_t i = 0; i < cars_cnt; i++) 
    {
        std::shared_ptr<Car> car = q1.front();
        set_time(&start_1, &str1);

        car->create_carcass(i + 1);

        set_time(&stop_1, &stp1);
        q2.push(car);
        q1.pop();

        car = q2.front();
        set_time(&start_2, &str2);
        car->create_engine(i + 1);
        set_time(&stop_2, &stp2);


        q3.push(car);
        q2.pop();

        car = q3.front();
        set_time(&start_3, &str3);
        car->create_wheels(i + 1);
        set_time(&stop_3, &stp3);
        q3.pop();

        print_my(i + 1, 1, str1, start_1);
        print_my(i + 1, 1, stp1, stop_1);

        print_my(i + 1, 2, str2, start_1);
        print_my(i + 1, 2, stp2, stop_2);

        print_my(i + 1, 3, str3, start_1);
        print_my(i + 1, 3, stp3, stop_3);
    }
}

void Conveyor::create_carcass()
{
    size_t task_num = 0;

    while (!this->q1.empty())
    {
        std::shared_ptr<Car> car = q1.front();
        car->create_carcass(++task_num);

        q2.push(car);
        q1.pop();
    }
}

void Conveyor::create_engine()
{
    size_t task_num = 0;

    do
    {
        if (!this->q2.empty())
        {
            std::shared_ptr<Car> car = q2.front();
            car->create_engine(++task_num);

            q3.push(car);
            q2.pop();
        }
    } while(!q1.empty() || !q2.empty());
}

void Conveyor::create_wheels()
{
    size_t task_num = 0;

    do
    {
        if (!this->q3.empty())
        {
            std::shared_ptr<Car> car = q3.front();
            car->create_wheels(++task_num);
            q3.pop();
        }
    } while (!q1.empty() || !q2.empty() || !q3.empty());
}