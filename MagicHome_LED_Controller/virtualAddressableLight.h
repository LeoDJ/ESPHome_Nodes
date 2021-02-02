#include "esphome.h"

class VirtualAddressableLight : /*public Component,*/ public AddressableLight {
 protected:
    light::LightState *_outputLight;
    uint8_t effect_data_;
    uint8_t r, g, b;
 public:
    /*void setup() override {
        // This will be called by App.setup()
        // pinMode(5, INPUT);
    }*/

    VirtualAddressableLight(light::LightState *output) {
        _outputLight = output;
    }

    inline int32_t size() const override {
        return 1;
    }

    void clear_effect_data() override {
        // // from fastled_light.h
        // for (int i = 0; i < this->size(); i++)
        //     this->effect_data_[i] = 0;
        effect_data_ = 0;
    }

    light::ESPColorView get_view_internal(int32_t index) const override {
        return {(uint8_t*)&this->r, (uint8_t*)&g, (uint8_t*)&b, nullptr, (uint8_t*)&this->effect_data_, &this->correction_};
    }


    LightTraits get_traits() override {
        // return the traits this light supports
        auto traits = LightTraits();
        traits.set_supports_brightness(true);
        traits.set_supports_rgb(true);
        return traits;
    }

    void write_state(LightState *state) override {
        // This will be called by the light to get a new state to be written.
        float red, green, blue;
        // use any of the provided current_values methods
        state->current_values_as_rgb(&red, &green, &blue);
        // Write red, green and blue to HW
        // ...
        auto call = _outputLight->turn_on();
        call.set_transition_length(0);
        call.set_rgb(red, green, blue);
        call.set_publish(false);
        call.perform();
    }

    void loop() override {
        if(this->should_show_()) {
            this->mark_shown_();
            auto call = _outputLight->turn_on();
            call.set_transition_length(1);
            call.set_rgb(r / 255.0, g / 255.0, b / 255.0);
            call.set_publish(false);
            call.perform();
        }
    }

};