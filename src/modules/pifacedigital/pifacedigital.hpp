#pragma once

#include <zmqpp/socket.hpp>
#include "modules/moduleconfig.h"
#include <boost/property_tree/ptree.hpp>
#include <zmqpp/reactor.hpp>

/**
* This is a implementation class. It's not exposed to the user and is for this
* module internal code only.
*
* It abstract a GPIO pin driven by the PifaceDigital card..
*/
struct PFGpioPin
    {
    PFGpioPin(zmqpp::context &ctx, const std::string &name, int gpio_no);
    ~PFGpioPin();

    PFGpioPin(const PFGpioPin &) = delete;
    PFGpioPin &operator=(const PFGpioPin &) = delete;

    PFGpioPin(PFGpioPin &&o);
    PFGpioPin &operator=(PFGpioPin &&o);

    /**
    * Write to PFDigital to turn the gpio on.
    */
    bool turn_on();

    /**
    * Write to PFDigital turn the gpio off.
    */
    bool turn_off();

    bool toggle();

    /**
    * The PFGpioModule will register this method so its called when a message
    * is ready on the pin socket.
    */
    void handle_message();

    int gpio_no_;

    /**
    * listen to command from other component.
    */
    zmqpp::socket sock_;

    /**
    * PUSH socket to write to the bus.
    */
    zmqpp::socket bus_push_;

    std::string name_;

    };

/**
* Handle GPIO management over sysfs.
*/
class PFGpioModule
    {
public:
    PFGpioModule(const boost::property_tree::ptree &config,
            zmqpp::socket *module_manager_pipe,
            zmqpp::context &ctx
    );

    /**
    * Module's main loop.
    */
    void run();

private:
    zmqpp::socket &pipe_;
    boost::property_tree::ptree config_;

    zmqpp::reactor reactor_;

    bool is_running_;

    /**
    * Handle message coming from the pipe.
    * This is basically handle the stop signal from the module manager.
    */
    void handle_pipe();

    /**
    * An interrupt was triggered. Lets handle it.
    */
    void handle_interrupt();

    /**
    * Process the configuration, preparing configured GPIO pin.
    */
    void process_config(const boost::property_tree::ptree &cfg);

    zmqpp::context &ctx_;

    /**
    * Socket to push event to the bus.
    */
    zmqpp::socket bus_push_;

    /**
    * PFDigital provide a fixed number of GPIO, so we use fixed length array to store them all.
    * 0-7 are INPUT. 8-15 are OUTPUT.
    */
    std::vector<PFGpioPin> gpios_;


    /**
    * File descriptor of the PIN that triggers interrupts. This is card and will not change.
    */
    int interrupt_fd_;

    bool first_;
    };
