#include <omnetpp.h>
#include <vector>
#include <algorithm>

using namespace omnetpp;

class SDNController : public cSimpleModule {
private:
    int numMECDevices;
    int numCoreServers;
    double epsilon, alpha, gamma;

    // SARSA-related variables
    std::vector<std::vector<double>> qTable;
    int numStates, numActions;
    int currentState, lastAction;

protected:
    virtual void initialize() override {

        EV << "Gate 'out' size: " << gateSize("out") << "\n";
        EV << "Gate 'coreOut' size: " << gateSize("coreOut") << "\n";
        numMECDevices = par("numMECDevices");
        numCoreServers = par("numCoreServers");
        numStates = 10; // Example: discretized states
        numActions = numMECDevices + numCoreServers;

        epsilon = par("epsilon");
        alpha = par("alpha");
        gamma = par("gamma");

        qTable.resize(numStates, std::vector<double>(numActions, 0.0));
        currentState = 0;
        lastAction = -1;
    }

    virtual void handleMessage(cMessage *msg) override {
        if (msg->isSelfMessage()) {
            handleTaskCompletion(msg);
        } else {
            handleNewTask(msg);
        }
    }

private:
    void handleNewTask(cMessage *task) {
        int nextState = getState();
        int action = chooseAction(nextState);

        // Assign task to the chosen server
        assignTaskToServer(action, task);

        // Perform SARSA update
        if (lastAction != -1) {
            double reward = getReward(action);
            qTable[currentState][lastAction] +=
                alpha * (reward + gamma * qTable[nextState][action] - qTable[currentState][lastAction]);
        }

        currentState = nextState;
        lastAction = action;
    }

    int chooseAction(int state) {
        if (uniform(0, 1) < epsilon) {
            return uniform(0, numActions - 1); // Explore
        } else {
            return std::distance(qTable[state].begin(),
                                 std::max_element(qTable[state].begin(), qTable[state].end())); // Exploit
        }
    }

    void assignTaskToServer(int action, cMessage *task) {
        if (action < numMECDevices) {
            EV << "Task Should be assigned to MEC :)";
            send(task, "out", action); // Assign to MEC server
        } else {
            EV << "Task Should be assigned to Core Server :)";
            int serverIndex = action - numMECDevices; // Calculate core server index
            send(task, "coreOut", serverIndex);       // Assign to core server
        }
    }

    int getState() {
        // Example state logic: task queue size (discretized)
        return uniform(0, numStates - 1); // Simplified for demo
    }

    double getReward(int action) {
        // Example reward logic: incentivize lightly loaded servers
        if (action < numMECDevices) {
            return 1.0; // Reward for MEC servers
        } else {
            return 2.0; // Higher reward for core servers
        }
    }

    void handleTaskCompletion(cMessage *msg) {
        EV << "Task completed. Acknowledged by SDN Controller.\n";
        delete msg;
    }
};

Define_Module(SDNController);
