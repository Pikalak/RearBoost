#include "RearBoost.h"
#include <cmath>

#include "pluginterfaces/vst/ivstparameterchanges.h"

namespace Steinberg {
namespace Vst {

RearBoostProcessor::RearBoostProcessor()
{
    setControllerClass(kRearBoostControllerUID);
}

FUnknown* RearBoostProcessor::createInstance(void*)
{
    return static_cast<IAudioProcessor*>(new RearBoostProcessor());
}

tresult PLUGIN_API RearBoostProcessor::initialize(FUnknown* context)
{
    tresult result = AudioEffect::initialize(context);

    if (result != kResultOk)
        return result;

    addAudioInput(
        STR16("7.1 Input"),
        SpeakerArr::k71
    );

    addAudioOutput(
        STR16("7.1 Output"),
        SpeakerArr::k71
    );

    return kResultOk;
}

tresult PLUGIN_API RearBoostProcessor::setBusArrangements(
    SpeakerArrangement* inputs,
    int32 numIns,
    SpeakerArrangement* outputs,
    int32 numOuts)
{
    if (numIns == 1 &&
        numOuts == 1 &&
        inputs[0] == SpeakerArr::k71 &&
        outputs[0] == SpeakerArr::k71)
    {
        return AudioEffect::setBusArrangements(
            inputs,
            numIns,
            outputs,
            numOuts
        );
    }

    return kResultFalse;
}

tresult PLUGIN_API RearBoostProcessor::process(ProcessData& data)
{
    if (data.numInputs == 0 ||
        data.numOutputs == 0 ||
        data.inputs[0].channelBuffers32 == nullptr ||
        data.outputs[0].channelBuffers32 == nullptr)
    {
        return kResultOk;
    }

    double rearBoostDb = 0.0;

    if (data.inputParameterChanges)
    {
        IParamValueQueue* queue =
            data.inputParameterChanges->getParameterData(kRearGain);

        if (queue && queue->getPointCount() > 0)
        {
            int32 sampleOffset = 0;
            ParamValue value = 0.0;

            if (queue->getPoint(
                    queue->getPointCount() - 1,
                    sampleOffset,
                    value) == kResultOk)
            {
                rearBoostDb = value;
            }
        }
    }

    const float rearGain =
        static_cast<float>(
            std::pow(10.0, rearBoostDb / 20.0)
        );

    float** input =
        data.inputs[0].channelBuffers32;

    float** output =
        data.outputs[0].channelBuffers32;

    for (int32 sample = 0;
         sample < data.numSamples;
         ++sample)
    {
        // FL
        output[0][sample] = input[0][sample];

        // FR
        output[1][sample] = input[1][sample];

        // Center
        output[2][sample] = input[2][sample];

        // LFE
        output[3][sample] = input[3][sample];

        // Rear Left - BOOST
        output[4][sample] =
            input[4][sample] * rearGain;

        // Rear Right - BOOST
        output[5][sample] =
            input[5][sample] * rearGain;

        // Side Left
        output[6][sample] = input[6][sample];

        // Side Right
        output[7][sample] = input[7][sample];
    }

    return kResultOk;
}

}
}
