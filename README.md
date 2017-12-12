# SOMIPP-LAB
Simulation of Operating System work by simulation of Restaurant work.

# Architectural Decisions

Using `Suggested Order of Working` from  [laboratory work condition](https://github.com/mcosletjr/grand-somipp-lab#suggested-order-of-working-on-this-laboratory), I started project from dividing it in to main parts:
- Generator of Orders
- Execution core which includes cooks preparing generated orders

Because of fact that orders should be generated in parallel with execution of already generated orders, I have divided these 2 parts in 2 threads, where orders are generated at a new created thread and execution runs on the main thread.

All business logic related to generation of new orders is encapsulated in `OrdersGenerator` class, where with constant delay are generated new orders which
are added to a static std::vector `ordersList`, which represents collection of
generated orders, from `Restaurant` class, which represent abstraction of restaurant.

Collection of generated orders `ordersList` is static member, because of the fact
that it should be accessed from 2 already created threads, and in order to avoid
global reference or passing instance of `Restaurant` to thread, I have decided to
make it a static member of `Restaurant` class.

At initialization of `Restaurant` class, it is obtained a std::vector of `Cook` class instances from `CooksManager` class, where is embedded all business logic related to "cooking" of foods.

`Cook` class represents the core of execution, here is performed "preparation" and searching of "foods". Implementation of "cook" logic implies that cooks don't searching and take "order" and prepare sequential "foods" from it, but they a searching for unprepared foods from orders and start to prepare these foods.

Cooks searching for food, according to their proficiency, this means that one cook, take as many "foods" for preparing as his proficiency is, of course if there are such many foods in orders which are in `orderList`. I used such implementation because in case when one cook takes one order with condition of he doesn't care whether he is qualified enough or whether the stove is free, he will prepare sequential foods from order and the time of preparing one order will be much more than `maxWait` of an order, even in case if cook works to more dishes at the same time.

Foods which cook will prepare are obtained from method `findFoods()`, which returns a std::vector of pointer to instance of `Food` class. These foods represents result of searching of foods which runs on a separated thread which is unique for each cook. Preparation of food, also runs on separated thread which is unique for each food preparation. Cook starts that number of threads that foods he has to prepare. In this way one cook work with more dishes in parallel, according to his proficiency.

After all foods from an order are prepared, order is finished an removed from `orderList`. When order is finished is measured time of it execution and it is given star rating to it.
