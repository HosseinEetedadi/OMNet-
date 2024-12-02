#include <omnetpp.h>
#include <iostream> // for logging to console
#include <algorithm> // for std::max_element
#include <ctime> // for random seeding
#include <cstdlib> // for random
#include <vector>

using namespace omnetpp;
using namespace std;

class SDNController : public cSimpleModule {

private:
    // SARSA Parameters
    double alpha = 0.1;
    double gamma = 0.9;
    double epsilon = 0.1;

    // Q-table
    vector<vector<double>> Q;

    // load tracking
    vector<int> serverLoad;

    // initialize Q-table
    void initializeQTable(int numStates, int numActions){
        Q.resize(numStates);
        for(int i=0; i<numStates; i++){
            Q[i].resize(numActions, 0);
        }
    }

    //Function to choose action based on epsilon-greedy policy
    int chooseAction(int state){
        if((rand() / (RAND_MAX + 1.0)) < epsilon){
            // Exploration: Random Action
            return rand() % Q[state].size();
        }else{
            //Exploitation: Choose the best action
            int bestAction = 0;
            double maxQ = Q[state][0];
            for(int i = 1; i < Q[state].size(); i++){
                if(Q[state][i] > maxQ){
                    maxQ = Q[state][i];
                    bestAction = i;
                }
            }
            return bestAction;
        }
    }

    void updateQTableSARSA(int state, int action, double reward, int nextState, int nextAction){
        Q[state][action] = Q[state][action] + alpha * (reward + gamma * Q[nextState][nextAction] - Q[state][action]);

    }

    void sendTaskToServer(int action){
        serverLoad[action] +=1;
        EV << "Task routed to server/drone "<< action << ", updated load: "<< serverLoad[action] << "\n";

    }
    double computeReward(int action){
        int load = serverLoad[action];
        if (load <= 5 ){
            return 10 - load;
        }else{
            return -1.0 * (load -5);

        }
    }
protected:
    virtual void initialize() override{
        srand(time(0));
        int numStates = 10;
        int numActions = 8;

        initializeQTable(numStates, numActions);
        serverLoad.resize(numActions, 0);
    }

    virtual void handleMessage(cMessage *msg) override {
        int state = rand() % 10;

        int action = chooseAction(state);

        EV << "SDNController choose action: "<< action << "for state: " << state << "\n";

        sendTaskToServer(action);

        double reward = computeReward(action);

        EV << "Reward for action " << action << ": " << reward << "\n";

        int nextState = rand() % 10;

        int nextAction = chooseAction(nextState);

        updateQTableSARSA(state, action, reward, nextState, nextAction);

        EV << " Next state: " << nextState << ", Next action: " << nextAction << "\n";
    }
};

Define_Module(SDNController)
