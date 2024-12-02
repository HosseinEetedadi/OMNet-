//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <omnetpp.h>

using namespace omnetpp;

class MECServer : public cSimpleModule {
private:
    double processingCapacity;
    double currentLoad;

protected:
    virtual void initialize() override {
        processingCapacity = par("processingCapacity");
        currentLoad = 0.0;
        WATCH(currentLoad);
    }

    virtual void handleMessage(cMessage *msg) override {
        // Handle task processing
        if (strcmp(msg->getName(), "task") == 0) {
            if (currentLoad < processingCapacity) {
                // Process task
                scheduleAt(simTime() + 1.0, msg);
                currentLoad += 1.0;
            } else {
                // Forward to SDNController
                send(msg, "out");
            }
        } else if (msg->isSelfMessage()) {
            // Task completed
            currentLoad -= 1.0;
            delete msg;
        }
    }
};

Define_Module(MECServer);

