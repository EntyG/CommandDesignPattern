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

// Invoker
class Remote {
private:
    std::queue<Command*> commandQ;
    std::stack<Command*> undoQ;
public:
    void setCommand(Command* command) {
        commandQ.push(command);
    }
    void pressButton() {
        if (!commandQ.empty()) {
            Command* command = commandQ.front();
            command->execute();
            commandQ.pop();
            undoQ.push(command);
        }
    }
    void pressUndo() {
        if (!undoQ.empty()) {
            Command* command = undoQ.top();
            command->undo();
            undoQ.pop();
        }
    }
};

// Client
int main() {
    Light light;
    LightOnCommand lightOnCommand(&light);
    LightOffCommand lightOffCommand(&light);

    Remote remote;
    remote.setCommand(&lightOnCommand);
    remote.setCommand(&lightOffCommand);

    // Execute commands
    remote.pressButton();
    remote.pressButton();

    // Undo last command
    remote.pressUndo();

    return 0;
}
