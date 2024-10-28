#pragma once
#include "gdb-server/GdbServer.hpp"
#include "gdb-server/Utils.hpp"

#include "gdb-server/SimulationControlInterface.hpp"
#include <thread>
#include <chrono>

class SimControl : public SimulationControlInterface {
public:

  SimControl()
    : _serverRunning(false),
      _stopServer(false),
      _stalled(true)
  {}

    void runSimulation() {
        while (!shouldStopServer()) {
            if (!isStalled()) {
                // Simulate some processing
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                std::cout << "Simulating a running process..." << std::endl;
            }
        }
        std::cout << "Simulation stopped." << std::endl;
    }

  void setServerRunning(bool running) { _serverRunning = running; }
  bool isServerRunning() override { return _serverRunning; }

  void stopServer()              override { _stopServer = true; }
  void setStopServer(bool stop)  { _stopServer = stop; }
  bool shouldStopServer()  override { return _stopServer; }

  void stall()              { _stalled = true;  }
  void unstall()            { _stalled = false; }
  bool isStalled() override { return _stalled;  }

  void kill() override {
      std::cout << "Simulation killed.\n";
  }

  void reset() override {
      std::cout << "Simulation reset.\n";
  }

  void step() override {
      std::cout << "Single step executed.\n";
  }

  void insertBreakpoint(unsigned addr) override {
      std::cout << "Breakpoint inserted at address: " << addr << "\n";
  }

  void removeBreakpoint(unsigned addr) override {
      std::cout << "Breakpoint removed from address: " << addr << "\n";
  }

  uint32_t readReg(std::size_t num) override {
      std::cout << "Reading register " << num << "\n";
      return 0;  // Return a mock value
  }

  void writeReg(std::size_t num, uint32_t value) override {
      std::cout << "Writing value " << value << " to register " << num << "\n";
  }

  bool readMem(uint8_t *out, unsigned addr, std::size_t len) override {
      std::cout << "Reading " << len << " bytes from address " << addr << "\n";
      return true;  // Return a mock success
  }

  bool writeMem(uint8_t *src, unsigned addr, std::size_t len) override {
      std::cout << "Writing " << len << " bytes to address " << addr << "\n";
      return true;  // Return a mock success
  }

  uint32_t pcRegNum() override {
      return 15;  // Mock program counter register number
  }

  uint32_t nRegs() override {
      return 32;  // Mock number of registers
  }

  uint32_t wordSize() override {
      return 4;  // Assume 4-byte word size for this example
  }

//  void stopServer() override {
//      std::cout << "Server stopped.\n";
//  }

//  bool shouldStopServer() override {
//      return false;  // Return a mock value
//  }

//  bool isServerRunning() override {
//      return true;  // Return mock running status
//  }

//  void setServerRunning(bool status) override {
//      std::cout << "Server running status set to " << status << "\n";
//  }

  uint32_t htotl(uint32_t hostVal) override {
      return hostVal;  // Mock implementation; no endianness change
  }

  uint32_t ttohl(uint32_t targetVal) override {
      return targetVal;  // Mock implementation; no endianness change
  }

    bool _serverRunning;
    bool _stopServer;
    bool _stalled;
};
