#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"
#include "public.sdk/source/vst/vsteditcontroller.h"

namespace Steinberg {
namespace Vst {

static const FUID kRearBoostProcessorUID(
    0xA7B3C901, 0x11D24E55, 0x8A93B710, 0x6F21CC42);

static const FUID kRearBoostControllerUID(
    0xB8C4D012, 0x22E35F66, 0x9BA4C821, 0x7032DD53);

enum Parameters
{
    kRearGain = 0
};

class RearBoostProcessor : public AudioEffect
{
public:
    RearBoostProcessor();

    static FUnknown* createInstance(void*);

    tresult PLUGIN_API initialize(FUnknown*) SMTG_OVERRIDE;

    tresult PLUGIN_API setBusArrangements(
        SpeakerArrangement* inputs,
        int32 numIns,
        SpeakerArrangement* outputs,
        int32 numOuts) SMTG_OVERRIDE;

    tresult PLUGIN_API process(
        ProcessData&) SMTG_OVERRIDE;
};

class RearBoostController : public EditController
{
public:
    static FUnknown* createInstance(void*);

    tresult PLUGIN_API initialize(
        FUnknown*) SMTG_OVERRIDE;
};

}
}
