///*
// * File:   main.c
// * Author: Aaron Hunter
// * Brief:  Minimal application to test MAVLink communication with QGC 
// * project
// * Created on January 27, 2021 at 2:00 pm
// */
//
///*******************************************************************************
// * #INCLUDES                                                                   *
// ******************************************************************************/
//#include <stdio.h>
//#include <stdint.h>
//#include <stdlib.h>
//#include <math.h>
//#include "xc.h"
//#include "Board.h"
//#include <SerialM32.h>
//#include "System_timer.h"
//#include "NEO_M8N.h"
//
//
//
///*******************************************************************************
// * #DEFINES                                                                    *
// ******************************************************************************/
//#define GPS_PERIOD 100 //10 Hz update rate
//#define KNOTS_TO_MPS 0.5144444444 //1 meter/second is equal to 1.9438444924406 knots
//
//
///*******************************************************************************
// * VARIABLES                                                                   *
// ******************************************************************************/
//static struct GPS_data GPS_data;
//static uint8_t pub_GPS = TRUE;
//
//static float knots_to_mps = KNOTS_TO_MPS;
///*******************************************************************************
// * TYPEDEFS                                                                    *
// ******************************************************************************/
//
//
///*******************************************************************************
// * FUNCTION PROTOTYPES                                                         *
// ******************************************************************************/
///**
// * @function check_GPS_events(void)
// * @param none
// * @brief checks for GPS messages, parses, and stores data in module gps variable
// * @author aaron hunter
// */
//void check_GPS_events(void);
//
///**
// * @function publish_GPS(void)
// * @param none
// * @brief invokes mavlink helper function to generate GPS message and sends to
// * radio serial port
// * @author aaron hunter
// */
//void publish_GPS(void);
//
//
///**
// * @function check_GPS_events(void)
// * @param none
// * @brief checks for GPS messages, parses, and stores data in module gps variable
// * @author Aaron Hunter
// */
//void check_GPS_events(void) {
//    if (GPS_is_msg_avail() == TRUE) {
//        GPS_parse_stream();
//    }
//    if (GPS_is_data_avail() == TRUE) {
//        GPS_get_data(&GPS_data);
//    }
//}
//
///**
// * @function publish_GPS(void)
// * @param none
// * @brief invokes mavlink helper function to generate GPS message and sends to
// * radio serial port
// * @author Aaron Hunter
// */
//void publish_GPS(void) {
//    printf("Lat: %d Lon: %d Spd: %d Cog: %d\r", 
//            (int32_t) (GPS_data.lat * 10000000.0),
//            (int32_t) (GPS_data.lon * 10000000.0),
//            (uint16_t) (GPS_data.spd * knots_to_mps * 100.0),
//            (uint16_t) (GPS_data.cog * 100.0));
//
//}
//
//
//int main(void) {
//    uint32_t cur_time = 0;
//    uint32_t warmup_time = 250; //time in ms to allow subsystems to stabilize (IMU))
//    uint32_t gps_start_time = 0;
//
//    //Initialization routines
//    Board_init(); //board configuration
//    Serial_init(); //start debug terminal (USB)
//    Sys_timer_init(); //start the system timer
//    /*small delay to get all the subsystems time to get online*/
//    while (cur_time < warmup_time) {
//        cur_time = Sys_timer_get_msec();
//    }
//    GPS_init();
//
//    printf("\r\nGPS Test Harness %s, %s \r\n", __DATE__, __TIME__);
//
//    while (1) {
//        cur_time = Sys_timer_get_msec();
//        //check for all events
//        check_GPS_events(); //check and process incoming GPS messages
//
//        //publish GPS
//        if (cur_time - gps_start_time > GPS_PERIOD) {
//            gps_start_time = cur_time; //reset GPS timer
//            if (pub_GPS == TRUE) {
//                publish_GPS();
//            }
//        }
//
//    }
//    return 0;
//}