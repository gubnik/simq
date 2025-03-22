#pragma once

namespace simq
{

enum class State
{
    Generate,
    Queue,
    Enter,
    Advance,
    Leave,
    Terminate,
    _SIZE
};

}
