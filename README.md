# librlog
librlog is an object oriented C++ synchronous and asynchronous open source remote logging library.
It takes advantages of libcurl and C++11 facilities to implement a logging library.


# Install
You can compile and install the library doing this:

```bash
cd build
cmake ..
make
sudo make install
```

The headers will be located under ```/usr/local/include/rlog```

#Examples

Let's go straight to the examples. Let's suppose you have a webserver running on 8080 port and you want to log
certain event. Suppose your server url is http://localhost:8080/myendpoint and this endpoint accepts a POST request.

# Log an event synchronously
Here's an example on how to log an event in a synchronous way.

```c++
//
// Created by giuseppe on 15/04/18.
// This example shows how to log an event synchronously.
//

#include "rlog/client.hpp"
#include "rlog/stream.hpp"
#include "rlog/key_value.hpp"

#include <iostream>

int main(int argc, char **argv) {

	// Create a stream builder.
	remlog::message::stream message_stream_builder;

	// The stream accepts a key-value pair, where you can specify a key and its value.
	message_stream_builder << remlog::message::key_value<std::string>("message", "Hello world!");

	// Istantiate the client and the remote url
	remlog::client client;
	remlog::url url("http://localhost:8080/test");

	// Now simply log the event.
	remlog::response result = client.log(url, message_stream_builder);

	// Print the server response code and the entire response.
	std::cout << "CODE: " << result.get_code() << " RESPONSE: " << result.get_response() << std::endl;
	return 0;
}
```

# Log an event asynchronously
Now suppose you want to log an event but you don't want to wait the server to respond, because you have other code to
execute and more important computations to do:

```c++
//
// Created by giuseppe on 15/04/18.
// This example shows how to log an event asynchronously.
//

#include "rlog/client.hpp"
#include "rlog/stream.hpp"
#include "rlog/key_value.hpp"

#include <iostream>

int main(int argc, char **argv) {

	// Create a stream builder.
	remlog::message::stream message_stream_builder;

	// The stream accepts a key-value pair, where you can specify a key and its value.
	message_stream_builder << remlog::message::key_value<std::string>("message", "Hello world!");

	// Istantiate the client and the remote url
	remlog::client client;
	remlog::url url("http://localhost:8080/test");

	// Now simply log the event using the async_log method. This method returns a std::future object.
	std::future<remlog::response> future_response = client.async_log(url, message_stream_builder);

	// Do whatever you have to here ... computations and stuff ...

	// At certain point you call the future get method, that will return the response.
	remlog::response response = future_response.get();

	// Print the server response code and the entire response.
	std::cout << "CODE: " << response.get_code() << " RESPONSE: " << response.get_response() << std::endl;

    return 0;
}
```

# Log multiple events from multiple threads.
Now suppose you are in a multithreading environment and you have threads that wants to log different events in an
synchronous way. You can easly do:

```c++
//
// Created by giuseppe on 15/04/18.
// This example shows how to log events synchronously from multiple threads
//

#include "rlog/client.hpp"
#include "rlog/stream.hpp"
#include "rlog/key_value.hpp"

#include <iostream>
#include <thread>

void first_worker(const remlog::url &url) {
	// Create a stream builder.
	remlog::message::stream message_stream_builder;

	// Create something to write on the stream.
	std::thread::id thread_id = std::this_thread::get_id();
	remlog::message::key_value<std::string> message("message", "This is the first event from the first worker");
	remlog::message::key_value<std::thread::id> request_id("request_id", thread_id);

	// The stream accepts a key-value pair, where you can specify a key and its value.
	message_stream_builder << message << request_id;

	// Istantiate the client. This is thread safe, so you could pass it as parameter.
	remlog::client client;
	remlog::response response = client.log(url, message_stream_builder);
}

void second_worker(const remlog::url &url) {
	// Create a stream builder.
	remlog::message::stream message_stream_builder;

	// Create something to write on the stream.
	std::thread::id thread_id = std::this_thread::get_id();
	remlog::message::key_value<std::string> message("message", "This is the second event from the second worker");
	remlog::message::key_value<std::thread::id> request_id("request_id", thread_id);

	// The stream accepts a key-value pair, where you can specify a key and its value.
	message_stream_builder << message << request_id;

	// Istantiate the client. This is thread safe, so you could pass it as parameter.
	remlog::client client;
	remlog::response response = client.log(url, message_stream_builder);
}

int main(int argc, char **argv) {
	// The url is the same for both threads, but in your application could be different.
	remlog::url url("http://localhost:8080/test");

	// Create the threads and join them.
	std::thread worker_1(first_worker, url);
	std::thread worker_2(second_worker, url);

	worker_1.join();
	worker_2.join();

	return 0;
}
```
