#include <iostream>
#include <string>

// Enum to identify different events
enum class EventType {
    Event1,
    Event2,
    Event3
};

// Struct to hold event data
struct EventData {
    EventType type;
    std::string message;
};

// Class to handle button events
class ButtonEventHandler {
public:
    // Handle events based on the EventData
    int handleEvent(const EventData& event) {
        switch (event.type) {
            case EventType::Event1:
                std::cout << "ButtonEventHandler: Event 1 executed with message: " << event.message << std::endl;
                return event.message.length();
            case EventType::Event2:
                std::cout << "ButtonEventHandler: Event 2 executed with message: " << event.message << std::endl;
                return event.message.length() * 2;
            case EventType::Event3:
                std::cout << "ButtonEventHandler: Event 3 executed with message: " << event.message << std::endl;
                return event.message.length() * 3;
            default:
                std::cout << "ButtonEventHandler: Unknown event!" << std::endl;
                return -1;
        }
    }
};

// Simulate a button class
class Button {
public:
    // Define a type for the callback function using typedef
    typedef int(*Callback)(const EventData&);

    // Set the callback
    void setOnEvent(Callback callback) {
        onEventCallback = callback;
    }

    // Simulate Event 1
    void triggerEvent1(const std::string& message) {
        if (onEventCallback) {
            std::cout << "Event 1 triggered! Calling callback..." << std::endl;
            EventData event{EventType::Event1, message};
            int result = onEventCallback(event);
            std::cout << "Callback returned: " << result << std::endl;
        } else {
            std::cout << "Event 1 triggered, but no callback set." << std::endl;
        }
    }

    // Simulate Event 2
    void triggerEvent2(const std::string& message) {
        if (onEventCallback) {
            std::cout << "Event 2 triggered! Calling callback..." << std::endl;
            EventData event{EventType::Event2, message};
            int result = onEventCallback(event);
            std::cout << "Callback returned: " << result << std::endl;
        } else {
            std::cout << "Event 2 triggered, but no callback set." << std::endl;
        }
    }

    // Simulate Event 3
    void triggerEvent3(const std::string& message) {
        if (onEventCallback) {
            std::cout << "Event 3 triggered! Calling callback..." << std::endl;
            EventData event{EventType::Event3, message};
            int result = onEventCallback(event);
            std::cout << "Callback returned: " << result << std::endl;
        } else {
            std::cout << "Event 3 triggered, but no callback set." << std::endl;
        }
    }

private:
    Callback onEventCallback = nullptr; // Single callback for all events
};

// Free function to handle events
int onEventHandler(const EventData& event) {
    ButtonEventHandler handler;
    return handler.handleEvent(event);
}

int main() {
    Button button;

    // Set the single callback for all events
    button.setOnEvent(onEventHandler);

    // Trigger Event 1
    button.triggerEvent1("Hello, Event 1!");

    // Trigger Event 2
    button.triggerEvent2("Hello, Event 2!");

    // Trigger Event 3
    button.triggerEvent3("Hello, Event 3!");

    return 0;
}