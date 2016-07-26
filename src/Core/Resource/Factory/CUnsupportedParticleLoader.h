#ifndef CUNSUPPORTEDPARTICLELOADER_H
#define CUNSUPPORTEDPARTICLELOADER_H

#include "Core/Resource/CDependencyGroup.h"
#include "Core/Resource/ParticleParameters.h"

// This class is responsible for loading particle formats that aren't yet fully supported.
// Used for finding dependencies. Split from CUnsupportedFormatLoader for being too big.
class CUnsupportedParticleLoader
{
    CDependencyGroup *mpGroup;
    CUnsupportedParticleLoader() {}

    // Format-Specific Parameter Loading
    bool ParseParticleParameter(IInputStream& rPART);
    bool ParseElectricParameter(IInputStream& rELSC);
    bool ParseSwooshParameter(IInputStream& rSWHC);
    bool ParseDecalParameter(IInputStream& rDPSC);
    bool ParseWeaponParameter(IInputStream& rWPSC);
    bool ParseCollisionResponseParameter(IInputStream& rCRSC);

    // Function Loading
    void ParseBoolFunction(IInputStream& rFile);
    void ParseIntFunction(IInputStream& rFile);
    void ParseFloatFunction(IInputStream& rFile);
    void ParseVectorFunction(IInputStream& rFile);
    void ParseModVectorFunction(IInputStream& rFile);
    void ParseColorFunction(IInputStream& rFile);
    void ParseUVFunction(IInputStream& rFile);
    void ParseEmitterFunction(IInputStream& rFile);
    void ParseAssetFunction(IInputStream& rFile);
    void ParseSpawnSystemKeyframeData(IInputStream& rFile);
    void ParseKeyframeEmitterData(IInputStream& rFile, u32 ElemSize);

public:
    static CDependencyGroup* LoadParticle(IInputStream& rPART, CResourceEntry *pEntry);
};

#endif // CUNSUPPORTEDPARTICLELOADER_H
