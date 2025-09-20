#include <iostream>
#include <string>

// Network metrics simulation
struct NetworkState {
    bool wifiAvailable;
    int cellularSignalStrength; // 0 to 100
    bool isRoaming;
    float dataCostPerMB;
    bool downloadQueued;
};

// Simulated decision engine
std::string decideConnectivity(const NetworkState& state) {
    if (state.wifiAvailable) {
        return "Use Wi-Fi";
    }
    if (state.cellularSignalStrength > 70 && !state.isRoaming && state.dataCostPerMB < 0.05f) {
        return "Use Cellular Data";
    }
    if (state.downloadQueued) {
        return "Postpone Download";
    }
    return "No Suitable Network";
}

int main() {
    NetworkState currentState = {
        false,    // wifiAvailable
        85,       // cellularSignalStrength
        false,    // isRoaming
        0.02f,    // dataCostPerMB
        true      // downloadQueued
    };

    std::string decision = decideConnectivity(currentState);
    std::cout << "Connectivity Decision: " << decision << std::endl;

    return 0;
}
