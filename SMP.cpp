/*
 * SMP.cpp
 *
 *  Created on: Dec 21, 2018
 *      Author: yunfang
 */

#include "SMP.h"

#include <thread>

int SMP::get_num_cpus() {
    return std::thread::hardware_concurrency();
}
