# SOMIPP-LAB
Simulation of Operating System work by simulation of Restaurant work.

# Architectural Decisions

Using `Suggested Order of Working` from  [laboratory work condition](https://github.com/mcosletjr/grand-somipp-lab#suggested-order-of-working-on-this-laboratory), I started project from dividing it in to main parts:
- Generator of Orders
- Execution core which includes cooks preparing generated orders

Because of fact that orders should be generated in parallel with execution of already generated orders, I have divided these 2 parts in 2 threads, where orders are generated at a new created thread and execution runs on the main thread.

All business logic related to generation of new orders is encapsulated in `OrdersGenerator` class, where with constant delay are generated new orders which
are added to a static std::vector `ordersList`, which represents collection of
generated orders, from `Restaurant` class, which is abstraction of restaurant.

Collection of generated orders `ordersList` is static member, because of the fact
that it should be accessed from 2 already created threads, and in order to avoid
global variables or passing reference to instance of `Restaurant` to thread, I have decided to make it a static member of `Restaurant` class.

At initialization of `Restaurant` class, it is obtained a std::vector of `Cook` class instances from `CooksManager` class. In `Cook` class is embedded all business logic related to "cooking" of foods.

`Cook` class represents the core of execution, here is performed "preparation" and searching of "foods". Implementation of "cook" logic implies that cooks don't searching and take "order" and prepare sequential "foods" from it, but they a searching for unprepared foods from orders and start to prepare these foods.

Cooks searching for food, according to their proficiency and rank, this means that one cook, take as many "foods" for preparing as his proficiency is, of course if there are such many foods in orders which are in `orderList`, also "cook" take a "food" for preparing only in case if his rank allow him to cook this food. In this way each cook decide which "foods" he will prepare, and this can be "foods" from different and of course can appear moments when "cook" can't find foods, or find amount less than his proficiency is.

I used such implementation because in case when one cook takes one order with condition of he doesn't care whether he is qualified enough or whether the stove is free, he will prepare sequential foods from order and the time of preparing one order will be much more than `maxWait` of an order, even in case if cook works to more dishes at the same time.

Foods which cook will prepare are obtained from method `findFoods()`, which returns a std::vector of pointer to instance of `Food` class. These foods represents result of searching of foods which runs on a separated thread which is unique for each cook. Preparation of food, also runs on separated thread which is unique for each food preparation. Cook starts that number of threads that foods he has to prepare. In this way one cook work with more dishes in parallel, according to his proficiency.

After all foods from an order are prepared, order is finished an removed from `orderList`. When order is finished is measured time of its execution and it is given star rating to it.

In this way, my implementation implies several number of threads:
1. Main Thread

    On this thread are initialized all program objects, and is started thread where are generated orders, also on this thread runs a loop where is checked if there are some orders in `orderList` which are finished.

2. Order generation thread.

    On this thread is performed continuously generation of new orders. This thread is starting from main thread and run in parallel with it.

3. Cook threads.

    Each "cook" runs on his own thread, which is starting at initialization of `Cook` class, from main thread. On these threads are performed searching of foods for each cook. These threads are synchronized between them and also are synchronized with main thread because they are accessed the same variable `orderList` from `Restaurant` class.

4. Food cooking threads.

    Each cook prepares each food on separated thread and number of threads which "cook" starts depends on how many foods he found for preparing. These threads starts from "cook" threads and finish when "food" is "prepared".

# Multi-process synchronization problems

### Readers-Writers problem

This problem appears at the moment when 3 main parts of the program, which runs on separated threads, try to access `orderList` from `Restaurant` class. Variable `orderList` is accessed by `Restaurant`, `OrdersGenerator` and `Cook` classes instances, and because this variable is continuously modified by all them, it should't be accessed simultaneously by more than one object.

In order to synchronize access to this variable I used pthread mutex, which is set to `lock` at any access of this variable, and is set to `unlock` when variable is no more accessed. In this way when some cook starts searching for foods in orders from `orderList`, mutex is set to `lock`, and when searching is finished mutex is set to `unlock`, this also happens then in `Restaurant` class is performed checking if there are some orders in `orderList` which are totally prepared.

### Producer-Consumer problem

This problem appears at the moment when is implemented "cook" rank system. When to each cock is associated a rank, and cooks can prepare foods only according to it. In order to solve this problem I used implementation where cooks don't take hole order in manage it exclusively, but take only foods for preparing taking into consideration only if he is able to prepare it.

This approach, in my opinion, is closer to the real restaurant work, and simulates better a real behavior of restaurant, and this is the reason why I used this implementation, even if I understand what in our simulation an order, represents a process from operating system, and foods from it represents processes's threads on which it runs, and in an operating system we can't runt separate processes of different threads, but can only run a process which implies run of his threads.
