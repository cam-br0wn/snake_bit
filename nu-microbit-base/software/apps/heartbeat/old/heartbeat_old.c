#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>

#include "nrf.h"
#include "nrf_delay.h"
#include "app_timer.h"
#include "nrfx_saadc.h"
#include "microbit_v2.h"

// analog input
#define HEARTBEAT_SENSE_IN NRF_SAADC_INPUT_AIN1

// ADC channel configurations
#define ADC_HEARTBEAT_CHANNEL 0 //what pin is it on
#define ADC_MAX_COUNTS (16384)

// Timer configuration
#define TIMER_TICKS (16000000/SAMPLING_FREQUENCY)

// sample data config
#define SAMPLING_FREQUENCY 16 // sampling frequency in hz. Fastest heartbeat of 300 bpm = 5hz. Nyquist frequency = 10hz
#define BUFFER_SIZE 2*SAMPLING_FREQUENCY // buffer size is 2 seconds worth of data * sample rate.

uint16_t samples[BUFFER_SIZE] = {0}; // buffer to store the ADC samples
int index = 0; // index of buffer to put the next sample.
APP_TIMER_DEF(sample_timer); // define an app timer

static void saadc_event_callback(nrfx_saadc_evt_t const* event) {
    if (event->type == NRFX_SAADC_EVT_DONE) {
        // adjust the data here before returning
        // Warning: don't try to print all the ADC samples without adding an nRF
        //  delay every few samples. It really messes up the system. Something
        //  definitely breaks and it needs to be re-programmed to start again
        // determine the average of the samples
        uint32_t average = 0;
        for (int i=0; i<BUFFER_SIZE; i++) {
            average += (uint16_t)samples[i];
        }
        average = average/BUFFER_SIZE;
    }
}

static void adc_init(){
    // initialize the SAADC
    nrfx_saadc_config_t saadc_config = {
            .resolution = NRF_SAADC_RESOLUTION_14BIT,
            .oversample = NRF_SAADC_OVERSAMPLE_DISABLED,
            .interrupt_priority = 1, // higher than whatever hardware timers are put in the project.
            .low_power_mode = false,
    };
    nrfx_saadc_init(&saadc_config, saadc_event_callback);

    // initialize the adc channel
    // a small signal we're sampling slowly, so max out the gain. We don't really care about acquisition time though.
    nrf_saadc_channel_config_t heartbeat_channel_config = NRFX_SAADC_DEFAULT_CHANNEL_CONFIG_SE(HEARTBEAT_SENSE_IN);
    heartbeat_channel_config.gain = NRF_SAADC_GAIN4;
    heartbeat_channel_config.acq_time = NRF_SAADC_ACQTIME_10US;
    nrfx_saadc_init(ADC_HEARTBEAT_CHANNEL, &heartbeat__channel_config);

}

static void sample_sensor(void* _unused){
    // collect an ADC sample and store it in the buffer every time the app timer is triggered.
    nrfx_saadc_sample();
}

int main(){
    printf("startup"); // tell me that you're alive please.
    // initialize app timer
    app_timer_init();
    app_timer_create(&sample_timer, APP_TIMER_MODE_REPEATED, sample_sensor);
}