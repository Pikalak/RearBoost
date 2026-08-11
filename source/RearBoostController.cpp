#include "RearBoost.h"

namespace Steinberg {
namespace Vst {

FUnknown* RearBoostController::createInstance(void*)
{
    return static_cast<IEditController*>(
        new RearBoostController()
    );
}

tresult PLUGIN_API RearBoostController::initialize(
    FUnknown* context)
{
    tresult result =
        EditController::initialize(context);

    if (result != kResultOk)
        return result;

    // Rear Boost: 0.0 dB to +12.0 dB
    parameters.addParameter(
        STR16("Rear Boost"),
        STR16("dB"),
        0,
        0.0,
        ParameterInfo::kCanAutomate,
        kRearGain
    );

    return kResultOk;
}

}
}
