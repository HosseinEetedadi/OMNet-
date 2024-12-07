#include <omnetpp.h>

using namespace omnetpp;

class CoreServer : public cSimpleModule {
private:
    double processingCapacity; // Tasks per second
    int currentLoad;           // Number of tasks currently being processed

protected:
    virtual void initialize() override {
        processingCapacity = par("processingCapacity"); // Load from NED file
        currentLoad = 0; // Start with no tasks
    }

    virtual void handleMessage(cMessage *msg) override {
        if (msg->isSelfMessage()) {
            handleTaskCompletion(msg);
        } else {
            handleIncomingTask(msg);
        }
    }

private:
    void handleIncomingTask(cMessage *task) {
        if (currentLoad < processingCapacity) {
            EV << "CoreServer: Task accepted. Current load: " << currentLoad + 1 << "\n";
            currentLoad++;
            simtime_t processingTime = 1.0 / processingCapacity; // Calculate processing delay
            scheduleAt(simTime() + processingTime, task);
        } else {
            EV << "CoreServer: Task rejected. Server overloaded.\n";
            delete task; // Reject the task
        }
    }

    void handleTaskCompletion(cMessage *task) {
        EV << "CoreServer: Task completed. Current load: " << currentLoad - 1 << "\n";
        currentLoad--;

        // Notify SDN controller about task completion
        cMessage *completionNotification = new cMessage("TaskCompleted");
        completionNotification->addPar("serverId") = getId(); // Include server ID
        send(completionNotification, "out");

        delete task; // Clean up the task
    }
};

Define_Module(CoreServer);
