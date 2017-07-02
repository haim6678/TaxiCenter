# TaxiCenter
Taxi center simulation

A center taht runs the taxies,gets the calls and deliver to the drivers
each driver can find is own path to the client using bfs
we can track wich taxi is busy and send the call to the closest empty driver.

cuurently supporting 2 types of taxies.
currently unattached->google testing for this project.

the communication is through sockets.
each drivers gets is thread and everything is running in a thread pool.

