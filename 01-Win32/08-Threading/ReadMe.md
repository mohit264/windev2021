# Threading
> Running entity inside the process or program is known as Thread.

1. Every Process itself contains atleast one thread called as **Primary Thread** or **Main Thread** 
2. Thread share memory of the parent
3. Every thread has it's own stack
4. Every Thread has it's own message queue ( Not applicable in Linux )
5. Thread shares files opened by the parent
6. Every thread has its own CPU quantum
7. Any thread can kill any other thread, parent thread can kill any of his child thread, OS can kill any thread without intimation
8. Let the thread die on it's own after completed its associated function
9. Though thread shares everything with the parent, it is not true with siblings threads, Siblings thread by default do not share anything between them. If they want to share, they have to use a special mechanism know as Thread Local Storage (TLS)
10. Based on above points, we may think that threads are not independent. But every thread is an independent entity

**In Linux, It is unlikely that when Parent gets killed all of its child get automatically killed. Thread is a special kind of process in Linux.** 
