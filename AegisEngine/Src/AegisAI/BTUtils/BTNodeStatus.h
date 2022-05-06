#pragma once

enum BTNodeStatus{
    None,   //doesn't even been executed
    Failure, // failed their objective
    Running, // is on progress to be completed
    Success  // is completed 
};