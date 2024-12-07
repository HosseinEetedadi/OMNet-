#include <omnetpp.h>

using namespace omnetpp;

class IoTDevice : public cSimpleModule {
private:
    double taskGenerationInterval; // Task generation interval
    cMessage *taskGenerationEvent; // Event that triggers task generation

protected:
    virtual void initialize() override {
        // Initialize parameters from the NED file
        taskGenerationInterval = par("taskGenerationInterval");

        // Create a self-message to trigger task generation
        taskGenerationEvent = new cMessage("taskGenerationEvent");

        // Schedule the first task generation event
        scheduleAt(simTime() + taskGenerationInterval, taskGenerationEvent);
    }

    virtual void handleMessage(cMessage *msg) override {
        if (msg == taskGenerationEvent) {
            // Generate a new task
            generateTask();

            // Reschedule the task generation event
            scheduleAt(simTime() + taskGenerationInterval, taskGenerationEvent);
        } else {
            // Handle response from the SDN controller or processing units
            EV << "IoTDevice received a response\n";
            delete msg;
        }
    }

private:
    void generateTask() {
        // Create a new task
        cMessage *task = new cMessage("Task");

        // Optionally, add parameters to the task (e.g., task size)
        task->addPar("taskSize") = par("taskSize").doubleValue();

        // Send the task to the SDN Controller
        send(task, "out");
        EV << "IoTDevice generated and sent a new task\n";
    }
};

Define_Module(IoTDevice);
