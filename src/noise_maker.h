#pragma once
#include "constants.h"
#include "audio_buffer.h"
#include "components.h"

#include <atomic>
#include <functional>
#include <semaphore>
#include <thread>
#include <mutex>

namespace blga {

class noise_maker
{
    // Fix the race condition in accessing this (mostly will go when we switch to
    // using notes)
    std::mutex d_instrument_mtx;
    std::unordered_map<std::size_t, blga::instrument> d_channels;
    std::vector<blga::note> d_notes;

	blga::audio_buffer<blga::num_blocks, blga::samples_per_block> d_audio_buffer;

	std::jthread d_thread;
	std::atomic<bool> d_ready;
    std::atomic<double> d_time;

	std::counting_semaphore<num_blocks> d_semaphore;

public:
	noise_maker();
    ~noise_maker();

    auto add_channel(std::size_t channel, const blga::instrument& instrument) -> void;

    auto note_on(int key) -> void;
    auto note_off(int key) -> void;
};

}