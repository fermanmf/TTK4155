# TTK4155

At the heart of node1 and node2 we have the event manger (em). It waits patentially for asycnhronous events (interrupt based) to come in, queues them and emits them syncronously. This makes the "business logic" syncronous while all drivers and such are asynchronous. This makes code fast and efficient. em also takes care that both nodes have access to the same events (through CAN). This is scaleable and easy to debug. It also keeps the drivers and modules quite modularized.

The main codeflow consists of inits of different modules and a main loop. The inits sets up pin interrupts and timer-counters to so that they run independently from the main loop. Then the main loop is only concerned with waiting for events and reacting to these appropriatly - all syncronously and fast.
