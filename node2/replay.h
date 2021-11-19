/**
 * @file replay.h
 * @date 2021-11-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "em.h"
/**
 * @brief This function simply resets the log which contains 
 * all information about the previous game.
 * 
 */
void replay_reset_log();
/**
 * @brief This function take an event, parses it with a timestamp and adds it to the log array.
 * 
 * @param event Could be any event.
 */
void replay_log_event(EmEvent event);
/**
 * @brief This function starts the replay. 
 * It blocks everything else when in action.
 * 
 */
void replay_run();