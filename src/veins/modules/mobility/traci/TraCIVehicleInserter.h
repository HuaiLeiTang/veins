//
// Copyright (C) 2006-2018 Christoph Sommer <sommer@ccs-labs.org>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#pragma once

#include <queue>

#include <omnetpp.h>

#include "veins/base/utils/MiXiMDefs.h"

namespace Veins {

class TraCIScenarioManager;

/**
 * @brief
 * Uses the TraCIScenarioManager to programmatically insert new vehicles at the TraCI server.
 *
 * This is done whenever the total number of active vehicles drops below a given number.
 *
 * See the Veins website <a href="http://veins.car2x.org/"> for a tutorial, documentation, and publications </a>.
 *
 * @author Christoph Sommer, David Eckhoff, Falko Dressler, Zheng Yao, Tobias Mayer, Alvaro Torres Cortes, Luca Bedogni
 *
 * @see TraCIScenarioManager
 *
 */
class TraCIVehicleInserter : public cSimpleModule, public cListener {
public:
    TraCIVehicleInserter();
    ~TraCIVehicleInserter();
    virtual int numInitStages() const override;
    virtual void initialize(int stage) override;
    virtual void finish() override;
    virtual void finish(cComponent* component, simsignal_t signalID) override;
    virtual void handleMessage(cMessage* msg) override;
    virtual void receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details) override;
    virtual void receiveSignal(cComponent* source, simsignal_t signalID, const SimTime& t, cObject* details) override;

protected:
    /**
     * adds a new vehicle to the queue which are tried to be inserted at the next SUMO time step;
     */
    void insertNewVehicle();

    /**
     * tries to add all vehicles in the vehicle queue to SUMO;
     */
    void insertVehicles();

    // signals
    const omnetpp::simsignal_t traciModuleAddedSignal;
    const omnetpp::simsignal_t traciTimestepBeginSignal;

    // parameters
    int vehicleRngIndex;
    int numVehicles;

    // internal
    TraCIScenarioManager* manager;
    cRNG* mobRng;
    std::map<int, std::queue<std::string>> vehicleInsertQueue;
    std::set<std::string> queuedVehicles;
    std::vector<std::string> routeIds;
    uint32_t vehicleNameCounter;
    std::vector<std::string> vehicleTypeIds;
};

} // namespace Veins