#include <iostream>
#include <queue>
#include <stack>

// Command Interface
class Command {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~Command() {}
};

// Invoker
class Remote {
private:
    std::queue<Command*> Pending;
    std::stack<Command*> Executed;
public:
    void setCommand(Command* command) {
        Pending.push(command);
    }
    void pressButton() {
        if (!Pending.empty()) {
            Command* command = Pending.front();
            command->execute();
            Pending.pop();
            Executed.push(command);
        }
    }
    void pressUndo() {
        if (!Executed.empty()) {
            Command* command = Executed.top();
            command->undo();
            Executed.pop();
        }
    }
};

//Light
// Receiver
class Light {
public:
    void on() {
        std::cout << "Light is on" << std::endl;
    }
    void off() {
        std::cout << "Light is off" << std::endl;
    }
};

// Concrete Command
class LightOnCommand : public Command {
private:
    Light* light;
public:
    LightOnCommand(Light* light) : light(light) {}
    void execute() override {
        light->on();
    }
    void undo() override {
        light->off();
    }
};

// Concrete Command
class LightOffCommand : public Command {
private:
    Light* light;
public:
    LightOffCommand(Light* light) : light(light) {}
    void execute() override {
        light->off();
    }
    void undo() override {
        light->on();
    }
};

//Fan
// Receiver
class Fan {
public:
    void on() {
        std::cout << "Fan is on" << std::endl;
    }
    void off() {
        std::cout << "Fan is off" << std::endl;
    }
};

// Concrete Command
class FanOnCommand : public Command {
private:
    Fan* fan;
public:
    FanOnCommand(Fan* fan) : fan(fan) {}
    void execute() override {
		fan->on();
	}
    void undo() override {
		fan->off();
	}
};

// Concrete Command
class FanOffCommand : public Command {
private:
    Fan* fan;
public:
    FanOffCommand(Fan* fan) : fan(fan) {}
    void execute() override {
        fan->off();
    }
    void undo() override {
		fan->on();
	}
};

// Client
int main() {
    Light light;
    LightOnCommand lightOnCommand(&light);
    LightOffCommand lightOffCommand(&light);

    Fan fan;
    FanOnCommand fanOnCommand(&fan);
    FanOffCommand fanOffCommand(&fan);

    Remote remote;
    remote.setCommand(&lightOnCommand);
    remote.setCommand(&fanOnCommand);

    remote.pressButton();
    remote.pressButton();

    remote.pressUndo();

    remote.setCommand(&lightOffCommand);

    remote.pressButton();

    return 0;
}
