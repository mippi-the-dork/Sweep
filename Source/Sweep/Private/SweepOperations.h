// Copyright Mippithedork 2026, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class UK2Node_VariableGet;

namespace SweepOperations
{
    bool IsSupportedVariableGet(UK2Node_VariableGet* VariableGet);

    bool CanSweep(UK2Node_VariableGet* VariableGet);
    bool Sweep(UK2Node_VariableGet* VariableGet);
    bool SweepMany(const TArray<UK2Node_VariableGet*>& VariableGets);

    bool CanConsolidate(
        const TArray<UK2Node_VariableGet*>& VariableGets,
        UK2Node_VariableGet* AnchorVariableGet);

    bool ConsolidateMany(
        const TArray<UK2Node_VariableGet*>& VariableGets,
        UK2Node_VariableGet* AnchorVariableGet);
}
