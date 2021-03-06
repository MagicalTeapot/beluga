#pragma once
#include <cmath>
#include <functional>

namespace blga {

struct note
{
    std::size_t channel;
    int         key;
    double      toggle_time; // Time it was last toggle on or off
    bool        active;
};

using oscillator = std::function<double(double, double)>;

struct envelope
{
    double attack_time;
    double decay_time;
    double release_time;

    double start_amplitude;
    double sustain_amplitude;
};

struct instrument
{
    blga::envelope   envelope;
    blga::oscillator oscillator;
};

auto amplitude(
    const blga::note& note, const blga::instrument& instrument, double time
) -> double;

}